#include "sgg/graphics.h"

class Widget {
protected:
    float m_pos[2];
    float m_color[3];

public:
    virtual void draw() = 0;
    virtual void update() = 0;

    virtual ~Widget() {};

    virtual float getPosX() = 0;
    virtual float getPosY() = 0;
    virtual void setPosX(float x) = 0;
    virtual void setPosY(float y) = 0;
};

class Sidebar : Widget {
    void draw();
    void update();

public:
    Sidebar();
    ~Sidebar();
    float getPosX() { return m_pos[0]; }
    float getPosY() { return m_pos[1]; }
    void setPosX(float x) { m_pos[0] = x; }
    void setPosY(float y) { m_pos[1] = y; }
};
