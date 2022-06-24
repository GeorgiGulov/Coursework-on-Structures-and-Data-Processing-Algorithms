#pragma once
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

//	���������  SIM �����
struct SIM
{
	string nomerSIM ;
	string tarif;
	int vipusk;
	  bool statusWork;

	  SIM(string nomerSIM = "", string tarif = "", int vipusk = NULL, bool statusWork = false) {
		  this->nomerSIM = nomerSIM;
		  this->tarif = tarif;
		  this->vipusk = vipusk;
		  this->statusWork = statusWork;
	  }
};

//	��������� ������ ��� �������
struct element
{
	SIM sim;
	bool empty      =  1;   // ������ ��
	bool deleted    =  0;   // ����� ��
	 int pos        = -1;   // �������
	 int collisions =  0;   // ��������
};


class HashTable
{
public:
	HashTable();
	const int size = 500;					// ������ �������
	int sizeCount = 0;						// ������� ��� ��������� � �������

	element* hashTable; // �� ��������� ������������ ����� ������� ������ ��� ������� �������� � ����;

	int getHashOne(string key);
	int getHashTwo(string key);
	
	
	int  addKeyHashTable(SIM);
	void  deleteObject(string deleteSIM);
	SIM searchObjectKey(string key);
	void allDelete();


	void printHashTable();

	bool findString(string s, string c);

	void searchSimTarif(string str);

	void switchTarif(string str); 

	bool chekSIM(string key);  // �������� ��� ����� �� ������������
};

