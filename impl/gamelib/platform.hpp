#ifndef INC_1HGJ384_PLATFORM_HPP
#define INC_1HGJ384_PLATFORM_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <shape.hpp>

class Platform : public jt::Box2DObject {
public:
    Platform(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def,
        jt::Vector2f const& pos, jt::Vector2f const& size);

private:
    std::shared_ptr<jt::Shape> m_shape;

    jt::Vector2f m_size;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // INC_1HGJ384_PLATFORM_HPP
