//
// Created by Suraj on 17-05-2018.
//

#ifndef PRAY_ORTHOGRAPHIC_H
#define PRAY_ORTHOGRAPHIC_H

#include "Camera.h"

class Orthographic : public Camera
{
public:
    Orthographic();
    ~Orthographic() override;
//    Orthographic(const Orthographic& ortho);

    void render_scene(World& world) override;
};

#endif //PRAY_ORTHOGRAPHIC_H
