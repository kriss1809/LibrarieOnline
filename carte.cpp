#pragma once
#include "carte.h"

string Carte::getTitlu() const {
	return this->titlu;
}

string Carte::getAutor() const {
	return this->autor;
}

string Carte::getGen() const {
	return this->gen;
}

int Carte::getAn() const noexcept {
	return this->an;
}


void Carte::setTitlu(string titluNou)
{
	this->titlu = titluNou;
}

void Carte::setGen(string genNou)
{
	this->gen = genNou;
}

void Carte::setAutor(string autorNou)
{
	this->autor = autorNou;
}

void Carte::setAn(int anNou) noexcept
{
	this->an = anNou;
}

bool cmpAnGen(const Carte& c1, const Carte& c2)
{
	if (c1.getAn() < c2.getAn())
		return true;
	if (c1.getAn() == c2.getAn() && c1.getGen() <= c2.getGen())
		return true;
	return false;
}

bool cmpTitlu(const Carte& c1, const Carte& c2)
{
	return c1.getTitlu() < c2.getTitlu();
}

bool cmpAutor(const Carte& c1, const Carte& c2)
{
	return c1.getAutor() < c2.getAutor();
}