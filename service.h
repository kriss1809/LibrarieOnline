#pragma once 
#include "repo.h"
#include "validator.h"
#include <functional>
#include "DTO.h"
#include <map>
#include "undo.h"

using namespace std;
using std::unique_ptr;

class StocareCarti
{
private:
	//RepoCarti& repo;
	RepoCarti& repo;
	CosCarti& cos_carti;
	ValidatorCarte& validator;

	vector <unique_ptr<ActiuneUndo>> undoActions;
	vector<Carte> filtrare(function<bool(const Carte&)> functie);

public:
	StocareCarti(RepoCarti& repoCarte, CosCarti& cos, ValidatorCarte& val) noexcept :repo{ repoCarte }, cos_carti{ cos }, validator{ val } {};

	//constructor de copiere
	StocareCarti(const StocareCarti& ot) = delete;

	/*
	Adauga o carte cu titlul-titlu, genul-gen, autorul-autor si anul_aparitiei-an
	*@param titlu: titlul cartii care se adauga(string)
	*@param autor:autorul cartii care se adauga (string)
	*@param gen: genul cartii are se adauga(string)
	*@param an: anul aparitiei pentru cartea care se adauga(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca mai exista o alta carte cu acelasi titlu si autor
	*ValidationException daca cartea introdusa nu este valida
	*/
	void adaugare_carte(string titlu, string autor, string gen, int an);


	/*
	Actualizeaza o carte cu titlul-titlu, genul-gen, autorul-autor si anul_aparitiei-an
	*@param titlu: titlul cartii care se actualizeaza(string)
	*@param autor: autorul cartii care se actualizeaza(string)
	*@param gen: genul nou al cartii care se actualizeaza(string)
	*@param an: anul nou al aparitiei cartii care se actualizeaza(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista cartea
	*ValidationException daca cartea introdusa nu este valida
	*/
	void actualizare_carte(string titlu, string autor, string gen, int an);


	/*
	Sterge o carte cu titlul-titlu si autorul-autor
	*@param titlu: titlul cartii care se sterge(string)
	*@param autor: autorul cartii care se sterge(string)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista cartea
	*/
	void stergere_carte(string titlu, string autor);



	/*
	Cauta o carte cu titlul-titlu si autorul-autor
	*@param titlu: titlul cartii care se cauta(string)
	*@param autor: autorul cartii care se cauta(string)
	* return: cartea cautata (daca ea exista)
	*
	* * @throws:
	*ExceptieRepozitoriu daca nu exista cartea
	*/
	const Carte& cautare_carte(string titlu, string autor);

	/*
	return: lista de carti
	*/
	vector <Carte> getAll() noexcept
	{
		return this->repo.getAll();
	}

	/*
	Filtreaza cartile dupa titlu dat
	@param titlu: titlul dupa care se filtreaza (string)
	return: lista cartilor cu titlul dat(Dynamic Vector)
	*/
	vector<Carte> filtrare_titlu(string titlu);

	/*
	Filtreaza cartile dupa an dat
	@param an: anul dupa care se filtreaza (int)
	return: lista cartilor cu aparute in anul dat(Dynamic Vector)
	*/
	vector<Carte> filtrare_an(int an);

	/*
	* Sorteaza o lista dupa un criteriu dat
	*/
	vector<Carte> sortareGenerala(bool(*maiMicF)(const Carte&, const Carte&));

	/*
	* Sorteaza lista de carti dupa titlu
	*/
	vector<Carte> sortare_titlu();

	/*
	* Sorteaza lista de carti dupa autor
	*/
	vector<Carte> sortare_autor();

	/*
	* Sorteaza lista de carti dupa an, apoi gen
	*/
	vector< Carte> sortare_an_gen();

	/*
	Returneaza filmele care se afla in cos
	*@param: -
	*@throws:-
	*ExceptieRepozitoriu daca cosul e gol
	*/
	vector<Carte>& getAll_cos() noexcept
	{
		return this->cos_carti.getAll_cos();
	}


	CosCarti& get_cos() {
		return this->cos_carti;
	}

	/*
	* Returneaza numarul de carti din cos
	*/
	size_t get_marime_cos() noexcept;

	void adaugare_carte_in_cos(string titlu, string autor);

	/*
		Genereaza un numar de nr carti din lista
		@param nr: numarul de carti de generat
		@return: se adauga nr carti in cos
	*/
	void genereaza_cos(int nr);

	void golire_cos() noexcept;

	map<string, DTO> cerinta_noua();

	void export_cos(string nume_fisier);

	bool undo();

};
