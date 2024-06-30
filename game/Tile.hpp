#pragma once
#include "raylib-cpp.hpp"

class Tile {
private:
    int state; // 0 = nothing, 1 = black, 2 = white 
    int size;
    raylib::Vector2 pos;
public:
    Tile();
    Tile(int state, int size, raylib::Vector2 pos);
    void draw(bool is_black_turn, raylib::Vector2 mouse_pos);
    void set_state(int state);
};