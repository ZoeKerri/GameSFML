#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include "menu.h"
#include "button.h"
#include "ModeMenu.h"
#include "map.h"
#include "Create_Buttons.h"//class này bao gồm việc tạo nút và các thao tác với nút
class Game {
public:
	void gameloop()

	{
		int menu_state = 0;//chuyen doi giua cac trang thai menu: main, mode va vao gameplay
		sf::RenderWindow window(sf::VideoMode(1260, 800), "Lan's Home", sf::Style::Close | sf::Style::Titlebar);
		// ham destructor thi hoc r nhung chua xai cai quen de nghien cuu sau
		Menu Menu(window.getSize().x, window.getSize().y);//ham constructor chi duoc goi 1 lan 
		ModeMenu ModeMenu(window.getSize().x, window.getSize().y);
		Map map;
		Cre_Buttons Game_Buttons;
		sf::Font font;
		font.loadFromFile("arial.ttf");
		pair <int, int> start_finish;
		int start = start_finish.first;
		int finish = start_finish.second;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (menu_state == 0)
				{
					switch (event.type)
					{
					case::sf::Event::KeyReleased:
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
								window.clear();
								break;
							}
							case 1:
							{
								// đây là options k biết làm cái gì chắc để trống 
								std::cout << "Options button is pressed" << std::endl;
								break;
							}
							case 2://exit
							{
								window.close();
								break;
							}
							}

							break;//break ở đây để thoát khỏi cái case sf::Event::KeyRelease này 
							//nêu k có break thì nó sẽ chạy đến cái case tiếp theo nên cái window nó mới bị đóng.

						}
						case sf::Event::Closed:
						{
							window.close();
						}
						}
					}
					}
					window.clear();
					Menu.draw(window);
					window.display();
					break;
				}
				if (menu_state == 1)
				{
					switch (event.type)
					{
					case::sf::Event::KeyReleased:
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
							break;
						}
						}

						break;
					case sf::Event::Closed:
					{
						window.close();
					}
					}
					}
					window.clear();
					ModeMenu.drawto(window);
					window.display();
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
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						cout << mousePos.x << " " << mousePos.y << endl;
						Game_Buttons.Click_Button(event, window,start ,finish );

						break;
					}
					case sf::Event::Closed:
					{
						window.close();
					}
					}
					if (event.key.code == sf::Keyboard::Return)// in ra xong you win you lose xong thì quay lại clear màn hình và kêu chọn menu nào main menu hay mode menu - làm thêm cái menu state 3 là hiện ra cái màn hình đó 
					{
						if (Game_Buttons.is_Win()) cout << "YOU WIN";
						else
						{
							cout << "YOU LOSE";
						}
						Game_Buttons.print_matrix();
					}

					map.drawto(window);
					Game_Buttons.draw_buttons(window);
					window.display();
				}
			}
		}
	}
};
// xong menu h thi them cai back ground vao moi lv
//cach ve hinh tron
//hinh tron se ve o vi tri ma no nhan-done
//tức là nó vẽ từ chỗ tọa độ mà nó nhân một cái bán kính rồi nó bắt đầu vẽ nguyên hình tròn-done
//từ đó hình tròn tâm nó không phải là ở chỗ tọa độ mà nó nhận, tâm của nó là tọa độ mà nó nhận + thêm bán kính của nó vì thế nên hình lệch không như mong muốn-done
// để sửa thì ta lấy tọa độ trừ đi bán kính sẽ ra được hình ngay vị trí mà mình vẽ.-done
// h làm thêm 1 cái child screen vào phía dưới cùng của parent screen 