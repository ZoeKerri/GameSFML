#pragma once
#include<vector>
#include<string>
using namespace std;
int MaxLengthMatrix(vector<vector<int>>Matrix_Weight)
{
    int count(0);
    int max = Matrix_Weight[0][0];
    int n = Matrix_Weight.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            max = max < Matrix_Weight[i][j] ? Matrix_Weight[i][j] : max;
    while (max >= 10)
    {
        max /= 10;
        count++;
    }
    count++;
    return count;
}
int MaxLengthString(string nd[], int sl)
{
    int R = nd[0].length();
    for (int i = 1; i < sl; i++)
        R = R <= nd[i].length() ? nd[i].length() : R;
    return R;
}
int Cal(int y, int yptr, int h)
{
    int R = (yptr - y) / h;
    return R;
}
int isDigit(string a)
{
    if (a[0] == '-')
        a.erase(0, 1);
    for (char c : a)
        if (!isdigit(c))
            return false;
    return true;
}