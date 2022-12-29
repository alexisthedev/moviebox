#include "sgg/graphics.h"
#include "app.h"
#include "defines.h"
#include <string>

void App::draw() {
    // loading screen
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

    if (m_state == STATE_INIT) {
        graphics::setFont(ASSET_PATH + std::string("MontserratMedium.ttf"));
        graphics::drawText(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 0.5f, "Loading assets...", br);
        m_state = STATE_LOADING;
        return;
    }

    // draw background
    SETCOLOR(br.fill_color, 0.18f, 0.23f, 0.29f);
    br.fill_opacity = 1.0f;
    graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    for (auto w : m_widgets) {
        w->draw();
    }
}

void App::update() {
    if (m_state == STATE_INIT) {
        return;
    }

    if (m_state == STATE_LOADING) {
        init();
        m_state = STATE_IDLE;
        return;
    }
}

void App::init() {
    Sidebar* s = new Sidebar();
    m_widgets.push_front((Widget*) s);
    s->setPosX(CANVAS_WIDTH/12.0f);
    s->setPosY(CANVAS_HEIGHT/2.0f);

    graphics::preloadBitmaps(ASSET_PATH);
}

App::~App() {
    for (auto w : m_widgets) {
        delete w;
    }
    m_widgets.clear();
}

App* App::getInstance() {
    if (!m_instance) m_instance = new App();
    return m_instance;
}

App* App::m_instance = nullptr;
