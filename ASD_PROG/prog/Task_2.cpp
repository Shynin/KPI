#include <iostream>
#include <stdlib.h>
#include <time.h>

void fillMatrix(int** matrix, int n){	
	srand(time(NULL));
	for(int i = 0; i < n; i++) {
        matrix[i] = new int[n]; 
        for(int j = 0; j < n; j++){ 
			// matrix[i][j] = rand() % 150;
			*(*(matrix+i)+j) = rand() % 150;
		}
    }
}

void printMatrix(int** matrix, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			//printf("%d \t",matrix[i][j]);
			printf("%d \t",*(*(matrix+i)+j));
		}
		printf("\n");
	}
}

void clearMatrix(int** matrix, int n){
	for (int i = 0; i < n; i++){
		delete[] matrix[i];
	}
	delete[] matrix;
}

void findPalindromes(){
	int n;
	
	printf("Enter dimension of a matrix \n");
  	scanf("%d", &n);
	
	int** matrix = new int*[n];
	
	fillMatrix(matrix,n);
	printMatrix(matrix,n);
	
	printf("\nPalindromes:\n");
	
	for(int i = 0;i<n;i++){
		for(int j=i;j<n-i;j++){
			int elem = matrix[i][j];
			if((elem >= 0 && elem <= 9) || (elem < 100 && elem % 11 == 0)){
				printf("%d \t",elem);	
			}
		}
	}
	
	clearMatrix(matrix,n);
}

void findPalindromesWithPointers(){
	int n;
	
	printf("Enter dimension of a matrix \n");
  	scanf("%d", &n);
	
	int** matrix = new int*[n];
	
	fillMatrix(matrix,n);
	printMatrix(matrix,n);
	
	printf("\nPalindromes:\n");
	
	for(int i = 0;i<n;i++){
		for(int j=i;j<n-i;j++){
			int elem = *(*(matrix+i)+j);
			if((elem >= 0 && elem <= 9) || (elem < 100 && elem % 11 == 0)){
				printf("%d \t",elem);	
			}
		}
	}
	
	clearMatrix(matrix,n);
}


int main(int argc, char** argv) {
	findPalindromes();
	//findPalindromesWithPointers();
}
