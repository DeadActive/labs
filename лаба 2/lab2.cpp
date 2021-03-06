#include "stdafx.h"
#include <stdio.h>
#include <iostream>

#define VOWELS "aeiou"

char* strlower(const char *str);
char chtolower(char c);
char* substring(const char *str, char *out, int start, int end);
int get_vowels(const char *str);
int get_vowels(char *str);

int get_vowels(const char *in) {
	char* str = strlower(in);
	int count = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (VOWELS[j] == str[i])
				count++;
		}
	}

	return count;
}

int get_vowels(char *in) {
	char* str = strlower(in);
	int count = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (VOWELS[j] == str[i])
				count++;
		}
	}

	return count;
}

char* strlower(const char *str) {
	int len = strlen(str);
	
	char* outstr = (char *)malloc(sizeof(char) * len + 1);
	
	for (int i = 0; i < len + 1; i++)
	{
		outstr[i] = chtolower(str[i]);
	}

	return outstr;
}

char chtolower(char c) {
	if (c <= 'Z' && c >= 'A')
		return c - ('Z' - 'z');
	return c;
}

char* substring(const char *in, char *out, int start, int end) {
	if (end > strlen(in)) end = strlen(in);

	for (int i = 0; i < end - start; i++)
	{
		out[i] = in[i + start];
	}
	out[end - start + 1] = 0;
	return out;
}


int _tmain(int argc, _TCHAR* argv[])
{
	const char* str = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...";
	setlocale(0, "");

	double average = (double)((double)get_vowels(str) / (double)strlen(str));
	int count = 0;

	char* fifth = (char *)malloc(5 * sizeof(char));

	for (int i = 0; i < strlen(str); i+=5)
	{
		substring(str, fifth, i, i + 5);
		
		if (get_vowels(fifth) >= average)
			count++;
	}

	printf("Колличество пятерок в которых колличество гласных больше чем %2.1lf в строке \"%s\" равно %d\n", average, str, count);
	
	system("pause");
	return 0;
}

