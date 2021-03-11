#pragma once


#include <lights/directionalLight.h>
#include "mesh.hpp"
class RenderSystem {
public:
    static void setup();
    static void render(const std::vector<scratch::Mesh> &renderQueue, scratch::DirectionalLight &directionalLight);
};