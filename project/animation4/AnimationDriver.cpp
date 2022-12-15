#include "AnimationDriver.h"

AnimationDriver::AnimationDriver(DrawingWindow &window): window(window) {
}

void AnimationDriver::renderAndSaveFrame(Model &model) {
    model.renderFrame(window, nullptr);
    auto fileName = "./animation/" + std::to_string(frameCounter) + ".ppm";
    window.savePPM(fileName);
    frameCounter++;
}

void AnimationDriver::begin() {
    Model model;
    model = Model(ModelPreset::Sphere);
    model.lighting.shadingMode = ShadingMode::None;
    auto sphereFrames = 120;
    for (int i = 0; i < sphereFrames; i++) {
        auto progress = int((float) i / (float) sphereFrames * 100.0f);
        std::cout << "\r" << progress << "%" << std::flush;
        if (i == round(sphereFrames / 3)) model.lighting.shadingMode = ShadingMode::Gouraud;
        if (i == round(2.0 *sphereFrames / 3)) model.lighting.shadingMode = ShadingMode::Phong;
        renderAndSaveFrame(model);
        model.camera.rotatePositionAboutY(0.05);
        model.camera.rotatePositionAboutX(-0.05);
        model.camera.lookAt(glm::vec3(0, 1.5, 0));
    }

}

