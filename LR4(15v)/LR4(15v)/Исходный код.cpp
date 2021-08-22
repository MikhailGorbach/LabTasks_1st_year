#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

void vvod_a(int **a, int n, int m);
void vivod_a(int **a, int n, int m);
int summa(int **a, int n, int m);
int counter(int **a, int n, int m);
int posp(int **a, int n, int m);

int main() {
	setlocale(LC_ALL, "rus");
	char key;
	int n, m, i, j, k, sum, **a;

	cout << "Введите размер матрицы(n строк, m столбцов): "; cin >> n >> m;
	//выделение памяти под массив указателей
	a = new int *[n];
	//выделение памяти под массив значений
	for (i = 0; i < n; i++) a[i] = new int [m];

	while (true) {
		system("cls");
		cout << "------- МЕНЮ -------" << endl;
		cout << "1: Создание матрицы" << endl;
		cout << "2: Вывод матрицы" << endl;
		cout << "3: Нахождение позиции седловой точки" << endl;
		cout << "4: Сумма чётных элементов" << endl;
		cout << "5: Количество чётных элементов" << endl;
		cout << "6: Выход" << endl;
		key = getchar();
		switch (key) {
		case '1': {
					  vvod_a(a, n, m);
					  break;
		}
		case '2': {
					  vivod_a(a, n, m);
					  cout << "Нажмите Enter для продолжения." << endl;
					  _getch();
					  break;
		}
		case '3': {
					  cout << "Седловая точка: "; cout << posp(a, n, m);
					  cout << "Нажмите Enter для продолжения." << endl;
					  _getch();
					  break;
		}
		case '4': {
					  cout << "Сумма чётных элементов: " << summa(a, n, m) << endl;
					  cout << "Нажмите Enter для продолжения." << endl;
					  _getch();
					  break;
		}
		case '5':{
					 cout << "Количество чётных элементов матрицы: " << counter(a, n, m) << endl;
					 cout << "Нажмите Enter для продолжения." << endl;
					 _getch();
					 break;
		}
		case '6': {
					  for (i = 0; i < n; i++) delete[]a[i];
					  delete[]a;
					  exit(0);
		}

		}
	}
	return 0;
}
void vvod_a(int **a, int n, int m) {
	int i, j;
	cout << "Вводите элементы матрицы: " << endl;
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
		cin >> a[i][j];
}
void vivod_a(int **a, int n, int m) {
	int i, j;
	cout << "Элементы матрицы: " << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			cout << setw(3) << a[i][j];
		cout << endl;
	}
}
int summa(int **a, int n, int m) {
	int i, j, sum = 0;
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++) {
		if (a[i][j] % 2 == 0) {
			sum += a[i][j];
		}
	}
	return sum;
}
int posp(int **a, int n, int m) {
	int counter = 0;
	for (int i = 0; i < n; i++)
	for (int j = m - 1; j >= 0; j--)
	if ((a[i][j] == 0) && (j == n - 1 - i)) counter += 1;
	return counter;
}

int counter(int **a, int n, int m) {
	int i, j, k = 0;
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
	if (a[i][j] % 2 == 0) k += 1;
	return k;
}


