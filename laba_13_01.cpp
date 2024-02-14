#include <iostream>
#include <string.h>

using namespace std;

struct Letter {
	char* adr1;  // адрес получателя
	char* fam1;  // фамилия получателя
	char* name1; // имя получателя
	char* adr2;  // адрес отправителя
	char* fam2;  // фамилия отправителя
	char* name2; // имя отправителя
	double cost; // стоимость письма
};

// Динамически веделяем память по 100 писем
Letter* letters = new Letter[100];

// Считаем скоько реальных писем есть в списке
// чтобы случайно не перебрать несуществующие письма
int letterCounter = 0;

void printLettersTable (Letter* letters, int letterCounter) {
	printf("From\t\tSName\t\tSSurname\t\tRName\t\tRSurname\t\tCost\n");
	for (int i = 0; i < letterCounter; i++) {
		printf(
			"%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%f\n",
			letters[i].adr1,
			letters[i].fam1,
			letters[i].name1,
			letters[i].adr2,
			letters[i].fam2,
			letters[i].name2,
			letters[i].cost
		);
	}
	printf("\n");
}

void addLetter () {
	Letter l;

	printf("From: ");
	l.adr1 = new char(100);
	scanf("%s", l.adr1);
	
	printf("SName: ");
	l.fam1 = new char(100);
	scanf("%s", l.fam1);

	// TODO: ввеси каждое поле по 
	// примеру выше
	l.name1 = "Максим";
	l.adr2 = "Питера";
	l.fam2 = "Петрова";
	l.name2 = "Мария";
	l.cost = 12.1;

	letters[letterCounter] = l;
	letterCounter++;
}

void searchByRName (Letter*& finedLetters, int& counter) {
	char* name = new char[100];
	printf("Введите имя поиска: ");
	scanf("%s", name);

	counter = 0;
	for (int i = 0; i < letterCounter; i++) {
		if (strcmp(letters[i].name2, name)) {
			counter++;
		}
	}

	finedLetters = new Letter[counter];
	int index = 0;
	for (int i = 0; i < letterCounter; i++) {
		if (strcmp(letters[i].name2, name)) {
			finedLetters[index] = letters[i];
			index++;
		}
	}
}

// TODO: Сделать аналог с searchByRName только по fam2
void searchByRSurname () {}

// TODO: Сделать аналог с searchByRName только по cost
void searchByCost () {}

int main () {
	// Создадим 3 письма
	letters[0].adr1 = "Москва";
	letters[0].fam1 = "Петров";
	letters[0].name1 = "Максим";
	letters[0].adr2 = "Питера";
	letters[0].fam2 = "Петрова";
	letters[0].name2 = "Мария";
	letters[0].cost = 12.1;
	letterCounter++;

	letters[1].adr1 = "Москва";
	letters[1].fam1 = "Петров";
	letters[1].name1 = "Максим";
	letters[1].adr2 = "Питера";
	letters[1].fam2 = "Петрова";
	letters[1].name2 = "Мария";
	letters[1].cost = 12.1;
	letterCounter++;

	letters[2].adr1 = "Петрова";
	letters[2].fam1 = "Мария";
	letters[2].name1 = "Максим";
	letters[2].adr2 = "Москва";
	letters[2].fam2 = "Петров";
	letters[2].name2 = "Максим";
	letters[2].cost = 9.87;
	letterCounter++;

	Letter* finedLetters;
	int finedLettersCounter;
	searchByRName(finedLetters, finedLettersCounter);
	printLettersTable(finedLetters, finedLettersCounter);


	// addLetter();

	// printLettersTable(letters, letterCounter);
}
