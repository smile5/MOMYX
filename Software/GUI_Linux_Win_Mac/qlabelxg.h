#ifndef QLABELXG_H
#define QLABELXG_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class QLabelxg : public QLabel {
    Q_OBJECT

public:
    explicit QLabelxg(QWidget* parent = Q_NULLPTR);
    ~QLabelxg();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *e);

};


#endif // QLABELXG_H
