#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define OS_LINUX 1
#define COURBE_CO2 0
#define NB_PT_SCROLLING 500
#define TIME_DATA_SENDING 5
#define TEMPS_INTERVALLE_AFF_ALARME 10

#include "chartview.h"
#include "lineseries.h"
#include <QMainWindow>
#include <QLabel>
#include <QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QTime>
#include <QDateTime>
#include <QComboBox>
#include "textedit.h"
#include "qlabelxg.h"

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

#define COLOR_pression QColor(193,125,17)
#define COLOR_debit QColor(17,193,125)
#define COLOR_co2 QColor(125,17,193)
#define COLOR_rouge "background-color: rgb(234,41,41)"
#define COLOR_orange "background-color: rgb(254, 162,7)"

    typedef struct{
        bool rcv_ok;
        float pression;
        float debit;
        float volume_tidal;
        float frequence;
        float debit_moy;
        float co2;
        float divers;
        unsigned long long temp;
        unsigned char nb_char;
        unsigned char info;
        QString stringtemp;
    } rcv_message;

public:
    explicit MainWindow(QWidget *parent = 0);
     QSerialPortInfo serialPortInfo;
     QLabelxg *dev_label;
     QTextEditxg *texte_alarme;
     QLabelxg *serial_port_label;
     QLabel *etat_label;
     QComboBox *mode_combo;
     LineSeries *serie_pression,*serie_debit,*serie_co2;
     QValueAxis *axis_pression,*axis_debit,*axis_co2;
     QValueAxis *axe_temps_pression,*axe_temps_debit,*axe_temps_co2;
     QValueAxis *axe_dummy_pression,*axe_dummy_debit,*axe_dummy_co2;
     QChart *chart_pression ,*chart_debit,*chart_co2; ;
     ChartView *chartview_pression,*chartview_debit,*chartview_co2;
     double compteur=0;
     ~MainWindow();
     rcv_message rcv_serie;
     QTimer *timer,*date;
     QDateTime heure;

private slots:
    void clear_text_alarm();
    void mode_change(int index);
    void serial_timeout();
    void pt_pression_added(int index);
    void pt_debit_added(int index);
    void pt_co2_added(int index);
    void clear_series();
    void test(QPointF);
    void serialreceived();
    void dev_label_clicked();
    void append_point();
    void on_doubleSpinBox_cycle_valueChanged(double arg1);
    void on_doubleSpinBox_ratio_valueChanged(double arg1);
    void on_doubleSpinBox_inspi_valueChanged(double arg1);
    void on_doubleSpinBox_expi_valueChanged(double arg1);
    void on_horizontalSlider_expi_valueChanged(int value);
    void on_horizontalSlider_ratio_valueChanged(int value);
    void on_horizontalSlider_cycles_valueChanged(int value);
    void on_horizontalSlider_inspi_valueChanged(int value);
    void update_date();
    void on_Enregistrer_courbes_clicked();
    void text_alarm_clicked();
    void on_doubleSpinBox_trigger_vol_valueChanged(double arg1);
    void on_horizontalSlider_trigger_vol_valueChanged(int value);
    void serial_label_clicked();

    void on_vt_max_editingFinished();
    void on_vt_min_editingFinished();
    void on_freq_min_editingFinished();
    void on_freq_max_editingFinished();
    void on_debit_min_editingFinished();
    void on_debit_max_editingFinished();
    void on_pression_min_editingFinished();
    void on_pression_max_editingFinished();

private:
    QSerialPort *serial;
    Ui::MainWindow *ui;
    qreal ymin_pression,ymin_debit,ymin_co2,xmin_temps;
    qreal ymax_pression,ymax_debit,ymax_co2,xmax_temps;
    void envoie_trame_config(uint state);
    QByteArray serbuf;
    QVector<rcv_message> tab_data;
    QTimer *chart_update;
    long nbr;
    void connect_serial(bool checked);
    qint64 temps_aff_vt,temps_aff_debit,temps_aff_pression,temps_aff_freq,temps_aff_alarm;
};

#endif // MAINWINDOW_H
