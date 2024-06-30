#include "Board.hpp"
#include <algorithm>
#include <string>

Board::Board() {
    Board(0, 0);
}

Board::Board(int size, int board_size_px) {
    this->size = size;
    this->piece_size = board_size_px / size;
    is_black_turn = true;
    ko_rule = {-1, -1};
    black_captured = 0;
    white_captured = 0;
    for (int i = 0; i < size; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < size; j++) {
            Tile temp(0, piece_size, raylib::Vector2(j*piece_size, i*piece_size));
            row.push_back(temp);
        }
        board.push_back(row);
        std::vector<int> state_row(size);
        states.push_back(state_row);
    }
}

void Board::update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { // placing a new piece
        raylib::Vector2 mouse_pos = GetMousePosition();
        // x,y of piece being clicked
        int x = static_cast<int>(mouse_pos.x) / piece_size;
        int y = static_cast<int>(mouse_pos.y) / piece_size;
        if (x < size && y < size && states[y][x] == 0 && !(y == ko_rule[0] && x == ko_rule[1])) {
            // check legality
            std::vector<std::vector<int>> copy_states(states); // if revert is needed
            
            // add tile to board
            if (is_black_turn) {
                states[y][x] = 1;
            } else {
                states[y][x] = 2;
            }
            
            // check death of other sides groups
            std::vector<std::vector<int>> to_remove;
            for (auto lib : get_liberties({y,x})) {
                if (states[lib[0]][lib[1]] != 0 && states[lib[0]][lib[1]] != states[y][x]) { // if opposite colour
                    std::vector<std::vector<int>> group = get_group({lib[0], lib[1]});
                    // check if any stone in the group has a liberty
                    bool keep = false;
                    for (auto stone : group) {
                        for (auto lib2 : get_liberties({stone[0], stone[1]})) {
                            if (states[lib2[0]][lib2[1]] == 0) {
                                keep = true;
                                goto skip;
                            }
                        }
                    }
                    skip:
                    if (!keep) {
                        for (auto stone : group) {
                            to_remove.push_back(stone);
                        }
                    }
                }
            }
            for (auto stone : to_remove) {
                states[stone[0]][stone[1]] = 0;
            }
            // ko rule
            if (to_remove.size() == 1) {
                ko_rule = to_remove[0];
            } else {
                ko_rule = {-1, -1};
            }
            if (to_remove.size() > 0) {
                if (is_black_turn) {
                    black_captured += to_remove.size();
                } else {
                    white_captured += to_remove.size();
                }
                is_black_turn = !is_black_turn;
            }
            else { // if no capture, check if you arent removing your own stones
                std::vector<std::vector<int>> group = get_group({y,x});
                bool keep = false;
                for (auto stone : group) {
                    for (auto lib : get_liberties({stone[0], stone[1]})) {
                        if (states[lib[0]][lib[1]] == 0) {
                            keep = true;
                            goto skip2;
                        }
                    }
                }
                skip2:
                if (keep) {
                    is_black_turn = !is_black_turn;
                } else {
                    states = copy_states;
                }
            }
        }
        
    }
    // updating tiles
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j].set_state(states[i][j]);
        }
    }
}

void Board::draw() {
    // draw grid
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            DrawRectangleLines(i*piece_size + piece_size/2, j*piece_size + piece_size/2, piece_size, piece_size, BLACK);
        }
    }
    // draw circles / hovering
    raylib::Vector2 mouse_pos = GetMousePosition();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j].draw(is_black_turn, mouse_pos);
        }
    }
    // draw info
    raylib::DrawText("Black Captured: " + std::to_string(black_captured), 25, 760, 20, BLACK);
    raylib::DrawText("White Captured: " + std::to_string(white_captured), 300, 760, 20, BLACK);
}

std::vector<std::vector<int>> Board::get_liberties(std::vector<int> pos) { // y, x, seems to work
    std::vector<std::vector<int>> liberties;
    if (pos[0] > 0) { // up
        liberties.push_back({pos[0] - 1, pos[1]});
    }
    if (pos[0] < size - 1) { // down
        liberties.push_back({pos[0] + 1, pos[1]});
    }
    if (pos[1] > 0) { // left
        liberties.push_back({pos[0], pos[1] - 1});
    }
    if (pos[1] < size - 1) { // right
        liberties.push_back({pos[0], pos[1] + 1});
    }
    return liberties;
}

std::vector<std::vector<int>> Board::get_group(std::vector<int> pos) { // find group of same colour as pos
    std::vector<std::vector<int>> group;
    group.push_back(pos);
    int size;
    int change;
    do { // keep checking all stones liberties for new pieces until no more
        size = group.size();
        std::vector<std::vector<int>> to_add;
        for (auto stone : group) {
            for (auto liberty : get_liberties(stone)) {
                if (states[liberty[0]][liberty[1]] == states[pos[0]][pos[1]]) {
                    to_add.push_back(liberty);
                }
            }
        }
        for (auto stone : to_add) {
            if (std::find(group.begin(), group.end(), stone) == group.end()) {
                group.push_back(stone);
            }
        }
    } while (group.size() - size > 0);
    return group;
}