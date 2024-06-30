#pragma once
#include "raylib-cpp.hpp"
#include <string>

class Button {
private:
    std::string text;
    int text_size;
    int ID;
    int margin;
    raylib::Color bg;
    raylib::Color bgh; // background hover
    raylib::Color text_colour;
    raylib::Vector2 pos;
public:
    Button();
    Button(std::string text, int text_size, int ID, int margin, raylib::Color bg, raylib::Color bgh, raylib::Color text_colour, raylib::Vector2 pos);
    bool clicked(raylib::Vector2 mouse_pos);
    void draw(raylib::Vector2 mouse_pos);
    int get_ID();
};