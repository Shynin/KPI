#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <random>
#include <limits>

using namespace std;
typedef unsigned long long int UINT64;

struct TempFile {
	ifstream* file;
	string tempFileName;
	UINT64 value;
	int position;

	TempFile *next, *prev;
};
TempFile* TFListHead = 0;

string inputFileName = "data.in";
string outputFileName = "data.out";

int mode = 0;

// 1MB, 10MB, 100MB, 1GB
int fileSizes[] = {131072, 1310720, 13107200, 134217728};
int tempFilesNeeded[] = { 10, 50, 250, 1000 };

void selectWorkMode();
void writeToFile(UINT64 arr[], int arr_pos[], int length, string fileName, bool uniqOnly);
void readFromFile(UINT64 arr[], int length, string fileName);
int getInputsCount(string fileName);
void fillArray(UINT64 arr[], int length);
void printArray(UINT64 arr[], int length);
void generateSorceFile();
void sortData(char alg[]);
void insertionSort(UINT64 arr[], int arr_pos[], int length);
void radixSort(UINT64 arr[], int arr_pos[], int length);
void sortLargeData(char alg[]);
void printTime(bool startTime);

int main(int argc, char** argv) {

	while (true) {
		char command[10];

		printf("\n___________________________\n");
		printf("Select action: \n");
		printf("|G - generate sorce file \n");
		printf("|S - sort data \n");
		printf("|SL - sort large data \n");
		printf("|___________________________\n");

		gets(command);

		if (command[0] == 'G') {
			generateSorceFile();
		}
		else if (command[0] == 'S') {

			char alg[10];

			while (true) {
				printf("\n___________________________\n");
				printf("Select sorting algorithm: \n");
				printf("|I - insertion sort \n");
				printf("|R - radix sort \n");
				printf("|___________________________\n");

				gets(alg);

				if (alg[0] == 'I' || alg[0] == 'R') {
					break;
				}
			}

			if (command[1] == 'L') {
				selectWorkMode();
				sortLargeData(alg);
			}
			else {
				sortData(alg);
			}
		}
	}

	return 0;
}

void selectWorkMode() {
	int m = 0;

	printf("\n___________________________\n");
	printf("Select work mode: \n");
	printf("|0 - Super-short \n");
	printf("|1 - Short \n");
	printf("|2 - Half \n");
	printf("|3 - Full \n");
	printf("|___________________________\n");

	scanf("%d", &m);
	getchar();

	if(m > 0 || m < 3){
		mode = m;
	}
	else{
		printf("Incorrect mode was selected. Super-short is set.\n");
		mode = 0;
	}
}

int getInputsCount(string fileName) {
	int count = 0;
	string line;
	ifstream myfile;

	myfile.open(fileName);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			count++;
		}
	}
	myfile.close();

	return count;
}

void sortLargeData(char alg[]) {

	int intsInTempFile = fileSizes[mode] / tempFilesNeeded[mode];
	UINT64 *data = new UINT64[intsInTempFile];
	int *positions = new int[intsInTempFile];

	int tempFilesCount = 0;
	ifstream myReadFile;

	printTime(true);

	myReadFile.open(inputFileName);
	if (myReadFile.is_open()) {
		int pos = 1;
		while (true) {
			int i = 0;

			while (!myReadFile.eof()) {
				myReadFile >> data[i];
				i++;
				if (i >= intsInTempFile) {
					break;
				}
			}

			int len = myReadFile.eof() ? i - 1 : i;

			// positions
			for (int k = pos;k <= len + pos; k++) {
				positions[k - pos] = k;
			}
			pos = pos + len;

			if (alg[0] == 'I') {
				insertionSort(data, positions, len);
			}
			else if (alg[0] == 'R') {
				radixSort(data, positions, len);
			}
			else {
				printf("\nIncorrect algorithm was selected\n");
				return;
			}

			tempFilesCount++;
			string fname = "temp_" + to_string(tempFilesCount) + ".in";
			writeToFile(data, positions, len, fname, false);

			if (myReadFile.eof()) {
				break;
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		TempFile* current = 0;
		for (int i = 0; i < tempFilesCount; i++) {
			TempFile* newTF = new TempFile;
			newTF->tempFileName = "temp_" + to_string(i + 1) + ".in";
			newTF->file = new ifstream;
			(*(newTF->file)).open(newTF->tempFileName);
			newTF->value = 0;
			(*(newTF->file)) >> newTF->value;
			(*(newTF->file)) >> newTF->position;
			newTF->next = 0;
			newTF->prev = 0;

			if (TFListHead == 0) {
				TFListHead = newTF;
			}

			if (current != 0) {
				current->next = newTF;
				newTF->prev = current;
			}

			current = newTF;
		}

		ofstream resultFile;
		resultFile.open(outputFileName, ofstream::out);
		UINT64 lastWriten = 0;
		while (true) {
			TempFile* minTF = TFListHead;
			TempFile* current = TFListHead;
			while (current != 0) {
				if (current->value < minTF->value) {
					minTF = current;
				}
				current = current->next;
			}

			if (minTF->value != lastWriten) {
				resultFile << to_string(minTF->value) + "\t" + to_string(minTF->position) + "\n";
				lastWriten = minTF->value;
			}

			if (!(*(minTF->file)).eof()) {
				(*(minTF->file)) >> minTF->value;
				(*(minTF->file)) >> minTF->position;
			}
			else {
				(*(minTF->file)).close();

				if (minTF->next == 0 && minTF->prev == 0) {
					TFListHead = 0;
				}
				else if (minTF->next != 0 && minTF->prev == 0) {
					TFListHead = minTF->next;
					minTF->next->prev = 0;
				}
				else if (minTF->next == 0 && minTF->prev != 0) {
					minTF->prev->next = 0;
				}
				else {
					minTF->prev->next = minTF->next;
					minTF->next->prev = minTF->prev;
				}

				delete minTF->file;
				delete minTF;
			}
			if (TFListHead == 0) {
				break;
			}
		}
	}

	for (int i = 0; i < tempFilesCount; i++) {
		string fname = "temp_" + to_string(i + 1) + ".in";
		remove(fname.c_str());
	}

	myReadFile.close();

	printTime(false);

	delete[] data;
	delete[] positions;
}

void sortData(char alg[]) {
	int inputsCount;

	printTime(true);

	inputsCount = getInputsCount(inputFileName);

	UINT64 *data = new UINT64[inputsCount];

	readFromFile(data, inputsCount, inputFileName);

	int *positions = new int[inputsCount];
	for (int i = 1; i <= inputsCount; i++) {
		positions[i - 1] = i;
	}

	if (alg[0] == 'I') {
		insertionSort(data, positions, inputsCount);
	}
	else if (alg[0] == 'R') {
		radixSort(data, positions, inputsCount);
	}
	else {
		printf("\nIncorrect algorithm was selected\n");
		return;
	}

	writeToFile(data, positions, inputsCount, outputFileName, true);

	printTime(false);

	delete[] data;
	delete[] positions;
}

void insertionSort(UINT64 arr[], int arr_pos[], int length) {
	int i, j;
	UINT64 buff;
	int buff_pos;

	for (i = 1; i < length; i++) {
		j = i;
		while (j > 0 && arr[j] < arr[j - 1]) {
			buff = arr[j];
			buff_pos = arr_pos[j];

			arr[j] = arr[j - 1];
			arr_pos[j] = arr_pos[j - 1];

			arr[j - 1] = buff;
			arr_pos[j - 1] = buff_pos;

			j--;
		}
	}
}

void generateSorceFile() {

	selectWorkMode();

	UINT64 *data = new UINT64[fileSizes[mode]];
	fillArray(data, fileSizes[mode]);
	writeToFile(data, 0, fileSizes[mode], inputFileName, false);

	delete[] data;
}

void fillArray(UINT64 arr[], int length) {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<unsigned long long int> distr;

	for (int i = 0; i < length; i++) {
		arr[i] = distr(gen);
	}
}

void printArray(UINT64 arr[], int length) {
	for (int i = 0; i < length; i++) {
		printf("%llu \t", arr[i]);
	}
	printf("\n");
}

void writeToFile(UINT64 arr[], int arr_pos[], int length, string fileName, bool uniqOnly) {
	ofstream myfile;
	myfile.open(fileName, ofstream::out);

	UINT64 previous = 0;
	for (int i = 0; i < length; i++) {
		if (!uniqOnly || arr[i] != previous) {
			string pos_str = "";
			if (arr_pos != 0) {
				pos_str = "\t" + to_string(arr_pos[i]);
			}
			myfile << to_string(arr[i]) + pos_str + "\n";
		}
		if (uniqOnly) {
			previous = arr[i];
		}
	}
	myfile.close();
}

void readFromFile(UINT64 arr[], int length, string fileName) {

	ifstream myReadFile;
	myReadFile.open(fileName);
	if (myReadFile.is_open()) {
		int i = 0;
		while (!myReadFile.eof()) {
			myReadFile >> arr[i];
			i++;
		}
	}
	myReadFile.close();
}

void radixSort(UINT64 arr[], int arr_pos[], int length) {
	int maxDigits = 20;
	UINT64 exp = 1;

	for (int i = 1; i <= maxDigits; exp *= 10, i++) {

		UINT64 *output = new UINT64[length];
		int *output_pos = new int[length];

		int count[10] = { 0 };

		for (int j = 0; j < length; j++){
			int dig = (arr[j] / exp) % 10;
			count[dig]++;
		}

		for (int j = 1; j < 10; j++) {
			count[j] += count[j - 1];
		}

		for (int j = length - 1; j >= 0; j--)
		{
			int dig = (arr[j] / exp) % 10;
			int pos = count[dig] - 1;
			output[pos] = arr[j];
			output_pos[pos] = arr_pos[j];

			count[dig]--;
		}

		for (int j = 0; j < length; j++){
			arr[j] = output[j];
			arr_pos[j] = output_pos[j];
		}

		delete[] output;
		delete[] output_pos;
	}
}

void printTime(bool startTime) {
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	if (startTime) {
		cout << "Start time is:" << asctime(timeinfo) << endl;
	}
	else {
		cout << "End time is:" << asctime(timeinfo) << endl;
	}
}
