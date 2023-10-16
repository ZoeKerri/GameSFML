#include <iostream>
#define NOMINMAX
#include "Graph.h"
#include"UI.h"
#include<string>
#include"mywindow.h"
#include"Function.h"
#include "GameLoop.h"
#include "Create_Buttons.h"
#include "Result_Window.h";
#define pause system("pause")
int main()
{
    GameLoop game;
    resizeConsole(120, 29);
    SetConsoleTitle(L"Thuat Toan FLOYD");
    SetCenterConsole();
    vector<vector<int>>GG =
    {
        {0}
    };
    Graph g = Graph(GG.size());
    string nd[7] = { "1. Nhap File","2. Nhap thu cong","3. Tinh duong di ngan nhat","4. Truy Vet","5. Game Me Cung","6. Bai toan Cho Trung Tam","0. Dung chuong trinh" };
    string filedemo[3] = { "ViDu1.txt","ViDu2.txt","ChoTrungTam.txt"};
    int sl = 7;
    int h = 2, w = MaxLengthString(nd, sl) + 2;
    int x = 3, y = 5;
    int xptr = x, yptr = y;
    int xpre = xptr, ypre = yptr;
    int b_color = 159, b_color_bright = 75;

loop:
    xptr = x, yptr = y;
    xpre = xptr, ypre = yptr;
    int checkLuaChon = 1;
    int checkFloyd = 0;
    ShowCur(0);
    Box(1, 4, 118, 21, b_color, " ");
    Box_E(45, 0, 30, 2, b_color, "Thuat Toan Floyd");
    Box_E(45, 27, 30, 2, b_color, "Cre: Nhom 6");
    n_Box_divide(x, y, w, h, b_color, nd, 7);
    n_Box_NoBorder(40, y, (MaxLengthMatrix(GG) + 1) * (GG.size()) + 2, GG.size() + 1, 159, GG);
    colortext(32, y + 1, "Ma Tran:", 159);
    while (1)
    {
        if (checkFloyd == 0)
        {
            g.Floyd(GG);
            checkFloyd = 1;
        }
        if (checkLuaChon)
        {
            gotoXY(xpre, ypre);
            highlight(xpre, ypre, w, h, b_color, nd[Cal(y, ypre, h)]);
            xpre = xptr;
            ypre = yptr;
            highlight(xptr, yptr, w, h, b_color_bright, nd[Cal(y, yptr, h)]);
            checkLuaChon = false;
        }
        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            {

                c = _getch();
                if (c == 72)
                {
                    Beep(800, 50);
                    checkLuaChon = true; // đã bấm
                    if (yptr != y)
                        yptr -= h;
                    else
                    {
                        yptr = y + h * (sl - 1);
                    }
                }
                else if (c == 80)
                {
                    Beep(800, 50);
                    checkLuaChon = true; // đã bấm
                    if (yptr != y + h * (sl - 1))
                        yptr += h;
                    else
                    {
                        yptr = y;
                    }
                }
            }
            else if (c == 13)
            {
                int choice = Cal(y, yptr, h);
                if (choice >= 0 && choice < sl - 1)
                {
                    switch (choice)
                    {
                    case 0:

                        GG = UI_add_File(GG, filedemo, 3);
                        g = Graph(GG.size());
                        checkFloyd = 0;
                        break;
                    case 1:
                        GG = UI_add();
                        g = Graph(GG.size());
                        checkFloyd = 0;
                        break;
                    case 2:
                        UI_MinLength(g);
                        break;
                    case 3:
                        UI_TruyVet(g);
                        break;
                    case 4:
                        game.gameloop();//co 1 bug o day la khi thoat ra roi vo lai thi no tu dong chuyen sang mode menu luon
                        break;
                    case 5:
                        UI_CTT(g.Length);
                        break;
                    default:
                        break;
                    }
                }
                else
                    break;
                checkLuaChon = true;
                goto loop;
            }
        }
    }
    return 0;
}