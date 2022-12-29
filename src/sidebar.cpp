#include "widget.h"
#include "defines.h"

void Sidebar::draw() {
    graphics::Brush br;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    br.outline_opacity = 0.0f;
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH/6.0f, CANVAS_HEIGHT, br);
}

void Sidebar::update() {
}

Sidebar::Sidebar() {

}

Sidebar::~Sidebar() {

}
