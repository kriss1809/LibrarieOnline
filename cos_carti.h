#pragma once
#include "carte.h"
#include "observer.h"
#include <vector>
#include <algorithm>
#include <random> 
#include <chrono>   

class CosCarti : public Observable
{
private:
	vector <Carte> cos_carti;
public:
	CosCarti() = default;

	friend class RepoCarti;

	/*
	* Returneaza o lista cu toate cartile din cos
	*/
	vector<Carte>& getAll_cos() noexcept;

	/*
		Adauga in cos cartea din lista data
		@throws: ExceptieRepo daca nu exista cartea
	*/
	void adaugare_carte_in_cos(const Carte& carte);


	/*
	* Sterge toate cartile din cos
	*/
	void golire_cos() noexcept;

	void export_cos(string nume_fisier);
};

