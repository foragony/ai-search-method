#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

vector<string> visit;

int m(5), c(5), b(3);     //�ֱ��ʾ����ʿ��������Ұ�������������ؿ���
int totalanswer = 0;                      //�ⷨ��Ŀ

bool check(int M, int C, int flag)
{
	if ((flag != 0) && (flag != 1))
		return false;
	if (M < 0 || C < 0 || m - M < 0 || c - C < 0)           //��������С��0
		return false;
	if ((M&&M < C) || ((m - M) && (m - M) < (c - C)))               //�κ�һ���д���ʿ�Ҵ���ʿ����С��Ұ������
		return false;
	char s[30];
	sprintf_s(s, "M=%d, C=%d, flag=%d", M, C, flag);
	for (int i = 0; i < visit.size(); i++)          //�����֮ǰ���ֹ�
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
	for (i = b; i > 0; i--)          //����������i����
	{
		for (j = i; j >= 0; j--)        //jΪ���͵Ĵ���ʿ����
		{
			k = i - j;                 //kΪ���͵�Ұ����
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
	int flag = 1;                         //flag=1��ʾ������
	char s[30];
	sprintf_s(s, "M=%d, C=%d, flag=%d", m, c, flag);
	visit.push_back(s);
	path(m, c, flag);
	return 0;
}