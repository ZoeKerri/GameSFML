#include"SFML/Graphics.hpp"
#define MAX_NUMS_OF_MAIN_MENU 3
class mainmenu
{
public:
	mainmenu(int width,int height, sf::Font font)
	{
		position[0].x = width / 2;
		position[0].y = height / (MAX_NUMS_OF_MAIN_MENU + 1) * 1;//dat vi tri cua cac phan tu menu

		position[1].x = width / 2;
		position[1].y = height / (MAX_NUMS_OF_MAIN_MENU + 1) * 2;

		position[2].x = width / 2;
		position[2].y = height / (MAX_NUMS_OF_MAIN_MENU + 1) * 3;

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("Play");
		menu[0].setPosition(position[0]);

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Play");
		menu[1].setPosition(position[1]);

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Play");
		menu[2].setPosition(position[2]);

		selected_items_index = 0;
	}


	int get_Selected_Item()//lay vi tri index hien tai de thuc hien lenh nhan enter hay lam gi khac
	{
		return selected_items_index;
	}

	void moveup()
	{
		if (selected_items_index>0)
		{
			menu[selected_items_index].setFillColor(sf::Color::White);
			selected_items_index--;
			menu[selected_items_index].setFillColor(sf::Color::Red);
		}
	}


	void movedown()
	{
		if (selected_items_index < 2)
		{
			menu[selected_items_index].setFillColor(sf::Color::White);
			selected_items_index++;
			menu[selected_items_index].setFillColor(sf::Color::Red);
		}
	}
	void drawto(sf::RenderWindow &window)//ve len man hinh window
	{
		for (int i = 0; i < MAX_NUMS_OF_MAIN_MENU; i++)
		{
			window.draw(menu[i]);
		}
	}
protected:
	sf::Vector2f position[3];// bien nay co the duoc dung de lam menu cua do kho
private:
	sf::Text menu[MAX_NUMS_OF_MAIN_MENU];
	int selected_items_index;
};
