#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <string>
using namespace std;

struct list
{
    string surname;
    // string middlename;
    // string name;
    // int yyyy;
	int predmet[];
	struct list *ptr;
};

// Инициализация списка (ОЛС)
struct list * init(int a)
{
	struct list *lst;
	lst = (struct list*)malloc(sizeof(struct list)); // выделение памяти под корень списка
	lst->field = a;
	lst->ptr = NULL;			// это последний элемент списка
	return(lst);
}

struct list * addelem(list *lst, int number)
{
	struct list *temp, *p;
	temp = (struct list*)malloc(sizeof(list)); // выделение памяти под узел списка
	p = lst->ptr;				// временное сохранение указателя
	lst->ptr = temp;			// предыдущий узел указывает на создаваемый
	temp->field = number;		// сохранение поля данных добавляемого узла
	temp->ptr = p;			// созданный узел указывает на следующий элемент
	return(temp);
}

// Удаление элемента списка (возвращает предшествующий элемент) (ОЛС)
struct list  * deletelem(list *lst, list *root)
{
	struct list *temp;
	temp = root;
	while (temp->ptr != lst)				// просматриваем список начиная с корня
	{				// пока не найдем узел, предшествующий lst
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr; // переставляем указатель
	free(lst);		// освобождаем память удаляемого элемента
	return(temp);
}

// Вывод элементов списка (ОЛС)
void listprint(list *lst)
{
	struct list *p;
	p = lst;
	do {
		printf("%d ", p->field);	// вывод значения элемента p
		p = p->ptr;				// переход к следующему элементу
	} while (p != NULL);
}


int main()
{
    struct list *head, *r, *p;
	int a, n;
	system("chcp 1251");
	system("cls");
	cout << "n= ";
	scanf("%d",&n);
	head = 0;
	p = 0;
	// Создание списка
	for (int i = 0; i<n; i++)
	{
		cout << "your element:";
		scanf("%d", &a);
		if (i == 0)
		{
			p = init(a);
			head = p;
		}
		else
			p = addelem(p, a);
	}

    listprint(head);

return 0;
}

