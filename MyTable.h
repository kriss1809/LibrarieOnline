#pragma once
#include <QAbstractTableModel>
#include "Carte.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Carte> carti;
public:
	MyTableModel(const std::vector<Carte>& carti) :carti{ carti } {
	}


	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return carti.size();
	}


	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}


	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Carte c = carti[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(c.getTitlu());
			else if (index.column() == 1)
				return QString::fromStdString(c.getAutor());
			else if (index.column() == 2)
				return QString::fromStdString(c.getGen());
			else if (index.column() == 3)
				return QString::number(c.getAn());
		}
		return QVariant{};
	}


	void regenereaza_lista(const vector<Carte>& c) {
		this->carti = c;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
};