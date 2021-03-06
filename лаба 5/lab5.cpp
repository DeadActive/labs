#include "stdafx.h" 
#include <stdio.h> 
#include <iostream> 
#include <stdlib.h> 
#include <math.h>

int* arrcopy(int* in, size_t len);

int get_max(int* arr, int len)
{
	int mx = arr[0];
	for (int i = 0; i < len; i++)
		if (arr[i] > mx) mx = arr[i];
	return mx;
}

void bubble_sort(int* in, int len)
{
	bool exit = false;
	int t = 0;

	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (in[j] > in[j + 1]) {
				t = in[j];
				in[j] = in[j + 1];
				in[j + 1] = t;
			}
		}
	}
}

void countSort(int arr[], unsigned int n, int exp)
{
	int* output = new int[n];
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;


	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

void radix_sort(int* in, int len)
{
	int m = get_max(in, len);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(in, len, exp);
}

int* arrcopy(int* in, size_t len)
{
	int* out = (int*)calloc(len, sizeof(int));

	for (size_t i = 0; i < len; i++)
	{
		out[i] = in[i];
	}

	return out;
}

int* read_file(char *path, size_t* len)
{
	FILE* f_in;
	int* out = 0;

	fopen_s(&f_in, path, "r");

	if (f_in != 0)
	{
		fscanf_s(f_in, "%d", len);

		out = (int*)calloc(*len, sizeof(int));

		for (size_t i = 0; i < *len; i++)
			fscanf_s(f_in, "%d", &out[i]);

		fclose(f_in);
	}

	return out;
}

int write_file(char *path, int* in, size_t len)
{
	FILE* f_out;
	fopen_s(&f_out, path, "w");

	if (f_out != 0) {
		fprintf(f_out, "%d\n", len);

		for (size_t i = 0; i < len; i++)
			fprintf(f_out, "%d ", in[i]);

		fclose(f_out);

		return 1;
	}
	return 0;
}

int main()
{
	char file_in_path[] = "in.txt";
	char file_out_path[] = "out.txt";
	char c;
	size_t len;

	setlocale(0, "");

	int* arr = read_file(file_in_path, &len);
	if (arr == 0) {
		printf("Невозможно прочитать файл!\n");
		system("pause");
		return 0;
	}

	printf("Массив из файла %s: ", file_in_path);

	for (size_t i = 0; i < len; i++) printf("%d ", arr[i]);

	bubble_sort(arr, len);

	printf("\nСортированный массив пузырьком: ");

	for (size_t i = 0; i < len; i++) printf("%d ", arr[i]);

	radix_sort(arr, len);

	printf("\nСортированный массив поразрядно: ");
	for (size_t i = 0; i < len; i++) printf("%d ", arr[i]);

	printf("\nЗапись в файл...");
	if (write_file(file_out_path, arr, len) != 0)
		printf("\nЗапись в файл %s успешна", file_out_path);
	else
		printf("\nЗапись в файл %s невозможна", file_out_path);

	printf("\n");
	system("pause");
	return 0;
}