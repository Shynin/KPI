#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct spis {
	int asess[4];
	string sec_name;
	spis *next;
};

spis *newSpis(int n) {
	spis *student = new spis;
	spis *head = student;
	head->next = 0;
		for (int j = 0; j < 4; j++) {
			head->asess[j] = 2 + rand() % 4;
		}
		cout << "Surname " << 1 <<  " student: ";
		cin >> head->sec_name;
	for(int i = 1; i < n; i++) {
		head->next = new spis;
		head = head->next;
		head->next = 0;
		for (int j = 0; j < 4; j++) {
			head->asess[j] = 2 + rand() % 4;
		}
		cout << "Surname " << i + 1 <<  " student: ";
		cin >> head->sec_name;
	}
	return student;
}

void printSpis(spis *student) {
	spis *head = student;
	for(;head;) {
		cout << "second name: " << head->sec_name << endl;
		for(int j = 0; j < 4; j++) {
			cout << "asessment " << j+1 << ": " << head->asess[j] << endl;
		}
		head = head->next;
	}
	return;
}

spis *addStudent(spis *student) {

}

spis *delUnAsess(spis *student) {
    int ball;
    cout << "Minimum ball: ";
    cin >> ball;
    int predmet;
    cout << "Predmet #: ";
    cin >> predmet;
	spis *head = student;
	spis *buff;
    while(head && head->next) {
		for(int i = 0; i < 4; i++) {
			if(head->next->asess[predmet] < ball) {
				buff = head->next;
				head->next = head->next->next;
				delete buff;
				i = 4;
			}
		}
		head = head->next;
	}
	for(int i = 0; i < 4; i++) {
		if(student->asess[predmet] < ball) {
			buff = student->next;
			delete student;
			return buff;
		}
	}
	// while(head && head->next) {
	// 	for(int i = 0; i < 4; i++) {
	// 		if(head->next->asess[i] < ball) {
	// 			buff = head->next;
	// 			head->next = head->next->next;
	// 			delete buff;
	// 			i = 4;
	// 		}
	// 	}
	// 	head = head->next;
	// }
	// for(int i = 0; i < 4; i++) {
	// 	if(student->asess[i] < ball) {
	// 		buff = student->next;
	// 		delete student;
	// 		return buff;
	// 	}
	// }
	return student;
}

int main() {
	srand(time(0));
	int n;
	cout << "Number of students: ";
	cin >> n;
	if(!n) return 0;
	spis *student = newSpis(n);
	printSpis(student);
	cout << endl << endl << "--------------------------------------------------" << endl;
	student = delUnAsess(student);
	printSpis(student);
	return 0;
}