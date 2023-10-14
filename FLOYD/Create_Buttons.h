#pragma once
#include <fstream>
#include <vector>
#include "Graph.h"
#include <random>
#define EASY 8
#define MEDIUM 10
#define HARD 12
#define RAD 13
class Cre_Buttons 
{
public:
	Cre_Buttons() {};
	~Cre_Buttons() {};
	void set_item_index(int index)//lay gia tri index hien tai cua mode
	{
		selected_items_index = index;
	}
	 
	void get_Easy_Mode_Butons_Pos()
	{
		position = new sf::Vector2i[EASY];
		std::ifstream file("Position//EasyMode" + std::to_string(selected_items_index) + ".txt");
		if (!file)
		{
			std::cout << "Error!";
			return;
		}
		for (int i = 0; i < EASY; i++)
		{
			file >> position[i].x;
			file >> position[i].y;
		}
	}

	void get_Medium_Mode_Butons_Pos()
	{
		position = new sf::Vector2i[MEDIUM];
		int index = selected_items_index - 3;
		std::ifstream file("Position//MediumMode" + std::to_string(index) + ".txt");
		if (!file)
		{
			std::cout << "Error!";
			return;
		}
		for (int i = 0; i < MEDIUM; i++)
		{
			file >> position[i].x;
			file >> position[i].y;
		}
	}

	void get_Hard_Mode_Butons_Pos()
	{
		position = new sf::Vector2i[HARD];
		int index = selected_items_index - 6;
		std::ifstream file("Position//HardMode" + std::to_string(index) + ".txt");
		if (!file)
		{
			std::cout << "Error!";
			return;
		}
		for (int i = 0; i < HARD; i++)
		{
			file >> position[i].x;
			file >> position[i].y;
		}
	}

	/*void set_Button(std::string name, int char_size, float rad, sf::Color bgcolor, sf::Color textcolor, sf::CircleShape button, sf::Text text)
	{
	};*/ // chua thu co che overloading bao h nen k chac phai k
	void set_Mode_Buttons(unsigned int char_size, sf::Font &font,sf::Color bgcolor, sf::Color textcolor,sf::RenderWindow &window)//dat thuoc tinh va vi tri
	{
		if (selected_items_index <= 2)
		{
			buttons = new sf::CircleShape[EASY];
			text = new sf::Text[EASY];
			for (int i = 0; i < EASY; i++)
			{
				text[i].setFont(font);
				text[i].setString(std::to_string(i+1));
				text[i].setFillColor(textcolor);
				text[i].setCharacterSize(char_size);

				buttons[i].setRadius(RAD);
				buttons[i].setFillColor(bgcolor);

				buttons[i].setPosition(position[i].x - RAD, position[i].y - RAD);
				float textX = position[i].x - (text[i].getLocalBounds().width) / 2;
				float textY = position[i].y - (text[i].getLocalBounds().height) / 2;
				text[i].setPosition(textX, textY);

			}
		}
		else if (selected_items_index >2 && selected_items_index <= 5)
		{
			buttons = new sf::CircleShape[MEDIUM];
			text = new sf::Text[MEDIUM];
			for (int i = 0; i < MEDIUM; i++)
			{
				text[i].setFont(font);
				text[i].setString(std::to_string(i+1));
				text[i].setFillColor(textcolor);
				text[i].setCharacterSize(char_size);

				buttons[i].setRadius(RAD);
				buttons[i].setFillColor(bgcolor);

				buttons[i].setPosition(position[i].x - RAD, position[i].y - RAD);
				float textX = position[i].x - (text[i].getGlobalBounds().width) / 2;
				float textY = position[i].y - (text[i].getGlobalBounds().height) / 2;
				text[i].setPosition(textX, textY);
			}
		}
		else
		{
			buttons = new sf::CircleShape[HARD];
			text = new sf::Text[HARD];
			for (int i = 0; i < HARD; i++)
			{
				text[i].setFont(font);
				text[i].setString(std::to_string(i+1));
				text[i].setFillColor(textcolor);
				text[i].setCharacterSize(char_size);

				buttons[i].setRadius(RAD);
				buttons[i].setFillColor(bgcolor);

				buttons[i].setPosition(position[i].x - RAD, position[i].y - RAD);
				float textX = position[i].x - (text[i].getGlobalBounds().width) / 2;
				float textY = position[i].y - (text[i].getGlobalBounds().height) / 2;
				text[i].setPosition(textX, textY);
			}
		}
	}
	void draw_num(sf::RenderWindow& window)
	{
		for (int i = 0; i < EASY; i++)
		{
			window.draw(text[i]);
		}
	}
	void draw_buttons(sf::RenderWindow &window)
	{
		if (selected_items_index <= 2)
		{
			for (int i = 0; i < EASY; i++)
			{
				window.draw(buttons[i]);
				window.draw(text[i]);// ra là ở hàm cũ font nó không được truyền vào mà nó nằm ở trong code block hàm đó 
				//khi thoát ra hàm thì cái font nó mất tiêu thành ra khi vẽ thì chương trình nó truy cập vào bộ nhớ k hợp lệ.
			}
		}
		else if (selected_items_index >2 && selected_items_index <= 5)
		{
			for (int i = 0; i < MEDIUM; i++)
			{
				window.draw(buttons[i]);
				window.draw(text[i]);
			}
		}
		else
		{
			for (int i = 0; i < HARD; i++)
			{
				window.draw(buttons[i]);
				window.draw(text[i]);
			}
		}
	}

	void is_Over_Buttons(sf::RenderWindow &window)// lay gia tri index cua do dang to mau de khi click vao thi to mau luon
	{//them ham setpointcount vao de nhan gia tri diem nham để vẽ 
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (selected_items_index <= 2)
		{
			for (int i = 0; i < EASY; i++)
			{
				if (buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Click_Buttons_Color(i);
				} 
				else if(is_Click[i]==0 && !buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Non_Click_Buttons_Color(i);
				}
			}
		}
		else if (selected_items_index > 2 && selected_items_index <= 5)
		{
			for (int i = 0; i < MEDIUM; i++)
			{
				if (buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Click_Buttons_Color(i);
				}
				else if (is_Click[i] == 0 && !buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Non_Click_Buttons_Color(i);
				}
			}
		}
		else
		{
			for (int i = 0; i < HARD; i++)
			{
				if (buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Click_Buttons_Color(i);
				}
				else if (is_Click[i] == 0 && !buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
				{
					set_Non_Click_Buttons_Color(i);
				}
			}
		}
		
	}

	void set_Click_Buttons_Color(int index)
	{
		buttons[index].setFillColor(sf::Color::Yellow);
	}
	void set_Non_Click_Buttons_Color(int index)
	{
		buttons[index].setFillColor(sf::Color::White);
	}
	void complete_level()
	{
		delete[] buttons;
		delete[] text;
		delete[] position;
	}
	void init_is_Click() 
	{
		sf::Color color;
		if (selected_items_index <= 2)
		{
			for (int i = 0; i < EASY; i++)
			{
				is_Click.push_back(0);
			}
		}
		else if (selected_items_index > 2 && selected_items_index <= 5)
		{
			for (int i = 0; i < MEDIUM; i++)
			{
				is_Click.push_back(0);
			}
		}
		else
		{
			for (int i = 0; i < HARD; i++)
			{
				is_Click.push_back(0);
			}
		}
	}
	bool is_Contain_Value(int trace_value)//Kiem tra xem gia tri truy vet co trong vector khong, neu co thi tra ve true co nghia la gia tri do khong duoc luu
		//hoac con duoc dung de xoa khi nhan chuot phai duoc ghi o ham Remove_Matrix_Trace
	{
		int size = matrix_trace.size();
		for (int i = 0; i < size; i++)
		{
			if (matrix_trace[i] == trace_value) return true;
		}
		return false;
	}
	int Trace_Index(int trace_value)//tra ve vi tri cua cho truy vet muon tim
	{
		int size = matrix_trace.size();
		for (int i = 0; i < size; i++)
		{
			if (matrix_trace[i] == trace_value) return i;
		}
		return - 1;
	}
	void Remove_Maxtrix_Trace(int trace_value)//ham nay dung de xoa gia tri truy vet tu cho bam chuot phai va huy to mau tu cho xoa do 
	{
		if (is_Contain_Value(trace_value))
		{
			int size = matrix_trace.size()-1;
			int removal_index = Trace_Index(trace_value);
			for (int i = size;i>=removal_index;i--)
			{
				is_Click[matrix_trace[i]-1] = 0;
				matrix_trace.erase(matrix_trace.begin() + i);
				matrix_trace.shrink_to_fit();
			}
		}
	}
	void Click_Button(sf::Event event,sf::RenderWindow &window,int start, int end)//ham nay dung de click hoac huy button bi click
		//HÀM NÀY CẦN THÊM 2 THAM SỐ NỮA LÀ START VÀ END ĐỂ KIỂM TRA RẰNG COI CÓ BẤM GIÁ TRỊ ĐẦU VÀ GIÁ TRỊ CUỐI CHƯA
		//Hàm này ở chỗ xét coi win hay lose thì nên đặt 1 cái dùng enter để xác định rằng kết thúc hay chưa, chắc bỏ điều kiện bắt buộc phải nhấn giá trị đầu và kết thúc bằng giá trị cuối quá 
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (event.mouseButton.button == sf::Mouse::Left)//bam chuot trai nhan gia tri
		{
			if (selected_items_index <= 2)
			{
				for (int i = 0; i < EASY; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 1;
						matrix_trace.push_back(trace);
						break;
					}
				}
			}
			else if (selected_items_index > 2 && selected_items_index <= 5)
			{
				for (int i = 0; i < MEDIUM; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 1;
						matrix_trace.push_back(trace);
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < HARD; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 1;
						matrix_trace.push_back(trace);
						break;
					}
				}
			}
		}
		else//cho nay la ham bam chuot phai nha code do qua :(( bam chuot phai de huy gia tri 
		//tai sao khi remove khong phai la trace? Tai vi ham remove no lay gia tri index chu khong phai gia tri truy vet, gia tri truy vet no tang len 1 de cho trung voi ham truy vet ben floyd roi
		{
			if (selected_items_index <= 2)
			{
				for (int i = 0; i < EASY; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 0;
						Remove_Maxtrix_Trace(trace);
						break;
					}
				}
			}
			else if (selected_items_index > 2 && selected_items_index <= 5)
			{
				for (int i = 0; i < MEDIUM; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 0;
						Remove_Maxtrix_Trace(trace);
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < HARD; i++)
				{
					if (buttons[i].getFillColor() == sf::Color::Yellow && buttons[i].getGlobalBounds().contains(static_cast <float> (mousePos.x), static_cast <float> (mousePos.y)))
					{
						int trace = i + 1;
						is_Click[i] = 0;
						Remove_Maxtrix_Trace(trace);
						break;
					}
				}
			}
		}
	}
	void init_mode_game_trace()
	{
		GG =
		{
			{0}
		};
		map_trace = Graph(GG.size());
	}

	void set_Mode_Matrix()
	{
		std::string FileName;
		if (selected_items_index <= 2) 
		{
			FileName = "Game_Mode_Matrix//easy" + to_string(selected_items_index+1) + ".txt";
		}
		else if (selected_items_index > 2 && selected_items_index <= 5)
		{
			int index = selected_items_index - 2;//do game bat dau tu 1 2 3 chu khong phai tu 0 nen o mode medium thi selected_items_index la 3-5 nen tru 2 thi con so se bat dau tu 1-3 nhu o trong file tuong tu voi hard thi -5
			FileName = "Game_Mode_Matrix//medium" + to_string(index) + ".txt";
		}
		else
		{
			int index = selected_items_index - 5;
			FileName = "Game_Mode_Matrix//hard" + to_string(index) + ".txt";
		}
		std::ifstream file(FileName);
		if (!file)
		{
			std::cout << "Error!";
			return;
		}
		int N(0);
		file >> N;
		vector < vector<int>> temp(N, vector<int>(N, 0));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				file >> temp[i][j];
			}
		GG = temp;
		map_trace = Graph(GG.size());
		map_trace.Floyd(GG);
		file.close();
	}
	void set_Start_Finish()//random ra 2 dinh u va v de cho nguoi choi chon , u va v khong duoc trung nhau
	{
		std:: random_device rd;
		std::mt19937_64 engine(rd());
		std::uniform_int_distribution <int> dist(1, 12);
		if (selected_items_index <= 2)
		{
			while (1)
			{
				start_finish.first = dist(engine);
				start_finish.second = dist(engine);
				if ((start_finish.first > 0 && start_finish.first <= 8) && (start_finish.second > 0 && start_finish.second <= 8))
					if (start_finish.first != start_finish.second) break;
			}
		}

		else if (selected_items_index > 2 && selected_items_index <=5)
		{
			while (1)
			{
				start_finish.first = dist(engine);
				start_finish.second = dist(engine);
				if ((start_finish.first > 0 && start_finish.first <= 10) && (start_finish.second > 0 && start_finish.second <= 10))
					if (start_finish.first != start_finish.second) break;
			}
		}

		else 
		{
			while (1)
			{
				start_finish.first = dist(engine);
				start_finish.second = dist(engine);
				if ((start_finish.first > 0 && start_finish.first <= 12) && (start_finish.second > 0 && start_finish.second <= 12))
					if (start_finish.first != start_finish.second) break;
			}
		}

	}

	pair<int,int> get_start_finish()
	{
		return start_finish;
	}
	bool is_Win()
	{
		std::queue <int> Way;
		std::vector <int> temp = matrix_trace;
		Way = map_trace.TruyVet(start_finish.first, start_finish.second);
		if (temp.empty()) return false;
		if (Way.back() != temp[temp.size() - 1]) return false;
		while (!Way.empty())
		{
			if (!(Way.front() == temp[0])) return false;// neu gia tri truy vet cua game khac gia tri tri vet cua nguoi choi thi nguoi choi thua ngay
			else
			{
				Way.pop();
				temp.erase(temp.begin());
				temp.shrink_to_fit();
				if (Way.empty() && !temp.empty()) return false;
			}
		}
		if (Way.empty() && temp.empty()) return true;
	}
	
	void print_matrix()
	{
		int size = matrix_trace.size();
		for (int i = 0; i < size; i++)
		{
			std::cout << matrix_trace[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "Dieu kien thang:" << start_finish.first << "\t" << start_finish.second<<std::endl;
		for (int i = 0; i < EASY; i++)
		{
			for (int j = 0; j < EASY; j++)
			{
				std::cout << GG[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::queue <int> Way = map_trace.TruyVet(start_finish.first,start_finish.second);
		std::cout << std::endl;
		while (!Way.empty())
		{
			cout << Way.front() << " ";
			Way.pop();
		}
	}
	
	queue <int> get_result_trace()
	{
		map_trace.Floyd(GG);
		std::queue <int> Way = map_trace.TruyVet(start_finish.first, start_finish.second);
		return Way;
	}
	vector <int> get_matrix_trace()
	{
		return matrix_trace;
	}
	//ta cần 1 vector của vector có 1 giá trị duy nhất là 0 tức matrix 1x1 để có thể khởi tạo class graph-done
	// xong thì ta nhập file vào graph đó the0 level - done
	// tiếp tục, ta truy vết gía trị của nó và giá trị truy vết là queue - done
	//xong thì ta sẽ so sánh liên tục giữa vector truy vết của game và queue truy vết từ ma trận game ban đầu -done
	// đối với ma trận truy vết thì nó sẽ nhận giá trị random rồi kêu người chơi chơi - done
	//chắc cần làm thêm 1 cái màn hình con sẽ hiện thì yêu cầu cho người chơi
private:
	sf::CircleShape* buttons;
	sf::Text* text;
	sf::Vector2i *position;
	int selected_items_index;
	std::vector <int> is_Click;
	std::vector <int> matrix_trace;//truy vet ma tran ket qua cua viec nhan button
	std::pair<int, int> start_finish;
	std::vector <std::vector<int>> GG;
	Graph map_trace;//truy vet ma tran cua mode game
	// trong graph thi co bao gom truy vet va tim duong di nho nhat, trong truy vet thi no se tra ve 1 gia tri la queue 
};
