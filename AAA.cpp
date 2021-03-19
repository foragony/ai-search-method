#include <iostream>
#include<queue>
#include<vector>
#include<string>
#include <time.h>

using namespace std;

#define N 5  //传教士与野人人数
#define K 3  //乘船人数

int m, c;

struct node
{
	int m;
	int c;
	int ship;
	int top;
	int front;
	int key;
};
//查找结点，m传教士，c野人，ship船位置，0为起点，1为对岸 

vector<node>open;

struct node temp[1000];
int way[8][2] = { {3,0},{2,1},{0,3},{2,0},{1,1},{0,2},{1,0},{0,1} };		//过河方案
int num = 0;

int safe(node state)		//检验
{
	if (state.c < 0 || state.m < 0)
		return 0;
	if (state.m == N || state.m == 0)
		return 1;
	else if (state.m == state.c)
		return 1;
	else
		return 0;
}

int repeat(node state, int num)		//检验重复
{
	for (int i = 0; i < num; i++)
		if (state.m == temp[i].m && state.c == temp[i].c && state.ship == temp[i].ship)
			return 0;
	return 1;
}

int FN(node state)		//启发式函数，深度+M+C-K*B
{
	int value;
	value = state.top + state.c + state.m - 3 * state.ship;
	return value;
}

int FN2(node state)		//启发式函数，深度+M+C-K*B
{
	int value;
	if(state.ship == 1)
		value = state.top + state.c + state.m - 3;
	else
		value = state.top + state.c + state.m;
	return value;
}

int Astar()		//
{
	while(!open.empty())
	{
	node temp1 = *open.begin();
	m = temp1.m;
	c = temp1.c;
	for (int i = 0; i < 8; i++)
	{
		if (temp1.ship == 1)
		{
			node temp2;
			temp2.m = m - way[i][0];
			temp2.c = c - way[i][1];
			temp2.ship = -temp1.ship;
			temp2.top = temp1.top + 1;
			if (temp2.m == 0 && temp2.c == 0)
			{
				temp2.front = temp1.key;
				temp2.key = num;
				temp[num++] = temp2;
				goto loop;
			}
			if (safe(temp2) && repeat(temp2, num))
			{
				temp2.front = temp1.key;
				temp2.key = num;
				temp[num++] = temp2;
				open.push_back(temp2);
			}
		}
		if (temp1.ship == -1)
		{
			node temp2;
			temp2.m = m + way[i][0];
			temp2.c = c + way[i][1];
			temp2.ship = -temp1.ship;
			temp2.top = temp1.top + 1;
			if (safe(temp2) && repeat(temp2, num))
			{
				temp2.front = temp1.key;
				temp2.key = num;
				temp[num++] = temp2;
				open.push_back(temp2);
			}
		}
	}
	open.erase(open.begin());
	int l = open.size();
	for (int i = 0; i < l; i++)
	{
		for (int j = i; j < l-i-1; j++)
		{
			if (FN2(open[j]) > FN2(open[j + 1]))
				swap(open[j], open[j + 1]);
		}
	}
	
}
loop:;
return 0;
}

int main()
{
	clock_t start_time, end_time;
	start_time = clock();   //获取开始执行时间

	node p;
	p.m = 5;
	p.c = 5;
	p.ship = 1;
	p.top = 0;
	p.front = 0;
	p.key = 0;
	open.push_back(p);
	temp[num++] = p;
	Astar();
	cout << "传教士 野人   船(倒序)" << endl;
	for (int i = num - 1; i > 0; )
	{
		cout << temp[i].m << "      " << temp[i].c << "      " << temp[i].ship << endl;
		i = temp[i].front;
	}
	cout << "5      5      1" << endl;

	end_time = clock();     //获取结束时间
	double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("%f seconds\n", Times);
	return 0;
}