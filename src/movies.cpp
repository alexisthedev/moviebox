#include "sgg/graphics.h"
#include "movies.h"
#include "defines.h"

std::string Movie::getDirectors() {
    std::string str;
    bool first = true;
    for (auto s : m_directors) {
        if (first) {str = s; first = false; continue;}
        str += ",  " + s;
    }
    return str;
}

std::string Movie::getActors() {
    std::string str;
    bool first = true;
    for (auto a : m_actors) {
        if (first) {str = a; first = false; continue;}
        str += ",  " + a;
    }
    return str;
}
