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

	void set_text_origin_demo()
	{
		text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);//đặt tọa độ gốc 
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

	void set_trace_to_text_demo(int start, int end, std::vector <int> matrix_trace)
	{
		string start_point = to_string(start);
		string end_point = to_string(end);
		text.setString("Click Left mouse to move \nClick Right mouse to cancel\nPress Enter to get your result\n\Press ESC to return to menu\nYou can move the result screen by clicking on it, and click again to drop it\nYou need to go from " + start_point + " to " + end_point + "\nYour trace:");
		int size = matrix_trace.size();
		string trace = text.getString();
		for (int i = 0; i < size; i++)
		{
			if (i == 0) trace += to_string(matrix_trace[i]);
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

	void win_lose_demo(int start, int end, std::vector <int> matrix_trace, queue <int> result_trace, bool is_win)
	{
		is_press = 1;//dung de hien you win you lose
		string start_point = to_string(start);
		string end_point = to_string(end);
		text.setString("Click Left mouse to move \nClick Right mouse to cancel\nPress Enter to get your result\nPress ESC to return to menu\nYou can move the result screen by clicking on it, and click again to drop it\nYou need to go from " + start_point + " to " + end_point + "\nYour trace:");
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
			result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height / 2);
			//neu muon can trai thi tru giong ben y
			result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);
		}
		else
		{
			result.setFont(font);
			result.setFillColor(sf::Color::Red);
			result.setCharacterSize(20);
			result.setString("YOU LOSE");
			result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height / 2);
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

	void set_position_mouse(sf::Vector2f mouse_pos)
	{
		if (is_dragging)
		{
			childwindow.setPosition(mouse_pos);
		}
	}
	
	void set_position(sf::Vector2f pos)
	{
		childwindow.setPosition(pos);
		text.setPosition(childwindow.getPosition().x - childwindow.getSize().x / 2 + text.getGlobalBounds().width, childwindow.getPosition().y - childwindow.getSize().y / 2 + text.getGlobalBounds().height);
		text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
		result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height / 2);
	}
	void change_Status()
	{
		if (is_dragging) is_dragging = false;
		else is_dragging = true;
	}

	int get_is_dragging()
	{
		return is_dragging;
	}
	void reset_is_press()//cai nay dung de xoa hien you win you lose
	{
		is_press = 0;
	}
	
	void set_Text_Pos()
	{
		text.setPosition(childwindow.getPosition().x - childwindow.getSize().x / 2 + text.getGlobalBounds().width, childwindow.getPosition().y - childwindow.getSize().y / 2 + text.getGlobalBounds().height);
		text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
		result.setPosition(childwindow.getPosition().x, childwindow.getPosition().y + text.getGlobalBounds().height / 2);
	}

	void resize(int width, int height)
	{
		childwindow.setSize(sf::Vector2f(width, height));
		childwindow.setOrigin(sf::Vector2f(width / 2, height / 2));
	}
	
	int get_height()
	{
		return childwindow.getSize().y;
	}
	int get_width()
	{
		return childwindow.getSize().x;
	}

private:
	sf::RectangleShape childwindow;
	sf::Text text;
	sf::Text result;
	sf::Font font;
	int is_press = 0;//dung de hien you win, you lose
	bool is_dragging=false;
};