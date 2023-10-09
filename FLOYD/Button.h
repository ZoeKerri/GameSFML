#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"


class Button
{
public:
	Button() {};
	void set_Button(std::string name, int char_size, float rad, sf::Color bgcolor, sf::Color textcolor, sf::CircleShape button, sf::Text text)//dat thuoc tinh
	{
		sf::Font font;
		if (!font.loadFromFile("arial.ttf"))
		{
			//do sth
		}
		text.setFont(font);
		text.setString(name);
		text.setFillColor(textcolor);
		text.setCharacterSize(char_size);
		
		button.setRadius(rad);
		button.setFillColor(bgcolor);

	}

	void setBgColor(sf::Color color,sf::CircleShape button)
	{
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void setPositon(sf::Vector2f pos, int rad, sf::CircleShape button, sf::Text text) //input: toa do cua noi minh can nhan, va ban kinh hinh tron
	{
		//tọa độ Oxy không phải là tâm hình tròn mà là nó vẽ từ tọa độ đó một hình tròn có đường kính mà nó nhận tức Oxy cách tâm hình tròn 1 khoảng bằng r 
		button.setPosition(pos.x-rad,pos.y-rad);

		//con doi voi text thi ta lay tam cua hinh roi dat vao thoi o day tru ra do dai cua chu so de co the cho no ngay chinh giua tam luon
		float textX = pos.x  - (text.getGlobalBounds().width) / 2;
		float textY = pos.y - (text.getGlobalBounds().height) / 2;

		text.setPosition(textX, textY);
	}

	
	void draw(sf::RenderWindow& window,sf::CircleShape button, sf::Text text)
	{
		window.draw(button);
		window.draw(text);
	}
	void set_Name(std::string name)
	{
		text.setString(name);
	}
	 //getlocalbounds nhan gia tri ve cac kich thuoc va vi tri cua hinh hoac sprite, text ma no nhan
	bool isMouseOver(sf::RenderWindow& window, sf::CircleShape button)//kiem tra xem chuot co nam ngoai cai hinh khong
		//lay toa do cua chuot
		//ham getGlobalBounds se nhan gia tri ve kich thuoc va vi tri cua hinh ma no duoc goi 
		//ham contains giup kiem tra xem bien nam trong no co nam trong gia tri nao cua getGlabalBounds khong
		// chua hieu ro ve getLocal getGlobal ntn ;-;
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		return button.getGlobalBounds().contains(static_cast <float> (mousePos.x),static_cast <float> (mousePos.y));
	}
private:
	sf::CircleShape button;
	sf::Text text;
};