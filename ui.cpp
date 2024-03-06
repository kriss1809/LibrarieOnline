#pragma once 
#include "ui.h"
#include <iostream>

using namespace std;

void consola::Meniu()
{
	cout << "1.Afisare carti din lista." << "\n";
	cout << "2.Adaugare carte in lista." << "\n";
	cout << "3.Modificare carte din lista." << "\n";
	cout << "4.Stergere carte din lista." << "\n";
	cout << "5.Cautare carte in lista." << "\n";
	cout << "6.Filtrare carti din lista." << "\n";
	cout << "7.Sortare carti din lista." << "\n";
	cout << "8.Afisare cate carti din fiecare gen exista." << "\n";
	cout << "9.Undo." << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "10.Afisare carti din cos." << "\n";
	cout << "11.Adaugare carte in cos." << "\n";
	cout << "12.Generare cos." << "\n";
	cout << "13.Golire cos." << "\n";
	cout << "14.Export cos in fisier CSV sau HTML." << "\n";
	cout << "15.Iesire." << "\n";
}

void consola::afisare_carti()
{
	auto carti = service.getAll();
	if (carti.size() == 0)
		cout << "\nNu exista carti.\n";
	else
		cout << "\nCartile din biblioteca sunt: \n";
	for (const auto& Carte : carti)
		cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
	cout << "\n";
}

void consola::adaugare_ui()
{

	string titlu, gen, autor;
	int an;
	cout << "Titlu: ";
	getline(cin >> ws, titlu);
	cout << "Autor: ";
	getline(cin >> ws, autor);
	cout << "Gen: ";
	getline(cin >> ws, gen);
	cout << "Anul aparitiei: ";
	cin >> an;

	try
	{
		service.adaugare_carte(titlu, autor, gen, an);
		cout << "\nCarte adaugata cu succes!\n\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
}

void consola::modificare_ui()
{
	string titlu, gen, autor;
	int an;
	cout << "Titlul cartii: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii: ";
	getline(cin >> ws, autor);
	cout << "Modificare gen: ";
	getline(cin >> ws, gen);
	cout << "Modificare an aparitie: ";
	cin >> an;
	try
	{
		service.actualizare_carte(titlu, autor, gen, an);
		cout << "\nCarte modificata cu succes!\n\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
}

void consola::stergere_ui()
{
	string titlu, autor;
	cout << "Titlul cartii: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii: ";
	getline(cin >> ws, autor);
	try
	{
		service.stergere_carte(titlu, autor);
		cout << "\nCarte eliminata cu succes!\n\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
}

void consola::cautare_ui()
{
	string titlu, autor;
	cout << "Titlul cartii: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii: ";
	getline(cin >> ws, autor);

	try
	{
		Carte c = service.cautare_carte(titlu, autor);
		cout << "\nCartea cautata este: \n";
		cout << "Titlu: " << c.getTitlu() << " | Autor: " << c.getAutor() << " | Gen: " << c.getGen() << " | Anul aparitiei: " << c.getAn() << "\n\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
}

void consola::filtrare_ui()
{
	string titlu;
	int an;
	cout << "Dupa ce doriti sa filtrati?\n 1. Titlu\n 2.Anul aparitiei ";
	int comanda;
	cin >> comanda;
	if (comanda == 1)
	{
		cout << "Titlul: ";
		getline(cin >> ws, titlu);
		auto lista_carti = service.filtrare_titlu(titlu);
		if (lista_carti.size() == 0)
			cout << "Nu exista carti." << "\n";
		else
			for (auto Carte : lista_carti)
			{
				cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
			}
	}
	else if (comanda == 2)
	{
		cout << "Anul: ";
		cin >> an;
		auto lista_carti = service.filtrare_an(an);
		if (lista_carti.size() == 0)
			cout << "Nu exista carti." << "\n";
		else
			for (auto Carte : lista_carti)
			{
				cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
			}
	}
	else
	{
		cout << "Optiune invalida.\n";
	}
}

void consola::sortare_ui()
{
	cout << "Dupa ce doriti sa filtrati?\n 1. Titlu\n 2. Autor\n 3.Anul aparitiei + gen ";
	int comanda;
	cin >> comanda;
	if (comanda == 1)
	{
		auto lista_carti = service.sortare_titlu();
		if (lista_carti.size() == 0)
			cout << "Nu exista carti." << "\n";
		else
			for (auto Carte : lista_carti)
			{
				cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
			}
	}
	else if (comanda == 2)
	{
		auto lista_carti = service.sortare_autor();
		if (lista_carti.size() == 0)
			cout << "Nu exista carti." << "\n";
		else
			for (auto Carte : lista_carti)
			{
				cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
			}
	}
	else if (comanda == 3)
	{
		auto lista_carti = service.sortare_an_gen();
		if (lista_carti.size() == 0)
			cout << "Nu exista carti." << "\n";
		else
			for (auto Carte : lista_carti)
			{
				cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
			}
	}
	else
		cout << "Optiune invalida\n";
}

void consola::afisare_cos() {
	auto lista_carti = service.getAll_cos();
	if (lista_carti.size() == 0)
		cout << "\nCosul este gol.\n";
	else
		for (auto Carte : lista_carti)
		{
			cout << "Titlu: " << Carte.getTitlu() << " | Autor: " << Carte.getAutor() << " | Gen: " << Carte.getGen() << " | Anul aparitiei: " << Carte.getAn() << "\n";
		}
	cout << "\n";
}

void consola::adaugare_in_cos_ui()
{
	size_t cnt_carti;
	auto carti = service.getAll();
	if (carti.size() == 0)
	{
		cout << "\nLista de carti este goala momentan!\n\n";
		cnt_carti = service.get_marime_cos();
		cout << "\nIn cos se afla " << cnt_carti << " carti.\n\n";
	}
	else
	{
		string titlu, autor;
		cout << "Titlu: ";
		getline(cin >> ws, titlu);
		cout << "Autor: ";
		getline(cin >> ws, autor);

		try
		{
			service.adaugare_carte_in_cos(titlu, autor);
			cnt_carti = service.get_marime_cos();
			cout << "\nIn cos se afla " << cnt_carti << " carti.\n\n";
		}
		catch (ExceptieRepo& er)
		{
			cout << er.getMesajeEroare();
		}
	}
}

void consola::generare_cos_ui()
{
	size_t cnt_carti;
	auto carti = service.getAll();
	if (carti.size() == 0)
	{
		cout << "\nLista de carti este goala momentan!\n\n";
		cnt_carti = service.get_marime_cos();
		cout << "\nIn cos se afla " << cnt_carti << " carti.\n\n";
	}
	else
	{
		int ok = 1;
		string nr;
		cout << "Introduceti numarul dorit: ";
		getline(cin >> ws, nr);
		for (char const& c : nr)
		{
			if (std::isdigit(c) == 0)
			{
				ok = 0;
				break;
			}
		}
		if (ok == 0)
			cout << "Trebuie sa introduceti un numar pozitiv!" << endl;
		else
		{
			try
			{
				const int numar = stoi(nr);
				if (numar > carti.size())
				{
					cout << "Numarul dorit depaseste lungimea listei!" << endl;
					return;
				}
				service.genereaza_cos(numar);
				cnt_carti = service.get_marime_cos();
				cout << "\nIn cos se afla " << cnt_carti << " carti.\n\n";
			}
			catch (ExceptieValidator& ev)
			{
				cout << ev.get_mesaje_eroare();
			}
		}
	}
}

void consola::golire_cos_ui()
{
	size_t cnt_carti;
	auto cos = service.getAll_cos();
	if (cos.size() == 0)
	{
		cout << "Cosul este deja gol!\n";
		return;
	}
	service.golire_cos();
	cnt_carti = service.get_marime_cos();
	cout << "\nIn cos se afla " << cnt_carti << " carti.\n\n";
}

void consola::cerinta_noua()
{
	map<string, DTO> dict = service.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		cout << it->second.get_gen() << " " << it->second.get_cnt() << "\n";
	}
}

void consola::export_cos_ui()
{
	string fisier;
	cout << "\nDati numele fisierului: ";
	getline(cin >> ws, fisier);
	try
	{
		service.export_cos(fisier);
		cout << "Export efectuat cu succes!\n\n";
	}
	catch (ExceptieValidator& ve)
	{
		cout << ve.get_mesaje_eroare();
	}
}

void consola::undo_ui()
{
	if (service.undo() == 1)
		cout << "\nNu se mai poate face undo!\n\n";
	else
		cout << "\nUndo realizat cu succes!\n\n";
}

void consola::run()
{
	int comanda, ok = 1;
	while (ok)
	{
		Meniu();
		cout << "Ce doriti sa faceti? ";
		cin >> comanda;
		switch (comanda)
		{
		case 1:
			afisare_carti();
			break;
		case 2:
			adaugare_ui();
			break;
		case 3:
			modificare_ui();
			break;
		case 4:
			stergere_ui();
			break;
		case 5:
			cautare_ui();
			break;
		case 6:
			filtrare_ui();
			break;
		case 7:
			sortare_ui();
			break;
		case 8:
			cerinta_noua();
			break;
		case 9:
			undo_ui();
			break;
		case 10:
			afisare_cos();
			break;
		case 11:
			adaugare_in_cos_ui();
			break;
		case 12:
			generare_cos_ui();
			break;
		case 13:
			golire_cos_ui();
			break;
		case 14:
			export_cos_ui();
			break;
		case 15:
			ok = 0;
			break;
		default:
			break;
		}
	}
}