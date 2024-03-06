#pragma once
#include "carte.h"
#include <vector>
#include "cos_carti.h"

using namespace std;

//Clasa de exceptii specifice Repo-ului
class ExceptieRepo
{
private:
	string mesajEroare;
public:
	ExceptieRepo(string mesajEroare) : mesajEroare{ mesajEroare } {};
	string getMesajeEroare()
	{
		return this->mesajEroare;
	}
};

class RepoCarti
{
private:
	vector <Carte> carti;
public:

	RepoCarti() = default;
	//constructorul de copiere
	RepoCarti(const RepoCarti& ot) = delete;

	/*
	Adauga o carte in lista
	@param carte: cartea care se adauga(Carte)
	@return -
	post: cartea va fi adaugata in lista
	@throws: ExceptieRepo daca o o carte cu acelasi titlu si acelasi autor exista deja
	*/
	virtual void adaugare(const Carte& carte);



	/*
	Actualizeaza o carte din lista
	@param carte: cartea care se actualizeaza(Carte)
	@return -
	post: cartea din lista va fi actualizat
	@throws: ExceptieRepo daca nu exista o carte cu acelasi titlu si acelasi an de aparitie
	*/
	virtual void actualizare(const Carte& carte);



	/*
	Sterge o carte din lista
	@param carte: cartea care se sterge(Carte)
	@return -
	post: cartea din lista va fi sters
	@throws: ExceptieRepo daca nu exista o carte cu acelasi titlu si acelasi an de aparitie
	*/
	virtual void stergere(string titlu, string autor);


	/*
	Returneaza o lista cu toate cartile
	@return: lista cu cartile (vector de obiecte Carte)
	*/
	vector <Carte> getAll();


	/*
	Cauta o carte cu titlul si autorul dat

	@param titlu: titlul dupa care se cauta
	@param autor: autorul dupa care se cauta
	@return: entitatea Carte cu titlul si autorul (daca aceasta exista)
	@throws: ExceptieRepo daca nu exista cartea cu titlul si autorul dat
	*/
	const Carte& gaseste_carte(string titlu, string autor);


	/*
	Verifica daca o carte data exista in lista

	@param carte: cartea care se cauta in lista
	@return: true daca cartea exista, false altfel
	*/
	bool exista(const Carte& carte);


	virtual void sterge_undo(string titlu, string autor)
	{
		auto iterator = remove_if(carti.begin(), carti.end(), [titlu, autor](Carte carte)
			{
				if (carte.getTitlu() == titlu && carte.getAutor() == autor)
				return true;
		return false;
			});
		carti.erase(iterator, carti.end());
	}

	virtual void actualizeaza_undo(const Carte& carte)
	{
		if (exista(carte))
			for (auto& c : carti)
				if (c.getTitlu() == carte.getTitlu() && c.getAutor() == carte.getAutor())
				{
					c = carte;
					break;
				}
	}


	virtual void adauga_undo(const Carte& carte) {
		if (!exista(carte))
			this->carti.push_back(carte);
	}

};


class RepoFile : public RepoCarti {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: titlu,autor,gen,an\n
	*/
	void saveToFile();
public:
	RepoFile(string fname) :RepoCarti(), filename{ fname } {
		loadFromFile();
	};
	void adaugare(const Carte& c) override;
	void stergere(string titlu, string autor)override;
	void actualizare(const Carte& carte)override;
	void sterge_undo(string titlu, string autor) override;
	void actualizeaza_undo(const Carte& carte)override;
	void adauga_undo(const Carte& carte) override;
};

