#include "app.h"
#include "defines.h"
#include "moviedb.h"

/* Welcome Screen */

void WelcomeScreen::draw() {
    if (APP()->getScreen() != "Welcome") return;

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    graphics::drawText(m_pos[0]-4.0f, m_pos[1] - 4.0f, 1.0f, "Who's Watching?", br);

    for (auto w : m_widgets) {
        w->draw();
    }
}

void WelcomeScreen::update() {
    if (APP()->getScreen() != "Welcome") return;

    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    // Highlight button
    UserButton* cur_button = nullptr;
    for (auto b : m_buttons) {
        if (b->contains(mx, my)) {
            b->setHighlight(true);
            cur_button = b;
        } else {
            b->setHighlight(false);
        }
    }

    // Activate movie
    if (ms.button_left_pressed && cur_button) {
        m_active_button = cur_button;
        m_active_button->setActive(true);
        for (auto b : m_buttons) {
            if (b != m_active_button) {
                b->setActive(false);
            }
        }
    }

    if (m_active_button) {
        APP()->setScreen("Home");
        APP()->setUser(m_active_button->getUser());
    }

    for (auto w : m_widgets) {
        w->update();
    }
}

void WelcomeScreen::init() {
    User* users[] = {new User(" Alex", "alexuser"), new User("Katerina", "kateuser"), new User(" Guest", "guestuser")};
    // Initialize Buttons
    for (int i=0; i<3; i++) {
        UserButton* ub = new UserButton();
        m_widgets.push_front((Widget*) ub);
        m_buttons.push_front(ub);
        ub->setUser(users[i]);
        ub->setPosX(6.5f + 7.5f*i);
        ub->setPosY(CANVAS_HEIGHT/2.0f);
    }
}

WelcomeScreen::~WelcomeScreen() {
    for (auto w : m_widgets) {
        delete w;
    }
    m_widgets.clear();
    m_buttons.clear();
}

/* User Button */

void UserButton::draw() {
    graphics::Brush br;
    br.outline_opacity = 1.0f * m_highlighted;
    br.outline_width = 2.0f;
    br.texture = m_user->getProfilePic();
    graphics::drawRect(m_pos[0], m_pos[1], 4.0f, 4.0f, br);
    SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    graphics::drawText(m_pos[0]-0.8f, m_pos[1] + 3.0f, 0.4f, m_user->getName(), br);
}

void UserButton::update() {

}

bool UserButton::contains(float x, float y) {
    return m_pos[0] - 2.0f <= x && x <= m_pos[0] + 2.0f &&
            m_pos[1] - 2.0f <= y && y <= m_pos[1] + 2.0f;
}

/* Home Screen */

void HomeScreen::draw() {
    if (APP()->getScreen() != "Home") return;

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f, (CANVAS_HEIGHT/4.0f + 3.25f) + 1.2f, 0.5f, "Popular", br);
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f, (CANVAS_HEIGHT/4.0f + 3.25f) + 5.45f, 0.5f, "New Releases", br);

    if (m_active_button) {
        APP()->setScreen("Movie");
        APP()->setMovie(m_active_button->getMovie());
    }
    m_active_button = nullptr;

    for (auto w : m_widgets) {
        w->draw();
    }
}

void HomeScreen::update() {
    if (APP()->getScreen() != "Home") return;

    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    // Highlight button
    MovieButton* cur_button = nullptr;
    for (auto b : m_buttons) {
        if (b->contains(mx, my)) {
            b->setHighlight(true);
            cur_button = b;
        } else {
            b->setHighlight(false);
        }
    }

    // Activate movie
    if (ms.button_left_pressed && cur_button) {
        m_active_button = cur_button;
        m_active_button->setActive(true);
        for (auto b : m_buttons) {
            if (b != m_active_button) {
                b->setActive(false);
            }
        }
    }

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

    for (int i=0; i<2; i++) {
        std::vector<Movie*> home_movies = (i==0) ? DB()->getPopularMovies() : DB()->getMoviesFromRange(2021,2022);
        for (int j=0; j<5; j++) {
            MovieButton* m = new MovieButton();
            m_widgets.push_back((Widget*) m);
            m_buttons.push_back(m);
            m->setMovie(home_movies[j]);
            m->setText("Horizontal");
            m->setPosX(CANVAS_WIDTH/6.0f + 5.0/9.0f + 2.0f + (4.0f + 5.0/9.0f)*j);
            m->setPosY((s->getPosY()+3.25f) + 2.75f + 4.25*i);
        }
    }
}

HomeScreen::~HomeScreen() {
    for (auto w : m_widgets) {
        delete w;
    }
    m_widgets.clear();
}

/* Slide Show */

void Slideshow::draw() {
    // Draw slideshow banner pic
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    br.texture = ASSET_PATH + m_movies[m_slide-1]->getShortcut() + ".png";

    // Add gradient
    SETCOLOR(br.fill_secondary_color, 0.03f, 0.04f, 0.12f);
    br.fill_secondary_opacity = 1.0f;
    br.gradient = true;
    br.gradient_dir_u = 0.0f;
    br.gradient_dir_v = 1.0f;
    graphics::drawRect(m_pos[0], m_pos[1], CANVAS_WIDTH * 5.0f/8.0f, 6.5f, br);

    // Draw title
    br.texture = "";
    br.gradient = false;
    br.fill_secondary_opacity = 0.0f;
    graphics::drawText(m_pos[0]-CANVAS_WIDTH*5.0f/16.0f + 0.5f, m_pos[1]+3.0f, 0.6f, m_movies[m_slide-1]->getTitle(), br);

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

    // Check if user clicks on movie slide
    if (m_pos[0] - CANVAS_WIDTH*5.0f/16.0f <= mx && mx <= m_pos[0] + CANVAS_WIDTH*5.0f/16.0f &&
            m_pos[1] - 3.25f <= my && my <= m_pos[1] + 3.25f && ms.button_left_pressed) {
        APP()->setScreen("Movie");
        APP()->setMovie(m_movies[m_slide-1]);
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

    m_movies = DB()->getSlideshowMovies();
}

Slideshow::~Slideshow() {
    for (auto b : m_buttons) {
        delete b;
    }
    m_buttons.clear();
}


/* Slideshow Buttons */

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


/* Movie Widget */

void MovieButton::draw() {
    if (!m_movie) return;

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    if (m_text == "Horizontal") {
        br.texture = m_movie->getImg();
        graphics::drawRect(m_pos[0], m_pos[1], 4.0f, 2.5f, br);
    } else if (m_text == "Vertical") {
        br.texture = m_movie->getPoster();
        graphics::drawRect(m_pos[0], m_pos[1], 3.65f, 5.2f, br);
    }

    SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
    br.fill_opacity = 0.4f * m_highlighted;
    if (m_text == "Horizontal") {
        graphics::drawRect(m_pos[0], m_pos[1], 4.0f, 2.5f, br);
    } else if (m_text == "Vertical") {
        graphics::drawRect(m_pos[0], m_pos[1], 3.65f, 5.2f, br);
    }
}

void MovieButton::update() {

}

bool MovieButton::contains(float x, float y) {
    return (m_text == "Horizontal") ? m_pos[0] - 2.0f <= x && x <= m_pos[0] + 2.0f && m_pos[1] - 1.25f <= y && y <= m_pos[1] + 1.25f :
                                    m_pos[0] - 1.825f <= x && x <= m_pos[0] + 1.825f && m_pos[1] - 2.6f <= y && y <= m_pos[1] + 2.6f;
}

/* Browse Screen */

void BrowseScreen::draw() {
    if (APP()->getScreen() != "Browse") return;

    graphics::Brush br;
    br.outline_opacity = 0.0f;

    // Draw slider info
    SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    graphics::drawText(CANVAS_WIDTH/6.0f + 0.73f, 1.0f, 0.4f, "From: ", br);
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f + 5.0f, 1.0f, 0.4f, std::to_string(m_range_start), br);
    graphics::drawText(CANVAS_WIDTH/6.0f + 0.73f, 2.0f, 0.4f, "To: ", br);
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f + 5.0f, 2.0f, 0.4f, std::to_string(m_range_end), br);

    // Draw searchbar info
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f + 9.5f, 1.0f, 0.4f, "               Title:", br);
    graphics::drawText(CANVAS_WIDTH/6.0f + 5.0/9.0f + 9.5f, 2.0f, 0.4f, "Dir. / Act.:", br);

    int m = 0;
    // Show movies based on search results
    for (auto w : m_widgets) {
        MovieButton* mb = dynamic_cast<MovieButton*> (w);
        if (!mb) continue;
        // If we are here the element is a MovieButton
        mb->setMovie((m<m_results.size()) ? m_results[m] : nullptr);
        m++;
    }

    if (m_active_button && m_active_button->getText()=="Vertical") {
        APP()->setScreen("Movie");
        APP()->setMovie(((MovieButton*) m_active_button)->getMovie());
        m_active_button = nullptr;
    }

    for (auto w : m_widgets) {
        w->draw();
    }
}

void BrowseScreen::update() {
    if (APP()->getScreen() != "Browse") return;

    // Get mouse position
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Convert mouse cords to canvas cords
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    // Set genres selected previously as active
    for(auto w : m_buttons) {
        if(dynamic_cast<Checkbox*>(w) && std::count(m_active_genres.begin(), m_active_genres.end(), w->getText())) {
            w->setActive(true);
        }
    }

    // Highlight button
    Button* cur_button = nullptr;
    for (auto b : m_buttons) {
        // If the Button is a MovieButton but has no movie, continue
        if (dynamic_cast<MovieButton*> (b) && !((MovieButton*) b)->getMovie()) continue;
        if (b->contains(mx, my)) {
            b->setHighlight(true);
            cur_button = b;
        } else {
            b->setHighlight(false);
        }
    }

    // Activate Button
    if (ms.button_left_pressed && cur_button && !dynamic_cast<Checkbox*>(cur_button)) {
        m_active_button = cur_button;
        m_active_button->setActive(true);
        for (auto b : m_buttons) {
            if (b != m_active_button && !dynamic_cast<Checkbox*>(cur_button)) {
                b->setActive(false);
            }
        }
    } else if (ms.button_left_pressed && cur_button) {
        // The button is a Checkbox and it was clicked
       if (cur_button->isActive()){
            m_active_genres.erase(cur_button->getText());
       } else {
            m_active_genres.insert(cur_button->getText());
       }
       cur_button->setActive(!cur_button->isActive());
    }

    // Move slider
    if (ms.dragging && m_active_button && (m_active_button->getText() == "From" || m_active_button->getText() == "To")) {
        Slider* sl = (Slider*) m_active_button;
        sl->slide(mx);
        m_range_start= (sl->getText() == "From") ? sl->pos_to_value(): m_range_start;
        m_range_end = (sl->getText() == "To") ? sl->pos_to_value() : m_range_end;
    }

    // Ensure slider is deactivated after releasing lmb
    if (m_active_button && (m_active_button->getText()=="From" || m_active_button->getText()=="To") && ms.button_left_released) {
        m_active_button = nullptr;
    }

    // Change searchbar text
    if (m_active_button && (dynamic_cast<Searchbar*>(m_active_button))) {
        Searchbar* sb = dynamic_cast<Searchbar*>(m_active_button);
        for (auto it=m_keys.begin(); it!=m_keys.end(); ++it) {
            if (graphics::getKeyState(it->second)) {
                sb->write(it->first);
                sleep(125);
            }
        }
        m_active_title_search = (sb->getText() == "Title") ? sb->getSearch() : m_active_title_search;
        m_active_diract_search = (sb->getText() == "DirAct") ? sb->getSearch() : m_active_diract_search;
    }

    // Display movies based on filters
    m_results.clear();
    std::vector<Movie*> movies_by_range = DB()->getMoviesFromRange(m_range_start, m_range_end);
    if(!m_active_genres.empty()) {
        // If all genre buttons are unchecked show all genres
        // Else filter both by year and by genre
        std::vector<Movie*> movies_by_genre = DB()->getMoviesByGenre(m_active_genres);
        for(auto m : movies_by_genre) {
            if(std::count(movies_by_range.begin(), movies_by_range.end(), m) != 0) {
                m_results.push_back(m);
            }
        }
    } else {
        m_results = movies_by_range;
    }

    // Now keep the already filtered movies and filter again by search terms
    std::vector<Movie*> movies_from_search = m_results;

    if (m_active_title_search != "") {
        m_results.clear();
        for (auto m : movies_from_search) {
            std::string title = m->getTitle();
            for(auto &c : title) c = (char)toupper(c);
            if (title.find(m_active_title_search) != std::string::npos) {
                m_results.push_back(m);
            }
        }
    }

    // Re-filter by director/actor
    if (m_active_diract_search != "") {
        movies_from_search = m_results;
        m_results.clear();
        for (auto m : movies_from_search) {
            std::string term = m->getDirectors();
            std::string term2 = m->getActors();
            for (auto &c : term) c = (char)toupper(c);
            for (auto &c : term2) c = (char)toupper(c);
            if (term.find(m_active_diract_search) != std::string::npos ||
                    term2.find(m_active_diract_search) != std::string::npos) {
                m_results.push_back(m);
            }
        }
    }

    // Clear filters
    if (m_active_button && m_active_button->getText() == "Clear") {
        for(auto w : m_widgets) {
            delete w;
        }
        m_widgets.clear();
        m_buttons.clear();
        m_active_button = nullptr;
        m_active_diract_search = "";
        m_active_title_search = "";
        init();
    }

    // Call update on dependent members
    for (auto b : m_buttons) {
        b->update();
    }
}

void BrowseScreen::init() {
    // Show all movies intially
    m_active_genres.clear();
    m_range_start = 1980;
    m_range_end = 2022;
    m_results = DB()->getMoviesFromRange(m_range_start, m_range_end);

    // Intialize Sliders
    Slider* f = new Slider();
    m_widgets.push_front(f);
    m_buttons.push_front(f);
    f->setPosX(CANVAS_WIDTH/6.0f + 5.0/9.0f + 3.0f);
    f->setPosY(0.85f);
    f->setText("From");
    f->init();

    Slider* t = new Slider();
    m_widgets.push_front(t);
    m_buttons.push_front(t);
    t->setPosX(CANVAS_WIDTH/6.0f + 5.0/9.0f + 3.0f);
    t->setPosY(1.85f);
    t->setText("To");
    t->init();

    //Initialize Searchbars
    Searchbar* sb_title =  new Searchbar();
    m_widgets.push_front(sb_title);
    m_buttons.push_front(sb_title);
    sb_title->setPosX(CANVAS_WIDTH/6.0f + 5.0/9.0f + 15.0f);
    sb_title->setPosY(0.9f);
    sb_title->setText("Title");

    Searchbar* sb_dir =  new Searchbar();
    m_widgets.push_front(sb_dir);
    m_buttons.push_front(sb_dir);
    sb_dir->setPosX(CANVAS_WIDTH/6.0f + 5.0/9.0f + 15.0f);
    sb_dir->setPosY(0.9f + 1.0f);
    sb_dir->setText("DirAct");


    // Initialize key map
    using namespace graphics;
    m_keys = {{"A", SCANCODE_A}, {"B", SCANCODE_B}, {"C", SCANCODE_C},
                {"D", SCANCODE_D}, {"E", SCANCODE_E}, {"F", SCANCODE_F},
                {"G", SCANCODE_G}, {"H", SCANCODE_H}, {"I", SCANCODE_I},
                {"J", SCANCODE_J}, {"K", SCANCODE_K}, {"L", SCANCODE_L},
                {"M", SCANCODE_M}, {"N", SCANCODE_N}, {"O", SCANCODE_O},
                {"P", SCANCODE_P}, {"Q", SCANCODE_Q}, {"R", SCANCODE_R},
                {"S", SCANCODE_S}, {"T", SCANCODE_T}, {"U", SCANCODE_U},
                {"V", SCANCODE_V}, {"W", SCANCODE_W}, {"X", SCANCODE_X},
                {"Y", SCANCODE_Y}, {"Z", SCANCODE_Z}, {" ", SCANCODE_SPACE},
                {"BACKSPACE", SCANCODE_BACKSPACE}};


    // Initialize Checkboxes
    int counter = 0;
    for (auto g : DB()->getGenres()) {
        Checkbox* genre_button = new Checkbox();
        m_widgets.push_front(genre_button);
        m_buttons.push_front(genre_button);
        genre_button->setPosX(CANVAS_WIDTH/6.0f + 0.73f + 1.825f*2.0f + 3.675f*4.0f + 0.73f);
        genre_button->setPosY(3.8f + 1.0f*counter);
        genre_button->setText(g);
        counter++;
    }

    // Initialize Movie Buttons
    counter = 0;
    for (int i=0; i<2; i++) {
        for (int j=0; j<5; j++) {
            MovieButton* m = new MovieButton();
            m_widgets.push_back((Widget*) m);
            m_buttons.push_back((Button*) m);
            m->setText("Vertical");
            m->setPosX(CANVAS_WIDTH/6.0f + 0.73f + 1.825f + 3.675f*j);
            m->setPosY(6.0f + 5.22f*i);
            counter++;
        }
    }

    // Initialize clear filter button
    SlideshowButton* cf = new SlideshowButton();
    m_widgets.push_front(cf);
    m_buttons.push_front(cf);
    cf->setText("Clear");
    cf->setPosX(CANVAS_WIDTH/6.0f + 0.73f + 1.825f*2.0f + 3.675f*4.0f + 0.73f + 0.5f);
    cf->setPosY(CANVAS_HEIGHT - 3.0f);
    cf->setIcon(ASSET_PATH + std::string("clear.png"));
}

BrowseScreen::~BrowseScreen() {
    for (auto w : m_widgets) {
        if (w) delete w;
    }
    m_widgets.clear();
    m_buttons.clear();
}

/* Slider */

void Slider::draw() {
    // Draw slider bar
    graphics::Brush br;
    br.outline_width = 1.0f;
    SETCOLOR(br.outline_color, 0.80f, 0.80f, 0.85f);
    SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    graphics::drawLine(m_pos[0]-SLIDER_LENGTH/2.0f, m_pos[1], m_pos[0]+SLIDER_LENGTH/2.0f, m_pos[1], br);

    // Draw slider rectangle
    br.outline_opacity = 0.0f;
    SETCOLOR(br.fill_color, 1.0f, 0.54f, .0f);
    graphics::drawRect(m_rect_pos, m_pos[1], 0.1f, 0.4f, br);

    br.fill_opacity = 0.4f * m_highlighted;
    SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
    graphics::drawRect(m_rect_pos, m_pos[1], 0.1f, 0.4f, br);
}

void Slider::update() {

}

bool Slider::contains(float x, float y) {
    return m_rect_pos-0.05f <= x && x <= m_rect_pos+0.05f && m_pos[1]-0.2f <= y && y <= m_pos[1]+0.2f;
}

void Slider::slide(float x) {
    if (x < m_pos[0]-SLIDER_LENGTH/2.0f) {
        m_rect_pos = m_pos[0]-SLIDER_LENGTH/2.0f;
    } else if (x > m_pos[0]+SLIDER_LENGTH/2.0f) {
        m_rect_pos = m_pos[0]+SLIDER_LENGTH/2.0f;
    } else {
        m_rect_pos = x;
    }
}

int Slider::pos_to_value() {
    if (m_rect_pos == m_pos[0] - SLIDER_LENGTH / 2.0f) return 1980;
    if (m_rect_pos == m_pos[0] + SLIDER_LENGTH / 2.0f) return 2022;
    return (int) 1980 + (m_rect_pos - m_pos[0] + SLIDER_LENGTH/2.0f)/0.05f;
}


/* Checkbox */

void Checkbox::draw() {
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;

    if (m_active || m_highlighted) {
        SETCOLOR(br.fill_color, 1.0f, 0.54f, .0f);
    } else {
        SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    }

    graphics::drawText(m_pos[0], m_pos[1], 0.4f, m_text, br);
}

void Checkbox::update() {

}

bool Checkbox::contains(float x, float y) {
    return (x >= CANVAS_WIDTH/6.0f + 0.73f + 1.825f*2.0f + 3.675f*4.0f + 0.73f) && m_pos[1]-0.7f < y && y < m_pos[1]+0.3f;
}

/* Searchbar */

void Searchbar::draw() {
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    if (m_highlighted) {
        SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    } else {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    }

    graphics::drawRect(m_pos[0], m_pos[1], 6.0f, 0.7f, br);
    SETCOLOR(br.fill_color, .0f, .0f, .0f);
    graphics::drawText(m_pos[0]- 2.8f, m_pos[1]+0.2f, 0.4f, m_display_text, br);
}

void Searchbar::update() {

}

bool Searchbar::contains(float x, float y) {
    return m_pos[0] - 3.0f <= x && x <= m_pos[0] + 3.0f && m_pos[1] - 0.35f <= y && y <= m_pos[1] + 0.35f;
}

void Searchbar::write(std::string s) {
    if(s!="BACKSPACE" && m_display_text.size()<18) {
        m_display_text += s;
    } else if (s == "BACKSPACE") {
        if(m_display_text.size() == 1) {
            m_display_text = "";
        } else {
            m_display_text = m_display_text.substr(0, m_display_text.size()-1);
        }
    }
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
    br.outline_opacity = 0.0f;
    graphics::setFont(ASSET_PATH + std::string("MontserratMedium.ttf"));
    graphics::drawText(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.1f, CANVAS_HEIGHT/2.0f + 1.5f, 0.45f, "Alex    Papadopoulos", br);
    graphics::drawText(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.0f, CANVAS_HEIGHT/2.0f + 1.5f, 0.45f, "Katerina    Mantaraki", br);

    // Draw Social Media
    br.texture = ASSET_PATH + std::string("linkedin.png");
    graphics::drawRect(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.55f, CANVAS_HEIGHT/2.0f + 3.0f, 0.6f, 0.6f, br);
    graphics::drawRect(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.45f, CANVAS_HEIGHT/2.0f + 3.0f, 0.6f, 0.6f, br);

    graphics::drawText(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.1f, CANVAS_HEIGHT/2.0f + 3.15f, 0.35f, "linkedin.com/in/alexiospap", br);
    graphics::drawText(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.0f, CANVAS_HEIGHT/2.0f + 3.15f, 0.35f, "linkedin.com/in/katerinamant", br);

    br.texture = ASSET_PATH + std::string("github.png");
    graphics::drawRect(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.55f, CANVAS_HEIGHT/2.0f + 4.0f, 0.75f, 0.75f, br);
    graphics::drawRect(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.45f, CANVAS_HEIGHT/2.0f + 4.0f, 0.75f, 0.75f, br);

    graphics::drawText(m_pos[0] - CANVAS_WIDTH * 5.0f/24.0f - 2.1f, CANVAS_HEIGHT/2.0f + 4.15f, 0.35f, "github.com/alexisthedev", br);
    graphics::drawText(m_pos[0] + CANVAS_WIDTH * 5.0f/24.0f - 2.0f, CANVAS_HEIGHT/2.0f + 4.15f, 0.35f, "github.com/katerinamant", br);
}

void InfoScreen::update() {
    if (APP()->getScreen() != "Info") return;
}

/* Movie Screen */

void MovieScreen::draw() {
    if (APP()->getScreen() != "Movie") return;

    Movie* m = APP()->getMovie();

    // Draw movie details
    graphics::Brush br;
    br.outline_opacity = 0.0f;

    // Add gradient
    SETCOLOR(br.fill_secondary_color, 0.03f, 0.04f, 0.12f);
    br.fill_secondary_opacity = 1.0f;
    br.gradient = true;
    br.gradient_dir_u = 0.0f;
    br.gradient_dir_v = 1.0f;

    // Draw movie banner
    br.texture = m->getBanner();
    graphics::drawRect(m_pos[0], CANVAS_HEIGHT/5.0f, CANVAS_WIDTH, 2.0f*CANVAS_HEIGHT/5.0f, br);

    br.fill_secondary_opacity = 0.0f;
    br.gradient = false;

    // Draw movie poster
    br.texture = m->getPoster();
    br.outline_opacity = 1.0f;
    br.outline_width = 4.0f;
    SETCOLOR(br.outline_color, 1.0f, 1.0f, 1.0f);
    graphics::drawRect(CANVAS_WIDTH/8.0f, 2.0f*CANVAS_HEIGHT/5.0f, 4.375f, 6.25f, br);

    // Draw movie title
    br.texture = "";
    br.outline_opacity = 0.0f;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(CANVAS_WIDTH/8.0f + 2.8f, 2.0f*CANVAS_HEIGHT/5.0f + 1.25f, 0.8f, m->getTitle() + " (" + std::to_string(m->getYear())+")", br);

    // Draw director, actors, gerne
    SETCOLOR(br.fill_color, 0.80f, 0.80f, 0.85f);
    graphics::drawText(CANVAS_WIDTH/8.0f + 2.8f, 2.0f*CANVAS_HEIGHT/5.0f + 2.0f, 0.4f, "Directed  by:  " + m->getDirectors(), br);
    graphics::drawText(CANVAS_WIDTH/8.0f + 2.8f, 2.0f*CANVAS_HEIGHT/5.0f + 2.75f, 0.4f, "Starring:  " + m->getActors(), br);
    graphics::drawText(CANVAS_WIDTH/8.0f - 2.18525f, 2.0f*CANVAS_HEIGHT/5.0f + 3.875f, 0.4f, m->getGenre(), br);

    // Draw description
    graphics::drawText(CANVAS_WIDTH/8.0f - 2.18525f, 2.0f*CANVAS_HEIGHT/5.0f + 4.6f, 0.4f, m->getDesc(), br);

    // Draw movie scenes
    br.texture = m->getScene1();
    graphics::drawRect(m_pos[0] - 7.0f, CANVAS_HEIGHT - 2.5f, 6.0f, 4.0f, br);
    br.texture = m->getScene2();
    graphics::drawRect(m_pos[0] + 7.0f, CANVAS_HEIGHT - 2.5f, 6.0f, 4.0f, br);

    for (auto b : m_buttons) {
        b->draw();
    }
}

void MovieScreen::update() {
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

    // Close movie screen
    if (ms.button_left_pressed && cur_button) {
        if (cur_button->getText() == "Back") {
            APP()->setScreen(APP()->getPrevScreen());
            APP()->setMovie(nullptr);
        }
    }

    // Call update on dependent members: buttons
    for (auto b : m_buttons) {
        b->update();
    }
}

void MovieScreen::init() {
    // We will be reusing the slideshow button for the "X" icon of this screen
    // Yes we know that the name doesn't make sense
    // No we will not change it
    SlideshowButton* b = new SlideshowButton();
    m_buttons.push_back(b);
    b->setText("Back");
    b->setIcon(ASSET_PATH + std::string("back.png"));
    b->setPosX(1.0f);
    b->setPosY(1.0f);
}

MovieScreen::~MovieScreen() {
    for (auto b : m_buttons) {
        delete b;
    }
    m_buttons.clear();
}
