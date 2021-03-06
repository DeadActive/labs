#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* Определяет, начинается ли строка с подстроки
* @param TestArray Строка, в которой проверяем
* @param StringToFind Строка, которую ищем
* @param count Число символов для проверки
* @return 1 - да, 0 - нет
**/
int StringStartsWith(char TestArray[], const char StringToFind[], int count)
{
	// TODO: необходимодобавить проверку на случай, если строки разной
	for (int i = 0; i < count; i++)
	{
		if (TestArray[i] != StringToFind[i])
			return 0;
	}
	return 1;
}
/**
* Структура элемента в дереве "Книга"
* @property name Название книги
* @property author Автор книги
* @property Left Указатель на левое поддерево
* @property Right Указатель на правое поддерево
* @property Parent Указатель на родительский элемент
**/
typedef struct HumanNode
{
	char name[80];
	char surname[80];
	char gender[10];
	char birthday[40];
	char number[20];
	char adress[80];
	float height;
	float weight;
	struct HumanNode* Left;
	struct HumanNode* Right;
	struct HumanNode* Parent;
} HumanNode;
/**
* Инициализация элемента дерева начальными значениями
* @param B Указатель на элемент дерева
**/
void InitNode(HumanNode* B)
{
	B->Left = NULL;
	B->Right = NULL;
	B->Parent = NULL;
}

void GetData(HumanNode* dest, HumanNode* source)
{
	strcpy_s(dest->name, source->name);
	strcpy_s(dest->surname, source->surname);
	strcpy_s(dest->gender, source->gender);
	strcpy_s(dest->birthday, source->birthday);
	strcpy_s(dest->adress, source->adress);
	strcpy_s(dest->number, source->number);

	dest->height = source->height;
	dest->weight = source->weight;

	dest->Right = source->Right;
	dest->Left = source->Left;
	dest->Parent = source->Parent;
}
/**
* Печать в консоль информации о книге
* @param B Указатель на элемент дерева
**/
void print(HumanNode* B)
{
	if (B != NULL)
		printf("\nName: %s\nSurname: %s\nGender: %s\nBirthday: %s\nHeight: %1.2f\nWeight: %3.2f\nAdress: %s\nNumber: %s\n",
			B->name,
			B->surname,
			B->gender,
			B->birthday,
			B->height,
			B->weight,
			B->adress,
			B->number);
}
/**
* Дерево книг
* @property Root Указатель на корень дерева
**/
typedef struct HumanTree
{
	HumanNode* Root;
} HumanTree;
/**
* Инициализация дерева начальным значением
* @param B Указатель на структуру дерева
**/
void InitTree(HumanTree* T)
{
	T->Root = NULL;
}
/**
* Добавление нового элемента в дерево (с рекурсивным проходом)
* @param Т Указатель на структуру дерева
* @param N Указатель на новый элемент
* @param Current Указатель на текущий элемент (при первом вызове равен
NULL)
**/
void Add_R(HumanTree* T, HumanNode* N, HumanNode* Current)
{
	if (T == NULL) return;
	if (T->Root == NULL)
	{
		T->Root = N;
		return;
	}
	if (Current == NULL) Current = T->Root;
	// Сравниваем элементы по названию
	int c = strcmp(Current->name, N->name);
	// Если новое имя больше текущего, то переходим в левое поддерево
	if (c < 0)
	{
		if (Current->Left != NULL)
			Add_R(T, N, Current->Left);
		else
			Current->Left = N;
	}
	// Если новое имя меньше текущего, то переходим в правое поддерево
	if (c > 0)
	{
		if (Current->Right != NULL)
			Add_R(T, N, Current->Right);
		else
			Current->Right = N;
	}
	if (c == 0)
	{
		//нашли совпадение имён
	}
	return;
}
/**
* Добавление нового элемента в дерево (нерекурсивная версия)
* @param Т Указатель на структуру дерева
* @param N Указатель на новый элемент
**/
void Add(HumanTree* T, HumanNode* N)
{
	if (T == NULL) return;
	if (T->Root == NULL)
	{
		T->Root = N;
		return;
	}
	HumanNode* Current = T->Root;
	while (Current != NULL)
	{
		int c = strcmp(Current->name, N->name);
		if (c < 0)
		{
			if (Current->Left != NULL)
			{
				Current = Current->Left;
				continue;
			}
			Current->Left = N;
			break;
		}
		if (c > 0)
		{
			if (Current->Right != NULL)
			{
				Current = Current->Right;
				continue;
			}
			Current->Right = N;
			break;
		}
		if (c == 0)
		{
			//нашли совпадение имён
		}
	}
}
/**
* Удаление элемента из дерева по названию
* @param Т Указатель на структуру дерева
* @param BookName Название книги
**/

HumanNode* FindMax(HumanNode* n)
{
	while (n->Right != 0)
		n = n->Right;
	return n;
}

HumanNode* FindMin(HumanNode* n)
{
	while (n->Left != 0)
		n = n->Left;
	return n;
}

/**
* Поиск элемента в дереве по названию
* @param Т Указатель на структуру дерева
* @param BookName Название книги
* @return Найденный элемент или NULL
**/
HumanNode* Find(HumanTree* T, char HumanName[])
{
	if (T == NULL) return NULL;
	HumanNode* Current = T->Root;
	while (Current != NULL)
	{
		int c = strcmp(Current->surname, HumanName);
		if (c < 0)
		{
			Current = Current->Left;
			continue;
		}
		if (c > 0)
		{
			Current = Current->Right;
			continue;
		}
		if (c == 0)
			return Current;
	}
	return NULL;
}
/**
* Поиск элемента в дереве по названию (рекурсивная версия)
* @param Т Указатель на структуру дерева
* @param BookName Название книги
* @param Current Указатель на текущий элемент (при первом вызове равен
NULL)
* @return Найденный элемент или NULL
**/
HumanNode* Find_R(HumanTree* T, const char HumanName[], HumanNode* Current)
{
	if (T == NULL) return NULL;
	if (Current == NULL) Current = T->Root;
	int c = strcmp(Current->surname, HumanName);
	if (c < 0)
	{
		if (Current->Left != NULL) return Find_R(T, HumanName, Current->Left);
		else return NULL;
	}
	if (c > 0)
	{
		if (Current->Right != NULL) return Find_R(T, HumanName, Current->Right);
		else return NULL;
	}
	if (c == 0)
		return Current;
	return NULL;
}

HumanNode* Find_R_Adress(HumanTree* T, const char Adress[], HumanNode* Current)
{
	if (T == NULL) return NULL;
	if (Current == NULL) Current = T->Root;
	int c = strcmp(Current->adress, Adress);
	if (c < 0)
	{
		if (Current->Left != NULL) return Find_R(T, Adress, Current->Left);
		else return NULL;
	}
	if (c > 0)
	{
		if (Current->Right != NULL) return Find_R(T, Adress, Current->Right);
		else return NULL;
	}
	if (c == 0)
		return Current;
	return NULL;
}

HumanNode* FindSuccessor(HumanTree* T, char HumanName[])
{
	HumanNode* x = Find(T, HumanName);
	HumanNode* y;

	if (x == 0)
		return 0;
	if (x->Right != 0)
		return FindMin(x->Right);
	y = x->Parent;

	while (y != 0 && x == y->Right) {
		x = y;
		y = y->Parent;
	}

	return y;
}

void Remove(HumanTree* T, HumanNode* n)
{
	HumanNode* y;
	HumanNode* x;
	if (n->Left == 0 || n->Right == 0)
		y = n;
	else
		y = FindSuccessor(T, n->surname);
	if (y->Left != 0)
		x = y->Left;
	else
		x = y->Right;
	if (x != 0)
		x->Parent = y->Parent;
	if (y->Parent == 0)
		T->Root = x;
	else
	{
		if (y == (y->Parent)->Left)
			(y->Parent)->Left = x;
		else
			(y->Parent)->Right = x;
	}
	if (y != n)
		GetData(n, y);
}

void FilterAdress(HumanTree* T, HumanTree* out, const char filter[])
{
	HumanNode* current = T->Root;
	HumanNode* x;

	HumanNode* n = (HumanNode*)malloc(sizeof(HumanNode));
	n = current;
	Add_R(out, n, NULL);

	if (strcmp(current->adress, filter) != 0) {
		Remove(out, current);
	}
	do
	{
		current = current->Right;
		if (strcmp(current->adress, filter) != 0) {
			Remove(out, current);
		}
	} while (current->Right != 0);
}
/**
* Вызывает переданную по указателю функцию для каждого элемента дерева
(рекурсивно обходит дерево)
* @param Node Указатель на текущий элемент дерева
* @param f Указатель на функцию-действие
**/
void MakeAction(HumanNode* Node, void(*f)(HumanNode*))
{
	if (Node != NULL)
		f(Node);
	if (Node->Left != NULL)
		MakeAction(Node->Left, f);
	if (Node->Right != NULL)
		MakeAction(Node->Right, f);
}
/**
* Загружает дерево из файла
* @param Т Дерево
* @param FileName Имя файла
**/
void Load(HumanTree* T, char FileName[])
{
	if (T == NULL) return;
	FILE* fp;
	fopen_s(&fp, FileName, "r");
	if (fp == NULL)
	{
		printf("\nCouldn't open the file: %s", FileName);
		return;
	}

	char Name[80]; char Surname[80];
	char Gender[20]; char Birthday[40];
	char Number[20]; char Adress[80];
	float Weight, Height;

	while (1)
	{

		fgets(Name, 80, fp);
		fgets(Surname, 80, fp);
		fgets(Gender, 20, fp);
		fgets(Birthday, 40, fp);
		fgets(Number, 20, fp);
		fgets(Adress, 80, fp);
		fscanf_s(fp, "%f%f", &Weight, &Height);
		//if(strcmp(Name, "NULL")!=0 && strcmp(Author, "NULL")!=0)
		if (!StringStartsWith(Name, "NULL", 4) && !
			StringStartsWith(Surname, "NULL", 4) && !
			StringStartsWith(Gender, "NULL", 4) && !
			StringStartsWith(Birthday, "NULL", 4) && !
			StringStartsWith(Number, "NULL", 4) && !
			StringStartsWith(Adress, "NULL", 4))
		{
			HumanNode* N = (HumanNode*)malloc(sizeof(HumanNode));
			InitNode(N);
			strcpy_s(N->surname, Surname); strcpy_s(N->name, Name);
			strcpy_s(N->gender, Gender); strcpy_s(N->birthday, Birthday);
			strcpy_s(N->number, Number); strcpy_s(N->adress, Adress);
			N->weight = Weight; N->height = Height;
			Add(T, N);
		}
		else
			break;
	}
	fclose(fp);
}
/**
* Сохраняем элемент в файл
* @param Node Элемент
* @param fp Указатель на файл
**/
void SaveNode(HumanNode* Node, FILE* fp)
{
	if (fp == NULL)
		return;
	if (Node != NULL)
	{
		//fprintf(fp, "%s%s", Node->name, Node->author);
		fputs(Node->name, fp);
		fputs("\n", fp);
		fputs(Node->surname, fp);
		fputs("\n", fp);
		fputs(Node->gender, fp);
		fputs("\n", fp);
		fputs(Node->birthday, fp);
		fputs("\n", fp);
		fputs(Node->number, fp);
		fputs("\n", fp);
		fputs(Node->adress, fp);
		fputs("\n", fp);
		fprintf(fp, "%f\n%f\n", Node->weight, Node->height);
		if (Node->Left != NULL)
			SaveNode(Node->Left, fp);
		if (Node->Right != NULL)
			SaveNode(Node->Right, fp);
	}
}
/**
* Сохраняем дерево в файл
* @param Т Дерево
* @param FileName Имя файла
**/
void Save(HumanTree* T, char FileName[])
{
	if (T == NULL) return;
	FILE *ptr;
	fopen_s(&ptr, FileName, "w");
	if (ptr == NULL)
	{
		printf("\nCouldn't open the file: %s", FileName);
		return;
	}
	SaveNode(T->Root, ptr);
	fputs("NULL\n", ptr);
	fputs("NULL", ptr);
	fclose(ptr);
}
/**
* Производит прямой обход (CLR) дерева и вызывает для каждого узла
переданную функцию
* @param Node Указатель на текущий элемент дерева
* @param f Указатель на функцию-действие
**/
void PreOrder(HumanNode* Node, void(*f)(HumanNode*))
{
	if (Node != NULL)
		f(Node);
	if (Node->Left != NULL)
		PreOrder(Node->Left, f);
	if (Node->Right != NULL)
		PreOrder(Node->Right, f);
}
/**
* Производит центрированный (симметричный) (LCR) обход дерева и вызывает для
каждого узла переданную функцию
* @param Node Указатель на текущий элемент дерева
* @param f Указатель на функцию-действие
**/
void InOrder(HumanNode* Node, void(*f)(HumanNode*))
{
	if (Node->Left != NULL)
		InOrder(Node->Left, f);
	if (Node != NULL)
		f(Node);
	if (Node->Right != NULL)
		InOrder(Node->Right, f);
}
/**
* Производит обратный обход (LRC) дерева и вызывает для каждого узла
переданную функцию
* @param Node Указатель на текущий элемент дерева
* @param f Указатель на функцию-действие
**/
void PostOrder(HumanNode* Node, void(*f)(HumanNode*))
{
	if (Node->Left != NULL)
		PostOrder(Node->Left, f);
	if (Node->Right != NULL)
		PostOrder(Node->Right, f);
	if (Node != NULL)
		f(Node);
}
int main()
{
	// Создаем дерево
	HumanTree Tree;
	InitTree(&Tree);
	HumanTree* ptr = &Tree;
	// Создаем несколько элементов
	HumanNode* John = (HumanNode*)malloc(sizeof(HumanNode));
	InitNode(John);
	strcpy_s(John->surname, "Smith"); strcpy_s(John->name, "John");
	strcpy_s(John->gender, "Male"); strcpy_s(John->birthday, "12.04.1975");
	strcpy_s(John->number, "+1 555 213 42 51"); strcpy_s(John->adress, "Baker st.");
	John->height = 1.8; John->weight = 81.5;
	HumanNode* Jack = (HumanNode*)malloc(sizeof(HumanNode));
	InitNode(Jack);
	strcpy_s(Jack->surname, "Sparrow"); strcpy_s(Jack->name, "Jack");
	strcpy_s(Jack->gender, "Male"); strcpy_s(Jack->birthday, "15.09.1899");
	strcpy_s(Jack->number, "+1 585 313 28 61"); strcpy_s(Jack->adress, "Tortogue");
	Jack->height = 1.75; Jack->weight = 75.5;
	HumanNode* Beth = (HumanNode*)malloc(sizeof(HumanNode));
	InitNode(Beth);
	strcpy_s(Beth->surname, "Smith"); strcpy_s(Beth->name, "Beth");
	strcpy_s(Beth->gender, "Female"); strcpy_s(Beth->birthday, "15.08.1977");
	strcpy_s(Beth->number, "+1 555 355 22 13"); strcpy_s(Beth->adress, "Baker st.");
	Beth->height = 1.62; Beth->weight = 45.8;
	// Добавляем элементы в дерево
	Add_R(ptr, John, NULL);
	Add_R(ptr, Jack, NULL);
	Add_R(ptr, Beth, NULL);
	// Поиск элемента
	HumanNode* B = Find_R(ptr, "Smith", NULL);
	if (B != NULL)
		print(B);
	printf("\n");
	// Вывод узлов дерево с обходом в глубину тремя способами
	printf("\n-----\nPreorder:");
	void(*f_ptr)(HumanNode*); f_ptr = print;
	PreOrder(Tree.Root, f_ptr);
	printf("\n-----\nInorder:");
	InOrder(Tree.Root, f_ptr);
	printf("\n-----\nPostorder:");
	PostOrder(Tree.Root, f_ptr);

	printf("\n-----\nFiltered preoder:");
	HumanTree ftree; InitTree(&ftree);
	FilterAdress(&Tree, &ftree, "Baker st.");
	PreOrder(ftree.Root, f_ptr);
	free(Jack);
	free(John);
	free(Beth);

	char c; scanf_s("%c", &c);
	return 0;
}