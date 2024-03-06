#pragma once 
#include "service.h"
#include <vector>
#include "carte.h"
#include <functional>
#include <random>
#include <algorithm>
#include <chrono>
#include "undo.h"

using namespace std;

void StocareCarti::adaugare_carte(string titlu, string autor, string gen, int an)
{
	Carte carte{ titlu, autor, gen, an };
	validator.validare(carte);
	repo.adaugare(carte);
	undoActions.push_back(make_unique<UndoAdauga>(repo, carte));
}


void StocareCarti::actualizare_carte(string titlu, string autor, string gen, int an)
{
	Carte carte1 = repo.gaseste_carte(titlu, autor);
	Carte carte2{ titlu, autor, gen, an };
	validator.validare(carte2);
	repo.actualizare(carte2);
	undoActions.push_back(make_unique<UndoActualizeaza>(repo, carte1));
}

void StocareCarti::stergere_carte(string titlu, string autor)
{
	Carte carte = repo.gaseste_carte(titlu, autor);
	repo.stergere(carte.getTitlu(), carte.getAutor());
	undoActions.push_back(make_unique<UndoSterge>(repo, carte));
}

const Carte& StocareCarti::cautare_carte(string titlu, string autor)
{
	return repo.gaseste_carte(titlu, autor);
}


vector<Carte> StocareCarti::filtrare(function <bool(const Carte&)> functie)
{
	vector<Carte> v{ repo.getAll() };
	vector<Carte> carti_filtrate;
	for (auto i : v)
	{
		if (functie(i))
			carti_filtrate.push_back(i);
	}
	return carti_filtrate;
}

vector<Carte> StocareCarti::filtrare_titlu(string titlu)
{
	return filtrare([titlu](const Carte& carte)
		{
			return carte.getTitlu() == titlu;
		});
}


vector<Carte> StocareCarti::filtrare_an(int an)
{
	return filtrare([an](const Carte& carte) noexcept
		{
			return carte.getAn() == an;
		});
}


vector<Carte> StocareCarti::sortareGenerala(bool(*maiMicF)(const Carte&, const Carte&))
{
	vector<Carte> v{ repo.getAll() };
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			if (!maiMicF(v[i], v[j]))
			{
				Carte aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}


vector<Carte> StocareCarti::sortare_titlu()
{
	return sortareGenerala(cmpTitlu);
}

vector<Carte> StocareCarti::sortare_autor()
{
	return sortareGenerala(cmpAutor);
}


vector<Carte> StocareCarti::sortare_an_gen()
{
	return sortareGenerala(cmpAnGen);
}

size_t StocareCarti::get_marime_cos() noexcept
{
	size_t numar = 0;
	numar = cos_carti.getAll_cos().size();
	return numar;
}

void StocareCarti::adaugare_carte_in_cos(string titlu, string autor)
{
	const auto& c = repo.gaseste_carte(titlu, autor);
	cos_carti.adaugare_carte_in_cos(c);
}

void StocareCarti::genereaza_cos(int nr)
{
	vector<Carte> carti = getAll();
	vector<Carte> copie(carti.size());
	int numar_random;
	copy(carti.begin(), carti.end(), copie.begin());
	for (int i = 0; i < nr; i++)
	{
		//facem o copie a vectorului de produse si o amestecam de nr ori
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(copie.begin(), copie.end(), default_random_engine(int(seed))); //amesteca vectorul
		// generam o pozitie random cuprinsa intre 0 si lungimea copiei - 1
		mt19937 mt{ std::random_device{}() };
		uniform_int_distribution<> dist(0, int(copie.size() - 1));
		numar_random = dist(mt);
		//adaugam in cos o carte cu indice random
		adaugare_carte_in_cos(copie[numar_random].getTitlu(), copie[numar_random].getAutor());
	}
}

void StocareCarti::golire_cos() noexcept
{
	cos_carti.golire_cos();
}

map<string, DTO> StocareCarti::cerinta_noua()
{
	vector<Carte> lista = getAll();
	map<string, DTO> dict;
	for (auto c : lista)
	{
		string gen_curent = c.getGen();
		if (dict.find(gen_curent) == dict.end())
		{
			DTO nou{ gen_curent, 1 };
			dict[gen_curent] = nou;
		}
		else
		{
			dict[gen_curent].increment_cnt();
		}
	}
	return dict;
}

void StocareCarti::export_cos(string nume_fisier)
{
	int validare = 0;
	validare = ValidatorFisier::valideaza(nume_fisier);
	if (validare == 1)
		cos_carti.export_cos(nume_fisier);
}

bool StocareCarti::undo()
{
	if (undoActions.empty() == true)
		return 1;
	else
	{
		undoActions.back()->doUndo();
		undoActions.pop_back();
		return 0;
	}
}
