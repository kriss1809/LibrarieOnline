#pragma once 
#include "service.h"
#include "teste.h"

class consola
{
private:
	StocareCarti& service;

public:
	consola(StocareCarti& service) noexcept :service{ service } {};
	consola(const consola& ot) = delete;

	void Meniu();
	void run();
	void afisare_carti();

	void adaugare_ui();

	void modificare_ui();

	void stergere_ui();

	void cautare_ui();

	void filtrare_ui();

	void sortare_ui();

	void afisare_cos();

	void adaugare_in_cos_ui();

	void generare_cos_ui();

	void golire_cos_ui();

	void cerinta_noua();

	void export_cos_ui();

	void undo_ui();
};