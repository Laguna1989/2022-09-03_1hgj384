
#include "wind_particles.hpp"
#include <game_properties.hpp>
#include <random/random.hpp>
#include <screeneffects/screen_wrap.hpp>

void WindParticles::doCreate()
{
    for (auto i = 0U; i != 100U; ++i) {
        auto s = std::make_shared<jt::Shape>();
        s->makeRect({ 8, 2 }, textureManager());
        s->setPosition(
            jt::Random::getRandomPointIn({ 0, 0, GP::GetScreenSize().x, GP::GetScreenSize().y }));
        s->setScreenSizeHint(GP::GetScreenSize());
        if (jt::Random::getChance()) {
            s->setColor(GP::getPalette().getColor(1));
        } else {
            s->setColor(GP::getPalette().getColor(6));
        }

        m_shapes.push_back(s);
    }
}
void WindParticles::doUpdate(float const elapsed)
{
    jt::Vector2f const windSpeed { -150.0f, 0.0f };
    for (auto& s : m_shapes) {
        auto p = s->getPosition();
        //        float const f =
        p += windSpeed * elapsed * m_windSpeed;
        s->setPosition(p);
        jt::wrapOnScreen(*s.get());
        s->update(elapsed);
    }
}
void WindParticles::doDraw() const
{
    for (auto const& s : m_shapes) {
        s->draw(renderTarget());
    }
}
