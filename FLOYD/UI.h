#pragma once
#include<string>
#include"mywindow.h"
#include"Graph.h"
#include"Function.h"
using namespace std;
vector<vector<int>> UI_add_File(vector<vector<int>> &GG,string address[],int sl)
{
    Box(1, 4, 118, 21, 159, " ");
    int x = 3, y = 5;
    int h = 1;
    int xptr = x, yptr = y;
    int xpre = xptr, ypre = yptr;
    int b_color = 159;
    int checkLuaChon = 1;
    for (int i = 0; i < sl; i++)
    {
        gotoXY(x + 2, y + i);
        cout << address[i];
    }
    gotoXY(x + 2, y + sl);
    cout << "Tro ve";
    ShowCur(0);
    while (1)
    {
        if (checkLuaChon)
        {
            gotoXY(xpre, ypre);
            cout << " ";
            xpre = xptr;
            ypre = yptr;
            gotoXY(xptr, yptr);
            cout << ">";
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
                        yptr = y + h * (sl);
                    }
                }
                else if (c == 80)
                {
                    Beep(800, 50);
                    checkLuaChon = true; // đã bấm
                    if (yptr != y + h * (sl))
                        yptr += h;
                    else
                    {
                        yptr = y;
                    }
                }
            }
            else if (c == 13)
            {
                if (yptr - y == sl)
                {
                    return GG;
                }
                else
                {
                    int choice = yptr - y;
                    if (choice == 2)
                        GG=Nhap_Graph_File_Pair(address[2]);
                    else 
                        GG = Nhap_Graph_File(address[choice]);
                    break;
                }
            }
        }
    }
    return GG;
}
vector<vector<int>> UI_add()
{
    ShowCur(1);
    Box(1, 4, 118, 21, 159, " ");
    string n_str;
    int n_i;
    int x = 3, y = 5;
    while (1)
    {
        gotoXY(x, y);
        clreol();
        cout << "Nhap so diem cua do thi (1-10 diem): ";
        getline(cin,n_str);
        if(n_str!="")
        if (isDigit(n_str)&&stoi(n_str)>0&&stoi(n_str)<11)
        {
            n_i = stoi(n_str); 
            break;
        }
    }
    vector<vector<int>> GG(n_i, vector<int>(n_i, 0));
    int tmp_length(0);
    int xpre(0);
    for(int i=0;i<n_i;i++)
        for (int j = 0; j < n_i; j++)
        {
            while (1)
            {
                if (j == 0)
                {
                    tmp_length = 0; xpre = 0;
                }
                if (x + j * 3 + 2 + xpre > 120)
                    xpre -= 10;
                gotoXY(x, y + n_i+2);
                cout << "Nhap Matrix[" << i << "][" << j << "]: ";
                gotoXY(x + j * 3 + 2 + xpre, y + i + 1);
                for (int k = x + j * 3 + 2 + xpre; k < 119; k++)
                {
                    gotoXY(k, y + i + 1);
                    cout << " ";
                }
                gotoXY(x + j * 3 + 2 + xpre, y + i + 1);
                getline(cin, n_str);
                if (n_str != "")
                if (isDigit(n_str) && (i!=j || (i == j && stoi(n_str) == 0)))
                {
                    GG[i][j] = stoi(n_str);
                    tmp_length = n_str.length();
                    xpre += tmp_length;
                    break;
                    
                }
            }
        }
    ShowCur(0);
    return GG;
}
void UI_MinLength(Graph g)
{
    Box(32, 5, 85, 19, 159, " ");
    gotoXY(32 + 1, 5 + 1);
    cout << "Do thi co " << g.n << " diem";
    if (g.n==1)
    {
        gotoXY(32 + 1, 5 + 2);
        cout << "Duong di ngan nhat: 0";
    }
    else
    {
        string tmp;
        int u, v;
        ShowCur(1);
        while (1)
        {
            gotoXY(32 + 1, 5 + 2);
            cout << "Nhap diem bat dau:                   ";
            gotoXY(32 + 1, 5 + 2);
            cout << "Nhap diem bat dau: ";
            getline(cin,tmp);
            if (tmp != "")
            if (isDigit(tmp) && stoi(tmp) > 0 && stoi(tmp) <=g.n)
            {
                u = stoi(tmp);
                break;
            }
        }
        while (1)
        {
            gotoXY(32 + 1, 5 + 3);
            cout << "Nhap diem ket thuc:                     ";
            gotoXY(32 + 1, 5 + 3);
            cout << "Nhap diem ket thuc: ";
            getline(cin, tmp);
            if (tmp != "")
            if (isDigit(tmp) && stoi(tmp) > 0 && stoi(tmp) <= g.n&&stoi(tmp)!=u)
            {
                v = stoi(tmp);
                break;
            }
        }
        gotoXY(32 + 1, 5 + 4);
        cout << "Do dai duong di ngan nhat tu diem " << u << " den diem " << v << ": ";
        cout << g.Length[u - 1][v - 1];
    }
    ShowCur(0);
    _getch();
}
void UI_TruyVet(Graph g)
{
    Box(32, 5, 85, 19, 159, " ");
    gotoXY(32 + 1, 5 + 1);
    cout << "Do thi co " << g.n << " diem";// n la so diem cua do thi
    if (g.n == 1)
    {
        gotoXY(32 + 1, 5 + 2);
        cout << "Khong the di chuyen!!";
    }
    else
    {
        string tmp;
        int u, v;
        ShowCur(1);
        while (1)
        {
            gotoXY(32 + 1, 5 + 2);
            cout << "Nhap diem bat dau:                               ";
            gotoXY(32 + 1, 5 + 2);
            cout << "Nhap diem bat dau: ";
            getline(cin, tmp);
            if (tmp != "")
            if (isDigit(tmp) && stoi(tmp) > 0 && stoi(tmp) <= g.n)
            {
                u = stoi(tmp);
                break;
            }
        }
        while (1)
        {
            gotoXY(32 + 1, 5 + 3);
            cout << "Nhap diem ket thuc:                               ";
            gotoXY(32 + 1, 5 + 3);
            cout << "Nhap diem ket thuc: ";
            getline(cin, tmp);
            if (tmp != "")
            if (isDigit(tmp) && stoi(tmp) > 0 && stoi(tmp) <= g.n && stoi(tmp) != u)
            {
                v = stoi(tmp);
                break;
            }
        }
        gotoXY(32 + 1, 5 + 4);
        cout << "Duong di tu diem " << u << " den diem " << v << ": ";
        queue<int> Way = g.TruyVet(u,v);
        gotoXY(32 + 1, 5 + 5);
        while (!Way.empty())
        {
            cout << Way.front();
            if(Way.size()>1)
            cout<<"->";
            Way.pop();
        }
    }
    ShowCur(0);
    _getch();
}
void UI_AfterCredit(int screenweight,int screenheight)
{
    Box(1, 4, 118, 21, 159, " ");
    string nd[6] = { "Thanh Vien Nhom:","Nguyen Tran Quang","Bui Lam Hoang Phu","Ha Huynh Anh Ngan", "Lam Minh Sam", "Tran Thien Tai" };
    int x = screenweight/2, y = 15;
    
    for (int i = 0; i < 6; i++)
    {
        gotoXY(x-nd[i].length()/2, y++);
        cout << nd[i];
    }
    
    _getch();
}
void UI_CTT(vector<vector<int>>GG)
{
    pair<int, int>Info =CTT_Location(GG, GG.size());
    Box(32, 5, 85, 19, 159, " ");
    gotoXY(32 + 1, 5 + 1);
    cout << "Do thi co " << GG.size() << " diem";
    gotoXY(32 + 1, 5 + 2);
    cout << "Vi tri Trung Tam Dich Vu: " << Info.first;
    gotoXY(32 + 1, 5 + 3);
    cout << "Tong khoang cach tu trung tam dich vu den cac dia diem dan cu: " << Info.second;
    _getch();
}