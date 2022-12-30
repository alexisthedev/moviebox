#pragma once
#include <list>
#include "widgets.h"

class App {
public:
    enum app_state_t {STATE_INIT, STATE_LOADING, STATE_IDLE};
protected:
    static App* m_instance;

    std::list<Widget*> m_widgets;
    app_state_t m_state = STATE_INIT;
    std::string m_screen = "Home";

    App() {}
public:
    void draw();
    void update();
    void init();
    void setScreen(std::string s) { m_screen = s; }
    std::string getScreen() { return m_screen; }

    ~App();

    static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
    static App* getInstance();
};
