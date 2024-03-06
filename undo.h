#pragma once
#include "carte.h"
#include "repo.h"


class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};



class UndoAdauga :public ActiuneUndo {
	Carte carteAdaugata;
	RepoCarti& repo;
public:
	UndoAdauga(RepoCarti& repo, const Carte& f) :repo{ repo }, carteAdaugata{ f } {}
	void doUndo() override {
		repo.sterge_undo(carteAdaugata.getTitlu(), carteAdaugata.getAutor());
	}
};



class UndoActualizeaza :public ActiuneUndo {
	Carte carteActualizata;
	RepoCarti& repo;
public:
	UndoActualizeaza(RepoCarti& repo, const Carte& f) :repo{ repo }, carteActualizata{ f } {}
	void doUndo() override {
		repo.actualizeaza_undo(carteActualizata);
	}
};



class UndoSterge :public ActiuneUndo {
	Carte carteStearsa;
	RepoCarti& repo;
public:
	UndoSterge(RepoCarti& repo, const Carte& f) :repo{ repo }, carteStearsa{ f } {}
	void doUndo() override {
		repo.adauga_undo(carteStearsa);
	}
};