#pragma once
#include <vector>
#include "movies.h"

class MovieDB {
protected:
    static MovieDB* m_instance;
    std::vector<Movie*> m_movies;
    std::vector<Movie*> m_popular;
    std::vector<Movie*> m_slideshow;
    MovieDB() {}

public:
    std::vector<Movie*> getMoviesFromRange(int from, int to);
    std::vector<Movie*> getPopularMovies() { return m_popular; }
    std::vector<Movie*> getSlideshowMovies() { return m_slideshow; }

    void init();
    ~MovieDB();

    static void releaseInstance() { if (m_instance) {delete m_instance;} m_instance = nullptr; }
    static MovieDB* getInstance();
};
