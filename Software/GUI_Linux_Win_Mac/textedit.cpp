#include "textedit.h"

QTextEditxg::QTextEditxg(QWidget* parent)
{

}

QTextEditxg::~QTextEditxg() {}

void QTextEditxg::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit dblclicked();
}
