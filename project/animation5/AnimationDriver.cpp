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
    model = Model(ModelPreset::CornellBoxMirror);
    auto initialPos2 = model.camera.position;
    auto mirrorFrames = 150;
    for (int i = 0; i < mirrorFrames; i++) {
        model.camera.position = initialPos2;
        auto angle = 10 - (50.0f / (float) mirrorFrames * (float) i);
        model.camera.rotatePositionAboutY(angle);
        model.camera.lookAt(glm::vec3{0,0,0});
        renderAndSaveFrame(model);
    }

}

