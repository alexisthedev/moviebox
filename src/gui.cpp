#include "app.h"
#include "defines.h"

/* Home Screen */

void HomeScreen::draw() {
    if (APP()->getScreen() != "Home") return;

    for (auto w : m_widgets) {
        w->draw();
    }
}

void HomeScreen::update() {
    if (APP()->getScreen() != "Home") return;

    for (auto w : m_widgets) {
        w->update();
    }
}

void HomeScreen::init() {
    Slideshow* s = new Slideshow();
    m_widgets.push_back((Widget*) s);
    s->setPosX(m_pos[0]);
    s->setPosY(CANVAS_HEIGHT/4.0f);
}

void Slideshow::draw() {

    // Draw slideshow banner pic
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    br.texture = ASSET_PATH + std::string("bpwf.png");
    SETCOLOR(br.fill_secondary_color, 0.03f, 0.04f, 0.12f);
    br.fill_secondary_opacity = 1.0f;
    br.gradient = true;
    br.gradient_dir_u = 0.0f;
    br.gradient_dir_v = 1.0f;
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH * 5.0f/8.0f, 6.5f, br);

    // Draw slideshow left and right buttons
    br.fill_secondary_opacity = 0.0f;
    br.gradient = false;
    SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    br.texture = ASSET_PATH + std::string("left.png");
    graphics::drawRect(m_pos[0] - 1.5f - CANVAS_WIDTH * 5.0f/16.0f, m_pos[1], 1.0f, 1.0f, br);

    br.texture = ASSET_PATH + std::string("right.png");
    graphics::drawRect(m_pos[0] + 1.5f + CANVAS_WIDTH * 5.0f/16.0f, m_pos[1], 1.0f, 1.0f, br);
}

void Slideshow::update() {
    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);
}


/* Info Screen */

void InfoScreen::draw() {
    if (APP()->getScreen() != "Info") return;

    // Draw Pictures
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 1.0f;
    br.outline_width = 4.0f;
    br.texture = ASSET_PATH + std::string("alex.png");
    SETCOLOR(br.outline_color, 1.0f, 0.54f, .0f);
    graphics::drawRect(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f, CANVAS_HEIGHT/2.0f - 2.0f, 4.0f, 4.0f, br);
    br.texture = ASSET_PATH + std::string("kate.png");
    graphics::drawRect(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f, CANVAS_HEIGHT/2.0f - 2.0f, 4.0f, 4.0f, br);

    // Draw contact info
    graphics::setFont(ASSET_PATH + std::string("MontserratMedium.ttf"));
    graphics::drawText(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.1f, CANVAS_HEIGHT/2.0f + 2.0f, 0.45f, "Alex    Papadopoulos", br);
    graphics::drawText(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.0f, CANVAS_HEIGHT/2.0f + 2.0f, 0.45f, "Katerina    Mantaraki", br);
}

void InfoScreen::update() {
    if (APP()->getScreen() != "Info") return;
}
