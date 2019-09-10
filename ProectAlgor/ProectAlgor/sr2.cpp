#include <iostream>
using namespace std;

int main()
{
	cout << "Enter number of array elements: ";
	int size_array;
		cin >> size_array;
		int *a = new int[size_array];
		for (int i = 0; i < size_array; i++) {
		a[i] = rand() % 201 - 100;
		printf("%4d ", a[i]);
	}
	printf("\n");
    int max = a[0];
    for(int i = 0; i < size_array; i++){
        if(a[i] > max){
            max = a[i];
        }
    }
    int min = a[0];
    for(int i = 0; i < size_array; i++){
        if(a[i] < min){
            min = a[i];
        }
    }
    int count = max * min;
    cout << "max= " << max << endl;
    cout << "min = " << min << endl;
    cout << "max*min = " << count << endl;
	return 0;
}