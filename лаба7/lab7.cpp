#include "stdafx.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include <iostream> 
#include <string> 

struct Human
{
	int Key;
	float height, weight;

	char name[80];
	char surname[80];
	char gender[80];
	char birthday_date[80];
	char telephone_number[80];
	char adress[80];

	struct Human* next;
};
typedef struct Human Human;
void InitElement(Human* e, int K)
{
	e->next = NULL;
	e->Key = K;
}

typedef struct
{
	Human* First;
} List;

void InitList(List* L)
{
	L->First = NULL;
}

void add(List* L, Human* e)
{
	if (L->First == NULL)
	{
		L->First = e;
		return;
	}

	Human* Current = L->First;

	while (Current->next != NULL)
	{
		Current = Current->next;
	}

	e->next = NULL;
	Current->next = e;
}

Human* Search(List* L, Human* e)
{
	Human* Current = L->First;

	while (Current != NULL && Current->Key != e->Key)
	{
		Current = Current->next;
	}

	return Current;
}

void Insert(List* L, Human* WhereToInsert, Human* e)
{
	if (L->First == NULL)
	{
		L->First = e;
		return;
	}
	Human* p = Search(L, WhereToInsert);
	if (p == NULL) return;
	e->next = WhereToInsert->next;
	WhereToInsert->next = e;
}

Human* Successor(List* L, Human* e)
{
	Human* p = Search(L, e);
	if (p != NULL) return p->next;
	return NULL;
}

Human* Predecessor(List* L, Human* e)
{
	Human* Current = L->First;
	if (Current == NULL) return NULL;
	if (Current->Key == e->Key) return NULL;

	while (Current->next != NULL && Current->next->Key != e->Key)
	{
		Current = Current->next;
	}

	return Current;
}

void Free(List*L, Human* e)
{
	free(e);
}

void remove(List* L, Human* e)
{
	Human* p = Search(L, e);
	if (p == NULL) return;
	Human* prev = Predecessor(L, e);
	Human* next = Successor(L, e);
	prev->next = next;
	Free(L, p);
}

int list_range(List* l) {
	Human* current = l->First;
	int c = 1;
	while (current->next != NULL)
	{
		c++;
		current = current->next;
	}

	return c;
}

int SaveList(List* l, const char* path)
{
	FILE* f_out;
	fopen_s(&f_out, path, "w");
	Human* current = l->First;
	if (f_out != 0) {
		fprintf(f_out, "%d\n", list_range(l));
		while (current != NULL) {
			fprintf(f_out, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n%f\n",
				current->Key,
				current->name,
				current->surname,
				current->gender,
				current->adress,
				current->telephone_number,
				current->birthday_date,
				current->height,
				current->weight);
			current = current->next;
		}
		fclose(f_out);
		return 0;
	}
	fclose(f_out);
	return 1;
}

void LoadList(List* l, const char* path)
{
	FILE* f_in;
	fopen_s(&f_in, path, "r");
	InitList(l);

	if (f_in != 0) {
		int c;
		fscanf_s(f_in, "%d\n", &c);

		int Key = 0;
		float height = 0.0;
		float weight = 0.0;

		char name[80] = "";
		char surname[80] = "";
		char gender[80] = "";
		char birthday_date[80] = "";
		char telephone_number[80] = "";
		char adress[80] = "";

		for (int i = 0; i < c; i++)
		{
			fscanf_s(f_in, "%d\n", &Key);
			fgets(name, 80, f_in);
			fgets(surname, 80, f_in);
			fgets(gender, 80, f_in);
			fgets(birthday_date, 80, f_in);
			fgets(telephone_number, 80, f_in);
			fgets(adress, 80, f_in);
			fscanf_s(f_in, "%f\n", &weight);
			fscanf_s(f_in, "%f\n", &height);

			Human* human = (Human*)malloc(sizeof(Human));
			human->Key = Key;
			human->height = height;
			human->weight = weight;
			strcpy_s(human->name, 80, name);
			strcpy_s(human->surname, 80, surname);
			strcpy_s(human->gender, 80, gender);
			strcpy_s(human->birthday_date, 80, birthday_date);
			strcpy_s(human->telephone_number, 80, telephone_number);
			strcpy_s(human->adress, 80, adress);

			add(l, human);
		}
		fclose(f_in);
	}
}

void MakeAction(List* L, void(*f_ptr)(Human*), Human* e)
{
	if (e == NULL)
		e = L->First;
	if (e == NULL) return;
	f_ptr(e);
	if (e->next != NULL)
		MakeAction(L, f_ptr, e->next);
}

Human* find_bysurname(List* l, const char* surname)
{
	Human* current = l->First;

	while (current != NULL && _strcmpi(current->surname, surname))
	{
		current = current->next;
	}
	return current;
}

List filter_byadress(List* l, const char* addr)
{
	List outl;
	InitList(&outl);

	Human* current = l->First;

	while (current != NULL)
	{
		if (_strcmpi(current->adress, addr))
			add(&outl, current);
		current = current->next;
	}

	return outl;
}

int main()
{
	setlocale(0, "");

	Human* a = (Human*)malloc(sizeof(Human)); InitElement(a, 0);
	Human* b = (Human*)malloc(sizeof(Human)); InitElement(b, 1);
	Human* c = (Human*)malloc(sizeof(Human)); InitElement(c, 2);

	strcpy_s(a->name, 80, "Константин"); strcpy_s(a->surname, 80, "Кузнецов");
	strcpy_s(a->gender, 80, "Мужской"); strcpy_s(a->birthday_date, 80, "19.04.2000");
	strcpy_s(a->adress, 80, "ул. Пушкина"); strcpy_s(a->telephone_number, 80, "8 999 123 45 67");
	a->height = 1.7; a->weight = 63.2;
	strcpy_s(b->name, 80, "Василий"); strcpy_s(b->surname, 80, "Пупкин");
	strcpy_s(b->gender, 80, "Мужской"); strcpy_s(b->birthday_date, 80, "12.07.1993");
	strcpy_s(b->adress, 80, "Советский союз"); strcpy_s(b->telephone_number, 80, "8 999 132 55 66");
	b->height = 1.89; b->weight = 72.5;
	strcpy_s(c->name, 80, "Алена"); strcpy_s(c->surname, 80, "Караваева");
	strcpy_s(c->gender, 80, "Женский"); strcpy_s(c->birthday_date, 80, "19.04.2000");
	strcpy_s(c->adress, 80, "ул. Пушкина"); strcpy_s(c->telephone_number, 80, "8 495 121 43 65");
	c->height = 1.61; c->weight = 45.8;

	printf("%s\n", a->adress);
	List L; InitList(&L);
	add(&L, a); add(&L, b); Insert(&L, b, c);

	SaveList(&L, "list.txt");
	List ll;
	LoadList(&ll, "list.txt");

	Human* p = find_bysurname(&L, "Пупкин");
	printf("%s\n", p->adress);

	List lf = filter_byadress(&L, "ул. Пушкина");

	system("pause");
	return 0;
}
