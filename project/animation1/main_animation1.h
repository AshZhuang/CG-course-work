#ifndef _MAIN_H
#define _MAIN_H
#include "../render/Renderer.h"

enum class ModelPreset {
    CornellBoxTextured,
    CornellBox,
    CornellBoxSoftShadow,
    CornellBoxMirror,
    Sphere,
    Hackspace,
};

struct Model {
    Model() = default;
    std::vector<ModelTriangle> triangleSet;
    Camera camera = Camera(glm::vec3(), 0);
    LightingConfiguration lighting;
    ConcreteRenderer renderer = ConcreteRenderer::Raytraced;
    float movementSensitivity = 1.0;
    explicit Model(ModelPreset config);
    void renderFrame(DrawingWindow &window, void(*eventHandler)(SDL_Event event, DrawingWindow &window, Model &m));
};


#endif //_MAIN_H
