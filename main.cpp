#include <SFML/Graphics.hpp>
#include <vector>

// Block is 256 pixels in height and scaled down by 0.2.
#define JUMP_MOVEMENT 51.2

class Game {
	public:
		int move_right = 0;
		int move_left = 0;
};

class Block {
	public:
		Block(int, int, sf::Sprite);
		~Block();

		sf::Sprite& get_sprite(void);
		void set_scale(float, float);
		void set_position(float posX, float posY);

		void move_down();
		void move_right();
		void move_left();

	private:
		sf::Sprite sprite;

		int x;
		int y;
};

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
	sprite.setPosition(posX, posY);
}

void Block::move_down()
{
	sprite.move(0, JUMP_MOVEMENT);
}

void Block::move_right()
{
	sprite.move(JUMP_MOVEMENT, 0);
}

void Block::move_left()
{
	sprite.move(-(JUMP_MOVEMENT), 0);
}

class Shape {
	public:
		Shape();
		~Shape();
	private:
};

Game g_game;

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

void do_move(float& timer, std::vector<Block*>& all_blocks)
{
	float delay = 1.0;

	if (g_game.move_right) {
		for (Block* block : all_blocks) {
			block->move_right();
		}

		g_game.move_right = 0;
	}

	if (g_game.move_left) {
		for (Block* block : all_blocks) {
			block->move_left();
		}

		g_game.move_left = 0;
	}

	if (timer > delay) {
		// TODO wrap move so that sprite x/y is updated at the
		// same time as "bare" x/y.
		for (Block* block : all_blocks) {
			block->move_down();
		}

		timer = 0;
	}
}

#if 0
bare_xy_to_drawable_xy()
#endif

int main()
{
	float time = 0;
	float timer = 0;
	sf::Clock clock;

	std::vector<Block*> all_blocks;

	sf::Texture block_blue_texture;
	sf::Texture block_red_texture;
	sf::Texture block_green_texture;
	sf::Texture block_green_texture2;
	sf::Texture background_texture;

	block_blue_texture.loadFromFile("assets/tetris_blue_block.png");
	block_red_texture.loadFromFile("assets/tetris_red_block.png");
	block_green_texture.loadFromFile("assets/tetris_green_block.png");
	background_texture.loadFromFile("assets/tetris_background.png");

	sf::Sprite block_blue_sprite(block_blue_texture);
	sf::Sprite block_red_sprite(block_red_texture);
	sf::Sprite block_green_sprite(block_green_texture);
	sf::Sprite block_green_sprite2(block_green_texture);
	sf::Sprite background_sprite(background_texture);

	Block block_blue(0, 0, block_blue_sprite);
	Block block_red(0, 1, block_red_sprite);
	Block block_green(1, 0, block_green_sprite);
	Block block_green2(1, 1, block_green_sprite);

	sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris clone");

	block_blue.set_scale(0.2, 0.2);
	block_red.set_scale(0.2, 0.2);
	block_green.set_scale(0.2, 0.2);
	block_green2.set_scale(0.2, 0.2);

	block_red.set_position(0, 0);
	block_blue.set_position(JUMP_MOVEMENT, 0);
	block_green.set_position(0, JUMP_MOVEMENT);
	block_green2.set_position(JUMP_MOVEMENT, JUMP_MOVEMENT);

	all_blocks.push_back(&block_blue);
	all_blocks.push_back(&block_red);
	all_blocks.push_back(&block_green);
	all_blocks.push_back(&block_green2);

	while (window.isOpen())
	{
		handle_events(window);

		time = clock.getElapsedTime().asSeconds();
		timer = timer + time;
		clock.restart();

		do_move(timer, all_blocks);

		g_game.move_right = 0;
		g_game.move_left = 0;

do_draw:
		window.clear();
		window.draw(background_sprite);
		for (Block* block : all_blocks) {
			window.draw(block->get_sprite());
		}
		window.display();
	}

	return 0;
}
