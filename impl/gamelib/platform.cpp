#include "platform.hpp"
#include <game_properties.hpp>
#include <random/random.hpp>

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

    m_flashTimer = jt::Random::getFloat(0.2f, 1.75f);
}

void Platform::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(m_size, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_shape->setColor(GP::getPalette().getColor(7));
}

void Platform::doUpdate(float const elapsed)
{
    m_shape->setPosition(getPosition());
    m_shape->update(elapsed);

    if (m_shape->getPosition().x <= -100) {
        kill();
    }

    m_flashTimer -= elapsed;
    if (m_flashTimer <= 0) {
        if (jt::Random::getChance()) {
            m_shape->flash(0.25f, GP::getPalette().getColor(4));
        } else {
            m_shape->shake(0.25f, 10.0f);
        }

        m_flashTimer = jt::Random::getFloat(0.2f, 1.75f);
    }
}
void Platform::doDraw() const { m_shape->draw(renderTarget()); }
