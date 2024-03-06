#include "cos_carti_ReadOnly.h"

programReadOnlyGUI::programReadOnlyGUI(CosCarti& cos_carti) : cos_carti{ cos_carti } {
    this->cos_carti.addObserver(this);
    this->repaint();
}

void programReadOnlyGUI::paintEvent(QPaintEvent* event) {
    QPainter g{ this };

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    int a = 200, b = 200;       // coordonatele centrului cercului
    int r = 150;                // raza cercului
    int t = 0;
    int k = 0;
    for (const auto& prod : this->cos_carti.getAll_cos()) 
    {
        k++;
        if(k==1)
            g.setPen(Qt::blue);
        else if (k == 2)
            g.setPen(Qt::red);
        else if (k == 3)
            g.setPen(Qt::green);
        else if (k == 4)
            g.setPen(Qt::yellow);
        else if (k == 5)
        {
            g.setPen(Qt::black);
            k = 0;
        }

        int x = a + r * sin(t);
        int y = b + r * cos(t);
        g.drawEllipse(x, y, 50, 50);
        t += 14;
    }
}

void programReadOnlyGUI::update() {
    this->repaint();
}