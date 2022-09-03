#include "player.hpp"
#include <game_interface.hpp>
#include <game_properties.hpp>

Player::Player(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : Box2DObject(world, def)
{
    b2FixtureDef fixtureDef;
    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(8, 24);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);

    setPosition(jt::Vector2f { 50.0f, 50.0f });
}

void Player::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(jt::Vector2f { 16, 48 }, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_shape->setColor(GP::getPalette().getColor(0));
}

void Player::doUpdate(float const elapsed)
{
    auto& input = getGame()->input();
    if (input.keyboard()->pressed(jt::KeyCode::D)) {
        getB2Body()->ApplyForceToCenter(b2Vec2 { 150.0f, 0.0f }, true);
    } else if (input.keyboard()->pressed(jt::KeyCode::A)) {
        getB2Body()->ApplyForceToCenter(b2Vec2 { -150.0f, 0.0f }, true);
    }

    m_jumpTimer -= elapsed;
    if (getPosition().y >= 315) {
        m_jumpTimer = 0.0f;
    }

    if (m_jumpTimer <= 0) {
        if (input.keyboard()->justPressed(jt::KeyCode::W)
            || input.keyboard()->justPressed(jt::KeyCode::Space)) {
            setVelocity(jt::Vector2f { 0.0f, -300.0f });
            m_jumpTimer = 3.0f;
        }
    }

    m_shape->setPosition(getPosition());
    m_shape->update(elapsed);

    auto v = getVelocity();
    v.x *= 0.99f;
    setVelocity(v);
}

void Player::doDraw() const { m_shape->draw(renderTarget()); }
