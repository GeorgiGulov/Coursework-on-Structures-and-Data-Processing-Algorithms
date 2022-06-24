#include "HashTable.h"
// ��� ������� � ������� ������������


//	���������� ���-�������
HashTable::HashTable() {
	hashTable = new element[500];
}



//	�������� ���-�������
int HashTable::getHashOne(string key)
{
	const double temp = 3.349051;
	int index = 0;
	index = (int)(((int)key[0]) + ((int)key[1]) * temp + ((int)key[2]) * pow(temp, 2) + ((int)key[3]) * pow(temp, 3) + ((int)key[4]) * pow(temp, 4) 
		+ ((int)key[5]) * pow(temp, 5)) * temp + ((int)key[6]) * pow(temp, 6) + ((int)key[7]) * pow(temp, 7)
		+ ((int)key[8]) * pow(temp, 8) + ((int)key[9]) * pow(temp, 9) + ((int)key[10]) * pow(temp, 10);

	return (index % 500);
}



//	��������������� ���-�������     
//  ������� ��� � ��������, �� � ����������� ������� � �������� � �������� �� ������� ������� �� ��������� �������� ����
int HashTable::getHashTwo(string key)
{
	const double temp = 2.393051;
	int index = 0;
	index = (int)(((int)key[0]) + ((int)key[1]) * temp + ((int)key[2]) * pow(temp, 2) + ((int)key[3]) * pow(temp, 3) +
		((int)key[4]) * pow(temp, 4) + ((int)key[5]) * pow(temp, 5)) * temp + ((int)key[6]) * pow(temp, 6) + ((int)key[7]) * pow(temp, 7)
		+ ((int)key[8]) * pow(temp, 8) + ((int)key[9]) * pow(temp, 9) + ((int)key[10]) * pow(temp, 10);

	index = index % 500;
	index = index + 1;
	index = index % 500;

	return index;
}



//	���������� ��������� ��� �����
int HashTable::addKeyHashTable(SIM sim)
{
	bool check = false;
	if (size - sizeCount < 1)
	{
		return 0; // ������ ������ ��� ���� ��� ���
	}

	element object;
	sizeCount++;
	object.sim = sim;
	object.pos = getHashOne(object.sim.nomerSIM);
	
	if (hashTable[object.pos].deleted == 1)
	{
		hashTable[object.pos] = object;
		hashTable[object.pos].deleted = 0;
		hashTable[object.pos].empty = 0;
		hashTable[object.pos].collisions++;
		check = true;
	}
	else if (hashTable[object.pos].empty == 1 && hashTable[object.pos].deleted == 0)
	{
		hashTable[object.pos] = object;
		hashTable[object.pos].empty = 0;
		check = true;
	}
	else
	{
		
		for (int i = 0; i < size; i++)
		{
			int h1 = getHashOne(hashTable[object.pos].sim.nomerSIM);
			int h2 = getHashTwo(hashTable[object.pos].sim.nomerSIM);
			object.pos = (h1 + h2) % size;
			if (hashTable[object.pos].empty == 1 && hashTable[object.pos].deleted == 0)
			{
				hashTable[object.pos] = object;
				hashTable[object.pos].empty = 0;
				check = true;
				break;
			}
		}
	}

	if (check) {
		sizeCount++;
	}else {
		cout << "�� ������� �������� ����\n";
	}
	return 1;
}



////	�������� ��� ����� �� ����� (����� ��� �����)
//int HashTable::deleteObject(string deleteSIM)
//{
//	int pos = -1;
//	int pos2 = -1;
//	int extra_check = 1;
//	pos = getHashOne(deleteSIM);
//	pos2 = getHashTwo(deleteSIM);
//
//	if (hashTable[pos].sim.nomerSIM == deleteSIM)
//	{
//		hashTable[pos].sim.nomerSIM = "";
//		hashTable[pos].deleted = 1;
//		hashTable[pos].empty = 1;
//		hashTable[pos].pos = -1;
//		sizeCount--;
//		if (hashTable[pos].collisions > 0)
//		{
//			hashTable[pos].collisions--;
//		}
//		extra_check = 0;
//	}
//	else
//	{
//		for (int i = 0; i < size; i++)
//		{
//			//if (hashTable[pos].sim.nomerSIM != "") {
//			//	int h1 = getHashOne(hashTable[pos].sim.nomerSIM);
//			//	pos2 = getHashTwo(hashTable[pos].sim.nomerSIM);
//			//	pos = (h1 + pos2) % size;
//			//}
//			//else {
//			//	pos = (pos + pos2) % size;
//			//}
//
//			if (hashTable[pos].sim.nomerSIM == deleteSIM)
//			{
//				hashTable[pos].sim.nomerSIM = "";
//				hashTable[pos].deleted = 1;
//				hashTable[pos].empty = 1;
//				hashTable[pos].pos = -1;
//				sizeCount--;
//				if (hashTable[pos].collisions > 0)
//				{
//					hashTable[pos].collisions--;
//				}
//				extra_check = 0;
//			}
//		}
//	}
//	if (extra_check == 1)
//	{
//		return 0;
//	}
//	return 1;
//}



////	����� �� ����� (������ ����� ��� �����)
//void HashTable::searchObjectKey(string key, SIM& simSearch)
//{
//	element object;
//	object.pos = getHashOne(key);
//	int f = getHashTwo(key);
//
//	if (hashTable[object.pos].deleted == 1)
//	{
//		while (hashTable[object.pos].deleted == 1)
//		{
//			hashTable[object.pos] = hashTable[object.pos + f];
//		}
//		simSearch = hashTable[object.pos].sim;
//	}
//	else if (hashTable[object.pos].empty == 0 && hashTable[object.pos].deleted == 0)
//	{
//		simSearch = hashTable[object.pos].sim;
//	}
//	else
//	{
//		cout << " � ������� ��� ������ �����" << endl;
//	}
//}


//	����� �� ����� ��� �����
SIM HashTable::searchObjectKey(string key) {
	int count = 0;
	int h1 = getHashOne(key);
	int h2 = getHashTwo(key);

	for (int i = 0; i < size; i++) {
		if (hashTable[h1].sim.nomerSIM == key)
		{
			return hashTable[h1].sim;
		}
		else {
			if (hashTable[h1].sim.nomerSIM != "") {
				h1 = getHashOne(hashTable[h1].sim.nomerSIM);
				h2 = getHashTwo(hashTable[h1].sim.nomerSIM);
				h1 = (h1 + h2) % size;
			}
			else {
				h1 = (h1 + h2) % size;
			}
		}
	}
	if (count == 0) {
		cout << " SIM ����� � ����� ������� �� ����������\n";
		SIM sim;
		return sim;
	}
}





//  ����� ���-�������
void HashTable::printHashTable()
{
	cout << setw(15) << " �����" << setw(15) << "�����" << setw(15) << "���" << setw(15) << "������" << '\n';
	bool chek = true;
	for (int i = 0; i < size; i++)
	{
		if (hashTable[i].sim.nomerSIM != "") {
			chek = false;
			string status = hashTable[i].sim.statusWork ? "������" : "��������";
			cout << setw(15) << hashTable[i].sim.nomerSIM << setw(15) << hashTable[i].sim.tarif << setw(15) << hashTable[i].sim.vipusk << setw(15) << status << '\n';
		}
	}
	if (chek) {
		cout << setw(15) << " ���� SIM ����� �����..." << endl;
	}
}


//  �������� ���� �������
void HashTable::allDelete() {
	for (int pos = 0; pos < size; pos++)
	{
		hashTable[pos].sim.nomerSIM = "";
		hashTable[pos].sim.tarif = "";
		hashTable[pos].sim.vipusk = 0;
		hashTable[pos].sim.statusWork = false;

		hashTable[pos].deleted = 1;
		hashTable[pos].empty = 1;
		hashTable[pos].pos = -1;
		sizeCount--;
	}
}


//	�������� �� �����
void HashTable::deleteObject(string deleteSIM) {
	int count = 0;
	int h1 = getHashOne(deleteSIM);
	int h2 = getHashTwo(deleteSIM);

	for (int i = 0; i < size; i++) {
		if (hashTable[h1].sim.nomerSIM == deleteSIM)
		{
			hashTable[h1].sim.nomerSIM = "";
			hashTable[h1].sim.tarif = "";
			hashTable[h1].sim.vipusk = 0;
			hashTable[h1].sim.statusWork = false;

			hashTable[h1].deleted = 1;
			hashTable[h1].empty = 1;
			hashTable[h1].pos = -1;
			sizeCount--;

			count = 1;
		}
		else {
			if (hashTable[h1].sim.nomerSIM != "") {
				h1 = getHashOne(hashTable[h1].sim.nomerSIM);
				h2 = getHashTwo(hashTable[h1].sim.nomerSIM);
				h1 = (h1 + h2) % size;
			}
			else {
				h1 = (h1 + h2) % size;
			}
		}
	}
	if (count == 0) {
		cout << "���������� �� �������\n";
	}
}


//  �������� ��������� ��������� � ������ ������
bool HashTable::findString(string str2, string str1) {
	int i, j;
	int len1 = str1.length();
	int len2 = str2.length();

	for (i = 0; i <= len2 - len1; i++) {
		for (j = 0; j < len1; j++)
			if (str2[i + j] != str1[j]) {
				break;
			}

		if (j == len1) {
			return true;
		}	
	}

	return false;
}




void HashTable::searchSimTarif(string str) {
	bool chek = false;
	for (int i = 0; i < size; i++)
	{
		if (findString(hashTable[i].sim.tarif, str)) {
			chek = true;
		}
	}
	if(chek) {
		cout << setw(15) << " �����" << setw(15) << "�����" << setw(15) << "���" << setw(15) << '\n';
		for (int i = 0; i < size; i++)
		{
			if (findString(hashTable[i].sim.tarif, str)) {
				cout << setw(15) << hashTable[i].sim.nomerSIM << setw(15) << hashTable[i].sim.tarif << setw(15) << hashTable[i].sim.vipusk << setw(15) << '\n';
			}
		}
	}
	else {
		cout << " � ���� ���������� �� ��������\n";
	}
	
}


void HashTable::switchTarif(string key) {
	int h1 = getHashOne(key);
	int h2 = getHashTwo(key);

	for (int i = 0; i < size; i++) {
		if (hashTable[h1].sim.nomerSIM == key)
		{
			hashTable[h1].sim.statusWork = !hashTable[h1].sim.statusWork;
			break;
		}
		else {
			if (hashTable[h1].sim.nomerSIM != "") {
				h1 = getHashOne(hashTable[h1].sim.nomerSIM);
				h2 = getHashTwo(hashTable[h1].sim.nomerSIM);
				h1 = (h1 + h2) % size;
			}
			else {
				h1 = (h1 + h2) % size;
			}
		}
	}
}


bool HashTable::chekSIM(string key) {
	int count = 0;
	int h1 = getHashOne(key);
	int h2 = getHashTwo(key);

	for (int i = 0; i < size; i++) {
		if (hashTable[h1].sim.nomerSIM == key)
		{
			return true;
		}
		else {
			if (hashTable[h1].sim.nomerSIM != "") {
				h1 = getHashOne(hashTable[h1].sim.nomerSIM);
				h2 = getHashTwo(hashTable[h1].sim.nomerSIM);
				h1 = (h1 + h2) % size;
			}
			else {
				h1 = (h1 + h2) % size;
			}
		}
	}
	if (count == 0) {
		return false;
	}
}

