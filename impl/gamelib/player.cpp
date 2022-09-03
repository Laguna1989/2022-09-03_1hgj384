#include "player.hpp"
#include <game_interface.hpp>

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
}

void Player::doUpdate(float const elapsed)
{

    auto& input = getGame()->input();
    if (input.keyboard()->pressed(jt::KeyCode::D)) {
        getB2Body()->ApplyForceToCenter(b2Vec2 { 100.0f, 0.0f }, true);
    } else if (input.keyboard()->pressed(jt::KeyCode::A)) {
        getB2Body()->ApplyForceToCenter(b2Vec2 { -100.0f, 0.0f }, true);
    }

    m_shape->setPosition(getPosition());
    m_shape->update(elapsed);
}

void Player::doDraw() const { m_shape->draw(renderTarget()); }
