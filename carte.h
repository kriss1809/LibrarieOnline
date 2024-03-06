#pragma once
#include <string>
#include <iostream>

using namespace std;

class Carte
{
private:
	string titlu;
	string autor;
	string gen;
	int an;

public:
	Carte() = default;
	Carte(const string t, string a, string g, int an) :titlu{ t }, autor{ a }, gen{ g }, an{ an } {}
	Carte(const Carte& ot) :titlu{ ot.titlu }, autor{ ot.autor }, gen{ ot.gen }, an{ ot.an }
	{
		//cout << "\nConstructorul de copiere a fost apelat.\n";
	}

	string getTitlu() const;
	string getAutor() const;
	string getGen() const;
	int getAn() const noexcept;

	void setTitlu(string titluNou);
	void setAutor(string autorNou);
	void setGen(string genNou);
	void setAn(int anNou) noexcept;
};

/*
Compara dupa an si gen
returneaza true daca c1.an e mai mic decat c2.an sau c1.an=c2.an si c1.gen < c2.gen
*/
bool cmpAnGen(const Carte& c1, const Carte& c2);

/*
Compara dupa titlu
returneaza true daca c1.titlu e mai mic decat c2.titlu
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
Compara dupa autor
returneaza true daca c1.autor e mai mic decat c2.autor
*/
bool cmpAutor(const Carte& c1, const Carte& c2);