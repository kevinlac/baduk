#include "raylib-cpp.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include <unordered_map>

int main() {
	// set up the window
	SetTargetFPS(FLAG_VSYNC_HINT);
	int BOARD_SIZE = 760;
	int WIDTH = 760;
	int HEIGHT = 800;
	raylib::Window window(WIDTH, HEIGHT, "Baduk");

	int state = 0; // 0 = menu, 1 = playing

	Board board(19, BOARD_SIZE);

	std::vector<Button> buttons;
	buttons.push_back(Button("19x19", 50, 19, 10, WHITE, LIGHTGRAY, BLACK, {530, 350}));
	buttons.push_back(Button("13x13", 50, 13, 10, WHITE, LIGHTGRAY, BLACK, {285, 350}));
	buttons.push_back(Button("9x9", 50, 9, 10, WHITE, LIGHTGRAY, BLACK, {80, 350}));

	std::unordered_map<int, std::vector<std::vector<int>>> numdots;
	numdots[9] = {{210, 210}, {378, 378}, {546, 546}, {210, 546}, {546, 210}};
	numdots[13] = {{203, 203}, {377, 377}, {551, 551}, {203, 551}, {551, 203}};
	numdots[19] = {{140, 140}, {380, 380}, {620, 620}, {140, 620}, {140, 380}, {380, 140}, {380, 620}, {620, 140}, {620, 380}};
	std::vector<std::vector<int>> dots;

	// game loop
	while (!WindowShouldClose()) {
		// drawing
		BeginDrawing();
		ClearBackground({232,204,113});
		switch (state)
		{
		case 0:
			{
			raylib::Vector2 mouse_pos = GetMousePosition();
			for (auto button : buttons) {
				button.draw(mouse_pos);		
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				for (auto button : buttons) {
					if (button.clicked(mouse_pos)) {
						board = Board(button.get_ID(), BOARD_SIZE);
						dots = numdots[button.get_ID()];
						state = 1;
						break;
					}
				}
			}
			}
			break;
		case 1:
			for (auto point : dots) {
				DrawCircle(point[0], point[1], 4, BLACK);
			}

			board.update();
			board.draw();
			break;
		}
		EndDrawing();
	}

	// cleanup
	CloseWindow();
}