#pragma once
#include "Tile.hpp"
#include <vector>

class Board {
private:
    int size; // size of grid
    int piece_size; // size of individual piece in px
    int black_captured;
    int white_captured;
    std::vector<int> ko_rule;
    std::vector<std::vector<Tile>> board; // cosmetic
    std::vector<std::vector<int>> states; // real board
    bool is_black_turn;
    std::vector<std::vector<int>> get_liberties(std::vector<int> pos); 
    std::vector<std::vector<int>> get_group(std::vector<int> pos);
public:
    Board();
    Board(int size, int board_size_px);
    void draw();
    void update();
};