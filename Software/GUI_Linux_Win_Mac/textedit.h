#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QWidget>
#include <Qt>

class QTextEditxg : public QTextEdit {
    Q_OBJECT

public:
    explicit QTextEditxg(QWidget* parent = Q_NULLPTR);
    ~QTextEditxg();

signals:
    void dblclicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *e);

};





#endif // TEXTEDIT_H
