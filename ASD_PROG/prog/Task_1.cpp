#include <iostream>
#include <stdlib.h>


void printArray(int arr[],int length){
	
	for (int i = 0; i < length; i++){	
		printf("%d \t",arr[i]);
	}
	printf("\n");
}

void findPrimes(){
	int n, i, j;	
		
	printf("How many primes you want to find\n");
  	scanf("%d", &n);
	
	int primes[n];	
	
	primes[0] = 1;
	int arrLength = 1;
		
	for(i = 2;arrLength<n;i++){
		bool isPrime = true;
		
		for(j=1;j<arrLength;j++){
			if(i % primes[j] == 0){
				isPrime = false;
				break;
			}
		}
		
		if(isPrime){
			primes[j] = i;
			arrLength++;	
		}
	}
	
	printArray(primes,n);
}



int main(int argc, char** argv) {
	findPrimes();
}
