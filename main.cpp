#pragma once
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "Carte.h"
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include "teste.h"
#include "my_gui.h"

using namespace std;


int main(int argc, char *argv[])
{
	testAll();
	QApplication a(argc, argv);

	string filename = "carti.txt";
	RepoFile repo{ filename };
	ValidatorCarte val;
	CosCarti cos;
	StocareCarti service{ repo,cos, val };
	MyGUI gui{ service };
	//gui.show();

    return a.exec();
}