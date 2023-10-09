#pragma once
#include<SFML/Graphics.hpp>
#include"menu.h"
#define MAX_NUM_OF_EACH_LEVEL 3
#define TOTAL_LEVELS 9
class Map
{
public:
	Map() {};
	~Map() {};

	void get_level_index(int selected_item_index)//ham nay lay selected_item_index ben modemenu de dat map
	{
		level_index = selected_item_index;
	}

	void set_map()//nhan vao gia tri level_index de nhap file hinh vo
	{
		std::string textture_name = "level" + std::to_string(level_index) + ".PNG";
		if (!level[level_index].loadFromFile(textture_name))
		{
			//lam gi do o day neu sai =))
		}
	}

	void drawto(sf::RenderWindow& window)
	{
		sf::Sprite map_game;
		level[level_index].setRepeated(true);
		map_game.setTexture(level[level_index]);
		map_game.setScale(sf::Vector2f(window.getSize().x/map_game.getGlobalBounds().width, window.getSize().y/map_game.getGlobalBounds().height));
		window.draw(map_game);
	}
private:
	sf::Texture level[TOTAL_LEVELS];
	int level_index=0;
};

