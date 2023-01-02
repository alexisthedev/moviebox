#include "sgg/graphics.h"
#include <string>
#include <list>

class Widget {
protected:
    float m_pos[2];
    float m_color[3];

public:
    virtual void draw() = 0;
    virtual void update() = 0;

    float getPosX() { return m_pos[0]; }
    float getPosY() { return m_pos[1]; }
    void setPosX(float x) { m_pos[0] = x; }
    void setPosY(float y) { m_pos[1] = y; }

    virtual ~Widget() {};
};

/* Buttons */

class Button : public Widget {
protected:
    std::string m_text;
    bool m_highlighted = false;

public:
    void setText(std::string text) { m_text = text; }
    std::string getText() { return m_text; }
    void setHighlight(bool h) { m_highlighted = h; }
    bool contains(float x, float y);
    Button() {}

};

class IconButton : public Button {
protected:
    std::string m_icon;
    bool m_active = false;

public:
    void setActive(bool a) { m_active = a; }
    void setIcon(std::string icon) { m_icon = icon; }
    virtual bool contains(float x, float y) = 0;
};

class SidebarButton : public IconButton {
public:
    void draw();
    void update();
    bool contains(float x, float y);
};

class SlideshowButton : public IconButton {
public:
    void draw();
    void update();
    bool contains(float x, float y);
};

/* Sidebar */

class Sidebar : public Widget {
    std::list<SidebarButton*> m_buttons;
    SidebarButton* m_active_button = nullptr;

public:
    void draw();
    void update();
    void init();
    Sidebar();
    ~Sidebar();
};

/* Screen Widgets */

class HomeScreen : public Widget {
    std::list<Widget*> m_widgets;
public:
    void draw();
    void update();
    void init();
    HomeScreen() {}
    ~HomeScreen() {}
};

class InfoScreen : public Widget {
public:
    void draw();
    void update();
    InfoScreen() {}
    ~InfoScreen() {}
};

/* Home Screen Widget */

class Slideshow : public Widget {
    std::list<SlideshowButton*> m_buttons;
    int m_slide = 1;
public:
    void draw();
    void update();
    void init();
    Slideshow() {}
    ~Slideshow() {}
};
