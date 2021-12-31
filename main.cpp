#include <SFML/Graphics.hpp>

void handle_events(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

int main()
{
	sf::Texture block_blue_texture;
	sf::Texture background_texture;

	block_blue_texture.loadFromFile("assets/tetris_blue_block.png");
	background_texture.loadFromFile("assets/tetris_background.png");

	sf::Sprite block_blue_sprite(block_blue_texture);
	sf::Sprite background_sprite(background_texture);

	sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris clone");

	block_blue_sprite.setScale(0.5, 0.5);

	while (window.isOpen())
	{
		handle_events(window);

		window.clear();
		window.draw(background_sprite);
		window.draw(block_blue_sprite);
		window.display();
	}

	return 0;
}
