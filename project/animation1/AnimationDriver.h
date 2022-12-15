#ifndef _ANIMATIONDRIVER_H
#define _ANIMATIONDRIVER_H


#include <DrawingWindow.h>
#include "../camera/Camera.h"
#include "../utils/LightingConfiguration.h"
#include "main_animation1.h"


class AnimationDriver {
public:
    explicit AnimationDriver(DrawingWindow &window);
    void begin();
private:
    uint32_t frameCounter{};
    DrawingWindow &window;
    void renderAndSaveFrame(Model &model);
};



#endif //_ANIMATIONDRIVER_H
