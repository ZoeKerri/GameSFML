#include "menu.h"

Menu::Menu() {};
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 1));//width là trục x và height là trục y

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("How to play");
	menu[1].setOrigin( menu[1].getGlobalBounds().width / 2,menu[1].getGlobalBounds().height / 2);//setOrigin truoc thi no se lay toa do goc la tan cung ben trai cua top thay doi top thi Origin cung thay doi
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 2));//so items cua man hinh chi co 3 thoi nen tru ra cho no nhin dep hon

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getGlobalBounds().width / 2,  menu[2].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 3));
	
	Select_Item_index = 0;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)// gọi hàm của class từ 1 file .h thì ta phải thêm kiểu trả về trước namespace để chương trình biết nó kiểu trả về là gì
// nếu để không thì nó k hiểu 
{
		for (int i = 0; i < MAX_NUM_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
}

void Menu::moveup()
{
	if (Select_Item_index  > 0)//menu main bat dau tu 0
	{
		menu[Select_Item_index].setFillColor(sf::Color::White);
		Select_Item_index--;
		menu[Select_Item_index].setFillColor(sf::Color::Red);
	}
}
void Menu::movedown()
{
	if (Select_Item_index < 2)//menu main bat dau tu 0
	{
		menu[Select_Item_index].setFillColor(sf::Color::White);
		Select_Item_index++;
		menu[Select_Item_index].setFillColor(sf::Color::Red);
	}
}
int Menu::getSelectedItem()
{
	return Select_Item_index;
}

