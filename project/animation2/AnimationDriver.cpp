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

    model = Model(ModelPreset::Hackspace);
    auto hackspaceFrames = 120;
    for (int i = 0; i < hackspaceFrames; i++) {
        renderAndSaveFrame(model);
        model.camera.rotatePositionAboutY(180.0f / (float) hackspaceFrames);
        model.camera.lookAt(glm::vec3{-250, 250, 0});
    }

}

