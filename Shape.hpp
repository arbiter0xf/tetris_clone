#ifndef SHAPE_HPP_DEFINED
#define SHAPE_HPP_DEFINED

#include "Block.hpp"

class Shape {
	public:
		Shape();
		~Shape();

		void add_block(Block* _block);
		void draw(sf::RenderWindow& window);

		void move_down();
		void move_right();
		void move_left();

		bool down_is_legal_move(void);
		bool is_floor_level(void);

		void on_movement_stop(void);

		std::vector<int> get_x_coords_of_blocks(void);
		std::vector<int> get_y_coords_of_blocks(void);

	private:
		std::vector<Block*> blocks;
};

#endif
