#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Block.hpp"
#include "Shape.hpp"

#define DEBUG_ON 0

// Block is 256 pixels in height and scaled down by 0.2.
#define BLOCK_LEN 51.2

#define SLOTS_HEIGHT 13
#define SLOTS_WIDTH 10

class Game {
	public:
		Shape* falling_shape;
		Block* block_slots[SLOTS_WIDTH][SLOTS_HEIGHT] = {0};
		int move_right = 0;
		int move_left = 0;
		int pending_shape_spawn = 0;
};

extern Game g_game;

#endif
