#include "stdafx.h"
extern "C" int eightQueen_(int *a);

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 8;
	int a[8] = {0};

	for (int i = 0; i < n; i++)
	{
		printf("%4d", a[i]);
	}
	printf("\n");

	eightQueen_(a);

	for (int i = 0; i < n; i++)
	{
		printf("%4d", a[i]);
	}
	printf("\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i] == j)
				printf(" * ");
			else
				printf(" 0 ");
		}
		printf("\n");
	}

	return 0;
}