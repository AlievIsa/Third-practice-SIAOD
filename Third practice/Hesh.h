#pragma once
#include <iostream>
#include <locale.h>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

struct HeshTable;
void reheshTable(HeshTable*&, int);

struct HTNode {
	unsigned int key;
	unsigned int num;
	// char name[200];
	// char address[200];
	bool isOpen = true;
	bool isDel = false;

	// HTNode() {}

	/* HTNode(unsigned int key, unsigned int num, string name, string address) {
		this->key = key;
		strcpy_s(this->name, name.c_str());
		strcpy_s(this->address, address.c_str());
		this->isOpen = false;
	} */
};

struct HeshTable {
	unsigned int size;
	unsigned int blockedSize;
	HTNode* HTNodes;

	HeshTable(unsigned int size) {
		this->size = size;
		this->blockedSize = 0;
		this->HTNodes = new HTNode[size];
	}

	~HeshTable() {
		delete(this->HTNodes);
	}

};

int hesh(int key, int size) {
	return key % size;
}

void addHTNode(HeshTable*& T, int key) {
	int i = hesh(key, T->size);
	while (!T->HTNodes[i].isOpen) // && !T->HTNodes[i].isDel
		i++;
	if (i < T->size) {
		T->HTNodes[i].key = key;
		T->HTNodes[i].num = i;
		T->HTNodes[i].isOpen = false;
		T->blockedSize++;
	}
	if (T->blockedSize > T->size * 0.75)
		reheshTable(T, T->size * 2);
}

void delHTNode(HeshTable*& T, int key) {
	int i = hesh(key, T->size);
	while (!T->HTNodes[i].isOpen && T->HTNodes[i].key != key) // && !T->HTNodes[i].isDel
		i++;
	if (i < T->size) {
		T->HTNodes[i].isDel = true;
	}
}

int getHTNode(HeshTable*& T, int key) {
	int i = hesh(key, T->size);
	while (!T->HTNodes[i].isOpen && T->HTNodes[i].key != key) // && !T->HTNodes[i].isDel 
		i++;
	if (i < T->size && T->HTNodes[i].key == key && !T->HTNodes[i].isDel)
		return i;
	else
		return -1;
}

void reheshTable(HeshTable*& T, int newSize) {
	HeshTable *newT = new HeshTable(newSize);
	for (int i = 0; i < T->size; i++) {
		if (!T->HTNodes[i].isDel && !T->HTNodes[i].isOpen) {
			newT->HTNodes[i].num = T->HTNodes[i].num;
			newT->HTNodes[i].key = T->HTNodes[i].key;
			newT->HTNodes[i].isOpen = T->HTNodes[i].isOpen;
		}
	}
	newT->blockedSize = T->blockedSize;
	T = newT;
}

void testHeshT() {
	cout << "Проверка работы хеш-таблицы\n";
	int size, switchNum, key;
	cout << "Введите размер таблицы: ";
	cin >> size;
	HeshTable* T = new HeshTable(size);
	cout << "Выберите номер:\n"
		"1. Вставка ключа без коллизии\n"
		"2. Вставка ключа и разрешение коллизии\n"
		"3. Вставка ключа с последующим рехешированием\n"
		"4. Удаление ключа из таблицы\n"
		"5. Поиск ключа в таблице\n"
		"0. Для возврата в функцию main\n"
		"Ваш выбор: ";
	cin >> switchNum;
	while (true) {
		switch (switchNum) {
		case 1:
			cout << "Введите ключ: ";
			cin >> key;
			addHTNode(T, key);
			cout << "Ключ добавлен!\n";
			break;
		case 2:
			cout << "Введите ключ для вызова коллизии: ";
			cin >> key;
			addHTNode(T, key);
			cout << "Ключ добавлен!\n";
			break;
		case 3:
			cout << "Введите ключ для вызова рехеширования: ";
			cin >> key;
			cout << "Таблица рехеширована, ключ добавлен!\n";
			break;
		case 4:
			cout << "Введите ключ: ";
			cin >> key;
			delHTNode(T, key);
			cout << "Ключ удален!\n";
			break;
		case 5:
			cout << "Введите ключ, расположенный после удаленного: ";
			cin >> key;
			cout << "Полученный индекс: " << getHTNode(T, key) << "\n";
			break;
		case 0:
			return;
			break;
		default:
			cout << "Нет такого номера!\n";
			break;
		}
		cout << "\nВыберите следующий номер: ";
		cin >> switchNum;
	}
}