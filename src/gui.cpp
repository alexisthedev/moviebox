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
    s->init();
}

void Slideshow::draw() {
    // Draw slideshow banner pic
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;

    switch (m_slide) {
        case 1:
            br.texture = ASSET_PATH + std::string("bpwf.png");
            break;
        case 2:
            SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
            break;
        case 3:
            SETCOLOR(br.fill_color, 0.0f, 1.0f, 0.0f);
            break;
        case 4:
            SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
            break;
        default:
            SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
            break;
    }

    SETCOLOR(br.fill_secondary_color, 0.03f, 0.04f, 0.12f);
    br.fill_secondary_opacity = 1.0f;
    br.gradient = true;
    br.gradient_dir_u = 0.0f;
    br.gradient_dir_v = 1.0f;
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH * 5.0f/8.0f, 6.5f, br);

    // Draw slideshow buttons
    for (auto b : m_buttons) {
        b->draw();
    }
}

void Slideshow::update() {
    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    // Highlight button
    SlideshowButton* cur_button = nullptr;
    for (auto b : m_buttons) {
        if (b->contains(mx, my)) {
            b->setHighlight(true);
            cur_button = b;
        } else {
            b->setHighlight(false);
        }
    }

    // Change to next or prev slide
    if (ms.button_left_pressed && cur_button) {
        if (cur_button->getText() == "Left") {
            m_slide = m_slide<=1 ? 4 : m_slide-1;
        } else {
            m_slide = m_slide>=4 ? 1 : m_slide+1;
        }
    }

    // Call update on dependent members: buttons
    for (auto b : m_buttons) {
        b->update();
    }
}

void Slideshow::init() {
    SlideshowButton* l = new SlideshowButton();
    m_buttons.push_front(l);
    l->setText("Left");
    l->setIcon(ASSET_PATH + std::string("left.png"));
    l->setPosX(m_pos[0] - 1.5f - CANVAS_WIDTH * 5.0f/16.0f);
    l->setPosY(m_pos[1]);

    SlideshowButton* r = new SlideshowButton();
    m_buttons.push_front(r);
    r->setText("Right");
    r->setIcon(ASSET_PATH + std::string("right.png"));
    r->setPosX(m_pos[0] + 1.5f + CANVAS_WIDTH * 5.0f/16.0f);
    r->setPosY(m_pos[1]);
}

void SlideshowButton::draw() {
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    br.texture = m_icon;

    if (m_highlighted) {
        SETCOLOR(br.fill_color, 1.0f, 0.54f, .0f);
    } else {
        SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    }
    graphics::drawRect(m_pos[0], m_pos[1], 1.0f, 1.0f, br);
}

void SlideshowButton::update() {

}

bool SlideshowButton::contains(float x, float y) {
    return x < m_pos[0] + 0.5f && x > m_pos[0] - 0.5f && y > m_pos[1] - 0.5f && y < m_pos[1] + 0.5f;
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
