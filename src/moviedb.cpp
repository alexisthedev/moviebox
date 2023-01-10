#include "moviedb.h"
#include <algorithm>

std::vector<Movie*> MovieDB::getMoviesFromRange(int from, int to) {
    std::vector<Movie*> res;
    for (auto m : m_movies) {
        if (from <= m->getYear() && m->getYear() <= to ) {
            res.push_back(m);
        }
    }
    return res;
}

std::vector<Movie*> MovieDB::getMoviesByGenre(std::vector<std::string> genres) {
    std::vector<Movie*> res;
    for (auto m : m_movies) {

        for (auto g : m->getGenreList()) {
            if (std::count(genres.begin(), genres.end(), g) != 0) {
                res.push_back(m);
                break;
            }
        }
    }
    return res;
}

void MovieDB::init() {
    Movie* m = nullptr;

    // Initialize movies
    std::string t = "Star Wars Episode V: The Empire Strikes Back";
    std::string desc = "After the Rebels are brutally overpowered by the Empire on the ice planet Hoth,  Luke Skywalker begins Jedi training with Yoda.";
    m = new Movie(t, 1980, { "George Lucas" }, { "Mark Hamill", "Carrie Fisher", "Harrison Ford" }, {"Science Fiction", "Adventure"}, desc, "sw");
    m_movies.push_back(m);
    m_popular.push_back(m);

    t = "Black Panther: Wakanda Forever";
    desc = "The people of Wakanda fight to protect their home from intervening world powers as they mourn the death of King T'Challa.";
    m = new Movie(t, 2022, {"Ryan Coogler"}, {"Letitia Wright", "Lupita Nyong'o", "Danai Gurira"}, {"Action", "Adventure"}, desc, "bpwf");
    m_movies.push_back(m);
    m_slideshow.push_back(m);

    t = "Home Alone";
    desc = "An eight-year-old troublemaker, mistakenly left home alone, must defend his home against a pair of burglars on Christmas eve.";
    m = new Movie(t, 1990, { "Chris Columbus" }, { "Macaulay Culkin", "Joe Pesci", "Daniel Stern" }, {"Comedy", "Family"}, desc, "home");
    m_movies.push_back(m);
    m_popular.push_back(m);
    m_slideshow.push_back(m);

    t = "Harry Potter and the Prisoner of Azkaban";
    desc = "Harry Potter, Ron and Hermione return to Hogwarts School of Witchcraft and Wizardry for their third year of study.";
    m = new Movie(t, 2004, { "Alfonso Cuaron" }, { "Daniel Radcliffe", "Emma Watson", "Rupert Grint" }, {"Family", "Fantasy"}, desc, "hp");
    m_movies.push_back(m);
    m_popular.push_back(m);

    t = "The Dark Knight";
    desc = "When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must fight injustice.";
    m = new Movie(t, 2008, { "Christopher Nolan" }, { "Christian Bale", "Heath Ledger", "Aaron Eckhart" }, {"Action", "Drama"}, desc, "tdk");
    m_movies.push_back(m);
    m_popular.push_back(m);

    t = "Clueless";
    desc = "Cher, a high school student in Beverly Hills, must survive the ups and downs of adolescent life.";
    m = new Movie(t, 1995, { "Amy Heckerling" }, { "Alicia Silverstone", "Stacey Dash", "Brittany Murphy" }, {"Comedy", "Family"}, desc, "clue");
    m_movies.push_back(m);
    m_popular.push_back(m);

    t = "Everything Everywhere All at Once";
    desc = "An aging Chinese immigrant is swept up in an insane adventure.";
    m = new Movie(t, 2022, { "Dan Kwan", "Daniel Scheinert" }, { "Michelle Yeoh", "Stephanie Hsu", "Jamie Lee Curtis" }, {"Adventure", "Comedy"}, desc, "everything");
    m_movies.push_back(m);
    m_slideshow.push_back(m);

    t = "Nope";
    desc = "The residents of a lonely gulch in inland California bear witness to an uncanny and chilling discovery.";
    m = new Movie(t, 2022, {"Jordan Peele"}, {"Daniel Kaluuya", "Keke Palmer", "Steven Yeun"}, {"Horror", "Science Fiction"}, desc, "nope");
    m_movies.push_back(m);
    m_slideshow.push_back(m);

    t = "Elvis";
    desc = "The life of American music icon Elvis Presley.";
    m = new Movie(t, 2022, { "Baz Luhrmann" }, { "Tom Hanks", "Austin Butler", "Olivia DeJonge" }, {"Drama"}, desc, "elvis");
    m_movies.push_back(m);
    m_slideshow.push_back(m);

    t = "Encanto";
    desc = "A Colombian teenage girl has to face the frustration of being the only member of her family without magical powers.";
    m = new Movie(t, 2021, { "Jared Bush", "Byron Howard", "Charise Castro Smith"}, {"Stephanie Beatriz", "Maria Cecilia Botero", "John Leguizamo"}, {"Comedy", "Family"}, desc, "encanto");
    m_movies.push_back(m);
    m_slideshow.push_back(m);

    m_genres = {"Science Fiction", "Adventure", "Action", "Comedy", "Family", "Fantasy", "Drama", "Horror"};
}

MovieDB::~MovieDB() {
    for (auto m : m_movies) {
        delete m;
    }
    m_movies.clear();
    m_popular.clear();
}

MovieDB* MovieDB::getInstance() {
    if (!m_instance) {
        m_instance = new MovieDB();
    }
    return m_instance;
}

MovieDB* MovieDB::m_instance = nullptr;
