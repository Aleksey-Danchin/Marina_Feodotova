#include <iostream>
// #include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

int get_char_string_length(char *s)
{
	int limit = 1000;

	for (int i = 0; i < limit; i++)
	{
		if (s[i] == '\0' || s[i] == ' ' || s[i] == '\t')
		{
			return i;
		}
	}

	return limit;
}

bool is_equal(char *s1, char *s2)
{
	int counter1 = get_char_string_length(s1);
	int counter2 = get_char_string_length(s2);

	if (counter1 != counter2)
	{
		return false;
	}

	for (int i = 0; i < counter1; i++)
	{
		if (s1[i] != s2[i])
		{
			return false;
		}
	}

	return true;
}

class Food
{
private:
	char *name; // pri - закрытые данные
	int quant;
	double cost;
	static int count; // СД - статические данные

public:
	// Конструктор
	Food(char *name = "", int quant = 0, double cost = 0.0) : name(name), quant(quant), cost(cost)
	{
		count++;
	}

	// Деструктор
	~Food()
	{
		count--;
	}

	static int getCount()
	{ // МК - метод класса
		return count;
	}

	static void resetCount()
	{
		count = 0;
	}

	char *getName()
	{
		return name;
	}

	int getQuant()
	{
		return quant;
	}

	double getCost()
	{
		return cost;
	}

	// ДФ - дружественная функция
	friend void findProductByName(char *name, vector<Food> &foods);
	friend void findProductsLessThanQuantity(int quantity, vector<Food> &foods);
};

int Food::count = 0;

// Функция для таблицы
void printHeader()
{
	cout << left << setw(20) << "Название" << setw(10) << "Количество" << setw(10) << "Стоимость" << endl;
	cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
}

// Функция для таблицы
void printRow(Food &food)
{
	cout << left << setw(20) << food.getName() << setw(10) << food.getQuant() << setw(10) << fixed << setprecision(2) << food.getCost() << endl;
}

// Функция для поиска товара по названию
void findProductByName(char *name, vector<Food> &foods)
{
	bool found = false;
	printHeader();
	for (auto &food : foods)
	{
		if (is_equal(food.getName(), name))
		{
			printRow(food);
			found = true;
		}
	}
	if (!found)
	{
		cout << "Товар не найден." << endl;
	}
}

// Функция для поиска товара ниже заданной
void findProductsLessThanQuantity(int quantity, vector<Food> &foods)
{
	printHeader();
	for (auto &food : foods)
	{
		if (food.getQuant() < quantity)
		{
			printRow(food);
		}
	}
}

// Функция для сохранения данных в файл
void saveDatabaseToFile(char *filename, vector<Food> &foods)
{
	FILE *file = fopen(filename, "w");

	if (file == NULL)
	{
		printf("Ошибка открытия файла для записи.");
		exit(1);
		return;
	}

	for (auto &food : foods)
	{
		fprintf(
			 file,
			 "%s | %d | %.2f\n",
			 food.getName(), food.getQuant(), food.getCost());
	}

	fclose(file);
}

// Функция для загрузки данных из файла
void loadDatabaseFromFile(char *filename, vector<Food> &foods)
{
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Ошибка открытия файла для чтения.");
		exit(1);
		return;
	}

	int counter = 0;
	char c;
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			counter++;
		}
	}

	rewind(file);

	for (int i = 0; i < counter; i++)
	{
		char *name = new char[100];
		int quant;
		float cost;

		fscanf(
			 file,
			 "%s | %d | %f",
			 name, &quant, &cost);

		foods.push_back(Food(name, quant, cost));
	}

	fclose(file);
}

int main()
{

	setlocale(LC_ALL, "RU");

	vector<Food> foods;
	char *filename = "products.txt";

	loadDatabaseFromFile(filename, foods);

	while (true)
	{
		cout << "Доступные функции:"
			  << "\n"
			  << endl;
		cout << "Добавить новый элемент (1)" << endl;
		cout << "Распечатать базу товаров (2)" << endl;
		cout << "Поиск товара по названию (3)" << endl;
		cout << "Найти все изделия меньше заданного количества (4)" << endl;
		cout << "Сохранить базу данных в файл (5)" << endl;
		cout << "Выход из программы (6)"
			  << "\n"
			  << endl;
		cout << "Введите номер функции: ";
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Введите название товара: ";
			char *name = new char[100];
			cin >> name;
			cout << "Введите количество товара: ";
			int quant;
			cin >> quant;
			cout << "Введите стоимость товара: ";
			double cost;
			cin >> cost;
			foods.push_back(Food(name, quant, cost));
		}
		break;
		case 2:
		{
			if (foods.empty())
			{
				cout << "База данных пуста." << endl;
			}
			else
			{
				cout << "Товары в базе данных:"
					  << "\n"
					  << endl;
				printHeader();
				for (auto &food : foods)
				{
					printRow(food);
				}
			}
		}
		break;
		case 3:
		{
			cout << "Введите название товара для поиска: ";
			char *name = new char[100];
			cin >> name;
			findProductByName(name, foods);
		}
		break;
		case 4:
		{
			cout << "Введите максимальное количество товара: ";
			int quantity;
			cin >> quantity;
			findProductsLessThanQuantity(quantity, foods);
		}
		break;
		case 5:
			saveDatabaseToFile(filename, foods);
			cout << "База данных успешно сохранена в файле." << endl;
			break;
		case 6:
			return 0;
		default:
			cout << "Некорректный ввод. Попробуйте снова." << endl;
		}
	}

	return 0;
}