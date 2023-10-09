#pragma once
#include"SFML/Graphics.hpp"
#define MAX_NUM_OF_ITEMS 3
class Menu
{
public:
	Menu(float width, float height);
	Menu();
	~Menu();
	void draw(sf::RenderWindow& window);
	void moveup();
	void movedown();
	int getSelectedItem();
protected:
	int Select_Item_index;
private:
	sf::Font font;
	sf::Text menu[MAX_NUM_OF_ITEMS];

};

