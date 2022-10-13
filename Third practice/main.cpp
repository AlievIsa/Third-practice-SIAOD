#include <locale.h>
#include <string>
#include <iostream>
#include "BinByHesh.h"

void createRandTxt(string fileName, int size);

int main() {
	setlocale(LC_ALL, "Rus");
	cout << "������������ ������ �3 - ����� ���\n";
	cout << "������� ��� �����: ";

	int switchNum;
	string name;
	cin >> name;
	name += ".txt";
	cout << "�������� ����� �������:\n"
		"1. ������� ����\n"
		"2. ������� ����\n"
		"3. �������� ����� ������ � ����� �����\n"
		"4. ��������� �������� ����� �� ������\n"
		"5. ���������� ���������� ����� � �����\n"
		"6. ������� �������� ������, ����� �������� ������ �����,\n"
		"�������� ������� � �������������� ������, ������ ��� ��� ���������� �����.\n"
		"0. ��� ���������� ������\n"
		"��� �����: ";
	while (true) {
		cin >> switchNum;
		switch (switchNum) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 0:
			return 0;
		default:
			cout << "��� ������ ������!\n";
			break;
		}
		cout << "�������� ��������� �����: ";
	}
}

void createRandTxt(string fileName, int size) {
	string addresses[10] = {"Matveevskaya 26", "Michurinskaya 15", "Davidkovo 3",
		"Arbatskaya 34", "Nikulinskaya 7", "Bagrationovskaya 8", "Veernaya 5",
		"Ochakovskaya 66", "Pushkinskaya 1", "Nevskiy 10"};
	string names[10] = { "Petr P", "Ivan I", "Kirill K", "Artem A", "Nadya N",
					"Katya K", "Darya D", "Polina P", "Elena E", "Stas S" };
	string address;
	string name;
	int key;
	ofstream file;
	file.open(fileName);
	key = rand() % 100000;
	address = addresses[(rand() % 10)];
	name = names[(rand() % 10)];
	file << key << "\n" << name << "\n" << address;
	for (int i = 1; i < size; i++) {
		file << "\n";
		key = rand() % 100000;
		address = addresses[(rand() % 10)];
		name = names[(rand() % 10)];
		file << key << "\n" << name << "\n" << address;
	}
	file.close();
}