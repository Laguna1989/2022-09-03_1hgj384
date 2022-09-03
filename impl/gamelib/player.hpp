#ifndef INC_1HGJ384_PLAYER_HPP
#define INC_1HGJ384_PLAYER_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <shape.hpp>

class Player : public jt::Box2DObject {
public:
    Player(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def);

private:
    std::shared_ptr<jt::Shape> m_shape;

    float m_jumpTimer = 0.1f;
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // INC_1HGJ384_PLAYER_HPP
