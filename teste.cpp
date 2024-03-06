#pragma once
#include <map>
#include <fstream>
#include "teste.h"

void testAll()
{
	test_carte();
	test_adaugare_repo();
	test_actualizare_repo();
	test_stergere_repo();
	test_cmp();
	test_actualizare_service();
	test_stergere_service();
	test_adaugare_service();
	test_cautare_service();
	test_gaseste_repo();
	test_filtrare();
	test_sortare();

	test_adaugare_cos_repo();
	test_golire_cos_repo();
	test_adaugare_cos_service();
	test_golire_cos_service();
	test_generare_cos_service();
	test_get_marime_cos();

	test_cerinta_noua();

	test_undo();
	test_validare_fisier();
	test_export_cos_csv();
	test_export_cos_html();
}

void test_carte()
{
	Carte carte{ "Misterul din Caraibe","Agatha Christie", "politist", 1967 };
	assert(carte.getTitlu() == "Misterul din Caraibe");
	assert(carte.getGen() == "politist");
	assert(carte.getAutor() == "Agatha Christie");
	assert(carte.getAn() == 1967);

	carte.setTitlu("Harry Potter");
	carte.setGen("fantasy");
	carte.setAutor("J.K.Rowling");
	carte.setAn(1998);

	assert(carte.getTitlu() == "Harry Potter");
	assert(carte.getGen() == "fantasy");
	assert(carte.getAutor() == "J.K.Rowling");
	assert(carte.getAn() == 1998);
}


void test_cmp()
{
	Carte carte1{ "Misterul din Caraibe","Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","fantasy", 1998 };
	Carte carte3{ "Ciresarii", "Constantin Chirita", "aventura", 1998 };
	assert(cmpTitlu(carte1, carte2) == false);
	assert(cmpAutor(carte1, carte2) == true);
	assert(cmpAnGen(carte1, carte2) == true);
	assert(cmpAnGen(carte3, carte2) == true);
	assert(cmpAnGen(carte3, carte1) == false);
}

void test_adaugare_repo()
{
	RepoCarti test;
	Carte carte1{ "Misterul din Caraibe","Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","fantasy", 1998 };
	test.adaugare(carte1);
	test.adaugare(carte2);
	assert(test.getAll().size() == 2);

	Carte carte3{ "HP","J.K.Rowling","fantasy", 1998 };
	try
	{
		test.adaugare(carte2);
	}
	catch (ExceptieRepo) {
		assert(true);
	}
}

void test_adaugare_service()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };

	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "fantasy", 1998);

	assert(testService.getAll().size() == 2);
	try
	{
		testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1997);
	}
	catch (ExceptieRepo&)
	{
		assert(true);
	}
	try
	{
		testService.adaugare_carte("HP", "JK", "", 2030);
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Titlul cartii trebuie sa aiba cel putin 3 caractere.\nGenul cartii trebuie sa aiba cel putin 1 caracter.\nNumele autorului trebuie sa aiba cel putin 3 caractere.\nCartea nu a fost inca publicata.\n");
	}
}


void test_actualizare_repo()
{
	RepoCarti test;
	Carte carte1{ "Misterul din Caraibe","Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","fantasy", 1998 };
	Carte carte3{ "Harry Potter","J.K.Rowling","SF", 1999 };
	Carte carte4{ "Harry Potter si Piatra Filozofala","J.K.Rowling","SF", 2000 };
	test.adaugare(carte1);
	test.adaugare(carte2);
	test.actualizare(carte3);
	try
	{
		test.actualizare(carte4);
	}
	catch (ExceptieRepo) {
		assert(true);
	}
}

void test_actualizare_service()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.actualizare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1977);
	auto carte_gasita = testService.cautare_carte("Misterul din Caraibe", "Agatha Christie");
	assert(carte_gasita.getAn() == 1977);
}

void test_stergere_repo()
{
	RepoCarti test;
	try
	{
		test.stergere("Harry Potter", "J.K.Rowling");
	}
	catch (ExceptieRepo)
	{
		assert(true);
	}
	Carte carte1{ "Misterul din Caraibe","Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","fantasy", 1998 };
	Carte carte3{ "Gandeste-te la un numar", "John Verdon", "politist", 2016 };
	test.adaugare(carte1);
	test.adaugare(carte2);
	test.adaugare(carte3);
	assert(test.getAll().size() == 3);
	test.stergere("Harry Potter", "J.K.Rowling");
	assert(test.getAll().size() == 2);
	try
	{
		test.stergere("Ciresarii", "Constantin Chirita");
	}
	catch (const ExceptieRepo&)
	{
		assert(true);
	}
}

void test_stergere_service()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1999);
	testService.stergere_carte("Harry Potter", "J.K.Rowling");
	assert(testService.getAll().size() == 1);
}

void test_gaseste_repo()
{
	RepoCarti test;
	Carte carte1{ "Misterul din Caraibe", "Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","SF", 1998 };
	Carte carte3{ "Gandeste-te la un numar", "John Verdon", "politist", 2016 };
	test.adaugare(carte1);
	test.adaugare(carte2);

	assert(test.exista(carte1));
	assert(!test.exista(carte3));

	auto carte_gasita = test.gaseste_carte("Misterul din Caraibe", "Agatha Christie");
	assert(carte_gasita.getAn() == 1967);
	assert(carte_gasita.getGen() == "politist");
	try
	{
		test.gaseste_carte("Gandeste-te la un numar", "John Verdon");
	}
	catch (ExceptieRepo& ev)
	{
		assert(ev.getMesajeEroare() == "Cartea cu titlul si autorul introdus nu exista in lista!\n");
	}
}


void test_cautare_service()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	auto carte_gasita = testService.cautare_carte("Misterul din Caraibe", "Agatha Christie");
	assert(carte_gasita.getAn() == 1967);
	assert(carte_gasita.getGen() == "politist");
}

void test_filtrare()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };

	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "fantasy", 1998);
	testService.adaugare_carte("Harry Potter", "Rowling", "fantasy", 2016);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);

	auto lista_filtrata_titlu = testService.filtrare_titlu("Harry Potter");
	assert(lista_filtrata_titlu.size() == 2);
	lista_filtrata_titlu = testService.filtrare_titlu("Harry");
	assert(lista_filtrata_titlu.size() == 0);

	auto lista_filtrata_an = testService.filtrare_an(2016);
	assert(lista_filtrata_an.size() == 2);
	lista_filtrata_an = testService.filtrare_an(1998);
	assert(lista_filtrata_an.size() == 1);
}

void test_sortare()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };

	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "fantasy", 1998);
	testService.adaugare_carte("Harry Potter", "Rowling", "fantasy", 2016);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);

	auto lista_sortata = testService.sortare_titlu();
	assert(lista_sortata[1].getTitlu() == "Harry Potter");
	assert(lista_sortata[3].getTitlu() == "Misterul din Caraibe");

	lista_sortata = testService.sortare_autor();
	assert(lista_sortata[0].getAutor() == "Agatha Christie");
	assert(lista_sortata[3].getAutor() == "Rowling");

	lista_sortata = testService.sortare_an_gen();
	assert(lista_sortata[0].getTitlu() == "Misterul din Caraibe");
	assert(lista_sortata[3].getTitlu() == "Gandeste-te la un numar");
}

void test_adaugare_cos_repo()
{
	CosCarti cos;
	Carte carte1{ "Misterul din Caraibe", "Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","SF", 1998 };
	Carte carte3{ "Gandeste-te la un numar", "John Verdon", "politist", 2016 };
	cos.adaugare_carte_in_cos(carte1);
	cos.adaugare_carte_in_cos(carte2);
}

void test_golire_cos_repo()
{
	RepoCarti testR;
	CosCarti cos;
	try
	{
		testR.stergere("Gandeste-te la un numar", "John Verdon");
	}
	catch (ExceptieRepo)
	{
		assert(true);
	}
	Carte carte1{ "Misterul din Caraibe", "Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter","J.K.Rowling","SF", 1998 };
	testR.adaugare(carte1);
	testR.adaugare(carte2);
	cos.adaugare_carte_in_cos(carte1);
	cos.adaugare_carte_in_cos(carte2);
	assert(cos.getAll_cos().size() == 2);
	cos.golire_cos();
	assert(cos.getAll_cos().size() == 0);
}

void test_adaugare_cos_service()
{
	vector<Carte>carti;
	RepoCarti testR;
	CosCarti cos;
	ValidatorCarte testV;
	StocareCarti testService{ testR,cos, testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte_in_cos("Misterul din Caraibe", "Agatha Christie");
	testService.adaugare_carte_in_cos("Harry Potter", "J.K.Rowling");
	assert(testService.getAll_cos().size() == 2);
}

void test_golire_cos_service()
{
	vector<Carte>cos_carti;
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte_in_cos("Misterul din Caraibe", "Agatha Christie");
	testService.adaugare_carte_in_cos("Harry Potter", "J.K.Rowling");
	assert(testService.getAll_cos().size() == 2);
	testService.golire_cos();
	assert(testService.getAll_cos().size() == 0);
}



void test_generare_cos_service()
{
	vector<Carte>cos_carti;
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);
	testService.genereaza_cos(3);
	assert(testService.get_marime_cos() == 3);
}


void test_get_marime_cos()
{
	vector<Carte>cos_carti;
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);
	testService.adaugare_carte_in_cos("Misterul din Caraibe", "Agatha Christie");
	testService.adaugare_carte_in_cos("Harry Potter", "J.K.Rowling");
	testService.adaugare_carte_in_cos("Gandeste-te la un numar", "John Verdon");
	assert(testService.get_marime_cos() == 3);
}

void test_undo()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);
	assert(testService.getAll().size() == 3);

	testService.stergere_carte("Misterul din Caraibe", "Agatha Christie");
	assert(testService.getAll().size() == 2);
	testService.undo();
	assert(testService.getAll().size() == 3);

	testService.undo();
	assert(testService.getAll().size() == 2);

	Carte carte1 = testService.cautare_carte("Harry Potter", "J.K.Rowling");
	assert(carte1.getGen() == "SF");
	testService.actualizare_carte("Harry Potter", "J.K.Rowling", "fantasy", 1993);
	Carte carte2 = testService.cautare_carte("Harry Potter", "J.K.Rowling");
	assert(carte2.getGen() == "fantasy");
	testService.undo();
	Carte carte3 = testService.cautare_carte("Harry Potter", "J.K.Rowling");
	assert(carte3.getGen() == "SF");
	testService.undo();
	testService.undo();

	assert(testService.undo() == 1);

}

void test_cerinta_noua()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);

	map<string, DTO> dict = testService.cerinta_noua();

	string gen;
	int cnt = 0;
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		gen = it->second.get_gen();
		cnt = it->second.get_cnt();
	}
	assert(cnt == 2);
	assert(gen == "politist");
}

void test_validare_fisier()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	try
	{
		testService.export_cos("csv");
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Numele fisierului trebuie sa aiba cel putin 4 caractere.\n");
	}
	try
	{
		testService.export_cos("cos.txt");
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Numele fisierului nu are extensia csv sau html.\n\n");
	}
}

void test_export_cos_csv()
{
	RepoCarti testR;
	CosCarti cos;
	ValidatorCarte testV;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);

	vector <Carte> carti;
	Carte carte1{ "Misterul din Caraibe", "Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter", "J.K.Rowling", "SF", 1998 };
	Carte carte3{ "Gandeste-te la un numar", "John Verdon", "politist", 2016 };
	carti.push_back(carte1);
	carti.push_back(carte2);
	carti.push_back(carte3);

	cos.adaugare_carte_in_cos(carte1);
	cos.adaugare_carte_in_cos(carte2);
	cos.adaugare_carte_in_cos(carte3);

	string nume_fisier = "test.csv";
	testService.export_cos(nume_fisier);
	std::ifstream in(nume_fisier);
	string linie, delimitator = "|";
	size_t pozitie, numar_linie = 0;
	vector <string> cuvinte;
	getline(in, linie);
	while (getline(in, linie))
	{
		cuvinte.erase(cuvinte.begin(), cuvinte.end());
		while ((pozitie = linie.find(delimitator)) != linie.npos)
		{
			string cuvant = linie.substr(0, pozitie);
			cuvinte.push_back(cuvant);
			linie.erase(linie.begin(), linie.begin() + pozitie + delimitator.length());
		}
		cuvinte.push_back(linie);
		assert(cuvinte[0] == carti[numar_linie].getTitlu());
		assert(cuvinte[1] == carti[numar_linie].getAutor());
		assert(cuvinte[2] == carti[numar_linie].getGen());
		numar_linie++;
	}
	in.close();
	remove("test.csv");
}

void test_export_cos_html()
{
	RepoCarti testR;
	ValidatorCarte testV;
	CosCarti cos;
	StocareCarti testService{ testR,cos,testV };
	testService.adaugare_carte("Misterul din Caraibe", "Agatha Christie", "politist", 1967);
	testService.adaugare_carte("Harry Potter", "J.K.Rowling", "SF", 1998);
	testService.adaugare_carte("Gandeste-te la un numar", "John Verdon", "politist", 2016);

	vector <Carte> carti;
	Carte carte1{ "Misterul din Caraibe", "Agatha Christie", "politist", 1967 };
	Carte carte2{ "Harry Potter", "J.K.Rowling", "SF", 1998 };
	Carte carte3{ "Gandeste-te la un numar", "John Verdon", "politist", 2016 };
	carti.push_back(carte1);
	carti.push_back(carte2);
	carti.push_back(carte3);

	testService.adaugare_carte_in_cos("Misterul din Caraibe", "Agatha Christie");
	testService.adaugare_carte_in_cos("Harry Potter", "J.K.Rowling");
	testService.adaugare_carte_in_cos("Gandeste-te la un numar", "John Verdon");

	string nume_fisier = "test.html";
	testService.export_cos(nume_fisier);
	std::ifstream in(nume_fisier);
	string linie, delimitator = "|";
	size_t pozitie, numar_linie = 0;
	vector <string> cuvinte;
	getline(in, linie);
	while (getline(in, linie))
	{
		cuvinte.erase(cuvinte.begin(), cuvinte.end());
		while ((pozitie = linie.find(delimitator)) != linie.npos)
		{
			string cuvant = linie.substr(0, pozitie);
			cuvinte.push_back(cuvant);
			linie.erase(linie.begin(), linie.begin() + pozitie + delimitator.length());
		}
		cuvinte.push_back(linie);
		assert(cuvinte[0] == carti[numar_linie].getTitlu());
		assert(cuvinte[1] == carti[numar_linie].getAutor());
		assert(cuvinte[2] == carti[numar_linie].getGen());
		numar_linie++;
	}
	in.close();
	remove("test.html");
}