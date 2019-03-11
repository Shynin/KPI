// ProectAlgor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#define SIZE 10


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

int main()
{
    int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = rand() % 201 - 100;
		printf("%4d ", a[i]);
	}
	printf("\n");

	qsortx(a, 0, SIZE - 1); // вызов функции сортировки
	for (int i = 0; i < SIZE; i++)
		printf("%4d ", a[i]);
	printf("\n");
	getchar();
	return 0;
}


