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
    SETCOLOR(br.fill_color, 0.03f, 0.04f, 0.12f);
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

    for (auto w : m_widgets) {
        w->update();
    }
}

void App::init() {
    // Initialize movies
    std::string t = "Star Wars Episode V: The Empire Strikes Back";
    std::string desc = "After the Rebels are brutally overpowered by the Empire on the ice planet Hoth,  Luke Skywalker begins Jedi training with Yoda.";
    m_movie_list.push_back(new Movie(t, 1980, {"George Lucas"}, {"Mark Hamill", "Carrie Fisher", "Harrison Ford"}, "Science Fiction", desc, "sw"));

    t = "Black Panther: Wakanda Forever";
    desc = "The people of Wakanda fight to protect their home from intervening world powers as they mourn the death of King T'Challa.";
    m_movie_list.push_back(new Movie(t, 2022, {"Ryan Coogler"}, {"Letitia Wright", "Lupita Nyong'o", "Danai Gurira"}, "Action", desc, "bpwf"));

    // Initialize components
    Sidebar* s = new Sidebar();
    m_widgets.push_front((Widget*) s);
    s->setPosX(CANVAS_WIDTH/12.0f);
    s->setPosY(CANVAS_HEIGHT/2.0f);
    s->init();

    HomeScreen* h = new HomeScreen();
    m_widgets.push_front((Widget*) h);
    h->setPosX(CANVAS_WIDTH * 7.0f/12.0f);
    h->setPosY(CANVAS_HEIGHT/2.0f);
    h->init();

    InfoScreen* i = new InfoScreen();
    m_widgets.push_front((Widget*) i);
    i->setPosX(CANVAS_WIDTH * 7.0f/12.0f);
    i->setPosY(CANVAS_HEIGHT/2.0f);

    MovieScreen* m = new MovieScreen();
    m_widgets.push_front((Widget*) m);
    m->setPosX(CANVAS_WIDTH/2.0f);
    m->setPosY(CANVAS_HEIGHT/2.0f);
    m->init();

    graphics::preloadBitmaps(ASSET_PATH);
    graphics::preloadBitmaps(MOVIE_PATH);
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
