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

//  СОРТИРОВКА СПИСКА ИЗВЛЕЧЕНИЕМ
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
		cout << "\n |-----------------------МЕНЮ-------------------------|\n";
		cout << " | 1.  Зарегистрировать нового клиента.               |" << endl;
		cout << " | 2.  Снятие с обслуживания клиента.                 |" << endl;
		cout << " | 3.  Просмотреть всех зарегистрированных клиентов.  |" << endl;
		cout << " | 4.  Очистить все данные о клиентах.                |" << endl;
		cout << " | 5.  Поиск клиента по паспорту.                     |" << endl;
		cout << " | 6.  Поиск клиента по фрагментам ФИО или адресу.    |" << endl;
		cout << " | 7.  Добавить новую SIM-карту.                      |" << endl;
		cout << " | 8.  Удаление сведения о SIM-карте.                 |" << endl;
		cout << " | 9.  Просмотреть все имеющиесяя SIM-карт.           |" << endl;
		cout << " | 10. Очистить все данные о SIM-картах.              |" << endl;
		cout << " | 11. Поиск SIM-карты по номеру SIM-карты.           |" << endl;
		cout << " | 12. Поиск SIM-карты по тарифу.                     |" << endl;
		cout << " | 13. Зарегистрировать выдачу клиенту SIM-карты.     |" << endl;
		cout << " | 14. Зарегистрировать возврат SIM-карты от клиента. |" << endl;
		cout << " | 15. Выход                                          |" << endl;
		cout << " |----------------------------------------------------|" << endl<<endl;
		cout << " введите число: ";
		cin >> key;
		cin.ignore();

		if (key == 1)
		{
			string pasport = Chek.inputPasport();

			if (MTree.checkPasport(pasport, MTree.root)) {
				cout << "Клиент с таким паспортом уже существует." << endl;
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
			cout << "Введите номер паспорта клиента: ";
			string pas = Chek.inputPasport();

			cout << " Введите дату удаления обслуживания клиента: ";
			string data = Chek.inputFullDate();

			cout << " Данные о удаляемоим клиенте: \n";
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
				cout << " У него снимаются с обслуживания SIM карты: \n";
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
				cout << " У данного клиента не было выданных SIM карт. \n";
			}
			
		}

		if (key == 3) {
			MTree.showKlient();
		}

		if (key == 4) {
			cout << " Все данные о клинтах удалены. \n";
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
				cout << "Клиент с таким паспортом не существует." << endl;
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
					cout << " Ему выданы SIM карты: \n";
					for (int i = 0; i < MList.GetSize(); i++)
					{
						if (MList[i].pasport == pasport && MList[i].endSrok == "") {
							cout << " " << MList[i].nomerSim << endl;
						}
					}
				}
				else {
					cout << " У данного клиента не было выданных SIM карт. \n";
				}
			}
		}

		if (key == 6) {
			string str;
			cout << "\n Введите часть ФИО или адресса клиента, которого хотите найти: ";
			getline(cin, str);
			bool chek = false;
			MTree.findKlientOnString(MTree.root, str,chek);
			if (!chek) {
				cout << "\n Совпадений не найденно\n";
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
				cout << "\n Такая SIM карта уже добавлена.\n";
			}
		}


		if (key == 8) {
			string nomerSIM = Chek.inputSIM();
			Table.deleteObject(nomerSIM);

			cout << " Введите дату удаления SIM карты: ";
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

			cout << " Все SIM карты удалены\n ";
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
				cout << setw(15) << " Номер" << setw(15) << "Тариф" << setw(15) << "Год" << setw(15) << "Статус" << '\n';
				string status = poisk.statusWork ? "выдана" : "невыдана";
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
					cout << " Данная SIM карта принадлежит: \n" << endl;
					
					for (int i = 0; i < MList.GetSize(); i++)
					{
						if (MList[i].endSrok == "" && MList[i].nomerSim == nomerSIM)
						{
							MTree.findCustomer(MTree.root, MList[i].pasport);
						}
					}
				}
				else {
					cout << " Данная SIM карта никому не выдана. \n" << endl;
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
				cout << " Клиент с таким паспортом не существует." << endl;
				continue;
			}
			else {
				string nomerSIM = Chek.inputSIM();
				SIM poisk = Table.searchObjectKey(nomerSIM);
				if (poisk.nomerSIM != "") {
					if (poisk.statusWork == false) {
						cout << " Введите дату выдачи SIM карты: " ;
						string data = Chek.inputFullDate();
						listPeaple vip(pasport, nomerSIM, data);
						MList.push_back(vip);
						sortList(MList);
						cout << " SIM карта выдана\n";
						Table.switchTarif(nomerSIM);
					}
					else {
						cout << " SIM карты с таким номером уже зарегистрирована клиенту." << endl;
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
				cout << " Клиент с таким паспортом не существует." << endl;
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
									cout << " Введите дату возврата SIM карты: ";
									data = Chek.inputFullDate();
									
								} while (!Chek.chekDifferentDate(MList[i].vipusk, data));

								MList[i].endSrok = data;
								break;
							}
						}
						cout << " SIM карта возвращена\n";
						Table.switchTarif(nomerSIM);
					}
					else {
						cout << " SIM карты с таким номером не зарегистрирована клиенту." << endl;
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
			string placeAndDate1 = "Ростов-на-Дону";
			string FIO1 = "Шлифер Роберт Александрович";
			int birthyear1 = 2001;
			string address1 = "Санкт-Петербург ул. Передовиков 13 кв. 151/3";
			clientTree clientAdd1(pasport1, placeAndDate1, FIO1, birthyear1, address1);
			MTree.addKlitnt(clientAdd1);

			string pasport6 = "2001-300000";
			string placeAndDate6 = "Ростов-на-Дону";
			string FIO6 = "Шлифер Роберт Александрович";
			int birthyear6 = 2001;
			string address6 = "Санкт-Петербург ул. Передовиков 13 кв. 151/3";
			clientTree clientAdd6(pasport6, placeAndDate6, FIO6, birthyear6, address6);
			MTree.addKlitnt(clientAdd6);

			string pasport2 = "2000-300450";
			string placeAndDate2 = "Самара";
			string FIO2 = "Смирнов Александ Дмитриевич";
			int birthyear2 = 1970;
			string address2 = "Санкт-Петербург ул. Садовая 3";
			clientTree clientAdd2(pasport2, placeAndDate2, FIO2, birthyear2, address2);
			MTree.addKlitnt(clientAdd2);

			string pasport3 = "0000-345006";
			string placeAndDate3 = "Москва";
			string FIO3 = "Шаталов Юрий Александрович";
			int birthyear3 = 1965;
			string address3 = "Санкт-Петербург ул.Усатая 66";
			clientTree clientAdd3(pasport3, placeAndDate3, FIO3, birthyear3, address3);
			MTree.addKlitnt(clientAdd3);

			string pasport4 = "4056-395725";
			string placeAndDate4 = "Шахты";
			string FIO4 = "Иванов Данил Михайлович";
			int birthyear4 = 2002;
			string address4 = "Санкт-Петербург улПередовиков 13 кв. 151/3а";
			clientTree clientAdd4(pasport4, placeAndDate4, FIO4, birthyear4, address4);
			MTree.addKlitnt(clientAdd4);

			string pasport5 = "0000-012345";
			string placeAndDate5 = "Лихая";
			string FIO5 = "Гулов Георгий Витальевич";
			int birthyear5 = 2002;
			string address5 = "Санкт-Петербург улПередовиков 13 кв. 151/2а";
			clientTree clientAdd5(pasport5, placeAndDate5, FIO5, birthyear5, address5);
			MTree.addKlitnt(clientAdd5);

			string n = "123-1234567";
			string t = "полный";
				int v = 1234;
				bool b = false;
				SIM s(n, t, v, b);
				Table.addKeyHashTable(s);

				string n1 = "176-1234567";
				string t1 = "полный";
				int v1 = 1234;
				bool b1 = false;
				SIM s1(n1, t1, v1, b1);
				Table.addKeyHashTable(s1);

				string n2 = "543-1234567";
				string t2 = "полный";
				int v2 = 1234;
				bool b2 = false;
				SIM s2(n2, t2, v2, b2);
				Table.addKeyHashTable(s2);


				string n3 = "123-1275567";
				string t3 = "полный";
				int v3 = 1234;
				bool b3 = true;
				SIM s3(n3, t3, v3, b3);
				Table.addKeyHashTable(s3);

				string n4 = "123-1275567";
				string t4 = "полный";
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