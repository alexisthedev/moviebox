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
    std::string m_genre;
    std::string m_description;
    std::string m_image;

public:
    void setTitle(std::string t) { m_title = t; }
    void setYear(int y) { m_year =y; }
    void setDirectors(std::list<std::string> d) { m_directors = d; }
    void setActors(std::list<std::string> a) { m_actors = a; }
    void setGenre(std::string g) { m_genre = g; }
    void setDesc(std::string d) { m_description = d; }
    void setImage(std::string i) { m_image = ASSET_PATH + i; }

    std::string getTitle() { return m_title; }
    int getYear() { return m_year; }
    std::list<std::string> getDirectors() { return m_directors; }
    std::list<std::string> getActors() { return m_actors; }
    std::string getGenre() { return m_genre; }
    std::string getDesc() { return m_description; }
    std::string getImg() { return m_image; }
};
