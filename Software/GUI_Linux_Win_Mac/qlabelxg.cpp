#include "qlabelxg.h"

QLabelxg::QLabelxg(QWidget* parent)
{

}

QLabelxg::~QLabelxg() {}

void QLabelxg::mousePressEvent(QMouseEvent *e)
{
    emit clicked();
}

