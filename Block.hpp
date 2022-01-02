#ifndef BLOCK_HPP_DEFINED
#define BLOCK_HPP_DEFINED

#include <SFML/Graphics.hpp>

class Block {
	public:
		Block(sf::Sprite);
		Block(int, int, sf::Sprite);
		~Block();

		sf::Sprite& get_sprite(void);
		void set_scale(float, float);
		void set_position(float posX, float posY);

		void move_down();
		void move_right();
		void move_left();

		bool down_is_legal_move(void);
		bool is_floor_level(void);

		int get_x(void);
		int get_y(void);

	private:
		sf::Sprite sprite;

		int x;
		int y;

		void update_sprite_position(void);
};

#endif
