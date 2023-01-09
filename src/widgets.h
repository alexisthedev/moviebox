#pragma once
#include "sgg/graphics.h"
#include <string>
#include <list>
#include "movies.h"
#include "moviedb.h"

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
    bool m_active = false;

public:
    void setText(std::string text) { m_text = text; }
    std::string getText() { return m_text; }
    void setHighlight(bool h) { m_highlighted = h; }
    void setActive(bool a) { m_active = a; }
    virtual bool contains(float x, float y) = 0;
};

class IconButton : public Button {
protected:
    std::string m_icon;

public:
    void setIcon(std::string icon) { m_icon = icon; }
    IconButton() {}
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

class MovieButton : public IconButton {
    Movie* m_movie = nullptr;

public:
    void draw();
    void update();
    bool contains(float x, float y);
    void setMovie(Movie* m) { m_movie = m; m_icon = (m) ? m_movie->getImg() : ""; }
    Movie* getMovie() { return m_movie; }
};

class Slider : public Button {
    float m_rect_pos;

public:
    void draw();
    void update();
    bool contains(float x, float y);
    void init() { m_rect_pos = (m_text == "From") ? m_pos[0]-SLIDER_LENGTH/2.0f : m_pos[0]+SLIDER_LENGTH/2.0f; }
    void slide(float x);
    int pos_to_value();
    Slider() {}
    ~Slider() {}
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
    std::list<MovieButton*> m_buttons;
    MovieButton* m_active_button = nullptr;

public:
    void draw();
    void update();
    void init();
    HomeScreen() {}
    ~HomeScreen();
};

class BrowseScreen : public Widget {
    std::list<Widget*> m_widgets;
    std::list<Button*> m_buttons;
    Button* m_active_button = nullptr;
    std::vector<Movie*> m_results;
    int m_range_start;
    int m_range_end;

public:
    void draw();
    void update();
    void init();
    BrowseScreen() {}
    ~BrowseScreen();
};

class InfoScreen : public Widget {
public:
    void draw();
    void update();
    InfoScreen() {}
    ~InfoScreen() {}
};

class MovieScreen : public Widget {
    std::list<SlideshowButton*> m_buttons;

public:
    void draw();
    void update();
    void init();
    MovieScreen() {}
    ~MovieScreen();
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
    ~Slideshow();
};
