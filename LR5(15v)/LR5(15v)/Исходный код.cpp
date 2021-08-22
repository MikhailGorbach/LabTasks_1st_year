#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");

	ifstream fin("File.txt", ios::in);
	if (!fin.is_open()) {
		cout << "���������� ������� ����." << endl;
		return 1;
	}
	else cout << "���� ������!" << endl;

	fin.seekg(0, ios::end);
	long len = fin.tellg();
	char *buf = new char[len + 1];
	char *word = new char[len + 1];
	char *maxw = new char[len + 1]; //���������� �����
	fin.seekg(0, ios::beg);
	fin.read(buf, len);

	buf[len] = '\0';
	word[len] = '\0';
	maxw[len] = '\0';

	long i = 0, k = 0, max = 0, n = 0, a = 1;
	
	//������� �������
	for (n = 0; n<len; n++) { 
		word[n] = ' ';
		maxw[n] = ' ';
	}

	while (buf[i]) {
		while ((buf[i] == '\n') || (buf[i] == ' ')) i++; //����������� �� �������� � ����� ������
		for (n = 0; buf[i] != ' ' && buf[i] && buf[i] != '\n'; n++) {
			word[n] = buf[i];
			k++; //������ �����
			i++;
		}
		if (k > max) {
			max = k;
			for (n = 0; n < len; n++) //���������� ���������� �����
				maxw[n] = word[n];
		}
		k = 0;
	}

	for (n = 0; n < len; n++) word[n] = ' '; //������� ������

	i = 0;
	while (buf[i]) {
		while ((buf[i] == '\n') || (buf[i] == ' ')) i++; //����������� �� �������� � ����� ������
		for (n = 0; buf[i] != ' ' && buf[i] && buf[i] != '\n'; n++) {
			word[n] = buf[i];
			i++;
			if (word[n] != maxw[n]) a--; //��������� �� �����, ��������� �� � �������� ���������� ������
		}
		if (a == 1) k++;
		for (n = 0; n < len; n++) word[n] = ' ';//������� ������
		a = 1;
	}
	cout << "�����: ";
	for (i = 0; i < len; i++) cout << maxw[i];
	cout << endl << "����������: " << k << endl;
	fin.close();
	system("pause");
	return 0;
}