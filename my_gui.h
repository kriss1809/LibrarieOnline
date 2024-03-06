#pragma once
#include <QtWidgets/QApplication>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QListWidget>
#include <QRadioButton>
#include "service.h"
#include <vector>
#include <algorithm>
#include <set>
#include "cos_carti.h"
#include "cos_carti_crud.h"
#include "cos_carti_ReadOnly.h"
#include "MyTable.h"

using namespace std;

class MyGUI : public QWidget 
{
	private:
		StocareCarti& srv;

		QLabel* lbl_titlu = new QLabel{ "Titlul cartii: " };
		QLabel* lbl_autor = new QLabel{ "Autorul cartii: " };
		QLabel* lbl_gen = new QLabel{"Genul cartii: "};
		QLabel* lbl_an = new QLabel{ "Anul publicarii: " };
		QLabel* lbl_nr = new QLabel{ "Numarul de carti de adaugat in cos: " };
		QLabel* lbl_nume_fisier = new QLabel{"Numele fisierului pentru export: "};
		QLabel* op_lista = new QLabel{ "\nOPERATII CU LISTA DE CARTI\n" };
		QLabel* op_cos = new QLabel{ "\nOPERATII CU COSUL DE CARTI\n" };
		QLabel* tabel1 = new QLabel{ "LISTA DE CARTI" };
		QLabel* tabel2 = new QLabel{ "COSUL CU CARTI" };
		QLabel* formular = new QLabel{ "FORMULAR\n" };

		QLineEdit* editare_titlu;
		QLineEdit* editare_autor;
		QLineEdit* editare_gen;
		QLineEdit* editare_an;
		QLineEdit* editare_nr;
		QLineEdit* editare_nume_fisier;

		QPushButton* btn_adaugare;
		QPushButton* btn_actualizare;
		QPushButton* btn_stergere;
		QPushButton* btn_cautare;
		QPushButton* btn_filtrare_titlu;
		QPushButton* btn_filtrare_an;
		QPushButton* btn_undo;
		QPushButton* btn_cnt_genuri;

		QGroupBox* groupBoxSortare = new QGroupBox(tr("Tip sortare"));
		QRadioButton* radio_sortare_titlu = new QRadioButton(QString::fromStdString("Titlu"));
		QRadioButton* radio_sortare_autor = new QRadioButton(QString::fromStdString("Autor"));
		QRadioButton* radio_sortare_an_gen = new QRadioButton(QString::fromStdString("Anul aparitiei+Gen"));
		QPushButton* btn_sortare;

		// ----------------------- cos ----------------------- //
		QPushButton* btn_adaugare_cos;
		QPushButton* btn_golire_cos;
		QPushButton* btn_generare_cos;
		QPushButton* btn_export_cos;
		QLabel* lblTitluCos = new QLabel{ "Titlul cartii: " };
		QLabel* lblAutorCos = new QLabel{ "Autorul cartii: " };
		QLabel* lblNumarCos = new QLabel{ "Numarul de carti de adaugat: " };
		QLabel* lblFisierCos = new QLabel{ "Numele fisierului pentru export:" };

		QTableWidget* tabel_carti = new QTableWidget;
		QTableWidget* tabel_cos = new QTableWidget;
		QListWidget* lista_cos = new QListWidget;

		QWidget* Report = new QWidget;
		QVBoxLayout* typesLayout = new QVBoxLayout{};
		//QPushButton* reloadTypes = new QPushButton{ "Reincarcare genuri." };

		QPushButton* buton_cos_obisnuit;
		QPushButton* buton_cos_desenat;

		//Model, QTableView
		MyTableModel* model;
		QTableView* tabelView = new QTableView;

		void initializeGUIComponents();
		void conectare_butoane();
		void preluare_date_din_fisier(vector<Carte> carti);
		void incarcare_cos(vector <Carte> cos_carti);

	public:
		MyGUI(StocareCarti& Srv) : srv{ Srv } 
		{
			initializeGUIComponents();
			model = new MyTableModel{ srv.getAll() };
			tabelView->setModel(model);
			conectare_butoane();
			incarcare_cos(srv.getAll_cos());
			preluare_date_din_fisier(srv.getAll());
		}
		void gui_adaugare();
		void gui_actualizare();
		void gui_stergere();
		void gui_cautare();
		void gui_filtrare_titlu();
		void gui_filtrare_an();
		void gui_sortare();
		void gui_undo();
		void gui_cnt_genuri();
		void gui_adaugare_cos();
		void gui_generare_cos();
		void gui_golire_cos();
		void gui_export_cos();
		void gui_raport_genuri();
		void clearLayout(QLayout* layout);
};