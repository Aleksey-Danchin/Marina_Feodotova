#include <stdio.h>
#include <stdlib.h>

char* FILE_NAME = "letters.txt";

struct Letter {
	char* adr1;  // адрес получателя
	char* fam1;  // фамилия получателя
	char* name1; // имя получателя
	char* adr2;  // адрес отправителя
	char* fam2;  // фамилия отправителя
	char* name2; // имя отправителя
	float cost; // стоимость письма
};

int get_char_string_length (char* s) {
	int limit = 1000;

	for (int i = 0; i < limit; i++) {
		if (s[i] == '\0' || s[i] == ' ' || s[i] == '\t') {
			return i;
		}
	}

	return limit;
}

bool is_equal (char* s1, char* s2) {
	int counter1 = get_char_string_length(s1);
	int counter2 = get_char_string_length(s2);

	if (counter1 != counter2) {
		return false;
	}

	for (int i = 0; i < counter1; i++) {
		if (s1[i] != s2[i]) {
			return false;
		}
	}

	return true;
}

void print_letters_table (Letter* letters, int counter) {
	printf("From\t\tSName\t\tSSurname\tTo\t\tRName\t\tRSurname\tCost\n");
	printf("-----------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < counter; i++) {
		printf(
			"%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%.2f\n",
			letters[i].adr1,
			letters[i].fam1,
			letters[i].name1,
			letters[i].adr2,
			letters[i].fam2,
			letters[i].name2,
			letters[i].cost
		);
	}
}

Letter enter_letter () {
	Letter letter;

	printf("From: ");
	letter.adr1 = new char(100);
	scanf("%s", letter.adr1);
	
	printf("Reciver Surname: ");
	letter.fam1 = new char(100);
	scanf("%s", letter.fam1);

	printf("Reciver Name: ");
	letter.name1 = new char(100);
	scanf("%s", letter.name1);

	printf("To: ");
	letter.adr2 = new char(100);
	scanf("%s", letter.adr2);
	
	printf("Senler Name: ");
	letter.fam2 = new char(100);
	scanf("%s", letter.fam2);

	printf("Senler Surname: ");
	letter.name2 = new char(100);
	scanf("%s", letter.name2);

	printf("Cost: ");
	scanf("%f", &letter.cost);

	return letter;
}

void search_by_name (
	char* name,
	Letter* letters, int counter,
	Letter*& fined, int& size
) {
	size = 0;
	for (int i = 0; i < counter; i++) {
		if (is_equal(letters[i].name2, name)) {
			size++;
		}
	}

	fined = new Letter[size];
	int index = 0;
	for (int i = 0; i < counter; i++) {
		if (is_equal(letters[i].name2, name)) {
			fined[index] = letters[i];
			index++;
		}
	}
}

void search_by_surname (
	char* surname,
	Letter* letters, int counter,
	Letter*& fined, int& size
) {
	size = 0;
	for (int i = 0; i < counter; i++) {
		if (is_equal(letters[i].fam2, surname)) {
			size++;
		}
	}

	fined = new Letter[size];
	int index = 0;
	for (int i = 0; i < counter; i++) {
		if (is_equal(letters[i].fam2, surname)) {
			fined[index] = letters[i];
			index++;
		}
	}
}

void search_by_cost (
	float cost,
	Letter* letters, int counter,
	Letter*& fined, int& size
) {
	size = 0;
	for (int i = 0; i < counter; i++) {
		if (letters[i].cost >= cost) {
			size++;
		}
	}

	fined = new Letter[size];
	int index = 0;
	for (int i = 0; i < counter; i++) {
		if (letters[i].cost >= cost) {
			fined[index] = letters[i];
			index++;
		}
	}
}

void from_file (char* file_name, Letter*& letters, int& counter) {
	FILE* file = fopen(file_name, "r");

	if (file == NULL) {
		printf("Can't open file for read.");
		exit(1);
		return;
	}

	counter = 0;
	char c;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			counter++;
		}
	}

	rewind(file);
	letters = new Letter[1000];

	for (int i = 0; i < counter; i++) {
		letters[i].adr1 = new char[100];
		letters[i].fam1 = new char[100];
		letters[i].name1 = new char[100];
		letters[i].adr2 = new char[100];
		letters[i].fam2 = new char[100];
		letters[i].name2 = new char[100];

		fscanf(
			file,
			"%s | %s | %s | %s | %s | %s | %f",
			letters[i].adr1,
			letters[i].fam1,
			letters[i].name1,
			letters[i].adr2,
			letters[i].fam2,
			letters[i].name2,
			&letters[i].cost
		);
	}

	fclose(file);
}

void to_file (char* file_name, Letter*& letters, int& counter) {
	FILE* file = fopen(file_name, "w");

	if (file == NULL) {
		printf("Can't open file for write.");
		exit(1);
		return;
	}

	for (int i = 0; i < counter; i++) {
		fprintf(
			file,
			"%s | %s | %s | %s | %s | %s | %.2f\n",
			letters[i].adr1,
			letters[i].fam1,
			letters[i].name1,
			letters[i].adr2,
			letters[i].fam2,
			letters[i].name2,
			letters[i].cost
		);
	}

	fclose(file);
}

int main () {
	Letter* letters;
	int counter;

	from_file(FILE_NAME, letters, counter);
	print_letters_table(letters, counter);

	while (true) {
		int command = -1;

		printf("\n");
		printf("Table                  0\n");
		printf("Write to file ........ 1\n");
		printf("Enter new letter       2\n");
		printf("Search by name ....... 3\n");
		printf("Search by surname      4\n");
		printf("Search by cost ....... 5\n");
		printf("Exit                   6\n");

		printf("\nEnter command: ");

		// Из интернета.
		// Если случайно будет введено не число,
		// а строчка (чтобы не было вечного цикла)
		if (scanf("%d", &command) != 1) {
			while(fgetc(stdin) != '\n');
		}

		printf("\n");

		if (command == 0) {
			print_letters_table(letters, counter);
		}
		
		else if (command == 1) {
			to_file(FILE_NAME, letters, counter);
			printf("\ndone\n");
		}
		
		else if (command == 2) {
			letters[counter] = enter_letter();
			counter++;
			printf("\ndone\n");
		}
		
		else if (command == 3) {
			char* name = new char[100];
			printf("Enter search name: ");
			scanf("%s", name);

			Letter* fined;
			int size;
			search_by_name(
				name,
				letters, counter,
				fined, size
			);

			print_letters_table(fined, size);
		}
		
		else if (command == 4) {
			char* surname = new char[100];
			printf("Enter search surname: ");
			scanf("%s", surname);

			Letter* fined;
			int size;
			search_by_surname(
				surname,
				letters, counter,
				fined, size
			);

			print_letters_table(fined, size);
		}
		
		else if (command == 5) {
			printf("Enter search cost: ");
			float cost;
			scanf("%f", &cost);

			Letter* fined;
			int size;
			search_by_cost(
				cost,
				letters, counter,
				fined, size
			);

			print_letters_table(fined, size);
		}
		
		else if (command == 6) {
			break;
		}
		
		else {
			printf("Command not recognize.\n");			
		}
	};
	
	printf("Goodbuy\n");
}
