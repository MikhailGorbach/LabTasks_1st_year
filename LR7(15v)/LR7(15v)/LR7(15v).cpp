#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
using namespace std;
//Константы и структуры
struct birth {
	int day;
	int month;
	int year;
};
struct anketa {
	char fio[15];
	birth b;
	char pol;
	int wealth;
	int deti;
	int oklad;
	anketa *next;
};
//Прототипы функций
anketa* Dob(anketa *end, const anketa &a);//Добавление эл.в очередь
anketa* Dob_first(const anketa &a);//Добавление первого элемента
anketa* Udal(anketa *beg);//Удаление элемента из очереди
anketa Vvod();//Ввод значений элемента
anketa* AddTwo(anketa *beg,anketa *end,const anketa &a, const anketa &a1);//Добавление двух элементов
anketa* Del(anketa* beg);
int Menu();//Меню
void Print(const anketa &a);//Вывод значений элемента
void Prosmotr(anketa *beg);//Просмотр очереди
int ReadF(const char *filename, anketa **beg, anketa **end);//Чтение из файла
int WriteF(const char *filename, anketa *temp);//Запись данных в файл
//Основная функция
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	anketa *beg = 0, *end = 0;
	const char *filename = "File.txt";

	ReadF(filename, &beg, &end);//Чтение данных из файла в очередь
	while(1) {
		switch (Menu())
		{
		case 1:
			if (beg) end = Dob(end, Vvod());
			else {
				beg = Dob_first(Vvod());
				end = beg;
			} break;
		case 2:
			beg = Udal(beg);
			break;
		case 3:
			Prosmotr(beg);
			break;
		case 4:
			WriteF(filename, beg);
			break;
		case 5:
			AddTwo(beg, end, Vvod(), Vvod());
			break;
		case 6:
			beg=Del(beg);
			break;
		case 7:
			return 0;
		default:
			cout << "Введите номер от 1 до 6" << endl;
			cin.get();
			break;
		}
	}
}
//Функции
anketa* Dob(anketa *end, const anketa &a) {
	anketa *newE = new anketa;
	*newE = a;
	newE->next = 0;
	end->next = newE;
	end = newE;
	return end;
}
anketa* Dob_first(const anketa &a) {
	anketa *beg = new anketa;
	*beg = a;
	beg->next = 0;
	return beg;
}
anketa Vvod() {
	anketa a;
	cout << "Введите ФИО:" << endl; scanf_s("%s", a.fio, 15);
	cout << "Введите дату рождения:" << endl;
	scanf_s("%d %d %d", &a.b.day, &a.b.month, &a.b.year);
	cout << "Введите пол:" << endl;
	cin.get();
	scanf_s("%c", &(a.pol), 1);
	cout << "Введите состояние:" << endl;
	scanf_s("%d", &a.wealth);
	cout << "Введите количество детей:" << endl;
	scanf_s("%d", &a.deti);
	cout << "Введите оклад:" << endl;
	scanf_s("%d", &a.oklad);
	return a;
}
int Menu() {
	char buf[10];
	int item;
	do {
		system("cls");
		cout << endl;
		cout << "===============БАЗА ДАННЫХ=================\n" << endl;
		cout << "1 - Добавление элемента в очередь" << endl;
		cout << "2 - Печать и удаление элемента" << endl;
		cout << "3 - Просмотр очереди" << endl;
		cout << "4 - Запись данных в файл" << endl;
		cout << "5 - Добавление двух элементов" << endl;
		cout << "6 - Удаление всего списка" << endl;
		cout << "7 - Выход" << endl;
		cout << "===========================================" << endl;
		cout << "Введите номер пункта меню ---> "; cin >> buf;
		cin.get();
		item = atoi(buf);
		if (!item) { cout << "Вводите число от 1 до 5" << endl; cin.get(); }
	} while (!item);
	return item;
}
anketa* Udal(anketa *beg) {
	anketa *temp;
	if (!beg) { cout << "Очередь пустая!" << endl; system("pause"); return 0; }
	cout << "===========================================" << endl;
	Print(*beg);
	cout << "===========================================" << endl;
	temp = beg;
	beg = beg->next;
	system("pause");
	delete temp;

	return beg;
}
void Print(const anketa &a) {
	cout << "Ф.И.О.: " << a.fio << endl;
	cout << "Дата рождения: "<< a.b.day << a.b.month << a.b.year << endl;
	cout << "Пол: " << a.pol << endl;
	cout << "Состояние: " << a.wealth << endl;
	cout << "Дети: " << a.deti << endl;
	cout << "Оклад: " << a.oklad << endl;
}
void Prosmotr(anketa *beg) {
	if (!beg) { cout << "Очередь пустая" << endl; cin.get(); return; }
	anketa *temp = beg;
	cout << "===========================================" << endl;
	while (temp) {
		Print(*temp);
		cout << "===========================================" << endl;
		cout << "Нажмите любую клавишу:" << endl;
		cin.get();
		temp = temp->next;
	}
}
int ReadF(const char *filename, anketa **beg, anketa **end) {
	ifstream fin(filename, ios::in);
	if (!fin) { cout << "Нет файла" << filename << endl; return 1; }
	anketa a;
	*beg = 0;
	while (fin.getline(a.fio, 15)) {
		fin >> a.b.day;
		fin >> a.b.month;
		fin >> a.b.year;
		fin >> a.pol;
		fin >> a.wealth;
		fin >> a.deti;
		fin >> a.oklad;
		fin.get();
		if (*beg) *end = Dob(*end, a);
		else { *beg = Dob_first(a); *end = *beg; }
	}
	return 0;
}
int WriteF(const char* filename, anketa* temp) {
	ofstream fout(filename);
	if (!fout) { cout << "Не могу открыть файл для записи" << endl; return 1; }
	while (temp) {
		fout << temp->fio << endl;
		fout << temp->b.day << endl;
		fout << temp->b.month << endl;
		fout << temp->b.year << endl;
		fout << temp->pol << endl;
		fout << temp->wealth << endl;
		fout << temp->deti << endl;
		fout << temp->oklad << endl;
		temp = temp->next;
	}
	cout << "Данные сохранены в файле: " << filename << endl;
	cout << "===========================================" << endl;
	cout << "Нажмите любую клавишу " << endl;
	cin.get();
	return 0;
}
anketa* AddTwo(anketa *beg, anketa *end, const anketa &a, const anketa &a1) {
	anketa *newE1;
	newE1 = (struct anketa*)malloc(sizeof(struct anketa));
	anketa* newE2;
	newE2 = (struct anketa*)malloc(sizeof(struct anketa));
	*newE1 = a;
	*newE2 = a1;
	newE1->next = newE2;
	for (end = beg; end->next->next != 0;end = end->next);
	newE2->next = end->next;
	end->next = newE1;
	return beg;
}
anketa* Del(anketa* beg) {
	anketa* temp;
	for (temp = beg; beg != 0;) {
		temp = beg;
		beg = beg->next;
		delete temp;
	}
	beg = 0;
	return beg;
}