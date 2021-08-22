#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fout = fopen("input.txt", "w");
	FILE* fin = fopen("output.txt", "r");
	char a;
	int i = 0;
	while (fscanf(fin, "%c", &a) != EOF) {
		fprintf(fout, "%c", a);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}