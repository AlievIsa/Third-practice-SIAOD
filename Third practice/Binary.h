#pragma once
#include <iostream>
#include <locale.h>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

struct readerSub {
	unsigned int key;
	char name[200];
	char address[200];
};

void convertTxtToBin(ifstream& textFile, ofstream& binFile, int& subsAmount)
{
	subsAmount = 0;
	while (!textFile.eof()) {
		readerSub r;
		string name, address;
		textFile >> r.key;
		textFile.get();
		getline(textFile, name);
		getline(textFile, address);
		strcpy_s(r.name, name.c_str());
		strcpy_s(r.address, address.c_str());
		binFile.write((char*)&r, sizeof(readerSub));
		subsAmount += 1;
	}
}

void convertBinToTxt(ofstream& textFile, ifstream& binFile)
{
	readerSub r;
	binFile.read((char*)&r, sizeof(readerSub));
	while (binFile.good()) {
		textFile << r.key << '\n' << r.name << '\n' << r.address;
		binFile.read((char*)&r, sizeof(readerSub));
		if (!binFile.eof())
			textFile << '\n';
	}
}

void outputBinFile(ifstream& binFile)
{
	readerSub r;
	binFile.read((char*)&r, sizeof(readerSub));
	while (!binFile.eof()) {
		cout << r.key << " " << r.name << " " << r.address << '\n';
		binFile.read((char*)&r, sizeof(readerSub));
	}
}

void addSub(ofstream& binFile, readerSub r) {
	binFile.write((char*)&r, sizeof(readerSub));
}

string getSubByNum(ifstream& binFile, int num)
{
	readerSub r;
	string value = "";
	num -= 1;
	binFile.seekg(sizeof(r) * num, ios::beg);
	binFile.read((char*)&r, sizeof(readerSub));
	value += to_string(r.key) + " " + r.name + " " + r.address;
	return value;
}

string getSubByKey(ifstream& binFile, int key)
{
	readerSub r;
	string value;
	while (binFile.good()) {
		binFile.read((char*)&r, sizeof(readerSub));
		if (r.key == key)
		{
			value += to_string(r.key) + " " + r.name + " " + r.address;
			return value;
		}
	}
	return "Данного ключа нет в файле";
}

string delSubByKey(ifstream& binFile, int key, string binFileName)
{
	readerSub r;
	ofstream tempBinFile;
	bool check = false;
	tempBinFile.open("tempBin.dat", ios::out | ios::binary);
	binFile.read((char*)&r, sizeof(readerSub));
	while (binFile.good()) {
		if (r.key == key)
			check = true;
		else
			tempBinFile.write((char*)&r, sizeof(readerSub));
		binFile.read((char*)&r, sizeof(readerSub));
	}
	binFile.close();
	remove(binFileName.c_str());
	tempBinFile.close();
	rename("tempBin.dat", binFileName.c_str());
	if (check)
		return "Запись удалена";
	else
		return "Данного ключа нет в файле";
}

void delSubByNum(ifstream& binFile, int num, string binFileName)
{
	readerSub r;
	ofstream tempBinFile;
	int i = 1;
	tempBinFile.open("tempBin.dat", ios::out | ios::binary);
	binFile.read((char*)&r, sizeof(readerSub));
	while (binFile.good()) {
		if (i != num)
			tempBinFile.write((char*)&r, sizeof(readerSub));
		binFile.read((char*)&r, sizeof(readerSub));
		i++;
	}
	binFile.close();
	remove(binFileName.c_str());
	tempBinFile.close();
	rename("tempBin.dat", binFileName.c_str());
}

string delSubByKeyWithReplace(ifstream& binFile, int key, string binFileName, int subsAmount)
{
	readerSub r, r1;
	ofstream tempBinFile;
	bool check = false;
	tempBinFile.open("tempBin.dat", ios::out | ios::binary);
	binFile.seekg(sizeof(r) * (subsAmount - 1), ios::beg);
	binFile.read((char*)&r1, sizeof(readerSub));
	binFile.seekg(sizeof(r) * 0, ios::beg);
	binFile.read((char*)&r, sizeof(readerSub));
	while (binFile.good())
	{
		if (r.key == key)
		{
			check = true;
			tempBinFile.write((char*)&r1, sizeof(readerSub));
		}
		else if (r.key != r1.key)
			tempBinFile.write((char*)&r, sizeof(readerSub));
		binFile.read((char*)&r, sizeof(readerSub));
	}
	binFile.close();
	remove(binFileName.c_str());
	tempBinFile.close();
	rename("tempBin.dat", binFileName.c_str());
	binFile.open(binFileName, ios::in | ios::binary);
	if (check)
		return "Запись удалена";
	else
		return "Данного ключа нет в файле";
}

void testBinF() {
	int switchNum, subsAmount = 0, key;
	ifstream textFileIf, binFileIf;
	ofstream binFileOf, textFileOf;
	string binFileName, name, address;
	readerSub r;
	cout << "Введите имя двоичного файла: ";
	getline(cin, binFileName);
	binFileName += ".dat";
	binFileOf.open(binFileName, ios::out | ios::binary);


	if (!binFileOf)
	{
		cout << "файл не открыт";
		return;
	}
	binFileOf.close();

	cout << "Выберите номер задания:\n"
		"1. Функция создания двоичного файла из текстового\n"
		"2. Функция добавления записи в двоичный файл\n"
		"3. Функция удаления записи с заданным ключом из файла\n"
		"4. Функция чтения записи с заданным номером из файла\n"
		"0. Для возврата в функцию main\n"
		"Ваш выбор: ";
	while (true) {
		cin >> switchNum;
		switch (switchNum) {
		case 1:
			textFileIf.open("subs.txt", ios::out);
			binFileOf.open(binFileName, ios::out | ios::binary);
			if (!textFileIf || !binFileOf)
			{
				cout << "файл не открыт";
				return;
			}
			convertTxtToBin(textFileIf, binFileOf, subsAmount);
			cout << "Файл преобразован!\n";
			textFileIf.close();
			binFileOf.close();
			break;
		case 2:
			binFileOf.open(binFileName, ios::out | ios::binary);
			if (!textFileIf || !binFileOf)
			{
				cout << "файл не открыт";
				return;
			}
			cout << "Введите ключ, имя и адрес структуры:\n";
			cin >> r.key;
			getline(cin, name);
			getline(cin, address);
			strcpy_s(r.name, name.c_str());
			strcpy_s(r.address, address.c_str());
			addSub(binFileOf, r);
			break;
		case 3:
			binFileIf.open(binFileName, ios::in | ios::binary);
			if (!binFileIf)
			{
				cout << "файл не открыт";
				return;
			}
			cout << "Введите ключ: ";
			cin >> key;
			cout << delSubByKey(binFileIf, key, binFileName) << '\n';
			binFileIf.close();
			subsAmount -= 1;
			break;
		case 4:
			binFileIf.open(binFileName, ios::in | ios::binary);
			if (!binFileIf)
			{
				cout << "файл не открыт";
				return;
			}
			int num;
			cout << "Введите номер записи: ";
			cin >> num;
			if (num > subsAmount || num <= 0)
				cout << "Данного номера нет в файле\n";
			else {
				cout << getSubByNum(binFileIf, num) << '\n';
			}
			binFileIf.close();
			break;
		case 0:
			return;
		default:
			cout << "Нет такого номера!\n";
			break;
		}
		cout << "\nВыберите следующий номер: ";
}