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
    model = Model(ModelPreset::CornellBoxSoftShadow);
    auto initialPos = model.camera.position;
    auto softShadowFrames = 150;
    for (int i = 0; i < softShadowFrames; i++) {
        auto progress = int((float) i / (float) softShadowFrames * 100.0f);
        std::cout << "\r" << progress << "%" << std::flush;
        model.camera.position = initialPos;
        auto angle = -30.0f + (60.0f / (float) softShadowFrames * (float) i);
        model.camera.rotatePositionAboutY(angle);
        model.camera.lookAt(glm::vec3{0,0,0});
        renderAndSaveFrame(model);
    }

}

