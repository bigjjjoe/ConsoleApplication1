#include "stdafx.h"
#define MAXSIZE 100

extern "C" int CanIGo_(int i, int j, int broad[], int H[]);
struct Stack
{
	int i;                  //������
	int j;                  //������
	int director;           //�洢����
}stack[MAXSIZE];


//Ϊ����Ĵ������� ��broad��Ϊһά����
int board[64];
int N = 8;
int x, y;
int top = -1;
//i��i+8���
int Htry[16] = { 1,-1,-2,2, 2, 1,-1,-2,   2,-2, 1,1,-1,-2, 2,-1 };


int TryPath(int i, int j)
{
	int find, director, number, min;
	int i1, j1, h, k, s;              //���弸����ʱ����
	int a[8], b1[8], b2[8], d[8];     //���弸����ʱ����
	while (top>-1)                 //ջ����ʱѭ��
	{
		for (h = 0; h<8; h++)    //������a[8]��¼��ǰλ�õ���һ��λ�õĿ���·��������
		{
			number = 0;
			i = stack[top].i + Htry[h];
			j = stack[top].j + Htry[h+8];
			b1[h] = i;
			b2[h] = j;

			number = CanIGo_(i, j, board, Htry);
			if (number > 0)
				a[h] = number;
			else
				a[h] = 0;
		}


		for (h = 0; h<8; h++)     //���ݿ���·������С�����±������������d[8]��
		{
			min = 9;
			for (k = 0; k<8; k++)
				if (min>a[k])
				{
					min = a[k];
					d[h] = k;    //���±��������d[8]��
					s = k;
				}
			a[s] = 9;
		}
		director = stack[top].director;
		if (top >= 63)                 //��������������̷���
			return (1);
		find = 0;                     //��ʾû���ҵ���һ��λ��


		/**********�������� ���� �û�����Ա�д************/
		for (h = director + 1; h<8; h++)   //��˸��������̽Ѱ
		{
			i = stack[top].i + Htry[d[h]];
			j = stack[top].j + Htry[d[h]+8];
			if (board[i * 8 + j] == 0 && i >= 0 && i<8 && j >= 0 && j<8) //����ҵ���һλ��
			{
				find = 1;       //��ʾ�ҵ���һ��λ��
				break;
			}
		}
		/***********************/


		if (find == 1)          //����ҵ���һ��λ�ý�ջ
		{
			stack[top].director = director; //�洢ջ���ķ���
			top++;                      //ջָ��ǰ�ƽ�ջ
			stack[top].i = i;
			stack[top].j = j;
			stack[top].director = -1;    //���³�ʼ����һջ���ĳ��Է���
			board[i * 8 + j] = top + 1;         //�������
		}
		else                           //������ջ
		{
			board[stack[top].i*8+stack[top].j] = 0;  //������̵ı��
			top--;                     //ջָ��ǰ����ջ
		}
	}
	return (0);
}

void Display()
{
	int i, j;
	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
			printf("\t%d  ", board[i * 8 + j]);  //���������������߹���·��
		printf("\n\n");
	}
	printf("\n");
}

void InitLocation(int xi, int yi)
{
	top++;                  //ջָ��ָ���һ��ջ�ĵײ�
	stack[top].i = xi;           //����ʼλ�õĺ������ջ
	stack[top].j = yi;           //����ʼλ�õ��������ջ
	stack[top].director = -1;     //����ʼλ�õĳ��Է��򸳳�ֵ
	board[xi*8+yi] = top + 1;       //�������
	if (TryPath(xi, yi))            //�������̽Ѱ������������̽Ѱ�������̷���1���򷵻�0
		Display();         //������������·��
	else
		printf("sorry ��There is no solution");
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
			board[i * 8 + j] = 0;
	while (1)
	{
		printf("Please enter the location of the first step of the horse(1<=x<=8 and 1<=y<=8)\n");
		printf("Input x = ");
		scanf_s("%d", &x);         //������ʼλ�õĺ�����
		printf("Input y = ");
		scanf_s("%d", &y);         //������ʼλ�õ�������
		if (x >= 1 && x <= 8 && y >= 1 && y <= 8)
			break;  //����������곬���������̵�����Χ������ѭ��
		printf("Your input is worng!!!\n");
	}

	InitLocation(x-1, y-1);
	return 0;
}