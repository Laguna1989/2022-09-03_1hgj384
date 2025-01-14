﻿#include "state_game.hpp"
#include "timer.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <random/random.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_menu.hpp>
#include <tweens/tween_alpha.hpp>

void StateGame::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 200.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_wind = std::make_shared<WindParticles>();
    add(m_wind);

    m_platforms = std::make_shared<jt::ObjectGroup<Platform>>();
    add(m_platforms);

    spawnPlatform(jt::Vector2f { 300.0f, GP::GetScreenSize().y - 50.0f },
        jt::Vector2f { GP::GetScreenSize().x, 20.0f });

    m_baseTimerForBlockSpawns1 = std::make_shared<jt::Timer>(1.8121412f, [this]() {
        spawnPlatform({ GP::GetScreenSize().x + 32,
                          jt::Random::getFloat(150, GP::GetScreenSize().y - 50.0f) },
            { 24, 48 });
    });
    add(m_baseTimerForBlockSpawns1);

    add(std::make_shared<jt::Timer>(2.722345f, [this]() {
        spawnPlatform({ GP::GetScreenSize().x + 32,
                          jt::Random::getFloat(150, GP::GetScreenSize().y - 50.0f) },
            { 48, 24 });
    }));

    createPlayer();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::spawnPlatform(jt::Vector2f const& pos, jt::Vector2f const& size)
{
    b2BodyDef def;
    def.type = b2_kinematicBody;
    auto p = std::make_shared<Platform>(m_world, &def, pos, size);

    //    if (m_platforms->size() != 0) {
    //        p->setVelocity({ -50, 0.0f });
    //    }
    add(p);
    m_platforms->push_back(p);
}

void StateGame::createPlayer()
{
    b2BodyDef def;
    def.type = b2BodyType::b2_dynamicBody;
    def.fixedRotation = true;
    m_player = std::make_shared<Player>(m_world, &def);
    add(m_player);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());

        auto const speed = m_player->getPosition().x / GP::GetScreenSize().x * 100.0f;
        m_hud->getObserverScoreP1()->notify(static_cast<int>(speed));

        m_wind->m_windSpeed = 0.1f + speed / 100.0f * 4.0f;

        if (speed > 100) {
            endGame(true);
        }
        if (speed < -1) {
            endGame(false);
        }

        auto const f = 0.3f + speed / 100.0f * 1.7f;

        for (auto i = 0U; i != m_platforms->size(); ++i) {
            auto p = m_platforms->at(i).lock();
            if (i == 0U) {
                p->m_flashTimer = 50000.0f;
                continue;
            }

            p->setVelocity(jt::Vector2f { -150.0f, 0.0f } * f);
        }

        if (m_player->getPosition().y >= 315 && m_lastPlayerY <= 315) {
            getGame()->gfx().camera().shake(0.5f, 9.0f);
        }

        m_lastPlayerY = m_player->getPosition().y;

        int const criticalHitX = 480;
        if (m_player->getPosition().x >= criticalHitX && m_lastPlayerX < criticalHitX) {
            spawnPlatform(jt::Vector2f { GP::GetScreenSize().x + 32, m_lastPlayerY }, { 48, 48 });
        }

        m_lastPlayerX = m_player->getPosition().x;
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame(bool win)
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchState(std::make_shared<StateMenu>());
}
std::string StateGame::getName() const { return "Game"; }
