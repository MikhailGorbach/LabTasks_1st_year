#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");

	ifstream fin("File.txt", ios::in);
	if (!fin.is_open()) {
		cout << "Невозможно открыть файл." << endl;
		return 1;
	}
	else cout << "Файл открыт!" << endl;

	fin.seekg(0, ios::end);
	long len = fin.tellg();
	char *buf = new char[len + 1];
	char *word = new char[len + 1];
	char *maxw = new char[len + 1]; //наибольшее слово
	fin.seekg(0, ios::beg);
	fin.read(buf, len);

	buf[len] = '\0';
	word[len] = '\0';
	maxw[len] = '\0';

	long i = 0, k = 0, max = 0, n = 0, a = 1;
	
	//очищаем массивы
	for (n = 0; n<len; n++) { 
		word[n] = ' ';
		maxw[n] = ' ';
	}

	while (buf[i]) {
		while ((buf[i] == '\n') || (buf[i] == ' ')) i++; //избавляемся от пробелов и конца строки
		for (n = 0; buf[i] != ' ' && buf[i] && buf[i] != '\n'; n++) {
			word[n] = buf[i];
			k++; //длинна слова
			i++;
		}
		if (k > max) {
			max = k;
			for (n = 0; n < len; n++) //запоминаем наибольшее слово
				maxw[n] = word[n];
		}
		k = 0;
	}

	for (n = 0; n < len; n++) word[n] = ' '; //очищаем массив

	i = 0;
	while (buf[i]) {
		while ((buf[i] == '\n') || (buf[i] == ' ')) i++; //избавляемся от пробелов и конца строки
		for (n = 0; buf[i] != ' ' && buf[i] && buf[i] != '\n'; n++) {
			word[n] = buf[i];
			i++;
			if (word[n] != maxw[n]) a--; //проверяем по букве, совпадает ли с найденым наибольшим словом
		}
		if (a == 1) k++;
		for (n = 0; n < len; n++) word[n] = ' ';//очищаем массив
		a = 1;
	}
	cout << "Слово: ";
	for (i = 0; i < len; i++) cout << maxw[i];
	cout << endl << "Количество: " << k << endl;
	fin.close();
	system("pause");
	return 0;
}