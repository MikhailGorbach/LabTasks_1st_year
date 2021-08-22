#include <iostream>
#include <conio.h>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	int n, m;
	int *a;
	int i,j;
	int s;
	int temp;
	system("cls");
	
	cout << "Введите количество символов массива: " << endl;
	cin >> n;
	a = new int[n];
	cout << "Введите " << n << " элементов массива: " << endl;
	//Заполение массива
	for (i = 0; i < n; i++) cin >> a[i];
	s = 0;
	//Нахождение суммы нечётных элементов последовательности с чётными индексами
	for (i = 0; i < n; i++)
		if ((a[i] % 2 != 0) && (i % 2 == 0)) s += a[i];
		cout << "Сумма: " << s << endl;
	//Сортировка массива методом вставки
	for (i = 1; i < n; i++) {
	temp = a[i];
	for (j = i - 1; j >= 0 && temp > a[j]; j--) a[j + 1] = a[j];
	a[j + 1] = temp;
	}
	//Вывод отсортированного массива
	for (i = 0; i < n; i++) cout << a[i] << " ";
	cout << "Нажмите любую клавишу..." << endl;
	_getch();
	delete []a;
	return 0;
}