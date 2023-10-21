#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include "menu.h"
#include "ModeMenu.h"//class tạo modemenu
#include "map.h"//class tạo map
#include "Create_Buttons.h"//class này bao gồm việc tạo nút và các thao tác với nút
#include "Result_Window.h"
class GameLoop {
public:
	void gameloop()
	{
		int menu_state = 0;//chuyen doi giua cac trang thai menu: main, mode va vao gameplay
		sf::RenderWindow window(sf::VideoMode(1260, 800), "I'm Lost. ", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(30);
		Menu Menu(window.getSize().x, window.getSize().y);
		ModeMenu ModeMenu(window.getSize().x, window.getSize().y);
		Map map;
		Cre_Buttons Game_Buttons;
		sf::Font font;
		font.loadFromFile("arial.ttf");
		Result_Window child(400, 100, window.getSize().x/2, 50, 15, font, sf::Color::White, sf::Color::Black);//400,100 la kich thuoc childwindow, 50 la vi tri cua y dang le la 0 nhung co setorigin nen phai dat la 50
		pair <int, int> start_finish;
		int start = start_finish.first;
		int finish = start_finish.second;
		sf::Event empty_event;
		empty_event.type = sf::Event::EventType::MouseMoved;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (menu_state == 0)
				{
					switch (event.type)
					{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case::sf::Event::KeyPressed:
					{
						switch (event.key.code)// .code thì chứa dữ liệu dạng enum trong sf::keyboard còn .scancode là thuộc dạng nguyên nó chỉ các phím trên bàn phím như WASD
						{
						case sf::Keyboard::Up:
						{
							Menu.moveup();
							break;
						}
						case sf::Keyboard::Down:
						{
							Menu.movedown();
							break;
						}
						case sf::Keyboard::Return:
						{
							switch (Menu.getSelectedItem())
							{
							case 0:
							{
								menu_state = 1;
								break;
							}
							case 1:
							{
								// đây là hướng dẫn - ta sẽ hiển thị cách chơi ở đây 
								std::cout << "Options button is pressed" << std::endl;
								break;
							}
							case 2://exit
							{
								window.close();
								break;
							}
							}
						}
						}
					}
					}
					break;
				}
				if (menu_state == 1)
				{
					switch (event.type)
					{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case::sf::Event::KeyPressed:
					{
						switch (event.key.code)// .code thì chứa dữ liệu dạng enum trong sf::keyboard còn .scancode là thuộc dạng nguyên nó chỉ các phím trên bàn phím như WASD
						{
						case sf::Keyboard::Up:
						{
							ModeMenu.moveup();
							break;
						}
						case sf::Keyboard::Down:
						{
							ModeMenu.movedown();
							break;
						}
						case sf::Keyboard::Left:
						{
							ModeMenu.moveleft();
							break;
						}

						case sf::Keyboard::Right:
						{
							ModeMenu.moveright();
							break;
						}
						case sf::Keyboard::Return:
						{
							menu_state = 2;
							map.get_level_index(ModeMenu.get_item_index());
							map.set_map();
							Game_Buttons.set_item_index(ModeMenu.get_item_index());
							if (ModeMenu.get_item_index() <= 2)
							{
								Game_Buttons.get_Easy_Mode_Butons_Pos();
							}
							else if (ModeMenu.get_item_index() > 2 && ModeMenu.get_item_index() <= 5)
							{
								Game_Buttons.get_Medium_Mode_Butons_Pos();
							}
							else
							{
								Game_Buttons.get_Hard_Mode_Butons_Pos();
							}
							Game_Buttons.set_Mode_Buttons(15, font, sf::Color::White, sf::Color::Black, window);//set button o day, 15 la kich co chu
							Game_Buttons.init_is_Click();
							Game_Buttons.init_mode_game_trace();
							Game_Buttons.set_Start_Finish();
							pair <int, int> start_finish = Game_Buttons.get_start_finish();
							start = start_finish.first;
							finish = start_finish.second;
							Game_Buttons.set_Mode_Matrix();
							vector <int> matrix_trace = Game_Buttons.get_matrix_trace();
							child.set_trace_to_text(start, finish, matrix_trace);
							break;
						}
						case sf::Keyboard::Escape:
						{
							menu_state = 0;
							break;
						}
						}
					}
					}
					break;
				}
				if (menu_state == 2)//hien map va cac button vao day
				{
					
					switch (event.type)
					{
					case sf::Event::MouseMoved:
					{
						Game_Buttons.is_Over_Buttons(window);
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						Game_Buttons.Click_Button(event, window, start, finish);
						vector <int> matrix_trace = Game_Buttons.get_matrix_trace();
						child.set_trace_to_text(start, finish, matrix_trace);
						if (child.is_Over_Window(window) && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
						{
							child.is_Drag();
							break;
						}
						else
						{
							child.is_Drop();
							break;
						}
					}
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::KeyPressed:
					{
						switch (event.key.code)
						{
						case sf::Keyboard::Return:
						{
							vector <int> matrix_trace = Game_Buttons.get_matrix_trace();
							queue <int> Way = Game_Buttons.get_result_trace();
							bool is_Win = Game_Buttons.is_Win();
							child.win_lose(start, finish, matrix_trace, Way, is_Win);
							menu_state = 3;
							break;
						}
						case sf::Keyboard::Escape:
						{
							menu_state = 1;
							break;
						}
						}
					}
					}

					if (child.get_is_dragging())
					{
						sf::Vector2f mouPos = static_cast <sf::Vector2f> (sf::Mouse::getPosition(window));
						child.set_position(mouPos);
						child.set_Text_Pos();
					}
					break;
				}
				if (menu_state == 3)
				{//phan nay dung if tai vi no chi co 2 phan thoi no kha la ngan nen khong can phai dung switch case chi
					if (event.type==sf::Event::Closed)
					{
						window.close();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						menu_state = 1;
						Game_Buttons.reset_matrix_trace();
						child.reset_is_press();
					}
				}
			}
			window.clear();
			switch (menu_state)
			{
			case 0:
			{
				Menu.draw(window);
				break;
			}
			case 1:
			{
				ModeMenu.drawto(window);
				break;
			}
			case 2:
			{
				map.drawto(window);
				Game_Buttons.draw_buttons(window);
				child.draw_to(window);
				break;
			}
			case 3:
			{
				map.drawto(window);
				Game_Buttons.draw_buttons(window);
				child.draw_to(window);
				break;
			}
			default: break;
			}
			window.display();
		}
	}
	
};
//tai sao can break sau khi hien thi? neu k break thi chuong trinh se thuc hien tiep viec so sanh o phia duoi, vi du neu nay ta nhan enter thi lenh se chuyen menu_state=1 va no k co break nen no se thuc hien ngay luon cai menu_state 1 do 
//vi the nen moi co loi giong nhu la enter bi thuc hien nhieu lan