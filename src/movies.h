#pragma once
#include <string>
#include <list>
#include <vector>
#include "defines.h"

class Movie {
    std::string m_title;
    int m_year;
    std::list<std::string> m_directors;
    std::list<std::string> m_actors;
    std::list<std::string> m_genre;
    std::string m_description;
    std::string m_image;
    std::string m_shortcut;

public:
    Movie(std::string t, int y, std::list<std::string> d,
          std::list<std::string> a, std::list<std::string> g,
          std::string desc, std::string i):
            m_title(t), m_year(y),
            m_directors(d), m_actors(a),
            m_genre(g), m_description(desc),
            m_shortcut(i) { m_image = MOVIE_PATH + i;}

    std::string getTitle() { return m_title; }
    int getYear() { return m_year; }
    std::string getDirectors();
    std::string getActors();
    std::string getGenre();
    std::string getDesc() { return m_description; }
    std::string getImg() { return m_image+".png"; }
    std::string getBanner() { return m_image+"b.png"; }
    std::string getPoster() { return m_image+"p.png"; }
    std::string getScene1() { return m_image +"1.png"; }
    std::string getScene2() { return m_image +"2.png"; }
    std::string getShortcut() { return m_shortcut; }
};
