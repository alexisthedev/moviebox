#pragma once

#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>

inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f
#define SLIDER_LENGTH 2.15f

#define ASSET_PATH "assets/"
#define MOVIE_PATH "assets/movies/"

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}
#define RAND0TO1() (rand()/(float)RAND_MAX)
#define APP() App::getInstance()
#define DB() MovieDB::getInstance()

inline float distance(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrtf(dx*dx + dy*dy);
}
