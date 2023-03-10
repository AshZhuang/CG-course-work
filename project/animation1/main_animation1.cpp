#include <DrawingWindow.h>
#include <glm/glm.hpp>
#include "CanvasTriangle.h"
#include "ObjFile.h"
#include "main_animation1.h"
#include "AnimationDriver.h"



#define WIDTH 640
#define HEIGHT 480

Model::Model(ModelPreset config) {
    switch (config) {
        case ModelPreset::Sphere:
            triangleSet = loadObj("sphere.obj", 1.0, Colour(255, 0, 0));
            camera = Camera(glm::vec3{0, 2, 6}, 800);
            camera.lookAt(glm::vec3(0, 1.5, 0));
            lighting = LightingConfiguration(glm::vec3 {0, 4, 6}, 200, 0.1, 32);
            lighting.shadingMode = ShadingMode::Phong;
            lighting.proximityWeighting = 50;
            lighting.specularWeighting = 30;
            lighting.angleOfIncidenceWeighting = 20;
            movementSensitivity = 3.0;
            break;
        case ModelPreset::Hackspace:
            triangleSet = loadObj("hackspace.obj", 1.0);
            camera = Camera(glm::vec3{0, 0, 600}, 600);
            camera.lookAt(glm::vec3{-250, 250, 0});
            renderer = ConcreteRenderer::Rasterised;
            movementSensitivity = 200;
            break;
        case ModelPreset::CornellBoxTextured:
            triangleSet = loadObj("textured-cornell-box.obj", 0.17f);
            camera = Camera(glm::vec3{0, 0, 4}, 1400);
            lighting = LightingConfiguration(glm::vec3 {0, 2, 0} * 0.17f, 4.0, 0.1, 16);
            renderer = ConcreteRenderer::Rasterised;
            break;
        case ModelPreset::CornellBox:
            triangleSet = loadObj("cornell-box.obj", 0.17f);
            camera = Camera(glm::vec3{0, 0, 4}, 1400);
            lighting = LightingConfiguration(glm::vec3 {0, 2, 0} * 0.17f, 4.0, 0.1, 16);
            break;
        case ModelPreset::CornellBoxSoftShadow:
            triangleSet = loadObj("cornell-box.obj", 0.17f);
            camera = Camera(glm::vec3{0, 0, 4}, 1400);
            lighting = LightingConfiguration(glm::vec3 {0, 2, 0} * 0.17f, 4.0, 0.1, 16);
            lighting.softShadow = true;
            lighting.lightRadius = 0.1;
            lighting.lightPoints = 100;
            lighting.ambientThreshold = 0.1;
            break;
        case ModelPreset::CornellBoxMirror:
            triangleSet = loadObj("cornell-box-mirror.obj", 0.17f);
            camera = Camera(glm::vec3{0, 0, 4}, 1400);
            lighting = LightingConfiguration(glm::vec3 {0, 2, 0} * 0.17f, 4.0, 0.1, 16);
            break;

        default:
            throw std::runtime_error("Invalid Model Preset");
    }
}

void Model::renderFrame(DrawingWindow &window, void(*eventHandler)(SDL_Event event, DrawingWindow &window, Model &m)) {
    SDL_Event event;
    if (window.pollForInputEvents(event) && eventHandler != nullptr) {
        eventHandler(event, window, (Model &) *this);
    };
    window.clearPixels();
    auto r = Renderer::getRenderer(renderer);
    r->draw(window, camera, triangleSet, lighting);
    window.renderFrame();
}

void keyboardHandler(SDL_Event event, DrawingWindow &window, Model &m) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
            m.camera.position[0] += (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
            m.camera.position[0] -= (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_UP) {
            m.camera.position[1] += (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_DOWN) {
            m.camera.position[1] -= (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_EQUALS) {
            m.camera.position[2] -= (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_MINUS) {
            m.camera.position[2] += (0.01f * m.movementSensitivity);
        } else if (event.key.keysym.sym == SDLK_o) {
            m.camera.rotatePositionAboutX(1);
        } else if (event.key.keysym.sym == SDLK_p) {
            m.camera.rotatePositionAboutX(-1);
        } else if (event.key.keysym.sym == SDLK_k) {
            m.camera.rotatePositionAboutY(1);
        } else if (event.key.keysym.sym == SDLK_l) {
            m.camera.rotatePositionAboutY(-1);
        } else if (event.key.keysym.sym == SDLK_a) {
            m.camera.rotateOrientationAboutY(-1);
        } else if (event.key.keysym.sym == SDLK_d) {
            m.camera.rotateOrientationAboutY(1);
        } else if (event.key.keysym.sym == SDLK_s) {
            m.camera.rotateOrientationAboutX(-1);
        } else if (event.key.keysym.sym == SDLK_w) {
            m.camera.rotateOrientationAboutX(1);
        } else if (event.key.keysym.sym == SDLK_1) {
            m.renderer = ConcreteRenderer::Wireframe;
        } else if (event.key.keysym.sym == SDLK_2) {
            m.renderer = ConcreteRenderer::Rasterised;
        } else if (event.key.keysym.sym == SDLK_3) {
            m.renderer = ConcreteRenderer::Raytraced;
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) window.savePPM("output.ppm");
}

int main(int argc, char *argv[]) {
    DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
    auto driver = AnimationDriver(window);
    driver.begin();

}
