#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Result_Window
{
public:
	Result_Window(int width, int height,int posX,int posY,int charsize,sf::Font textfont, sf::Color textcolor,sf::Color childwindowcolor)
	{
		childwindow.setSize(sf::Vector2f(static_cast <float> (width), static_cast <float> (height)));
		childwindow.setPosition(sf::Vector2f(static_cast <float> (posX), static_cast <float> (posY)));
		childwindow.setFillColor(childwindowcolor);
		sf::Vector2f origin(static_cast <float> (width/2), static_cast <float> (height/2));//đặt tọa độ gốc
		childwindow.setOrigin(origin);

		font = textfont;//nếu không gán cho font thì khi thoát khỏi hàm biến text font sẽ biến mất do nó chỉ là tham số tạm thời thôi 
		text.setFont(font);
		text.setFillColor(textcolor);
		text.setCharacterSize(charsize);
		text.setString("Nothing here");
		text.setPosition(childwindow.getPosition().x - childwindow.getSize().x/2+text.getGlobalBounds().width, childwindow.getPosition().y - childwindow.getSize().y / 2 + text.getGlobalBounds().height);
		//neu muon can trai thi tru giong ben y
		text.setOrigin( text.getLocalBounds().width , text.getLocalBounds().height);//đặt tọa độ gốc 
	}
	
	void set_text_origin()
	{
		text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height/2);//đặt tọa độ gốc 
	}

	void draw_to(sf::RenderWindow& window)
	{
		window.draw(childwindow);
		window.draw(text);
		if (is_press == 1) window.draw(result);
	}
	
	void set_trace_to_text(int start,int end,std::vector <int> matrix_trace)
	{
		string start_point = to_string(start);
		string end_point = to_string(end);
		text.setString("You need to go from " + start_point + " to " + end_point + "\nYour trace:");
		int size = matrix_trace.size();
		string trace = text.getString();
		for (int i = 0; i < size; i++)
		{
			if(i==0) trace+= to_string(matrix_trace[i]);
			else
			{
				trace += "->" + to_string(matrix_trace[i]);
			}
		}
		text.setString(trace);
	}

	void win_lose(int start, int end, std::vector <int> matrix_trace,queue <int> result_trace,bool is_win)
	{
		is_press = 1;//dung de hien you win you lose
		string start_point = to_string(start);
		string end_point = to_string(end);
		text.setString("You need to go from " + start_point + " to " + end_point + "\nYour trace:");
		int your_trace_size = matrix_trace.size();
		string trace = text.getString();
		int result_trace_size = result_trace.size();
		queue<int> temp = result_trace;
		for (int i = 0; i < your_trace_size; i++)
		{
			if (i == 0) trace += to_string(matrix_trace[i]);
			else
			{
				trace += "->" + to_string(matrix_trace[i]);
			}
		}
		trace += "\nThe result:";
		for (int i = 0; i < result_trace_size; i++)
		{
			if (i == 0) 
			{
				trace += to_string(temp.front());
				temp.pop();
				
			}
			else
			{
				trace += "->" + to_string(temp.front());
				temp.pop();
			}
		}
		text.setString(trace);
		if (is_win)
		{
			result.setFont(font);
			result.setFillColor(sf::Color::Red);
			result.setCharacterSize(20);
			result.setString("YOU WIN");
			result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y+text.getGlobalBounds().height/2);
			//neu muon can trai thi tru giong ben y
			result.setOrigin(result.getLocalBounds().width/2, result.getLocalBounds().height/2);
		}
		else
		{
			result.setFont(font);
			result.setFillColor(sf::Color::Red);
			result.setCharacterSize(20);
			result.setString("YOU LOSE");
			result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height/2 );
			//neu muon can trai thi tru giong ben y
			result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);
		}
	}
	bool is_Over_Window(sf::RenderWindow& window)
	{
		sf::Vector2i mouPos = sf::Mouse::getPosition(window);
		sf::Vector2f child_size (childwindow.getSize().x/2,childwindow.getSize().y/2);
		sf::FloatRect ChildRect(static_cast <sf::Vector2f> (childwindow.getPosition()-child_size), childwindow.getSize());
		if (ChildRect.contains(static_cast <sf::Vector2f> (mouPos))) return true;
		return false;
	}

	void set_position(sf::Vector2f mouse_pos)
	{
		if (is_dragging)
		{
			childwindow.setPosition(mouse_pos);
		}
	}

	void is_Drag()
	{
		is_dragging = true;
	}

	void is_Drop()
	{
		is_dragging = false;
	}

	int get_is_dragging()
	{
		return is_dragging;
	}
	void reset_is_press()
	{
		is_press = 0;
	}
	
	void set_Text_Pos()
	{
		text.setPosition(childwindow.getPosition().x - childwindow.getSize().x / 2 + text.getGlobalBounds().width, childwindow.getPosition().y - childwindow.getSize().y / 2 + text.getGlobalBounds().height);
		text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
		result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height / 2);
	}


private:
	sf::RectangleShape childwindow;
	sf::Text text;
	sf::Text result;
	sf::Font font;
	int is_press = 0;//dung de hien you win, you lose
	bool is_dragging=false;
};
//hàm này sẽ đc hàm creat_button kế thừa 
//dùng để vẽ 1 hình chữ nhật màu đen tầm 60x60 trong đó có chứa chữ và nội dung ma trận đc click và khi mà có chuột rê vào hình thì có thể kéo thả hình còn không thì thôi 