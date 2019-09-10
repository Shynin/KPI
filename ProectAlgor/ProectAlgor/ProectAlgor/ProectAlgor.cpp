
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


void qsortx(int *a, size_t low, size_t high) {
	size_t i, j;
	int tmp, pivot;

	i = low;
	j = high;

	pivot = a[(low + (high - low) / 2)];
	do {
		while (a[i] < pivot) {
			i++;
		}
		while (a[j] > pivot) {
			j--;
		}
		if (i <= j) {
			if (a[i] > a[j]) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
			i++;
			if (j > 0) {
				j--;
			}
		}
	} while (i <= j);

	if (i < high) {
		qsortx(a, i, high);
	}
	if (j > low) {
		qsortx(a, low, j);
	}
}

void bubbleSort(int* arrayPtr, int length_array) // сортировка пузырьком
{
	int temp = 0; // временная переменная для хранения элемента массива
	bool exit = false; // болевая переменная для выхода из цикла, если массив отсортирован

	while (!exit) // пока массив не отсортирован
	{
		exit = true;
		for (int int_counter = 0; int_counter < (length_array - 1); int_counter++) // внутренний цикл
		  //сортировка пузырьком по возрастанию - знак >
		  //сортировка пузырьком по убыванию - знак <
			if (arrayPtr[int_counter] > arrayPtr[int_counter + 1]) // сравниваем два соседних элемента
			{
				// выполняем перестановку элементов массива
				temp = arrayPtr[int_counter];
				arrayPtr[int_counter] = arrayPtr[int_counter + 1];
				arrayPtr[int_counter + 1] = temp;
				exit = false; // на очередной итерации была произведена перестановка элементов
			}
	}
}

void insertionSort(int *arrayPtr, int length) // сортировка вставками
{
	int temp, // временная переменная для хранения значения элемента сортируемого массива
		item; // индекс предыдущего элемента
	for (int counter = 1; counter < length; counter++)
	{
		temp = arrayPtr[counter]; // инициализируем временную переменную текущим значением элемента массива
		item = counter - 1; // запоминаем индекс предыдущего элемента массива
		while (item >= 0 && arrayPtr[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
		{
			arrayPtr[item + 1] = arrayPtr[item]; // перестановка элементов массива
			arrayPtr[item] = temp;
			item--;
		}
	}
}

void choicesSort(int* arrayPtr, int length_array) // сортировка выбором
{
	for (int repeat_counter = 0; repeat_counter < length_array; repeat_counter++)
	{
		int temp = arrayPtr[0]; // временная переменная для хранения значения перестановки
		for (int element_counter = repeat_counter + 1; element_counter < length_array; element_counter++)
		{
			if (arrayPtr[repeat_counter] > arrayPtr[element_counter])
			{
				temp = arrayPtr[repeat_counter];
				arrayPtr[repeat_counter] = arrayPtr[element_counter];
				arrayPtr[element_counter] = temp;
			}
		}
	}
}


int main()
{
	cout << "Enter number of array elements: ";
	int size_array;
		cin >> size_array;
		int *a = new int[size_array];
		for (int i = 0; i < size_array; i++) {
		a[i] = rand() % 20001 - 10000;
		printf("%4d ", a[i]);
	}
	printf("\n");

// вызов функции сортировки
	// qsortx(a, 0, size_array - 1);
	// bubbleSort(a, size_array);
	// insertionSort(a, size_array);
	choicesSort(a, size_array);

	for (int i = 0; i < size_array; i++)
		printf("%4d ", a[i]);
	printf("\n");
	cout << "runtime = " << clock() / 1000.0 << endl;
	getchar();
	return 0;
}


