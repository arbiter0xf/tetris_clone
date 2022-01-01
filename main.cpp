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
		Block(sf::Sprite);
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

		void update_sprite_position(void);
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
	sprite.setPosition(x * BLOCK_LEN, y * BLOCK_LEN);
}

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

Game g_game;
std::vector<Shape*> all_shapes;

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
		shape->move_down();
		timer = 0;
	}
}

#if 0
bare_xy_to_drawable_xy()
#endif

void spawn_shape(int x, int y, sf::Texture& texture)
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

	spawn_shape(1, 1, block_blue_texture);

	while (window.isOpen())
	{
		handle_events(window);

		time = clock.getElapsedTime().asSeconds();
		timer = timer + time;
		clock.restart();

		for (Shape* shape : all_shapes) {
			do_move(timer, shape);
		}

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
