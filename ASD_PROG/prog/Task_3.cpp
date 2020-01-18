#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iostream>

using namespace std;

struct Product{
	char name[100];
	int price;
	int quantity;
};

struct Store{
	char name[100];
	char address[300];
	int productsCount;
	Product *products[100];
	
	Store *prev, *next;
};

Store *head = 0;
Store *tail = 0;
int storesCount = 0;

Store* findCurrentStore(int pos){
	Store *current = head;
	int counter = 1;
	
	while(counter < pos && current->next != 0){
		current = current->next;
		counter++;
	}
	return current;
}

void fillProducts(Store *newStore){
	
	int i = 0;
	while(true){
		if(i >= 100){
			break;
		}
		
		printf("Add new product? (Y/N) \n");
		char command[10];
		cin.clear();
		gets(command);
		if(command[0] == 'N'){
			break;
		}
		
		newStore->products[i] = new Product;
		
		char name[100];
	    printf("Enter product's name \n");
		gets(name);
		strncpy(newStore->products[i]->name, name, 100);
		
		int price;
	    printf("Enter product's price \n");
	    scanf("%d", &price);
	    getchar();
		newStore->products[i]->price = price;
		
		int quantity;
	    printf("Enter product's quantity \n");
		scanf("%d", &quantity);
		getchar();
		newStore->products[i]->quantity = quantity;
		
		newStore->productsCount++;
		i++;			
	}
}

void isertStore(){
	
	Store *newStore = new Store;
	
	int pos = 0;
	Store *current = 0;
	if(head!=0){
		printf("Set the position of the new store in the list \n");
		scanf("%d", &pos);
		getchar();
		if(pos <= storesCount){
			current = findCurrentStore(pos);
		}
	}
	
    char name[100];
    printf("Enter a name of the store \n");
    gets(name);
	strncpy(newStore->name, name, 100);
	
	char address[300];
	printf("Enter an address of the store \n");
	gets(address);
	strncpy(newStore->address, address, 300);
	
	fillProducts(newStore);
	
	if(head == 0){
		newStore->prev = 0;
		newStore->next = 0;
		head = newStore;
		tail = newStore;
	}
	else{
		// add last element
		if(pos > storesCount){
			tail->next = newStore;
			newStore->prev = tail;
			newStore->next = 0;
			tail = newStore;
		}
		// add first element
		else if(current==head){
			current->prev = newStore;
			newStore->prev = 0;
			newStore->next = current;
			head = newStore;
		}
		// insert element
		else{
			current->prev->next = newStore;
			newStore->prev = current->prev;
			current->prev = newStore;
			newStore->next = current;
		}
	}
	storesCount++;
}

void printStores(){
	
	if(head == 0){
		printf("Stores list is empty. Fill the list first \n");
	}
	
	Store *current = head;
	int counter = 1;
	while(current != 0){
		printf("___________________________\n");
		printf("|STORE %d\n",counter);
		printf("|Name: %s\n",current->name);
		printf("|Address: %s\n",current->address);
		printf("|Products (%d): \n",current->productsCount);
		printf("|   NAME \t PRICE \t QUANYITY \n");
		for(int i = 0; i < current->productsCount; i++){
			printf("|   %s \t %d \t %d \n",current->products[i]->name,current->products[i]->price,current->products[i]->quantity);
		}
		printf("|___________________________\n");
		
		current = current->next;
		counter++;
	}
	delete current;
}

void deleteStore(){
	
	if(head==0){
		printf("Stores list is empty. Fill the list first \n");
		return;
	}
	
	int pos = 0;
	printf("Set the position of the store you want to delete \n");
	scanf("%d", &pos);
	getchar();
	
	Store *current = 0;
	if(pos <= storesCount){
		current = findCurrentStore(pos);
	}
	else{
		printf("No stores on positin %d. Try again. \n",pos);
		return;
	}
	
	// remove single element 
	if(tail == head){
		tail = 0;
		head = 0;
	}
	else{
		// remove the last element 
		if(current==tail){
			current->prev->next = 0;
			tail = current->prev;
		}
		// remove first element
		else if(current==head){
			current->next->prev = 0;
			head = current->next;
		}
		// remove element in the middle
		else{
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}
	}
	
	// destruction
	for(int i=0;i<100;i++){
		if(current->products[i] != NULL){
			delete current->products[i];
		}
	}
	delete current;
	
	storesCount--;
}

char** splitString(char str[], char separator){
	char** list = new char*[100];
	
	int j = 0;   
	int k = 0;
	list[0] = new char[100];
	for(int i = 0;i < 100; i++){
		if(str[i] == separator){
			j++;
			k = 0;
			list[j] = new char[100];
		}
		else{
			list[j][k] = str[i];
			k++;
		}
	}
	return list;
}

findStore(){
	printf("Enter products you are looking for separated by a comma (,) \n");
	
	char productsString[100];
	gets(productsString);
	char** productsList = splitString(productsString,',');
	
	printf("You can buy it in: \n");
	// search
	Store *current = head;
	while(current != 0){
		bool finded = false;
		Product **products = current->products;
		for(int j=0;j < 100 && productsList[j] != NULL;j++){
			for(int i=0; i<100 && products[i] != NULL; i++){
				if(strcmp(productsList[j],products[i]->name) == 0){
					printf("%s \n",current->name);
					finded = true;
				}
				if(finded) break;
			}
			if(finded) break;
		}	
		current = current->next;
	}
	
	// destruction
	for (int i = 0; i < 100; i++){
		delete[] productsList[i];
	}
	delete[] productsList;
}

int main(int argc, char** argv) {

	while(true){
		char command[10];
	
		printf("\n___________________________\n");
		printf("Select action: \n");
		printf("|I - insert new store \n");
		printf("|P - print stores list \n");
		if(head != 0){
			printf("|D - delete store \n");
			printf("|F - find store by product \n");
		}
		printf("|___________________________\n");
		
		gets(command);
		//scanf("%s", &(command[0]));
		
		if(command[0] == 'I'){
			isertStore();
		}
		else if(command[0] == 'P'){
			printStores();
		}
		else if(command[0] == 'D'){
			deleteStore();
		}
		else if(command[0] == 'F'){
			findStore();
		}
	}
}
