#include <iostream>
#include<time.h>

using namespace std;

#define K 10//�ֲ���������Kֵ

int queens[8][8] = { 0 };//���̣�1����ʺ������λ�ã�0��֮
int totalnum = 0;//ͳ���ܲ���

int display(int temp[8][8]);

int randomq()//������ɳ�ʼ״̬
{
	srand((unsigned int)(time(NULL)));
	queens[8][8] = { 0 };
	for (size_t i = 0; i < 8; i++)
	{
		int num = rand() % 8;
		queens[i][num] = 1;
	}
	//display(queens);
	return 0;
}

int display(int temp[8][8])//������
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << temp[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}

int copy(int temp1[8][8], int temp2[8][8])
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp2[i][j] = temp1[i][j];
		}
	}
	return 0;
}

int value(int temp[8][8])//ͳ�Ƴ�ͻ����
{
	int num = 0;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (temp[i][j] == 1)
			{
				for (size_t k = i + 1; k < 8; k++)//�±�
				{
					if (temp[k][j] == 1)
					{
						num++;
					}
				}
				for (size_t k = 1; (k + i < 8)&& (k + j < 8); k++)//����
				{
					if (temp[i+k][j+k] == 1)
					{
						num++;
					}
				}
				for (int k = 1; (i + k < 8) && ((j - k + 1) > 0); k++)//����
				{
					if (temp[i + k][j - k] == 1)
					{
						num++;
					}
				}
			}
		}
		
	}
	return num;
}

int check(int temp[8][8]) //��֤������
{
	if (value(temp) == 0)
	{
		return 1;
	}
	return 0;
}

int climb()//��ɽ��
{
	randomq();
	int temp[8][8];
	copy(queens, temp);
	int h, hmin;
	int temp1[8][8];
	hmin = value(temp);
	//cout << hmin<<endl;
	copy(temp, temp1);
	for (int t = 0; t < 10000; t++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			
			/*int k = 0;
			while (temp[i][k++] == 0);
			temp[i][k - 1] = 0;*/
			copy(temp1, temp);
			for (size_t j = 0; j < 8; j++)
			{
				for (size_t k = 0; k < 8; k++)
				{
				temp[i][k] = 0;
				}
				temp[i][j] = 1;
				h = value(temp);
				//cout << hmin << endl;
				if (h < hmin)
				{
					copy(temp, temp1);
					hmin = h;
				}
			}

		}
		if (check(temp1)) 
		{
			display(temp1);
			//check(temp1);
			return 1;
		}
		totalnum++;
		//cout << endl;
		//display(temp1);
	}
	//cout << hmin<<endl;
	return 0;
}

int fclimb()//��ѡ��ɽ��
{
	randomq();
	int temp[8][8];
	copy(queens, temp);
	int h, hmin;
	int temp1[8][8];
	hmin = value(temp);
	//cout << hmin << endl;
	copy(temp, temp1);
	for (int t = 0; t < 10000; t++)
	{
		for (size_t i = 0; i < 8; i++)
		{

			/*int k = 0;
			while (temp[i][k++] == 0);
			temp[i][k - 1] = 0;*/
			copy(temp1, temp);
			for (size_t j = 0; j < 8; j++)
			{
				for (size_t k = 0; k < 8; k++)
				{
					temp[i][k] = 0;
				}
				temp[i][j] = 1;
				h = value(temp);
				//cout << hmin << endl;
				if (h < hmin)
				{
					copy(temp, temp1);
					hmin = h;
					goto stop;
				}
			}

		}
		stop:;
		if (check(temp1))
		{
			display(temp1);
			check(temp1);
			return 1;
		}
		totalnum++;
		//cout << endl;
		//display(temp1);
	}
	//cout << hmin<<endl;
	return 0;
}

int rclimb()//���������ɽ��
{
	while(!climb())
		randomq();
	return 1;
}

int pbs()//�ֲ�������
{
	int temp[8][8];
	int hmin[K],h;
	int state[K][8][8];
	for (size_t i = 0; i < K; i++)
	{
		randomq();
		copy(queens, state[i]);
		hmin[i] = value(state[i]);
		//display(state[i]);
	}
	for (int t = 0; t < 10000; t++)
	{
		for (size_t b = 0; b < K; b++)
		{
			copy(state[b], temp);
			for (size_t i = 0; i < 8; i++)
			{
				copy(state[b], temp);
				for (size_t j = 0; j < 8; j++)
				{
					for (size_t k = 0; k < 8; k++)
					{
						temp[i][k] = 0;
					}
					temp[i][j] = 1;
					h = value(temp);
					for (size_t a = 0; a < K; a++)
					{
						if (h < hmin[a]) {
							copy(temp, state[a]);
							hmin[a] = h;
							break;
						}

					}
				}

			}
		}
		for (size_t i = 0; i < K; i++)
		{
			if (check(state[i]))
			{
				display(state[i]);
				return 1;
			}
		}
		totalnum++;
		//cout << hmin[0]<<endl;
	}
	return 0;
}

//int sbs()//���������
//{
//	int k, temp[8][8];
//	k = 2;
//	int hmin[10], h;
//	int state[10][8][8];
//	for (size_t i = 0; i < k; i++)
//	{
//		randomq();
//		copy(queens, state[i]);
//		hmin[i] = value(state[i]);
//		//display(state[i]);
//	}
//	for (int t = 0; t < 100; t++)
//	{
//		for (size_t b = 0; b < k; b++)
//		{
//			copy(state[b], temp);
//			for (size_t i = 0; i < 8; i++)
//			{
//				copy(state[b], temp);
//				for (size_t j = 0; j < 8; j++)
//				{
//					for (size_t k = 0; k < 8; k++)
//					{
//						temp[i][k] = 0;
//					}
//					temp[i][j] = 1;
//					h = value(temp);
//					for (size_t a = 0; a < k; a++)
//					{
//						if (h < hmin[a]) {
//							copy(temp, state[a]);
//							hmin[a] = h;
//							break;
//						}
//
//					}
//				}
//
//			}
//		}
//		for (size_t i = 0; i < k; i++)
//		{
//			if (check(state[i]))
//			{
//				display(state[i]);
//				return t;
//			}
//		}
//		totalnum++;
//	}
//	return 0;
//}

int sa() //ģ���˻��㷨
{
	randomq();
	int temp[8][8];
	double tem = 1;
	copy(queens, temp);
	int h, hmin;
	int temp1[8][8];
	hmin = value(temp);
	//cout << hmin << endl;
	copy(temp, temp1);
	while (tem > 0.00001)
	{
		for (size_t i = 0; i < 8; i++)
		{
			copy(temp1, temp);
			for (size_t j = 0; j < 8; j++)
			{
				for (size_t k = 0; k < 8; k++)
				{
					temp[i][k] = 0;
				}
				temp[i][j] = 1;
				h = value(temp);
				if (h < hmin)
				{
					copy(temp, temp1);
					hmin = h;
				}
				else if (exp((double)((hmin - h) / tem)) > ((double)(rand() % 1000) / 1000))
				{
					copy(temp, temp1);
					hmin = h;
				}
			}
		}
		if (check(temp1))
		{
			display(temp1);
			return 1;
		}
		tem = tem * 0.99;
		totalnum++;
	}
	return 0;
}

int main()
{
	cout <<endl<< "��ɽ����������Ϊ��" << endl;
	if (!climb())
		cout << "δ���ҵ������" << endl;
	else
		cout << "���ò���Ϊ��" << totalnum << endl;

	totalnum = 0;
	cout << endl << "��ѡ��ɽ����������Ϊ��" << endl;
	if (!fclimb())
		cout << "δ���ҵ������"<<endl;
	else
		cout << "���ò���Ϊ��" << totalnum << endl;

	totalnum = 0;
	cout << endl << "���������ɽ����������Ϊ��" << endl;
	if (!rclimb())
		cout << "δ���ҵ������"<<endl;
	else
		cout << "���ò���Ϊ��" << totalnum << endl;

	totalnum = 0;
	cout << endl << "�ֲ���������������Ϊ��" << endl;
	if (!pbs())
		cout << "δ���ҵ������" << endl;
	else
		cout << "���ò���Ϊ��" << totalnum << endl;

	totalnum = 0;
	cout << endl << "ģ���˻��㷨��������Ϊ��" << endl;
	if (!sa())
		cout << "δ���ҵ������" << endl;
	else
		cout << "���ò���Ϊ��" << totalnum << endl;

	return 0;
}