#include "Game.hpp"
#include "Shape.hpp"

Shape::Shape()
{
}

Shape::~Shape()
{
	for (Block* block : blocks) {
		delete block;
	}
}

void Shape::draw(sf::RenderWindow& window)
{
	for (Block* block : blocks) {
		window.draw(block->get_sprite());
	}
}

void Shape::add_block(Block* _block)
{
	blocks.push_back(_block);
}

void Shape::move_down()
{
	for (Block* block : blocks) {
		block->move_down();
	}
}

void Shape::move_right()
{
	for (Block* block : blocks) {
		block->move_right();
	}
}

void Shape::move_left()
{
	for (Block* block : blocks) {
		block->move_left();
	}
}

bool Shape::down_is_legal_move(void)
{
	for (Block* block : blocks) {
		if (!block->down_is_legal_move()) {
			return false;
		}
	}

	return true;
}

bool Shape::is_floor_level(void)
{
	bool floor_level = false;

	for (Block* block : blocks) {
		floor_level = block->is_floor_level();

		if (floor_level) {
			return floor_level;
		}
	}

	return floor_level;
}

std::vector<int> Shape::get_x_coords_of_blocks(void)
{
	std::vector<int> v;

	for (Block* block : blocks) {
		v.push_back(block->get_x());
	}

	return v;
}

std::vector<int> Shape::get_y_coords_of_blocks(void)
{
	std::vector<int> v;

	for (Block* block : blocks) {
		v.push_back(block->get_y());
	}

	return v;
}

void Shape::on_movement_stop()
{
	for (Block* block : blocks) {
		int x = block->get_x();
		int y = block->get_y();

#if DEBUG_ON
		printf("Setting block into slot [%d][%d]\n", x, y);
#endif

		g_game.block_slots[x][y] = block;
	}
}
