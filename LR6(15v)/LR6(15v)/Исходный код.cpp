#include <string.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <windows.h>
using namespace std;
//��������� � ���������
struct birth
{
	int day;
	int month;
	int year;
};
struct znak
{
	char fio[15];
	char zodiak[10];
	birth b;
};
const int size_p = sizeof(znak);
//��������� �������
int createF(FILE *fbin);
int sortF(FILE *fbin);
int printF(FILE *fbin);
int searchP(FILE *fbin);
//�������� �������
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fbin;
	char c;

	fbin = fopen("File.dat", "r+b");

	if (!fbin) {
		fbin = fopen("File.dat", "w+b");
		if (!fbin) {
			cout << "���������� �������(�������) ����" << endl;
			return 1;
		}
	}
	while (1) {
		system("cls");
		puts("1 - ������ � ����");
		puts("2 - ���������� �����");
		puts("3 - ����� �����");
		puts("4 - ����� � ����������");
		puts("5 - �����");
		puts("--------------------------");
		puts("������� ����� ������ ����: ");
		c = getch();
		switch (c) {
		case '1': createF(fbin);break;
		case '2':sortF(fbin);break;
		case '3':printF(fbin);break;
		case '4':searchP(fbin);break;
		case '5':fclose(fbin); return 0;
		}
	}
}
//�������
int createF(FILE* fbin) {
	znak z;
	fseek(fbin, 0, SEEK_END);
	puts("���� ������ � �����������");
	puts("��� ������ ������� *");
	puts("_________________________");
	while (1) {
		puts("������� �������: ");
		scanf("%15s", &z.fio);
		if (!strcmp(z.fio, "*")) return 1;
		puts("������� ���� ��������: ");
		scanf("%d %d %d", &z.b.day, &z.b.month, &z.b.year);
		puts("������� ���� �������: ");
		scanf("%s", &z.zodiak);
		fwrite(&z, size_p, 1, fbin);
	}
}
int printF(FILE *fbin) {
	znak z;
	int n;
	system("cls");
	rewind(fbin);
	puts(" ���              ���� ��������  ���� �������");
	do {
		n = fread(&z, size_p, 1, fbin);
		if (n < 1) break;
		printf("| %-15s| %-2d  %-2d  %-2d  | %-12s|\n", z.fio, z.b.day, z.b.month, z.b.year, z.zodiak);
	} 	while (1);
	puts("_______________________________________________");
	_getch();
	return 0;
}
int sortF(FILE* fbin) {
	int i, j;
	znak z1, z2;
	puts("��� ���������� ������� ����� �������");
	_getch();
	fseek(fbin, 0, SEEK_END);
	long len = ftell(fbin) / size_p;
	rewind(fbin);
	for (i = len - 1; i >= 1; i--)
		for (j = 0; j <= i - 1; j++) {
			fseek(fbin, j * size_p, SEEK_SET);
			fread(&z1, size_p, 1, fbin);
			fread(&z2, size_p, 1, fbin);
			if ((z1.b.year > z2.b.year) || ((z1.b.year == z2.b.year) && (z1.b.month > z2.b.month)) || ((z1.b.year == z2.b.year) && (z1.b.month == z2.b.month) && (z1.b.day > z2.b.day))) {
				fseek(fbin, (-2) * size_p, SEEK_CUR);
				fwrite(&z2, size_p, 1, fbin);
				fwrite(&z1, size_p, 1, fbin);
			}
		}
	return 0;
}
int searchP(FILE* fbin) {
	char s[15];
	znak z1,z2;
	int n;
	bool valid = false;
	printf("������� �������: \n");
		scanf("%s", s);
		rewind(fbin);
		do {
			n = fread(&z1, size_p, 1, fbin);
			if (n < 1) break;
			if (strcmp(s, z1.fio) == 0) {
				z2 = z1;
				valid = true;
			}
		} while (1);
		if (!valid) printf("������ �������� �� ����������!\n");
		else if (valid) printf("| %-15s| %-2d  %-2d  %-2d  | %-12s|\n", z2.fio, z2.b.day, z2.b.month, z2.b.year, z2.zodiak);
		_getch();
	return 0;
}