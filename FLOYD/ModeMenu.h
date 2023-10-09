#pragma once
#include"SFML/Graphics.hpp"
#define MAX_NUMS_OF_LEVEL 9
class ModeMenu
{
public:
	ModeMenu(int width, int height)
	{
		if (!font.loadFromFile("arial.ttf"))
		{

		}
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("easy 1");
		menu[0].setPosition(width / (MAX_NUMS_OF_LEVEL  +1) * 1, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 1);

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("easy 2");
		menu[1].setPosition(width / (MAX_NUMS_OF_LEVEL +1) * 1, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 2);

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("easy 3");
		menu[2].setPosition(width / (MAX_NUMS_OF_LEVEL  +1) * 1, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 3);

		menu[3].setFont(font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setString("medium 1");
		menu[3].setPosition(width / (MAX_NUMS_OF_LEVEL /2 +1) * 2, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 1);

		menu[4].setFont(font);
		menu[4].setFillColor(sf::Color::White);
		menu[4].setString("medium 2");
		menu[4].setPosition(width / (MAX_NUMS_OF_LEVEL /2 +1 ) * 2, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 2);

		menu[5].setFont(font);
		menu[5].setFillColor(sf::Color::White);
		menu[5].setString("medium 3");
		menu[5].setPosition(width / (MAX_NUMS_OF_LEVEL /2 +1) * 2, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 3);

		menu[6].setFont(font);
		menu[6].setFillColor(sf::Color::White);
		menu[6].setString("hard 1");
		menu[6].setPosition(width / (MAX_NUMS_OF_LEVEL /3 + 1) * 3, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 1);

		menu[7].setFont(font);
		menu[7].setFillColor(sf::Color::White);
		menu[7].setString("hard 2");
		menu[7].setPosition(width / (MAX_NUMS_OF_LEVEL /3 + 1) * 3, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 2);

		menu[8].setFont(font);
		menu[8].setFillColor(sf::Color::White);
		menu[8].setString("hard 3");
		menu[8].setPosition(width / (MAX_NUMS_OF_LEVEL /3+ 1) * 3, height / (MAX_NUMS_OF_LEVEL/3 + 1) * 3);

		selected_item_index = 0;
	}
	void moveup()
	{
		if (selected_item_index > 0)//menu main bat dau tu 0
		{
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index--;
			menu[selected_item_index].setFillColor(sf::Color::Red);
		}
	}
	void movedown()
	{
		if (selected_item_index < 8)//menu main bat dau tu 0
		{
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index++;
			menu[selected_item_index].setFillColor(sf::Color::Red);
		}
	}
	void moveleft()
	{
		if (selected_item_index - 3 >= 0)
		{
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index-=3;
			menu[selected_item_index].setFillColor(sf::Color::Red);
		}
	}
	void moveright()
	{
		if (selected_item_index + 3 <=8)
		{
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index += 3;
			menu[selected_item_index].setFillColor(sf::Color::Red);
		}
	}
	void drawto(sf::RenderWindow& window)
	{
		for (int i = 0; i < MAX_NUMS_OF_LEVEL; i++)
		{
			window.draw(menu[i]);
		}
	}
	int get_item_index()
	{
		return selected_item_index;
	}
private:
	sf::Text menu[MAX_NUMS_OF_LEVEL];
	sf::Font font;
	int selected_item_index;
};

