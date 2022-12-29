#include "sgg/graphics.h"
#include "defines.h"
#include "app.h"

void draw() {
    App* myapp = App::getInstance();
    myapp->draw();
}

void update(float ms) {
    App* myapp = App::getInstance();
    myapp->update();
}

int main(int argc, char** argv) {
    graphics::createWindow(1400, 800, "MovieBox v0.1");
    graphics::setFullScreen(true);

    App* app = App::getInstance();

    graphics::setCanvasSize(28,16);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::startMessageLoop();

    App::releaseInstance();

    return 0;
}
