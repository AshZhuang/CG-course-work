#ifndef _ANIMATIONDRIVER_H
#define _ANIMATIONDRIVER_H


#include <DrawingWindow.h>
#include "../camera/Camera.h"
#include "../utils/LightingConfiguration.h"
#include "main_animation5.h"

// A class to manage creating the frames for the video
// 10s at 60fps = need to save 600 frames
class AnimationDriver {
public:
    explicit AnimationDriver(DrawingWindow &window);
    void begin();
private:
    uint32_t frameCounter{};
    DrawingWindow &window;
    void renderAndSaveFrame(Model &model);
};



#endif 
