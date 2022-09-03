#include "game_properties.hpp"

jt::Palette GP::getPalette()
{
    static auto const p = jt::Palette::parseGPL(R"(GIMP Palette
#Palette Name: Juiciful-8
#Description: A nice palette i made up some times ago, it's colors reminds me of some tasty fruits :)
#Colors: 8
255	247	244	fff7f4
255	198	198	ffc6c6
255	130	130	ff8282
255	47	78	ff2f4e
198	10	95	c60a5f
130	10	95	820a5f
66	10	66	420a42
2	2	2	020202
)");
    return p;
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 16.0f, 16.0f }; }
