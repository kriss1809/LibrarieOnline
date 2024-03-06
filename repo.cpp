#pragma once
#include "repo.h"
#include <vector>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iostream>

vector <Carte> RepoCarti::getAll()
{
	return this->carti;
}


bool RepoCarti::exista(const Carte& carte)
{
	try
	{
		gaseste_carte(carte.getTitlu(), carte.getAutor());
		return true;
	}
	catch (ExceptieRepo)
	{
		return false;
	}
}

const Carte& RepoCarti::gaseste_carte(string titlu, string autor)
{
	auto iterator = std::find_if(this->carti.begin(), this->carti.end(), [titlu, autor](Carte carte)
		{
			if (carte.getTitlu() == titlu && carte.getAutor() == autor)
			return true;
	return false;
		});
	if (iterator == this->carti.end())
		throw ExceptieRepo("Cartea cu titlul si autorul introdus nu exista in lista!\n");
	return *iterator;
}

void RepoCarti::adaugare(const Carte& carte)
{
	if (exista(carte))
	{
		throw ExceptieRepo("Cartea cu titlul si autorul introdus exista deja in lista!\n");
	}
	this->carti.push_back(carte);
}


void RepoCarti::actualizare(const Carte& carte)
{
	if (exista(carte))
	{
		int i = 0;
		for (i = 0; i < this->carti.size(); i++)
			if (carti[i].getTitlu() == carte.getTitlu() && carti[i].getAutor() == carte.getAutor())
			{
				carti[i] = carte;
				break;
			}
	}
	else
		throw ExceptieRepo("Cartea cu titlul si autorul introdus nu exista in lista!\n");
}


void RepoCarti::stergere(string titlu, string autor)
{
	auto iterator = std::remove_if(this->carti.begin(), this->carti.end(), [titlu, autor](Carte carte) {
		if (carte.getTitlu() == titlu && carte.getAutor() == autor)
		return true;
	return false;
		});
	if (iterator == this->carti.end())
		throw ExceptieRepo("Cartea cu titlul si autorul introdus nu exista in lista!\n");
	this->carti.erase(iterator, this->carti.end());
}
//////////////////////////////////////////


void RepoFile::loadFromFile() {
	ifstream fisier_carti(this->filename);
	if (!fisier_carti.is_open()) {
		throw ExceptieRepo("Nu se poate citi din fisierul " + filename);
	}
	string line;
	while (getline(fisier_carti, line))
	{
		string titlu, autor, gen;
		int an = 0;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;

		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) autor = current_item;
			if (item_no == 2) gen = current_item;
			if (item_no == 3) an = stoi(current_item);
			item_no++;
		}
		Carte c{ titlu, autor, gen, an };

		RepoCarti::adaugare(c);
	}
	fisier_carti.close();
}

void RepoFile::saveToFile() {
	ofstream fisier(this->filename);
	if (!fisier.is_open())
		throw ExceptieRepo("Cannot write to file " + filename);
	for (auto& c : getAll()) {
		fisier << c.getTitlu() << "," << c.getAutor() << "," << c.getGen() << "," << c.getAn() << endl;
	}
	fisier.close();
}

void RepoFile::adaugare(const Carte& c) {

	RepoCarti::adaugare(c);
	saveToFile();

}

void RepoFile::stergere(string titlu, string autor) {

	RepoCarti::stergere(titlu, autor);
	saveToFile();
}

void RepoFile::actualizare(const Carte& carte)
{
	RepoCarti::actualizare(carte);
	saveToFile();
}

void RepoFile::sterge_undo(string titlu, string autor)
{
	RepoCarti::sterge_undo(titlu, autor);
	saveToFile();
}
void RepoFile::actualizeaza_undo(const Carte& carte)
{
	RepoCarti::actualizeaza_undo(carte);
	saveToFile();
}
void RepoFile::adauga_undo(const Carte& carte)
{
	RepoCarti::adauga_undo(carte);
	saveToFile();
}

//////////////////////////////////////////

vector <Carte>& CosCarti::getAll_cos() noexcept
{
	return this->cos_carti;
}
void CosCarti::adaugare_carte_in_cos(const Carte& carte)
{
	this->cos_carti.push_back(carte);
}

void CosCarti::golire_cos() noexcept
{
	this->cos_carti.clear();
}

void CosCarti::export_cos(string nume_fisier)
{
	std::ofstream fout(nume_fisier);
	fout << "Titlu | Autor | Gen | Anul aparitiei \n";
	for (auto carte : this->cos_carti)
		fout << carte.getTitlu() << "|" << carte.getAutor() << "|" << carte.getGen() << "|" << carte.getAn() << "\n";
	fout.close();
}