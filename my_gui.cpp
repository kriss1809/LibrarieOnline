#include "my_gui.h"

void MyGUI::initializeGUIComponents() {
	// main layout

	QWidget* fereastra_lista = new QWidget;

	QHBoxLayout* lyMain = new QHBoxLayout;
	fereastra_lista->setLayout(lyMain);

	// layout parte dreapta
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	// formular pt adaugare
	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);

	btn_adaugare = new QPushButton("Adaugare carte");
	btn_actualizare = new QPushButton("Actualizare carte");
	btn_stergere = new QPushButton("Stergere carte");
	btn_cautare = new QPushButton("Cautare carte");
	btn_filtrare_titlu = new QPushButton("Filtrare carti dupa titlu");
	btn_filtrare_an = new QPushButton("Filtrare carti dupa an");
	btn_undo = new QPushButton("Undo");

	QVBoxLayout* lyRadioBoxSortare = new QVBoxLayout;
	this->groupBoxSortare->setLayout(lyRadioBoxSortare);
	lyRadioBoxSortare->addWidget(radio_sortare_titlu);
	lyRadioBoxSortare->addWidget(radio_sortare_autor);
	lyRadioBoxSortare->addWidget(radio_sortare_an_gen);
	btn_sortare = new QPushButton("Sortare");
	lyRadioBoxSortare->addWidget(btn_sortare);

	Report->setLayout(typesLayout);

	ly_form->addRow(op_lista);
	ly_form->addRow(btn_adaugare);
	ly_form->addRow(btn_actualizare);
	ly_form->addRow(btn_stergere);
	ly_form->addRow(btn_cautare);
	ly_form->addRow(btn_filtrare_titlu);
	ly_form->addRow(btn_filtrare_an);
	ly_form->addRow(groupBoxSortare);
	ly_form->addRow(btn_undo);

	lyRight->addWidget(form);
	lyRight->addWidget(Report);
	
	// layout parte stanga
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	// tabel cu carti
	//int nr_linii = 10;
	//int nr_coloane = 4;
	//tabel_carti = new QTableWidget{ nr_linii, nr_coloane };

	//QStringList HeaderTabel;
	//HeaderTabel<< "Titlu" << "Autor" << "Gen" << "An publicare";
	//tabel_carti->setHorizontalHeaderLabels(HeaderTabel);
	//tabel_carti->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyLeft->addWidget(tabel1);
	lyLeft->addWidget(tabelView);


	/// adaugare left si right pe lyMain
	lyMain->addWidget(left);
	lyMain->addWidget(right);

	fereastra_lista->show();

	///////////////////////////////////////////////////////////////

	QWidget* fereastra_cos = new QWidget;
	
	QHBoxLayout* lyMain2 = new QHBoxLayout;
	fereastra_cos->setLayout(lyMain2);

	// layout parte dreapta
	QWidget* right2 = new QWidget;
	QVBoxLayout* lyRight2 = new QVBoxLayout;
	right2->setLayout(lyRight2);

	// formular pt adaugare
	QWidget* form2 = new QWidget;
	QFormLayout* ly_form2 = new QFormLayout;
	form2->setLayout(ly_form2);
	editare_titlu = new QLineEdit;
	editare_autor = new QLineEdit;
	editare_gen = new QLineEdit;
	editare_an = new QLineEdit;
	editare_nr = new QLineEdit;
	editare_nume_fisier = new QLineEdit;

	ly_form2->addRow(formular);
	ly_form2->addRow(lbl_titlu, editare_titlu);
	ly_form2->addRow(lbl_autor, editare_autor);
	ly_form2->addRow(lbl_gen, editare_gen);
	ly_form2->addRow(lbl_an, editare_an);
	ly_form2->addRow(lbl_nr, editare_nr);
	ly_form2->addRow(lbl_nume_fisier, editare_nume_fisier);

	btn_adaugare_cos = new QPushButton("Adaugare carte in cos");
	btn_golire_cos = new QPushButton("Golire cos");
	btn_generare_cos = new QPushButton("Generare cos");
	btn_export_cos = new QPushButton("Export cos");
	btn_cnt_genuri = new QPushButton("Inventar genuri");
	buton_cos_obisnuit = new QPushButton("Afisare cos CRUD");
	buton_cos_desenat = new QPushButton("Afisare cos READ ONLY");

	ly_form2->addRow(op_cos);
	ly_form2->addRow(btn_adaugare_cos);
	ly_form2->addRow(btn_generare_cos);
	ly_form2->addRow(btn_golire_cos);
	ly_form2->addRow(btn_export_cos);
	ly_form2->addRow(buton_cos_obisnuit);
	ly_form2->addRow(buton_cos_desenat);

	lyRight2->addWidget(form2);

	// layout parte stanga
	QWidget* left2 = new QWidget;
	QVBoxLayout* lyLeft2 = new QVBoxLayout;
	left2->setLayout(lyLeft2);

	lyLeft2->addWidget(tabel2);
	lyLeft2->addWidget(lista_cos);

	/// adaugare left si right pe lyMain
	lyMain2->addWidget(left2);
	lyMain2->addWidget(right2);

	fereastra_cos->show();
}


void MyGUI::preluare_date_din_fisier(vector <Carte> carti)
{
	/*tabel_carti->clearContents();
	tabel_carti->setRowCount(carti.size());

	int linie = 0;
	for (auto& c : carti)
	{
		tabel_carti->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(c.getTitlu())));
		tabel_carti->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(c.getAutor())));
		tabel_carti->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(c.getGen())));
		tabel_carti->setItem(linie, 3, new QTableWidgetItem(QString::number(c.getAn())));
		linie++;
	}*/
	model->regenereaza_lista(carti);
	gui_raport_genuri();
}

void MyGUI::incarcare_cos(vector<Carte> cos_carti) {
	tabel_cos->clearContents();
	tabel_cos->setRowCount(cos_carti.size());
	int linie = 0;
	for (auto& c : cos_carti) 
	{
		tabel_cos->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(c.getTitlu())));
		tabel_cos->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(c.getAutor())));
		tabel_cos->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(c.getGen())));
		tabel_cos->setItem(linie, 3, new QTableWidgetItem(QString::number(c.getAn())));
		linie++;
	}

	lista_cos->clear();
	for (auto& c : cos_carti)
	{
		string carte = c.getTitlu() + " | " + c.getAutor() + " | " + c.getGen() + " | " + to_string(c.getAn());
		QListWidgetItem* it = new QListWidgetItem{ QString::fromStdString(carte) };
		lista_cos->addItem(it);
	}
}


void MyGUI::conectare_butoane() 
{
	QObject::connect(btn_adaugare, &QPushButton::clicked, this, &MyGUI::gui_adaugare);
	QObject::connect(btn_actualizare, &QPushButton::clicked, this, &MyGUI::gui_actualizare);
	QObject::connect(btn_stergere, &QPushButton::clicked, this, &MyGUI::gui_stergere);
	QObject::connect(btn_undo, &QPushButton::clicked, this, &MyGUI::gui_undo);
	QObject::connect(btn_cautare, &QPushButton::clicked, this, &MyGUI::gui_cautare);
	QObject::connect(btn_filtrare_titlu, &QPushButton::clicked, this, &MyGUI::gui_filtrare_titlu);
	QObject::connect(btn_filtrare_an, &QPushButton::clicked, this, &MyGUI::gui_filtrare_an);
	QObject::connect(btn_sortare, &QPushButton::clicked, [&]()
	{
		if (radio_sortare_titlu->isChecked())
			preluare_date_din_fisier(srv.sortare_titlu());
		if (radio_sortare_autor->isChecked())
			preluare_date_din_fisier(srv.sortare_autor());
		if (radio_sortare_an_gen->isChecked())
			preluare_date_din_fisier(srv.sortare_an_gen());
	});
	QObject::connect(btn_cnt_genuri, &QPushButton::clicked, this, &MyGUI::gui_cnt_genuri);
	QObject::connect(btn_adaugare_cos, &QPushButton::clicked, this, &MyGUI::gui_adaugare_cos);
	QObject::connect(btn_golire_cos, &QPushButton::clicked, this, &MyGUI::gui_golire_cos);
	QObject::connect(btn_generare_cos, &QPushButton::clicked, this, &MyGUI::gui_generare_cos);
	QObject::connect(btn_export_cos, &QPushButton::clicked, this, &MyGUI::gui_export_cos);

	// fereastra cos CRUD
	QObject::connect(buton_cos_obisnuit, &QPushButton::clicked, [this] {
		auto cos = new programCRUDGUI(srv.get_cos(), srv);
		cos->run();
		});

	// fereastra cos READ ONLY
	QObject::connect(buton_cos_desenat, &QPushButton::clicked, [this] {
		auto cos_carti = new programReadOnlyGUI(srv.get_cos());
		cos_carti->show();
		});
	
}

void MyGUI::gui_adaugare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string autor = editare_autor->text().toStdString();
		string gen = editare_gen->text().toStdString();
		int an = editare_an->text().toInt();

		editare_an->clear();
		editare_autor->clear();
		editare_gen->clear();
		editare_titlu->clear();

		srv.adaugare_carte(titlu, autor, gen, an);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Carte adaugata cu succes!"));

	}
	catch(ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_genuri();
}

void MyGUI::gui_actualizare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string autor = editare_autor->text().toStdString();
		string gen = editare_gen->text().toStdString();
		int an = editare_an->text().toInt();

		editare_an->clear();
		editare_autor->clear();
		editare_gen->clear();
		editare_titlu->clear();

		srv.actualizare_carte(titlu, autor, gen, an);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Carte actualizata cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_genuri();
}

void MyGUI::gui_stergere()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string autor = editare_autor->text().toStdString();
		
		editare_autor->clear();
		editare_titlu->clear();

		srv.stergere_carte(titlu, autor);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Carte stearsa cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_genuri();
}

void MyGUI::gui_cautare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string autor = editare_autor->text().toStdString();

		editare_autor->clear();
		editare_titlu->clear();

		Carte c = srv.cautare_carte(titlu, autor);
		string carte;
		carte = "Titlu:";
		carte.append(c.getTitlu());
		carte.append("; ");
		carte.append("Autor:");
		carte.append(c.getAutor());
		carte.append("; ");
		carte.append("Gen:");
		carte.append(c.getGen());
		carte.append("; ");
		carte.append("Anul aparitiei:");
		carte.append(std::to_string(c.getAn()));
		QMessageBox::information(this, "info", QString::fromStdString(carte));
	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_genuri();
}

void MyGUI::gui_filtrare_titlu()
{
	string carte;
	string titlu = editare_titlu->text().toStdString();
	editare_titlu->clear();
	QListWidget* lista_carti = new QListWidget;
	vector <Carte> filtrare_titlu = srv.filtrare_titlu(titlu);
	if(filtrare_titlu.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista nicio carte publicata in anul dat"), lista_carti);
	for (auto c : filtrare_titlu)
	{
		carte = "Titlu:";
		carte.append(c.getTitlu());
		carte.append("; ");
		carte.append("Autor:");
		carte.append(c.getAutor());
		carte.append("; ");
		carte.append("Gen:");
		carte.append(c.getGen());
		carte.append("; ");
		carte.append("Anul aparitiei:");
		carte.append(std::to_string(c.getAn()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(carte), lista_carti);
	}
	lista_carti->show();
}

void MyGUI::gui_filtrare_an()
{
	string carte;
	int an = editare_an->text().toInt();
	editare_an->clear();
	QListWidget* lista_carti = new QListWidget;
	vector <Carte> filtrare_an = srv.filtrare_an(an);
	if (filtrare_an.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista nicio carte cu titlul dat"), lista_carti);
	for (auto c : filtrare_an)
	{
		carte = "Titlu:";
		carte.append(c.getTitlu());
		carte.append("; ");
		carte.append("Autor:");
		carte.append(c.getAutor());
		carte.append("; ");
		carte.append("Gen:");
		carte.append(c.getGen());
		carte.append("; ");
		carte.append("Anul aparitiei:");
		carte.append(std::to_string(c.getAn()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(carte), lista_carti);
	}
	lista_carti->show();
}

void MyGUI::gui_undo()
{
	if (srv.undo() == 0)
	{
		preluare_date_din_fisier(srv.getAll());
		QMessageBox::information(this, "info", QString::fromStdString("Undo efectuat cu succes!"));
		
	}
	else
		QMessageBox::information(this, "info", QString::fromStdString("Nu se mai poate face undo!"));
	gui_raport_genuri();
}

void MyGUI::gui_cnt_genuri()
{
	QListWidget* lista_genuri= new QListWidget;
	map<string, DTO> dict = srv.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		string gen;
		gen.append(it->second.get_gen());
		gen.append(": ");
		gen.append(std::to_string(it->second.get_cnt()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(gen), lista_genuri);
	}
	lista_genuri->show();
}

void MyGUI::gui_adaugare_cos()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string autor = editare_autor->text().toStdString();

		editare_autor->clear();
		editare_titlu->clear();

		srv.adaugare_carte_in_cos(titlu, autor);
		incarcare_cos(srv.getAll_cos());

		QMessageBox::information(this, "info", QString::fromStdString("Carte a fost adaugata in cos cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
}

void MyGUI::gui_golire_cos()
{
	try
	{
		srv.golire_cos();
		incarcare_cos(srv.getAll_cos());

		QMessageBox::information(this, "info", QString::fromStdString("Cosul a fost golit cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
}

void MyGUI::gui_generare_cos()
{
	try
	{
		int nr = editare_nr->text().toInt();
		editare_nr->clear();
		if(nr > srv.getAll().size())
			QMessageBox::warning(this, "warning", QString::fromStdString("Numarul depaseste lungimea listei!"));
		else
		{
			srv.genereaza_cos(nr);
			incarcare_cos(srv.getAll_cos());
			QMessageBox::information(this, "info", QString::fromStdString("Cosul a fost generat cu succes!"));
		}
	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
}

void MyGUI::gui_export_cos()
{
	try
	{
		string nume_fisier = editare_nume_fisier->text().toStdString();
		editare_nume_fisier->clear();

		srv.export_cos(nume_fisier);
		QMessageBox::information(this, "info", QString::fromStdString("Cosul a fost exportat cu succes!"));
	}
	catch (ExceptieValidator& ve)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(ve.get_mesaje_eroare()));
	}
}

void MyGUI::gui_raport_genuri()
{
	clearLayout(typesLayout);
	map<string, DTO> dict = srv.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		auto gen = it->second.get_gen();
		auto nr = it->second.get_cnt();
		
		QPushButton* typeButton = new QPushButton(QString::fromStdString(gen));
		typesLayout->addWidget(typeButton);
		QObject::connect(typeButton, &QPushButton::clicked, this, [=]() {
			QMessageBox::information(this, "info", QString::fromStdString("Genul: " + gen + " - numarul cartilor: " + std::to_string(nr)));
			});
	}
}

void MyGUI::clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}