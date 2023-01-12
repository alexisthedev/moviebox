#pragma once
#include <list>
#include "widgets.h"
#include "moviedb.h"

class App {
public:
    enum app_state_t {STATE_INIT, STATE_LOADING, STATE_IDLE};
protected:
    static App* m_instance;

    std::list<Widget*> m_widgets;
    app_state_t m_state = STATE_INIT;
    std::string m_screen = "Welcome";
    std::string m_prev_screen;
    Movie* m_cur_movie = nullptr;
    User* m_user = nullptr;

    App() {}
public:
    void draw();
    void update();
    void init();
    void setScreen(std::string s) { m_prev_screen = m_screen; m_screen = s; }
    std::string getScreen() { return m_screen; }
    std::string getPrevScreen() { return m_prev_screen; }
    void setMovie(Movie* m) { m_cur_movie = m; }
    Movie* getMovie() { return m_cur_movie; }
    void setUser(User* u) { m_user = u; }
    User* getUser() { return m_user; }

    ~App();

    static void releaseInstance() { if (m_instance) {delete m_instance;} m_instance = nullptr; DB()->releaseInstance();}
    static App* getInstance();
};
