#include "Tile.hpp"

Tile::Tile() {
    Tile(0, 0, {0,0});
};

Tile::Tile(int state, int size, raylib::Vector2 pos) {
    this->state = state;
    this->size = size;
    this->pos = pos;
}

void Tile::draw(bool is_black_turn, raylib::Vector2 mouse_pos) {
    switch (state)
    {
    case 0:
        if (mouse_pos.x >= pos.x && mouse_pos.x < pos.x + size && mouse_pos.y >= pos.y && mouse_pos.y < pos.y + size && state == 0) {
            if (is_black_turn) { // hovering black turn
                DrawCircle(pos.x + size/2, pos.y + size/2, size/2 - 3, ColorAlpha(BLACK, 0.75));
            }
            else { // hovering white turn
                DrawCircle(pos.x + size/2, pos.y + size/2, size/2 - 3, ColorAlpha(WHITE, 0.75));
            }
        }
        break;
    case 1: // black piece
        DrawCircle(pos.x + size/2, pos.y + size/2, size/2 - 3, BLACK);
        break;
    case 2: // white piece
        DrawCircle(pos.x + size/2, pos.y + size/2, size/2 - 3, WHITE);
        break;
    default:
        break;
    }
}

void Tile::set_state(int state) {
    this->state = state;
}