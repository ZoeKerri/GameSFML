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
		int menu_state = 0;//0 la main menu,1 la mode menu,2 la gameplay,3 la ket qua, 4 la huong dan choi,5 la ket qua huong dan choi
		sf::RenderWindow window(sf::VideoMode(1260, 800), "I'm Lost. ", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(30);
		Menu Menu(window.getSize().x, window.getSize().y);
		ModeMenu ModeMenu(window.getSize().x, window.getSize().y);
		Map map;
		Cre_Buttons Game_Buttons;
		sf::Font font;
		font.loadFromFile("arial.ttf");
		Result_Window child(400, 100, window.getSize().x/2, 50, 15, font, sf::Color::White, sf::Color::Black);//400,100 la kich thuoc childwindow
		//50 la mot nua cua chieu cao cua child, neu chieu cao child doi thi con so 50 cung thay doi
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
								menu_state = 4;//menu_state 4 la demo chuong trinh
								map.get_level_index(0);
								map.set_map();
								Game_Buttons.set_item_index(0);
								Game_Buttons.get_Easy_Mode_Butons_Pos();
								Game_Buttons.set_Mode_Buttons(15, font, sf::Color::White, sf::Color::Black, window);//set button o day, 15 la kich co chu
								Game_Buttons.init_is_Click();
								Game_Buttons.init_mode_game_trace();
								Game_Buttons.set_Start_Finish();
								pair <int, int> start_finish = Game_Buttons.get_start_finish();
								start = start_finish.first;
								finish = start_finish.second;
								Game_Buttons.set_Mode_Matrix();
								vector <int> matrix_trace = Game_Buttons.get_matrix_trace();
								child.set_trace_to_text_demo(start, finish, matrix_trace);
								child.resize(700, 200);
								child.set_Text_Pos();
								child.set_position(sf::Vector2f(window.getSize().x/2, child.get_height() / 2));//o day lay window.getsize()/2 de ve o vi tri chinh giua window
								//con child.get_height/2 la do dat origin la bang mot nua chieu cao cua child r nen h ta can ve o mot nua chieu cao cua child moi ra hinh ta muon
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
							child.resize(400, 100);
							break;
						}
						case sf::Keyboard::Escape:
						{
							menu_state = 0;
							ModeMenu.reset_selected_item_index();
							break;
						}
						}
					}
					}
					break;
				}
				if (menu_state == 2 || menu_state == 4)//hien map va cac button vao day
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
						if (menu_state == 4) child.set_trace_to_text_demo(start, finish, matrix_trace);
						else
						child.set_trace_to_text(start, finish, matrix_trace);
						if (child.is_Over_Window(window))
						{
							child.change_Status();
							break;
						}
						break;
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
							if (menu_state == 4) {
								child.win_lose_demo(start, finish, matrix_trace, Way, is_Win);
								menu_state = 5;
							}
							else
							{
								child.win_lose(start, finish, matrix_trace, Way, is_Win);
								menu_state = 3;
							}
							break;
						}
						case sf::Keyboard::Escape:
						{
							if (menu_state == 4) menu_state = 0;
							else
							menu_state = 1;
							Game_Buttons.reset_matrix_trace();
							Game_Buttons.reset_is_Click();
							ModeMenu.reset_selected_item_index();
							child.resize(400, 100);
							child.set_position(sf::Vector2f(window.getSize().x / 2, child.get_height()/2));
							if (child.get_is_dragging())
							{
								child.change_Status();
							}
							break;
						}
						}
					}
					}

					if (child.get_is_dragging())
					{
						sf::Vector2f mouPos = static_cast <sf::Vector2f> (sf::Mouse::getPosition(window));
						child.set_position_mouse(mouPos);
						child.set_Text_Pos();
					}
					break;
				}
				if (menu_state == 3 || menu_state == 5)
				{//phan nay dung if tai vi no chi co 2 phan thoi no kha la ngan nen khong can phai dung switch case chi
					if (event.type==sf::Event::Closed)
					{
						window.close();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						if (menu_state == 5) menu_state = 0;
						else menu_state = 1;
						Game_Buttons.reset_matrix_trace();
						child.reset_is_press();
						Game_Buttons.reset_is_Click();
						ModeMenu.reset_selected_item_index();
						child.resize(400, 100);
						child.set_position(sf::Vector2f(window.getSize().x / 2, child.get_height() / 2));
						break;
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
			case 4:
			{
				map.drawto(window);
				Game_Buttons.draw_buttons(window);
				child.draw_to(window);
				break;
			}
			case 5:
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