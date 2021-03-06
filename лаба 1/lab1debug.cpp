#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

const double M_PI = 3.141592653589793238462643;

double sinx(double x, double eps = 0.00001)
{
	x = fmod(x, 2 * M_PI);	//нахождение угла в передлах [-2п;2п]

	double sum = 0.0;
	double n = x;
	int i = 1;

	do
	{
		sum += n;
		n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));

		if ((i % 3) == 0)
			printf("\nIteration %d\nsum: %lf\nn: %lf", i, sum, n);

		i++;
	} while (fabs(n) > eps);

	return sum;
}

double cosx(double x, double eps = 0.00001) {
	x = fmod(x, 2 * M_PI);	//нахождение угла в передлах [-2п;2п]

	double sum = 0.0;
	double n = 1.0;
	int i = 1;

	do
	{
		sum += n;
		n *= -1.0 * x * x / ((2 * i - 1) * (2 * i));
		i++;
	} while (fabs(n) > eps);

	return sum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double arg;

	setlocale(0, "");	// установка русской локализации

	printf("Значение аргумента = ");
	scanf_s("%lf", &arg);

	double res = sinx(3 * arg) - cosx(arg*arg) - arg + 1;
	double libres = sin(3 * arg) - cos(arg*arg) - arg + 1;

	printf("\nРезультаты вычисления sin(3x) - cos(x^2) - x + 1 при x=%lf:\n"\
		"С помощью рядов Тейлора: %lf\nС помощью библиотечных функций: %lf\n", arg, res, libres);

	return 0;
}

