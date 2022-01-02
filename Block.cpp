#include "Block.hpp"
#include "Game.hpp"

Block::Block(sf::Sprite _s)
	: sprite{std::move(_s)}
{
}

Block::Block(int _x, int _y, sf::Sprite _s)
	: x{_x}, y{_y}, sprite{std::move(_s)}
{}

Block::~Block()
{}

sf::Sprite& Block::get_sprite(void)
{
	return sprite;
}

void Block::set_scale(float scaleX, float scaleY)
{
	sprite.setScale(scaleX, scaleY);
}

void Block::set_position(float posX, float posY)
{
	x = posX;
	y = posY;
	update_sprite_position();
}

void Block::move_down()
{
	y = y + 1;
	update_sprite_position();
}

void Block::move_right()
{
	x = x + 1;
	update_sprite_position();
}

void Block::move_left()
{
	x = x - 1;
	update_sprite_position();
}

void Block::update_sprite_position(void)
{
	// Always add BLOCK_LEN to cause 0,0 to be a bit further inside the
	// window.
	sprite.setPosition(BLOCK_LEN + x * BLOCK_LEN, BLOCK_LEN + y * BLOCK_LEN);
}

bool Block::is_floor_level(void)
{
	return y == SLOTS_HEIGHT - 1;
}

int Block::get_x(void)
{
	return x;
}

int Block::get_y(void)
{
	return y;
}

bool Block::down_is_legal_move(void)
{
	if (0 == g_game.block_slots[x][y + 1]) {
		return true;
	}

	return false;
}
