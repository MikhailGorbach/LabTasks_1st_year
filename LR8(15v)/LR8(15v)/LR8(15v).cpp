#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

//Константы
const int sizefio = 15;

//Структуры
struct birth {
	int day;
	int month;
	int year;
};
struct anketa {
	char fio[sizefio];
	char gender;
	int salary;
	int wealth;
	int children;
	birth b;
};
struct tree {
	anketa inf;
	tree* left, * right;
};

//Прототипы всех функций
tree* AddTree(tree* top, const anketa& newtree); //Добавление узла
int Menu();
int TreeCounter(tree* top, int level, int& n); //Подсчёт количества вершин уровня level
void ShowTree(tree* top, int space); //Отображение структуры дерева
void ShowInf(tree* top); //Просмотр значений узлов
void ShowInfT(tree* top);//Просмотр листьев
int WriteF(ofstream &f, tree* top); //Запись в файл
int ReadF(const char* filename, tree* &top);//Чтение из файла
void SrZnach(tree* top, float &sum, int &n);//Среднее значение по окладу
anketa DataRecord();//Ввод данных
tree* DelTree(tree* top);//Удаление дерева

//Основная функция
int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	tree *top = 0;
	float sum = 0;
	int n = 0;
	const char* filename = "File.txt";
	ofstream f;
	ReadF(filename, top);

	while (1) {
		switch (Menu()) {
		case 1: top = AddTree(top, DataRecord()); break;
		case 2:
			ShowTree(top, 1);
			cout << "Нажмите любую клавишу." << endl;
			cin.get(); break;
		case 3: 
			ShowInf(top);
			cout << "Нажмите любую клавишу." << endl;
			cin.get(); break;
		case 4:
		{
			int level;
			int n = 0;
			cout << "Введите значение уровня дерева:" << endl;
			cin >> level;
			cin.get();
			cout << "На уровне " << level << ": " << TreeCounter(top, level, n) << " вершин." << endl;
			cout << "Нажмите любую клавишу." << endl;
			cin.get();
		} break;
		case 5:
			f.open(filename);
			if (!f) { cout << "Ошибка открытия файла!" << endl; return 1; }
			WriteF(f, top);
			cout << "Данные сохранены в файле: " << filename << endl;
			cout << "=================================================" << endl;
			f.close();
			cout << "Нажмите любую клавишу." << endl;
			cin.get(); break;
		case 6:
		{
			string answer;
			cout << "Вы точно хотите удалить дерево?" << endl;
			cout << "Введите ответ: " << endl;
			cin >> answer;
			if (answer == "Да") {
				top = DelTree(top);
				cout << "Дерево удалено." << endl;
				system("pause");
			}
			else break;
		} break;
		case 7: ShowInfT(top); cin.get(); break;
		case 8:
			SrZnach(top, sum, n);
			cout << " Среднее значение по окладу: " << (sum / n) << endl; cin.get(); cout << "Нажмите любую клавишу." << endl;
			break;
		case 9: return 0;
		default: 
			cout << "Вводите число от 1 до 7." << endl;
			cin.get();
			break;
		}
	}

}

//Реализация функций
tree* AddTree(tree* top, const anketa& newtree) {
	if (!top) {
		top = new tree;
		if (!top) { cout << "Не хватает памяти!" << endl; return 0; }
		top->inf = newtree;
		top->left = 0;
		top->right = 0;
	}
	else
		if (top->inf.salary > newtree.salary) top->left = AddTree(top->left, newtree);
		else
			top->right = AddTree(top->right, newtree);
	return top;
}
int Menu() {
	char buf[10];
	int item;
	do {
		system("cls"); cout << endl;
		cout << "=================================================" << endl;
		cout << "==================== ДЕРЕВЬЯ ====================" << endl;
		cout << " 1 - Добавление элемента" << endl;
		cout << " 2 - Отображение дерева" << endl;
		cout << " 3 - Просмотр данных дерева" << endl;
		cout << " 4 - Подсчёт узлов на уровне" << endl;
		cout << " 5 - Запись данных в файл" << endl;
		cout << " 6 - Удаление дерева" << endl;
		cout << " 7 - Просмотр листьев" << endl;
		cout << " 8 - Среднее значение по окладу" << endl;
		cout << " 9 - Выход" << endl;
		cout << "=================================================" << endl;
		cout << "Введите номер пункта меню -> "; cin >> buf;
		cin.get(); item = atoi(buf);
		if (!item) { cout << "Вводите число от 1 до 7." << endl; cin.get(); }
	} while (!item);
	return item;
}
int TreeCounter(tree* top, int level, int& n) {
	if ((level >= 1) && top) {
		if (level == 1) n++;

		n = TreeCounter(top->left, level - 1, n);
		n = TreeCounter(top->right, level - 1, n);
	}
	return n;
}
void ShowTree(tree* top, int space) {
	if (top) {
		space += 3;
		ShowTree(top->right, space);
		cout << setw(space) << '*' << top->inf.salary << endl;
		ShowTree(top->left, space);
	}
}
void ShowInf(tree* top) {
	if (top) {
		cout << "ФИО сотрудника: ";
		cout << top->inf.fio << endl;
		cout << "Дата рождения: ";
		cout << top->inf.b.day << " " << top->inf.b.month << " " << top->inf.b.year << endl;
		cout << "Пол: ";
		cout << top->inf.gender << endl;
		cout << "Кол-во детей: ";
		cout << top->inf.children << endl;
		cout << "Оклад: ";
		cout << top->inf.salary << endl;
		cout << "Состояние ";
		cout << top->inf.wealth << endl;
		ShowInf(top->left);
		ShowInf(top->right);
	}
}
int WriteF(ofstream& f, tree* top) {
	if (top) {
		f << top->inf.fio << endl;
		f << top->inf.b.day << endl;
		f << top->inf.b.month << endl;
		f << top->inf.b.year << endl;
		f << top->inf.gender << endl;
		f << top->inf.children << endl;
		f << top->inf.salary << endl;
		f << top->inf.wealth << endl;
		WriteF(f, top->left);
		WriteF(f, top->right);
	}
	return 0;
}
int ReadF(const char* filename, tree* &top) {
	ifstream fin(filename, ios::in);
	if (!fin) { cout << "Не найден файл " << filename << endl; cin.get(); return 1; }
	anketa a;
	top = 0;
	while (fin.getline(a.fio, sizefio)) {
		fin >> a.b.day;
		fin >> a.b.month;
		fin >> a.b.year;
		fin >> a.gender;
		fin >> a.children;
		fin >> a.salary;
		fin >> a.wealth;
		fin.get();
		top = AddTree(top, a);
	}
	return 0;
}
anketa DataRecord() {
	anketa a;
	cout << "Введите ФИО:" << endl;
	cin.getline(a.fio, sizefio);
	cout << "Введите дату рождения:" << endl;
	cin >> a.b.day; cin >> a.b.month; cin >> a.b.year;
	cout << "Введите пол:" << endl;
	cin >> a.gender;
	cout << "Введите количество детей:" << endl;
	cin >> a.children;
	cout << "Введите оклад:" << endl;
	cin >> a.salary;
	cout << "Введите состояние:" << endl;
	cin >> a.wealth;
	return a;
}
tree* DelTree(tree* top) {
	if (top) {
		if ((top->left == 0) && (top->right == 0)) delete top;
		else {
			if (top->left) {
				DelTree(top->left);
				top->left = 0;
			}
			if (top->right) {
				DelTree(top->right);
				top->right = 0;
			}
		}
	}
	top = 0;
	return top;
}
void ShowInfT(tree* top) {
	if (top) {
		ShowInf(top->left);
		ShowInf(top->right);
		if ((top->left == 0) && (top->right == 0)) {
			cout << "ФИО сотрудника: ";
			cout << top->inf.fio << endl;
			cout << "Дата рождения: ";
			cout << top->inf.b.day << top->inf.b.month << top->inf.b.year << endl;
			cout << "Пол: ";
			cout << top->inf.gender << endl;
			cout << "Кол-во детей: ";
			cout << top->inf.children << endl;
			cout << "Оклад: ";
			cout << top->inf.salary << endl;
			cout << "Состояние ";
			cout << top->inf.wealth << endl;
		}
	}
}
void SrZnach(tree* top, float &sum, int &n) {
	if (top) {
		SrZnach(top->left, sum, n);
		sum += top->inf.salary;
		n++;
		SrZnach(top->right, sum, n);
	}
}

