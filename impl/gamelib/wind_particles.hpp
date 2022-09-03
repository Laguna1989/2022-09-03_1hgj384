#ifndef INC_1HGJ384_WIND_PARTICLES_HPP
#define INC_1HGJ384_WIND_PARTICLES_HPP

#include "game_object.hpp"
#include "shape.hpp"
class WindParticles : public jt::GameObject {

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;

public:
    float m_windSpeed { 1.0f };
};

#endif // INC_1HGJ384_WIND_PARTICLES_HPP
