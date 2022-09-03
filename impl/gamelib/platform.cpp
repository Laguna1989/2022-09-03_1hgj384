#include "platform.hpp"

Platform::Platform(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def,
    jt::Vector2f const& pos, jt::Vector2f const& size)
    : Box2DObject(world, def)
{
    m_size = size;

    b2FixtureDef fixtureDef;
    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(size.x / 2.0f, size.y / 2.0f);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);

    setPosition(pos);
}

void Platform::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(m_size, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
}

void Platform::doUpdate(float const elapsed)
{
    m_shape->setPosition(getPosition());
    m_shape->update(elapsed);
}
void Platform::doDraw() const { m_shape->draw(renderTarget()); }
