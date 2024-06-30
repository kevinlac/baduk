#include "Button.hpp"

Button::Button() {
    Button("", 0, 0, 0, BLACK, BLACK, BLACK, {0,0});
}

Button::Button(std::string text, int text_size, int ID, int margin, raylib::Color bg, raylib::Color bgh, raylib::Color text_colour, raylib::Vector2 pos) {
    this->text = text;
    this->text_size = text_size;
    this->ID = ID;
    this->margin = margin;
    this->bg = bg;
    this->bgh = bgh;
    this->text_colour = text_colour;
    this->pos = pos;
}

bool Button::clicked(raylib::Vector2 mouse_pos) {
    int width = raylib::MeasureText(text, text_size) + margin * 2;
    int height = text_size + margin * 2;
    if (mouse_pos.x >= pos.x && mouse_pos.x < pos.x + width && mouse_pos.y >= pos.y && mouse_pos.y < pos.y + height) {
        return true;
    }
    return false;
}

void Button::draw(raylib::Vector2 mouse_pos) {
    int width = raylib::MeasureText(text, text_size) + margin * 2;
    int height = text_size + margin * 2;
    if (mouse_pos.x >= pos.x && mouse_pos.x < pos.x + width && mouse_pos.y >= pos.y && mouse_pos.y < pos.y + height) { // hover
        DrawRectangle(pos.x, pos.y, width, height, bgh);
    } else {
        DrawRectangle(pos.x, pos.y, width, height, bg);
    }
    raylib::DrawText(text, pos.x + margin, pos.y + margin, text_size, text_colour);
}

int Button::get_ID() {
    return ID;
}