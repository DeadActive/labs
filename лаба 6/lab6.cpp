#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

struct vector
{
	int x, y, z;
};

double** array_generator(int dim1, int dim2)
{
	double** out = (double**)calloc(dim1, sizeof(double));
	for (int i = 0; i < dim1; i++)
		out[i] = (double*)calloc(dim2, sizeof(double));
	return out;
}

void array_destroyer(double** arr, int dim1)
{
	for (int i = 0; i < dim1; i++)
		free(arr[i]);
	free(arr);
}

double** matrix_multipl(double** arr1,int rows1, int cols1, double** arr2, int rows2, int cols2)
{
	double** out = array_generator(rows1, cols2);

	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols2; j++)
		{
			out[i][j] = 0;
			for (int k = 0; k < rows2; k++)
				out[i][j] += (arr1[i][k] * arr2[k][j]);
		}
	}

	return out;
}

double** arrcpy(double** arr, int dim1, int dim2)
{
	double** out = array_generator(dim1, dim2);
	for (int i = 0; i < dim1; i++)
		for (int j = 0; j < dim2; j++)
			out[i][j] = arr[i][j];
	return out;
}

double** scalar_product(double** in, int dim, vector v1, vector v2)
{
	double** arr = arrcpy(in, dim, dim);

	return 0;
}

void input_matrix(double** arr, int rows, int cols)
{
	double temp = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("[%d;%d]: ", i, j);
			scanf_s("%lf", &temp);
			arr[i][j] = temp;
		}
	}
}

int main()
{
	setlocale(0, "");
	
	printf("Введите матрицу Грама:\n");
	double** matrix = array_generator(3, 3);
	input_matrix(matrix, 3, 3);

	printf("\nВведите вектор А:\n");
	double** vector1 = array_generator(1, 3);
	input_matrix(vector1, 1, 3);
	
	printf("\nВведите вектор B:\n");
	double** vector2 = array_generator(3, 1);
	input_matrix(vector2, 3, 1);

	double** temp;
	double** result;
	temp = matrix_multipl(vector1, 1, 3, matrix, 3, 3);
	result = matrix_multipl(temp, 1, 3, vector2, 3, 1);
	
	printf("\nСкальрное произведение векторов А и В = %2.2lf\n", result[0][0]);

	system("pause");
	return 0;
}

