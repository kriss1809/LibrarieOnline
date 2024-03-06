#include "observer.h"
#include "service.h"
#include "cos_carti.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class programReadOnlyGUI : public QWidget, public Observer {
private:
    CosCarti& cos_carti;

public:
    programReadOnlyGUI(CosCarti& cos_carti);

    void update() override;

    void paintEvent(QPaintEvent* event) override;

    ~programReadOnlyGUI() {
        this->cos_carti.removeObserver(this);
    }
};
