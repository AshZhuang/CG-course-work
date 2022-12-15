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
    model = Model(ModelPreset::CornellBoxTextured);
    auto texturedFrames = 120;
    for (int i = 0; i < texturedFrames; i++) {
        renderAndSaveFrame(model);
        model.camera.rotatePositionAboutX(90.0f / (float) texturedFrames);
        model.camera.lookAt(glm::vec3{0,0,0});
    }

}

