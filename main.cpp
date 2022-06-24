#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <fstream>

#include "HashTable.h"
#include "ListTwo.h"
#include "Tree.h"
#include "ChelValue.h"

using namespace std;

//  ���������� ������ �����������
void sortList(ListTwo& list) {
	for (int i = 0; i < list.GetSize(); i++)
	{
		listPeaple min = list[i];
		int index = i;
		for (int t = i+1; t < list.GetSize(); t++)
		{
			if (stoi(list[t].nomerSim) < stoi(min.nomerSim)) {
				min = list[t];
				index = t;
			}
		}
		list[index] = list[i];
		list[i] = min;
	}
}

int main() {
	
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int key;
	
	HashTable Table;
	ListTwo MList;
	Tree MTree;
	ChelValue Chek;
	
	while (true) {
		cout << "\n |-----------------------����-------------------------|\n";
		cout << " | 1.  ���������������� ������ �������.               |" << endl;
		cout << " | 2.  ������ � ������������ �������.                 |" << endl;
		cout << " | 3.  ����������� ���� ������������������ ��������.  |" << endl;
		cout << " | 4.  �������� ��� ������ � ��������.                |" << endl;
		cout << " | 5.  ����� ������� �� ��������.                     |" << endl;
		cout << " | 6.  ����� ������� �� ���������� ��� ��� ������.    |" << endl;
		cout << " | 7.  �������� ����� SIM-�����.                      |" << endl;
		cout << " | 8.  �������� �������� � SIM-�����.                 |" << endl;
		cout << " | 9.  ����������� ��� ���������� SIM-����.           |" << endl;
		cout << " | 10. �������� ��� ������ � SIM-������.              |" << endl;
		cout << " | 11. ����� SIM-����� �� ������ SIM-�����.           |" << endl;
		cout << " | 12. ����� SIM-����� �� ������.                     |" << endl;
		cout << " | 13. ���������������� ������ ������� SIM-�����.     |" << endl;
		cout << " | 14. ���������������� ������� SIM-����� �� �������. |" << endl;
		cout << " | 15. �����                                          |" << endl;
		cout << " |----------------------------------------------------|" << endl<<endl;
		cout << " ������� �����: ";
		cin >> key;
		cin.ignore();

		if (key == 1)
		{
			string pasport = Chek.inputPasport();

			if (MTree.checkPasport(pasport, MTree.root)) {
				cout << "������ � ����� ��������� ��� ����������." << endl;
			}
			else {
				string placeAndDate = Chek.inputBirthdayAndPlaces();
				string FIO = Chek.inputFIO();
				int birthyear = Chek.inputYear();
				string address = Chek.inputArress();
				clientTree clientAdd(pasport, placeAndDate, FIO, birthyear, address);
				MTree.addKlitnt(clientAdd);
			}

		}

		if (key == 2) {
			cout << "������� ����� �������� �������: ";
			string pas = Chek.inputPasport();

			cout << " ������� ���� �������� ������������ �������: ";
			string data = Chek.inputFullDate();

			cout << " ������ � ���������� �������: \n";
			MTree.findCustomer(MTree.root, pas);
			MTree.deleteKlient(pas);

			
			bool chek = false;
			for (int i = 0; i < MList.GetSize(); i++)
			{
				if (MList[i].pasport == pas && MList[i].endSrok == "") {
					chek = true;
				}
			}

			if(chek) {
				cout << " � ���� ��������� � ������������ SIM �����: \n";
				for (int i = 0; i < MList.GetSize(); i++)
				{
					if (MList[i].pasport == pas && MList[i].endSrok == "") {
						cout << " " << MList[i].nomerSim << endl;
						Table.switchTarif(MList[i].nomerSim);
						MList[i].endSrok = data;
					}
				}
			}
			else {
				cout << " � ������� ������� �� ���� �������� SIM ����. \n";
			}
			
		}

		if (key == 3) {
			MTree.showKlient();
		}

		if (key == 4) {
			cout << " ��� ������ � ������� �������. \n";
			MTree.removeAll();

			for (int i = 0; i < MList.GetSize(); i++)
			{
				if (MList[i].endSrok == "") {
					Table.switchTarif(MList[i].nomerSim);
					MList[i].endSrok = "AllDeleteKlient";
				}
			}
		}

		if (key == 5) {
			string pasport = Chek.inputPasport();
			if (!MTree.checkPasport(pasport, MTree.root)) {
				cout << "������ � ����� ��������� �� ����������." << endl;
			}
			else {
				MTree.findCustomer(MTree.root, pasport);

				bool chek = false;
				for (int i = 0; i < MList.GetSize(); i++)
				{
					if (MList[i].pasport == pasport && MList[i].endSrok == "") {
						chek = true;
					}
				}

				if (chek) {
					cout << " ��� ������ SIM �����: \n";
					for (int i = 0; i < MList.GetSize(); i++)
					{
						if (MList[i].pasport == pasport && MList[i].endSrok == "") {
							cout << " " << MList[i].nomerSim << endl;
						}
					}
				}
				else {
					cout << " � ������� ������� �� ���� �������� SIM ����. \n";
				}
			}
		}

		if (key == 6) {
			string str;
			cout << "\n ������� ����� ��� ��� ������� �������, �������� ������ �����: ";
			getline(cin, str);
			bool chek = false;
			MTree.findKlientOnString(MTree.root, str,chek);
			if (!chek) {
				cout << "\n ���������� �� ��������\n";
			}
		}

		if (key == 7) {
			string nomerSIM = Chek.inputSIM();

			if (!Table.chekSIM(nomerSIM)) {
				string tarif = Chek.inputTarifSIM();
				int vipusk = Chek.inputYear();
				SIM newSIM(nomerSIM, tarif, vipusk);
				Table.addKeyHashTable(newSIM);
			}
			else {
				cout << "\n ����� SIM ����� ��� ���������.\n";
			}
		}


		if (key == 8) {
			string nomerSIM = Chek.inputSIM();
			Table.deleteObject(nomerSIM);

			cout << " ������� ���� �������� SIM �����: ";
			string data = Chek.inputFullDate();

			for (int i = 0; i < MList.GetSize(); i++)
			{
				if (MList[i].nomerSim == nomerSIM && MList[i].endSrok == "")
				{
					MList[i].endSrok = data;
				}
			}
		}


		if (key == 9) {
			Table.printHashTable();
		}


		if (key == 10) {
			Table.allDelete();

			cout << " ��� SIM ����� �������\n ";
			for (int i = 0; i < MList.GetSize(); i++)
			{
				if (MList[i].endSrok == "")
				{
					MList[i].endSrok = "AllDeleteSIM";
				}
			}
		}

		if (key == 11) {
			string nomerSIM = Chek.inputSIM();
			SIM poisk = Table.searchObjectKey(nomerSIM);
			if (poisk.nomerSIM != "") {
				cout << setw(15) << " �����" << setw(15) << "�����" << setw(15) << "���" << setw(15) << "������" << '\n';
				string status = poisk.statusWork ? "������" : "��������";
				cout << setw(15) << poisk.nomerSIM << setw(15) << poisk.tarif << setw(15) << poisk.vipusk << setw(15) << status << '\n';

				
				
				bool chek = false;
				for (int i = 0; i < MList.GetSize(); i++)
				{
					if (MList[i].endSrok == "" && MList[i].nomerSim == nomerSIM)
					{
						chek = true;
					}
				}

				if (chek)
				{
					cout << " ������ SIM ����� �����������: \n" << endl;
					
					for (int i = 0; i < MList.GetSize(); i++)
					{
						if (MList[i].endSrok == "" && MList[i].nomerSim == nomerSIM)
						{
							MTree.findCustomer(MTree.root, MList[i].pasport);
						}
					}
				}
				else {
					cout << " ������ SIM ����� ������ �� ������. \n" << endl;
				}
				
			}
		}


		if (key == 12) {
			string tarif = Chek.inputTarifSIM();
			Table.searchSimTarif(tarif);
		}


		if (key == 13) {
			string pasport = Chek.inputPasport();
			if (!MTree.checkPasport(pasport, MTree.root)) {
				cout << " ������ � ����� ��������� �� ����������." << endl;
				continue;
			}
			else {
				string nomerSIM = Chek.inputSIM();
				SIM poisk = Table.searchObjectKey(nomerSIM);
				if (poisk.nomerSIM != "") {
					if (poisk.statusWork == false) {
						cout << " ������� ���� ������ SIM �����: " ;
						string data = Chek.inputFullDate();
						listPeaple vip(pasport, nomerSIM, data);
						MList.push_back(vip);
						sortList(MList);
						cout << " SIM ����� ������\n";
						Table.switchTarif(nomerSIM);
					}
					else {
						cout << " SIM ����� � ����� ������� ��� ���������������� �������." << endl;
						continue;
					}
				}
				else {
					continue;
				}
			}
		}


		if (key == 14) {
			string pasport = Chek.inputPasport();
			if (!MTree.checkPasport(pasport, MTree.root)) {
				cout << " ������ � ����� ��������� �� ����������." << endl;
				continue;
			}
			else {
				string nomerSIM = Chek.inputSIM();
				SIM poisk = Table.searchObjectKey(nomerSIM);
				if (poisk.nomerSIM != "") {
					bool chek = false;

					for (int i = 0; i < MList.GetSize(); i++)
					{
						if (MList[i].nomerSim == nomerSIM && MList[i].endSrok == "" && MList[i].pasport == pasport)
						{
							chek = true;
						}
					}
					
					
					if (poisk.statusWork == true && chek) {
						for (int i = 0; i < MList.GetSize(); i++)
						{
							if (MList[i].nomerSim == nomerSIM && MList[i].pasport == pasport && MList[i].endSrok == "")
							{
								string data;
								do {
									cout << " ������� ���� �������� SIM �����: ";
									data = Chek.inputFullDate();
									
								} while (!Chek.chekDifferentDate(MList[i].vipusk, data));

								MList[i].endSrok = data;
								break;
							}
						}
						cout << " SIM ����� ����������\n";
						Table.switchTarif(nomerSIM);
					}
					else {
						cout << " SIM ����� � ����� ������� �� ���������������� �������." << endl;
						continue;
					}
				}
				else {
					continue;
				}
			}
		}



		if (key == 19) {
			string pasport1 = "2000-300000";
			string placeAndDate1 = "������-��-����";
			string FIO1 = "������ ������ �������������";
			int birthyear1 = 2001;
			string address1 = "�����-��������� ��. ����������� 13 ��. 151/3";
			clientTree clientAdd1(pasport1, placeAndDate1, FIO1, birthyear1, address1);
			MTree.addKlitnt(clientAdd1);

			string pasport6 = "2001-300000";
			string placeAndDate6 = "������-��-����";
			string FIO6 = "������ ������ �������������";
			int birthyear6 = 2001;
			string address6 = "�����-��������� ��. ����������� 13 ��. 151/3";
			clientTree clientAdd6(pasport6, placeAndDate6, FIO6, birthyear6, address6);
			MTree.addKlitnt(clientAdd6);

			string pasport2 = "2000-300450";
			string placeAndDate2 = "������";
			string FIO2 = "������� �������� ����������";
			int birthyear2 = 1970;
			string address2 = "�����-��������� ��. ������� 3";
			clientTree clientAdd2(pasport2, placeAndDate2, FIO2, birthyear2, address2);
			MTree.addKlitnt(clientAdd2);

			string pasport3 = "0000-345006";
			string placeAndDate3 = "������";
			string FIO3 = "������� ���� �������������";
			int birthyear3 = 1965;
			string address3 = "�����-��������� ��.������ 66";
			clientTree clientAdd3(pasport3, placeAndDate3, FIO3, birthyear3, address3);
			MTree.addKlitnt(clientAdd3);

			string pasport4 = "4056-395725";
			string placeAndDate4 = "�����";
			string FIO4 = "������ ����� ����������";
			int birthyear4 = 2002;
			string address4 = "�����-��������� ������������� 13 ��. 151/3�";
			clientTree clientAdd4(pasport4, placeAndDate4, FIO4, birthyear4, address4);
			MTree.addKlitnt(clientAdd4);

			string pasport5 = "0000-012345";
			string placeAndDate5 = "�����";
			string FIO5 = "����� ������� ����������";
			int birthyear5 = 2002;
			string address5 = "�����-��������� ������������� 13 ��. 151/2�";
			clientTree clientAdd5(pasport5, placeAndDate5, FIO5, birthyear5, address5);
			MTree.addKlitnt(clientAdd5);

			string n = "123-1234567";
			string t = "������";
				int v = 1234;
				bool b = false;
				SIM s(n, t, v, b);
				Table.addKeyHashTable(s);

				string n1 = "176-1234567";
				string t1 = "������";
				int v1 = 1234;
				bool b1 = false;
				SIM s1(n1, t1, v1, b1);
				Table.addKeyHashTable(s1);

				string n2 = "543-1234567";
				string t2 = "������";
				int v2 = 1234;
				bool b2 = false;
				SIM s2(n2, t2, v2, b2);
				Table.addKeyHashTable(s2);


				string n3 = "123-1275567";
				string t3 = "������";
				int v3 = 1234;
				bool b3 = true;
				SIM s3(n3, t3, v3, b3);
				Table.addKeyHashTable(s3);

				string n4 = "123-1275567";
				string t4 = "������";
				int v4 = 1234;
				bool b4 = false;
				SIM s4(n4, t4, v4, b4);
				Table.addKeyHashTable(s4);

		}
	}







	
	//HashTable t;
	//t.addKeyHashTable(s);
	//t.addKeyHashTable(s2);
	//t.deleteObject("12345678912");
	//t.printHashTable();

	//listPeaple a("71", "1", "123", "123");
	//listPeaple b("32", "2", "123", "123");
	//listPeaple c("23", "3", "123", "123");
	//listPeaple d("94", "4", "123", "123");
	//listPeaple r("55", "5", "123", "123");
	//
	//ListTwo l;

	//l.push_back(d);
	//l.push_back(c);
	//l.push_back(a);
	//l.push_back(b);
	//l.push_back(r);
	//
	//sortList(l);
	//////l.insert(c, 3);

	//l.pop_front();
	//
	//l.pop_back();
	//l.clear();
	

	//clientTree pp1("12323", "1", "1", 1, "1");
	//clientTree pp2("12311", "1", "1", 1, "1");
	//clientTree pp3("12332", "1", "1", 1, "1");
	//clientTree pp4("12335", "1", "1", 1, "1");
	//clientTree pp5("12348", "1", "1", 1, "1");
	//clientTree pp6("12344", "1", "1", 1, "1");
	//clientTree pp7("12347", "1", "1", 1, "1");

	//Tree tr;

	//tr.addKlitnt(pp1);
	//tr.addKlitnt(pp2);
	//tr.addKlitnt(pp3);
	//tr.addKlitnt(pp4);
	//tr.addKlitnt(pp5);
	//tr.addKlitnt(pp6);
	//tr.addKlitnt(pp7);
	//tr.addKlitnt(pp5);
	////tr.removeAll(tr.root);
	//tr.walk(tr.root);

}