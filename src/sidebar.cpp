#include "defines.h"
#include "app.h"

void Sidebar::draw() {
    // draw sidebar rectangle
    graphics::Brush br;
    SETCOLOR(br.fill_color, 0.08f, 0.12f, 0.20f);
    br.fill_opacity = 0.4f;
    br.outline_opacity = 0.0f;
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH/6.0f, CANVAS_HEIGHT, br);

    // draw sidebar right outline
    graphics::Brush reticle;
    SETCOLOR(reticle.fill_color, 0.47f, 0.47f, 0.47f);
    SETCOLOR(reticle.outline_color, 0.47f, 0.47f, 0.47f);
    reticle.fill_opacity = 0.4f;
    reticle.outline_opacity = 0.4f;
    reticle.outline_width = 2.0f;
    graphics::drawLine(CANVAS_WIDTH/6.0f, CANVAS_HEIGHT, CANVAS_WIDTH/6.0f, .0f, reticle);

    // draw sidebar buttons
    for (auto b : m_buttons) {
        b->draw();
    }
}

void Sidebar::update() {
    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    // Highlight button
    SidebarButton* cur_button = nullptr;
    for (auto b : m_buttons) {
        if (b->contains(mx, my)) {
            b->setHighlight(true);
            cur_button = b;
        } else {
            b->setHighlight(false);
        }
    }

    // Activate button
    if (ms.button_left_pressed && cur_button) {
        if (cur_button->getText() == "Log Out") {
            graphics::stopMessageLoop();
        }

        m_active_button = cur_button;
        m_active_button->setActive(true);
        APP()->setScreen(m_active_button->getText());
        for (auto b : m_buttons) {
            if (b != m_active_button) {
                b->setActive(false);
            }
        }
    }

    // Call update on dependent members: buttons
    for (auto b : m_buttons) {
        b->update();
    }
}

void Sidebar::init() {
    // Initialize home button
    SidebarButton* home = new SidebarButton();
    home->setText("Home");
    home->setIcon(ASSET_PATH + std::string("home.png"));
    home->setActive(true);
    m_buttons.push_back(home);

    // Initialize browse button
    SidebarButton* browse = new SidebarButton();
    browse->setText("Browse");
    browse->setIcon(ASSET_PATH + std::string("browse.png"));
    m_buttons.push_back(browse);

    // Initialize info button
    SidebarButton* info = new SidebarButton();
    info->setText("Info");
    info->setIcon(ASSET_PATH + std::string("info.png"));
    m_buttons.push_back(info);

    // Set buttons position inside sidebar
    int i=0;
    for (auto b : m_buttons) {
        b->setPosX(getPosX());
        b->setPosY(getPosY()-4.0f + i*2.0f);
        i++;
    }

    // Initialize logout button
    SidebarButton* logout = new SidebarButton();
    logout->setText("Log Out");
    logout->setIcon(ASSET_PATH + std::string("logout.png"));
    logout->setPosX(CANVAS_WIDTH/12.0f);
    logout->setPosY(CANVAS_HEIGHT - 2.0f);
    m_buttons.push_back(logout);

}

Sidebar::Sidebar() {

}

Sidebar::~Sidebar() {
    for (auto b : m_buttons) {
        delete b;
    }
    m_buttons.clear();
}

/* Sidebar Buttons */

void SidebarButton::draw() {
    graphics::Brush br;
    br.texture = m_icon;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;

    if (m_active || m_highlighted) {
        SETCOLOR(br.fill_color, 1.0f, 0.54f, .0f);
    } else {
        SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    }

    // Draw button icon
    graphics::drawRect(m_pos[0]-1.5f, m_pos[1], 0.80f, 0.8f, br);

    // Draw button text
    graphics::setFont(ASSET_PATH + std::string("MontserratMedium.ttf"));
    graphics::drawText(m_pos[0]-0.8f, m_pos[1]+0.175f, 0.45f, m_text, br);

    /* Uncomment to see button outline
    graphics::Brush test;
    test.outline_opacity = 1.0f;
    test.fill_opacity = 0.0f;
    SETCOLOR(test.outline_color, 1.0f, 1.0f, 1.0f);
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH/6.0f, 1.0f, test);
    */
}

void SidebarButton::update() {

}

bool SidebarButton::contains(float x, float y) {
    return (x < CANVAS_WIDTH/6.0f) && m_pos[1]-0.5f < y && y < m_pos[1]+0.5f;
}
