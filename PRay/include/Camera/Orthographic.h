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
    Orthographic(const Orthographic& ortho);
    ~Orthographic() override;

    void render_scene(World& world) override;

    void set_zoom(float zm);
    float get_zoom() const;

private:
    float zoom;
};

#endif //PRAY_ORTHOGRAPHIC_H
