#pragma once
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<vector>
#include<queue>
#define vc 100
using namespace std;
class Graph
{
public:
	int n;
	vector<vector<int>>Length;
	vector<vector<int>>LuuVet;
	Graph(int N) :n(N), Length(N, vector<int>(N, 0)),LuuVet(N, vector<int>(N,0))
	{
	}
	Graph() :n(2), Length(2, vector<int>(2, 0)), LuuVet(2, vector<int>(2, 0))
	{
	}
	~Graph()
	{
	}
	queue<int> TruyVet(int u,int v) // Lưu trữ đường đi
	{
		queue<int> Way;
		int tmp = u;
		while (tmp != v)
		{
			Way.push(tmp);
			tmp = LuuVet[tmp-1][v-1];// luư vết chứa các giá trị truy vết của ma trận, hàm này sẽ coi khi nao giá trị cuối bằng với giá trị truy vết thì dừng
		}
		Way.push(v);
		return Way;
	}
	void Floyd(vector<vector<int>>Matrix_Weight) // Thuật toán Floyd
	{
		for (int i = 0; i < n; i++)// khoi tao ma tran D
			for (int j = 0; j < n; j++)
			{
				Length[i][j] = Matrix_Weight[i][j];
				if (Length[i][j] != 0 && Length[i][j] != vc)
					LuuVet[i][j] = j + 1;
				else LuuVet[i][j] = 0;
				if (Length[i][j] == 0 && i != j)
					Length[i][j] = vc;

			}

		for (int k = 0; k < n; k++) // Thuat toan Floyd
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (Length[i][j] > (Length[i][k] + Length[k][j]))
					{
						Length[i][j] = Length[i][k] + Length[k][j];
						LuuVet[i][j] = LuuVet[i][k];
					}
		}
	}
};
vector<vector<int>> Nhap_Graph_File(string address)
{
	ifstream Input(address, ios::in);
	int N(0);
	Input >> N;
	vector < vector<int>> GG(N,vector<int>(N,0));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			Input >> GG[i][j];
		}
	Input.close();
	return GG;
}
vector<vector<int>> Nhap_Graph_File_Pair(string address)
{
	ifstream Input(address, ios::in);
	int N(0),M(0);
	int i, j, length;
	Input >> N >> M;
	vector < vector<int>> GG(N, vector<int>(N, 0));
	for (int k = 0; k < M; k++)
	{
		Input >> i >> j >> length;
		GG[i - 1][j - 1] = GG[j - 1][i - 1] = length;
	}
	Input.close();
	return GG;
}
vector<vector<int>> Nhap_Graph(string address)
{
	int N;
	int tmp;
	do
	{
		cin >> N;
	} while (N <= 0);
	vector < vector<int>> GG(N, vector<int>(N, 0));
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			do
			{
				cin >> tmp;
				if (i == j)
					tmp = 0;
			} while (tmp < 0);
			GG[i][j] = tmp;
		}
	return GG;
}
int checkMinLocation(vector<int>sumLength, int N) {
	int imin = 0;
	for (int i = 1; i < N; i++) {
		if (sumLength[imin] > sumLength[i])
			imin = i;
	}return imin;
}
void sumLengthEachPoint(vector<vector<int>>GG, vector<int> &sumLength, int N) {
	for (int i = 0; i < N; i++) {
		sumLength[i] = GG[i][1];
		for (int j = 1; j < N; j++) {
			sumLength[i] += GG[i][j];
		}
	}
}
pair<int,int> CTT_Location(vector<vector<int>>GG, int N) {
	pair<int, int>result;
	vector<int>sumLength(N);
	sumLengthEachPoint(GG, sumLength, N);
	int imin = checkMinLocation(sumLength, N);
	result.first = imin + 1;
	result.second = sumLength[imin];
	return result;
}