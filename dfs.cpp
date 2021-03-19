#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

vector<string> visit;

int m(5), c(5), b(3);     //分别表示传教士总人数，野人总人数，船载客量
int totalanswer = 0;                      //解法数目

bool check(int M, int C, int flag)
{
	if ((flag != 0) && (flag != 1))
		return false;
	if (M < 0 || C < 0 || m - M < 0 || c - C < 0)           //人数不得小于0
		return false;
	if ((M&&M < C) || ((m - M) && (m - M) < (c - C)))               //任何一岸有传教士且传教士人数小于野人人数
		return false;
	char s[30];
	sprintf_s(s, "M=%d, C=%d, flag=%d", M, C, flag);
	for (int i = 0; i < visit.size(); i++)          //此情况之前出现过
		if (s == visit[i])
			return false;
	visit.push_back(s);
	return true;
}

int path(int M, int C, int flag)
{
	if ((M == 0) && (C == 0) && (flag == 0)&&  totalanswer == 0)
	{
		totalanswer++;
		for (int i = 0; i < visit.size(); i++)
			cout << visit[i] << endl;
	}

	int i, j, k;
	for (i = b; i > 0; i--)          //船本次载了i个人
	{
		for (j = i; j >= 0; j--)        //j为运送的传教士人数
		{
			k = i - j;                 //k为运送的野人数
			if (check(M - j, C - k, flag - 1))
			{
				path(M - j, C - k, flag - 1);
				visit.pop_back();
			}
			else if (check(M + j, C + k, flag + 1))
			{
				path(M + j, C + k, flag + 1);
				visit.pop_back();


			}
		}
	}
	return 0;
}


int main()
{
	int flag = 1;                         //flag=1表示船在左岸
	char s[30];
	sprintf_s(s, "M=%d, C=%d, flag=%d", m, c, flag);
	visit.push_back(s);
	path(m, c, flag);
	return 0;
}