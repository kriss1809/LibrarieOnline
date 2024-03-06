#pragma once
#include "cos_carti.h"
#include "observer.h"
#include "Service.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>
#include <qlabel.h>
#include <qformlayout.h>

using std::vector;

class programCRUDGUI : public QWidget, public Observer 
{
    private:
        CosCarti& cos_carti;
        StocareCarti& srv;
        QWidget* wnd;
        QVBoxLayout* layout;
        QTableWidget* table;
        QSlider* slider;
        QPushButton* btnadd;
        QPushButton* btnempty;

        void initComponents();
        void connectSignals();

        void populateTable(QTableWidget* table, vector<Carte>& all);

    public:
        explicit programCRUDGUI(CosCarti& cos_carti, StocareCarti& srv) :cos_carti{ cos_carti }, srv{ srv } {
            wnd = new QWidget;
            layout = new QVBoxLayout;
            btnadd = new QPushButton("Generare de carti random");
            btnempty = new QPushButton("Goleste cosul cu carti");
            slider = new QSlider;
            table = new QTableWidget(0, 4);

        };
        void run();

        void update() override;

        ~programCRUDGUI() {
            this->cos_carti.removeObserver(this);
        }
    };
