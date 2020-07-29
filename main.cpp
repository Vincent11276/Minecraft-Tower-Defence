#include<SFML/Graphics.hpp>
#include<iostream>	
using namespace std;




int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecraft Tower Defence");
	
	sf::Texture menuBackground_t;
	if(!menuBackground_t.loadFromFile("src/img/menu_backgroundd.png")) system("pause");
	sf::Sprite menuBackground(menuBackground_t);
	
	sf::Texture grassBlock_t;
	if(!grassBlock_t.loadFromFile("src/img/GrassBlock.jpg")) system("pause");
	sf::Sprite grassBlock(grassBlock_t);
	
	sf::Texture diamondShovel_t;
	if(!diamondShovel_t.loadFromFile("src/img/diamond_shovel.png")) system("pause");
	sf::Sprite diamondShovel(diamondShovel_t);
	
	sf::RectangleShape playButton(sf::Vector2f(200, 70));
	playButton.setOrigin(playButton.getGlobalBounds().width / 2, playButton.getGlobalBounds().height / 2);
	playButton.setPosition(window.getSize().x / 2, 600);
	playButton.setFillColor(sf::Color(0, 190, 0));
	playButton.setOutlineThickness(-2);
	playButton.setOutlineColor(sf::Color(25, 25, 25));
	
	sf::RectangleShape enemySpawnBox(sf::Vector2f(grassBlock.getGlobalBounds().width, grassBlock.getGlobalBounds().height));
	
	sf::RectangleShape enemy(sf::Vector2f(50, 50));
	
	sf::Vector2i tileMapDim(15, 10);
	sf::Vector2i tileMapPosition(0, 0);
	sf::Vector2i enemySpawnLocation;
	sf::Vector2i baseLocation;
	sf::Vector2i mobPath[30];
	
	bool tile_map[tileMapDim.y][tileMapDim.x];
	for(int y = 0; y < tileMapDim.y; y++) {
		for(int x = 0; x < tileMapDim.x; x++) {
			tile_map[y][x] = true;		
		}
	}
	
	bool playing = false;
	bool diggingMode = true;
	bool digging = false;
	
	
	
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					break;
				case sf::Event::MouseButtonPressed:
					if(playing) {
						if(event.mouseButton.button == sf::Mouse::Left) {
							digging = true;
						}
					}					
															
					break;			
				case sf::Event::MouseButtonReleased:
					if(!playing) {
						sf::Vector2i mouse = sf::Mouse::getPosition(window);
						if(playButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
							playing = true;
						}
					}
					break;
				case sf::Event::MouseMoved:
					sf::Vector2i mouse = sf::Mouse::getPosition(window);
					diamondShovel.setPosition(mouse.x, mouse.y);
			}
		}
		
		int speed = 0.1;
		
		
		enemy.move(speed, 0);
		
		
		
		window.clear();
		
		
		if(playing) {
			for(int y = 0; y < tileMapDim.y; y++) {
				for(int x = 0; x < tileMapDim.x; x++) {
					if(diggingMode) {
						if(digging) {
							sf::Vector2i mouse = sf::Mouse::getPosition(window);
							grassBlock.setPosition(tileMapPosition.x + (x*grassBlock.getGlobalBounds().width), 
												   tileMapPosition.y + (y*grassBlock.getGlobalBounds().height));
							if(grassBlock.getGlobalBounds().contains(mouse.x, mouse.y)) {
								tile_map[y][x] = false;
							}
						}				
					}
					if(tile_map[y][x] == true) {
						grassBlock.setPosition(tileMapPosition.x + (x*grassBlock.getGlobalBounds().width), 
											   tileMapPosition.y + (y*grassBlock.getGlobalBounds().height));
						window.draw(grassBlock);
					}		
				}
			}
			if(diggingMode) {
				window.draw(diamondShovel);
			}
			else {
				
			}
			
		}
		
		
		
		if(!playing) {
			window.draw(menuBackground);
			window.draw(playButton);
			
			window.draw(enemy);
		}
				
		window.display();
	}
	
	return 0;
}

