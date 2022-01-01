#include <SFML/Graphics.hpp>
#include <vector>

// Block is 256 pixels in height and scaled down by 0.2.
#define BLOCK_LEN 51.2

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

class Shape {
	public:
		Shape();
		~Shape();

		void add_block(Block* _block);
		void draw(sf::RenderWindow& window);

		void move_down();
		void move_right();
		void move_left();

	private:
		std::vector<Block*> blocks;
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
	// TODO Update "bare" x/y in addition to updating Sprite x/y
	sprite.move(0, BLOCK_LEN);
}

void Block::move_right()
{
	// TODO Update "bare" x/y in addition to updating Sprite x/y
	sprite.move(BLOCK_LEN, 0);
}

void Block::move_left()
{
	// TODO Update "bare" x/y in addition to updating Sprite x/y
	sprite.move(-(BLOCK_LEN), 0);
}

Shape::Shape()
{
}

Shape::~Shape()
{
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

void do_move(float& timer, Shape& shape)
{
	float delay = 0.2;

	if (g_game.move_right) {
		shape.move_right();
		g_game.move_right = 0;
	}

	if (g_game.move_left) {
		shape.move_left();
		g_game.move_left = 0;
	}

	if (timer > delay) {
		shape.move_down();
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

	sf::RectangleShape floor;
	floor.setSize(sf::Vector2f(BLOCK_LEN * 10, 10));
	floor.setFillColor(sf::Color::Black);
	floor.setPosition(BLOCK_LEN, BLOCK_LEN * 14);

	sf::RectangleShape roof;
	roof.setSize(sf::Vector2f(BLOCK_LEN * 10, 10));
	roof.setFillColor(sf::Color::Black);
	roof.setPosition(BLOCK_LEN, BLOCK_LEN);

	Shape shape;

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
	block_blue.set_position(BLOCK_LEN, 0);
	block_green.set_position(0, BLOCK_LEN);
	block_green2.set_position(BLOCK_LEN, BLOCK_LEN);

	shape.add_block(&block_blue);
	shape.add_block(&block_red);
	shape.add_block(&block_green);
	shape.add_block(&block_green2);

	while (window.isOpen())
	{
		handle_events(window);

		time = clock.getElapsedTime().asSeconds();
		timer = timer + time;
		clock.restart();

		do_move(timer, shape);

		g_game.move_right = 0;
		g_game.move_left = 0;

do_draw:
		window.clear();
		window.draw(background_sprite);
		window.draw(floor);
		window.draw(roof);
		shape.draw(window);
		window.display();
	}

	return 0;
}
