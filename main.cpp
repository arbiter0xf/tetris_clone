#include <SFML/Graphics.hpp>
#include <vector>

#include "Block.hpp"
#include "Game.hpp"
#include "Shape.hpp"

std::vector<Shape*> all_shapes; // TODO move inside Game

void handle_events(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (sf::Event::KeyPressed == event.type) {
			if (sf::Keyboard::Right == event.key.code) {
				g_game.move_right = 1;
			} else if (sf::Keyboard::Left == event.key.code) {
				g_game.move_left = 1;
			}
		}
	}
}

void do_move(float& timer, Shape* shape)
{
	float delay = 1.0;

	if (g_game.move_right) {
		shape->move_right();
		g_game.move_right = 0;
	}

	if (g_game.move_left) {
		shape->move_left();
		g_game.move_left = 0;
	}

	if (timer > delay) {
		if (shape->is_floor_level()) {
			shape->on_movement_stop();
			g_game.falling_shape = 0;
			g_game.pending_shape_spawn = 1;
			goto reset_timer;
		}

		if (!shape->down_is_legal_move()) {
			shape->on_movement_stop();
			g_game.falling_shape = 0;
			g_game.pending_shape_spawn = 1;
			goto reset_timer;
		}

		shape->move_down();

reset_timer:
		timer = 0;
	}
}

#if 0
bare_xy_to_drawable_xy()
#endif

Shape* spawn_shape(int x, int y, sf::Texture& texture)
{
	const int blocks_amount = 4;

	Shape* shape = new Shape();
	sf::Sprite sprite(texture);
	Block* new_blocks[blocks_amount];

	for (int i = 0; i < blocks_amount; i++) {
		new_blocks[i] = new Block(sprite);
	}

	new_blocks[0]->set_position(x + 0, y + 0);
	new_blocks[1]->set_position(x + 1, y + 0);
	new_blocks[2]->set_position(x + 0, y + 1);
	new_blocks[3]->set_position(x + 1, y + 1);

	new_blocks[0]->set_scale(0.2, 0.2);
	new_blocks[1]->set_scale(0.2, 0.2);
	new_blocks[2]->set_scale(0.2, 0.2);
	new_blocks[3]->set_scale(0.2, 0.2);

	shape->add_block(new_blocks[0]);
	shape->add_block(new_blocks[1]);
	shape->add_block(new_blocks[2]);
	shape->add_block(new_blocks[3]);

	all_shapes.push_back(shape);

	g_game.pending_shape_spawn = 0;

	return shape;
}

int main()
{
	float time = 0;
	float timer = 0;
	sf::Clock clock;

	sf::RectangleShape floor;
	floor.setSize(sf::Vector2f(BLOCK_LEN * 10, 10));
	floor.setFillColor(sf::Color::Black);
	floor.setPosition(BLOCK_LEN, BLOCK_LEN * 14);

	sf::RectangleShape roof;
	roof.setSize(sf::Vector2f(BLOCK_LEN * 10, 10));
	roof.setFillColor(sf::Color::Black);
	roof.setPosition(BLOCK_LEN, BLOCK_LEN);

	sf::Texture block_blue_texture;
	sf::Texture block_red_texture;
	sf::Texture block_green_texture;
	sf::Texture block_green_texture2;
	sf::Texture background_texture;

	block_blue_texture.loadFromFile("assets/tetris_blue_block.png");
	block_red_texture.loadFromFile("assets/tetris_red_block.png");
	block_green_texture.loadFromFile("assets/tetris_green_block.png");
	background_texture.loadFromFile("assets/tetris_background.png");

	sf::Sprite background_sprite(background_texture);

	sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris clone");

	g_game.pending_shape_spawn = 1;

	while (window.isOpen())
	{
		handle_events(window);

		time = clock.getElapsedTime().asSeconds();
		timer = timer + time;
		clock.restart();

		if (g_game.pending_shape_spawn) {
			g_game.falling_shape = spawn_shape(0, 0, block_blue_texture);
		}

		do_move(timer, g_game.falling_shape);

		g_game.move_right = 0;
		g_game.move_left = 0;

do_draw:
		window.clear();
		window.draw(background_sprite);
		window.draw(floor);
		window.draw(roof);
		for (Shape* shape : all_shapes) {
			shape->draw(window);
		}
		window.display();
	}

	for (Shape* shape : all_shapes) {
		delete shape;
	}

	return 0;
}
