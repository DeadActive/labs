#include "stdafx.h"
#include <stdio.h>
#include <iostream>

bool isComposite(int i, int itr = 100) {
	for (int n = 2; n < itr; n++)
	{
		if ((i % n) == 0) return true;
	}
	return false;
}

int getlen(int *in) {
	int len = 0;
	for (int i = 0; i < in[i]; i++)
	{
		len++;
	}
	return len;
}

int composite(int *in, int *max) {
	int _max = 0;
	int count = 0;
	
	for (int i = 0; i < getlen(in); i++)
	{
		if (isComposite(in[i])) {
			count++;
			if (in[i] > _max)
				_max = in[i];
		}
	}

	*max = _max;
	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(0, "");
	printf("Введите массив:\n");

	int(*cmpt)(int*, int*) = &composite;

	int* a = (int *)malloc(sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
	{
		printf("%d элемент:",i);
		scanf_s("%d", &a[i]);
	}

	int max = 0;

	int count = cmpt(a, &max);

	printf("\nКолличество составных чисел в массиве - %d\nНаибольшее из них - %d\n", count, max);

	system("pause");

	free(a);
	return 0;
}

