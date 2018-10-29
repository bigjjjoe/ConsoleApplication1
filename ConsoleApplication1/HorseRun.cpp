#include "stdafx.h"
#define MAXSIZE 100

extern "C" int CanIGo_(int i, int j, int broad[], int H[]);
struct Stack
{
	int i;                  //行坐标
	int j;                  //列坐标
	int director;           //存储方向
}stack[MAXSIZE];


//为传入寄存器方便 将broad设为一维数组
int board[64];
int N = 8;
int x, y;
int top = -1;
//i和i+8配对
int Htry[16] = { 1,-1,-2,2, 2, 1,-1,-2,   2,-2, 1,1,-1,-2, 2,-1 };


int TryPath(int i, int j)
{
	int find, director, number, min;
	int i1, j1, h, k, s;              //定义几个临时变量
	int a[8], b1[8], b2[8], d[8];     //定义几个临时数组
	while (top>-1)                 //栈不空时循环
	{
		for (h = 0; h<8; h++)    //用数组a[8]记录当前位置的下一个位置的可行路径的条数
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


		for (h = 0; h<8; h++)     //根据可行路径条数小到大按下表排序放入数组d[8]中
		{
			min = 9;
			for (k = 0; k<8; k++)
				if (min>a[k])
				{
					min = a[k];
					d[h] = k;    //将下表存入数组d[8]中
					s = k;
				}
			a[s] = 9;
		}
		director = stack[top].director;
		if (top >= 63)                 //如果走完整个棋盘返回
			return (1);
		find = 0;                     //表示没有找到下一个位置


		/**********功能与上 相似 用汇编语言编写************/
		for (h = director + 1; h<8; h++)   //向八个方向进行探寻
		{
			i = stack[top].i + Htry[d[h]];
			j = stack[top].j + Htry[d[h]+8];
			if (board[i * 8 + j] == 0 && i >= 0 && i<8 && j >= 0 && j<8) //如果找到下一位置
			{
				find = 1;       //表示找到下一个位置
				break;
			}
		}
		/***********************/


		if (find == 1)          //如果找到下一个位置进栈
		{
			stack[top].director = director; //存储栈结点的方向
			top++;                      //栈指针前移进栈
			stack[top].i = i;
			stack[top].j = j;
			stack[top].director = -1;    //重新初始化下一栈结点的尝试方向
			board[i * 8 + j] = top + 1;         //标记棋盘
		}
		else                           //否则退栈
		{
			board[stack[top].i*8+stack[top].j] = 0;  //清除棋盘的标记
			top--;                     //栈指针前移退栈
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
			printf("\t%d  ", board[i * 8 + j]);  //输出马儿在棋盘上走过的路径
		printf("\n\n");
	}
	printf("\n");
}

void InitLocation(int xi, int yi)
{
	top++;                  //栈指针指向第一个栈的底层
	stack[top].i = xi;           //将起始位置的横坐标进栈
	stack[top].j = yi;           //将起始位置的纵坐标进栈
	stack[top].director = -1;     //将起始位置的尝试方向赋初值
	board[xi*8+yi] = top + 1;       //标记棋盘
	if (TryPath(xi, yi))            //调用马儿探寻函数，如果马儿探寻整个棋盘返回1否则返回0
		Display();         //输出马儿的行走路径
	else
		printf("sorry ，There is no solution");
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
		scanf_s("%d", &x);         //输入起始位置的横坐标
		printf("Input y = ");
		scanf_s("%d", &y);         //输入起始位置的纵坐标
		if (x >= 1 && x <= 8 && y >= 1 && y <= 8)
			break;  //若输入的坐标超出所给棋盘的允许范围则跳出循环
		printf("Your input is worng!!!\n");
	}

	InitLocation(x-1, y-1);
	return 0;
}