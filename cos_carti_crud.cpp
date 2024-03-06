#include "cos_carti_crud.h"

void programCRUDGUI::run() {
    this->cos_carti.addObserver(this);

    this->initComponents();
    this->connectSignals();
    this->update();
    wnd->show();
}


void programCRUDGUI::initComponents() {
    wnd->setLayout(layout);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(table);

    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    layout->addWidget(slider);

    layout->addWidget(btnadd);
    layout->addWidget(btnempty);
}


void programCRUDGUI::connectSignals() {
    QObject::connect(btnadd, &QPushButton::clicked, [this]() {

        int number = slider->value();
        srv.genereaza_cos(number);
        cos_carti.notify();
        });
    QObject::connect(btnempty, &QPushButton::clicked, [this]() {
        cos_carti.golire_cos();
        cos_carti.notify();
        });
}


void programCRUDGUI::populateTable(QTableWidget* table, vector<Carte>& all) {
    this->table->clearContents();
    this->table->setRowCount(static_cast<int>(all.size()));

    int lineNumber = 0;
    for (Carte& carte : all) {
        this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(carte.getTitlu())));
        this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(carte.getAutor())));
        this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(carte.getGen())));
        this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(carte.getAn())));
        lineNumber++;
    }
}


void programCRUDGUI::update() {
    this->populateTable(table, this->cos_carti.getAll_cos());
}