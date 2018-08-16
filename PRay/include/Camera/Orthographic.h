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

    void zoom(float zm);
    float zoom() const;

private:
    float mZoom;
};

typedef std::shared_ptr<Orthographic> OrthographicPtr;

#endif //PRAY_ORTHOGRAPHIC_H
