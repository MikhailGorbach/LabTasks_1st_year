﻿#include <conio.h>          //подключение библиотеки управления вводом-выводом средствами консоли
#include <iostream>         //подключение библиотеки стандартных объектов и операции              
#include <math.h>           //подключение библиотеки математических функций
using namespace std;        //использование пространства имён std  
const double ex = 2.718282;
int main()
//вычисление значения функции y=f(x)
{
	setlocale(LC_ALL, "rus");           //подключение русской консоли
	float a,                            //параметр a
		b,                              //параметр b
		x, dx, xk, xn,                  //аргумент х
		y;                              //значение функции y 
	bool valid;                         //флаг, отображающий принадлежность 
	//аргумента области допустимых значений 
	//очистка экрана
	system("cls");
	//ввод значений а,b,х
	cout << "Введите параметр а: ";
	cin >> a;
	cout << "Введите параметр b: ";
	cin >> b;
	cout << "Введите аргумент x нач., шаг dx, х кон.: ";
	cin >> xn >> dx >> xk;
	//вычисление значения функции y
	valid = true;
	cout << "Значение y = f(x) " << " x " << endl;
	for (x = xn; x <= xk; x += dx) {
		if (x <= a)
		{
			//проверка ОДЗ
			if ((x - tanh(x) + pow(x, 4)) < 0)                   //флаг сбрасывается, если аргумент имеет недопустимое значение
				valid = false;
			else
			{
				//вычисление значения функции y
				double k = x - tanh(x) + pow(x, 4);
				y = sqrt(k) / cos(pow(x, 2));
			}
		}
		else if (x < b)    //вычисление значения функции y
		{
			if (x <= 0) valid = false;
			else {
				double s = pow(ex, -2 * sin(4 * x));
				y = s + log10(x) + atan(x);
			}
		}
		else
		{
			//вычисление значения функции y
			y = 3.7 * pow(x, 7.3) * sin(abs(pow(x, 2))) + 4.5 * cosh(pow(x, 3));
		}
		cout.setf(ios::left, ios::adjustfield);
		cout.setf(ios::showpoint);
		cout.precision(5);
		if (valid)
			//вывод на экран значения функции y
			cout << y << "  " << x << endl;
		else
			cout << "Недопустимое значение аргумента " << endl;
	}
	cout << "Нажмите любую клавишу...";
	_getch();
	return 0;
}
