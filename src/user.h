#pragma once
#include <string>
#include "defines.h"

class User {
    std::string m_name;
    std::string m_profile_pic;

public:
    std::string getName() { return m_name; }
    std::string getProfilePic() { return ASSET_PATH + m_profile_pic + ".png"; }
    std::string getProfileIcon() { return ASSET_PATH + m_profile_pic + "i.png"; }

    User(std::string n, std::string p): m_name(n), m_profile_pic(p) {}
};
