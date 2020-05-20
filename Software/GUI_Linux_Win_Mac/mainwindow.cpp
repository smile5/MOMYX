#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartview.h"
#include "lineseries.h"
#include "textedit.h"
#include "qlabelxg.h"
#include <QDebug>

#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QFileDialog>
#include <QMessageBox>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTimer>
#include <QTime>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    dev_label(new QLabelxg),
    serial_port_label(new QLabelxg),
    etat_label(new QLabel),
    mode_combo(new QComboBox),
    serial(new QSerialPort), 
    ui(new Ui::MainWindow)
{
    //heure.start();
    timer = new QTimer();
    date = new QTimer();
    connect(date, SIGNAL(timeout()), this, SLOT(update_date()));
    date->start(1000);
    nbr=0;
    chart_update = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(serial_timeout()));
    timer->stop();
    connect(chart_update,SIGNAL(timeout()),this,SLOT(append_point()));
    chart_update->stop();
    rcv_serie.nb_char=0;
    rcv_serie.rcv_ok=false;
    ui->setupUi(this);
    connect(ui->info,SIGNAL(dblclicked()),this,SLOT(clear_text_alarm()));

    dev_label->setAlignment(Qt::AlignLeft);
    dev_label->setFixedWidth(150);
    connect(dev_label,SIGNAL(clicked()),this,SLOT(dev_label_clicked()));
    connect(serial_port_label,SIGNAL(clicked()),this,SLOT(serial_label_clicked()));
    texte_alarme =new QTextEditxg();

     ui->Alarmes->show();
     ui->texte_alarme->show();
     connect(ui->texte_alarme,SIGNAL(clicked()),this,SLOT(text_alarm_clicked()));
    // connect(this,SIGNAL(alarm_text_changed()),this,SLOT(text_alarm_changed()));
     //connect(ui->texte_alarme, &QTextEditxg::dblclicked, this, &MainWindow::text_alarm_clicked);
     ui->Alarmes->hide();
    serial_port_label->setAlignment(Qt::AlignCenter);
    serial_port_label->setIndent(25);

    mode_combo->setStyleSheet("background-color: rgb(22, 100,192)");
    mode_combo->addItem("VPC");
    mode_combo->addItem("VNI");
    mode_combo->addItem("VPC-AI");
    mode_combo->addItem("OFF");
    mode_combo->setCurrentIndex(3);

    connect(mode_combo,SIGNAL(currentIndexChanged(int)),this,SLOT(mode_change(int)));

    etat_label->setAlignment(Qt::AlignRight);
    etat_label->setIndent(25);

    ui->statusBar->addWidget(dev_label);
    ui->statusBar->addWidget(serial_port_label, 1);
    ui->statusBar->addWidget(mode_combo,2);
    ui->statusBar->addWidget(etat_label,3);
    etat_label->setText(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
    dev_label->setText("OMYXAir - 2020");
    serial_port_label->setText("Port série: "+serial->portName());

    // initialisation composant pour le graphique et le graphique
    serie_pression = new LineSeries();
    serie_pression->setUseOpenGL(true);
    serie_pression->connect(serie_pression, SIGNAL(pointAdded(int)),this,SLOT(pt_pression_added(int)));
    serie_pression->setPen(QPen(COLOR_pression,2, Qt::DotLine,Qt::SquareCap,Qt::BevelJoin));
    axis_pression = new QValueAxis;
    axe_temps_pression = new QValueAxis;
    axe_dummy_pression=new QValueAxis;
    axis_pression->setLinePenColor(COLOR_pression);
    axis_pression->setMinorTickCount(2);
    axe_temps_pression->setTickCount(11);
    axe_temps_pression->setMinorTickCount(4);
    axe_dummy_pression->setTickCount(11);
    axe_dummy_pression->setMinorTickCount(4);
    axis_pression->show();
    axe_dummy_pression->setRange(0,50);
    axe_temps_pression->setRange(0,50);
    axe_dummy_pression->setLabelFormat("%.0f");
    axe_dummy_pression->show();
    axe_temps_pression->hide();
    serie_pression->show();
    chart_pression = new QChart();
    chart_pression->addSeries(serie_pression);
    serie_pression->setObjectName("Pression");
    chart_pression->legend()->hide();
    chart_pression->addAxis(axe_temps_pression, Qt::AlignBottom);
    chart_pression->addAxis(axis_pression, Qt::AlignLeft);
    chart_pression->setObjectName("Chart_pression");
    chart_pression->setMargins(QMargins(0,0,0,0));
    chart_pression->addAxis(axe_dummy_pression,Qt::AlignBottom);
    serie_pression->attachAxis(axis_pression);
    serie_pression->attachAxis(axe_temps_pression);
    chart_pression->setTitle("Pression en cmH2O");
    chartview_pression = new ChartView(chart_pression);
    chartview_pression->connect(chartview_pression,SIGNAL(efface()),this,SLOT(clear_series()));
    ui->Chart_layout->addWidget(chartview_pression,0,0);

    serie_debit = new LineSeries();
    serie_debit->setUseOpenGL(true);
    serie_debit->connect(serie_debit, SIGNAL(pointAdded(int)),this,SLOT(pt_debit_added(int)));
    serie_debit->setPen(QPen(COLOR_debit,2, Qt::DotLine,Qt::SquareCap,Qt::BevelJoin));
    axis_debit= new QValueAxis;
    axe_temps_debit = new QValueAxis;
    axe_dummy_debit=new QValueAxis;
    axis_debit->setLinePenColor(COLOR_debit);
    axis_debit->setMinorTickCount(2);
    axe_temps_debit->setTickCount(11);
    axe_temps_debit->setMinorTickCount(4);
    axe_dummy_debit->setTickCount(11);
    axe_dummy_debit->setMinorTickCount(4);
    axis_debit->show();
    axe_dummy_debit->setRange(0,50);
    axe_temps_debit->setRange(0,50);
    axe_dummy_debit->setLabelFormat("%.0f");
    axe_dummy_debit->show();
    axe_temps_debit->hide();
    serie_debit->show();
    chart_debit = new QChart();
    chart_debit->addSeries(serie_debit);
    serie_debit->setObjectName("Debit");
    chart_debit->legend()->hide();
    chart_debit->addAxis(axe_temps_debit, Qt::AlignBottom);
    chart_debit->addAxis(axis_debit, Qt::AlignLeft);
    chart_debit->setObjectName("Chart_debit");
    chart_debit->setMargins(QMargins(0,0,0,0));
    chart_debit->addAxis(axe_dummy_debit,Qt::AlignBottom);
    serie_debit->attachAxis(axis_debit);
    serie_debit->attachAxis(axe_temps_debit);
    chart_debit->setTitle("Débit en L/min ");
    chartview_debit= new ChartView(chart_debit);
    chartview_debit->connect(chartview_debit,SIGNAL(efface()),this,SLOT(clear_series()));
    ui->Chart_layout->addWidget(chartview_debit,1,0);

#if COURBE_CO2 == 1
    serie_co2 = new LineSeries();
    serie_co2->setUseOpenGL(true);
    serie_co2->connect(serie_co2, SIGNAL(pointAdded(int)),this,SLOT(pt_co2_added(int)));
    serie_co2->setPen(QPen(COLOR_co2,2, Qt::DotLine,Qt::SquareCap,Qt::BevelJoin));
    axis_co2= new QValueAxis;
    axe_temps_co2 = new QValueAxis;
    axe_dummy_co2=new QValueAxis;
    axis_co2->setLinePenColor(COLOR_co2);
    axis_co2->setMinorTickCount(2);
    axe_temps_co2->setTickCount(11);
    axe_temps_co2->setMinorTickCount(4);
    axe_dummy_co2->setTickCount(11);
    axe_dummy_co2->setMinorTickCount(4);
    axis_co2->show();
    axe_dummy_co2->setRange(0,50);
    axe_temps_co2->setRange(0,50);
    axe_dummy_co2->setLabelFormat("%.0f");
    axe_dummy_co2->show();
    axe_temps_co2->hide();
    serie_co2->show();
    chart_co2 = new QChart();
    chart_co2->addSeries(serie_co2);
    serie_co2->setObjectName("CO2");
    chart_co2->legend()->hide();
    chart_co2->addAxis(axe_temps_co2, Qt::AlignBottom);
    chart_co2->addAxis(axis_co2, Qt::AlignLeft);
    chart_co2->setObjectName("Chart_co2");
    chart_co2->setMargins(QMargins(0,0,0,0));
    chart_co2->addAxis(axe_dummy_co2,Qt::AlignBottom);
    serie_co2->attachAxis(axis_co2);
    serie_co2->attachAxis(axe_temps_co2);
    chart_co2->setTitle("Co2 en  ???? ");  
    chartview_co2=new ChartView(chart_co2);    
    chartview_co2->connect(chartview_co2,SIGNAL(efface()),this,SLOT(clear_series()));
    ui->Chart_layout->addWidget(chartview_co2,2,0);
#endif
    temps_aff_vt=QDateTime::currentSecsSinceEpoch();
    temps_aff_freq=temps_aff_vt;
    temps_aff_debit=temps_aff_vt;
    temps_aff_pression=temps_aff_vt;
    temps_aff_alarm=temps_aff_vt;
    this->setBaseSize(750,500);
    clear_series();
    connect_serial(1);
 //   envoie_trame_config(1);
}

void MainWindow::mode_change(int index)
{
    this->setWindowTitle("OMYXAir - Mode de Fonctionnement : " + mode_combo->itemText(index) );
    if(index==0) // Mode VPC
    {
        ui->horizontalSlider_trigger_vol->setDisabled(true);
        ui->doubleSpinBox_trigger_vol->setDisabled(true);
        ui->label_cycle->setText("Frequence cy/min ");
        ui->label_ratio->setText("Ratio I/E  %");
    }
    else if((index==1)||(index==2))
    {
        ui->horizontalSlider_trigger_vol->setEnabled(true);
        ui->doubleSpinBox_trigger_vol->setEnabled(true);
        ui->label_cycle->setText("Freq Sauv. cy/min ");
        ui->label_ratio->setText("Ratio Sauv. I/E  %");
    }
    else
    {
        ui->horizontalSlider_trigger_vol->setEnabled(true);
        ui->doubleSpinBox_trigger_vol->setEnabled(true);
        ui->label_cycle->setText("Frequence cy/min ");
        ui->label_ratio->setText("Ratio I/E  %");
    }

    envoie_trame_config(6);
}
void MainWindow::clear_text_alarm()
{
    ui->info->clear();
}
void MainWindow::text_alarm_clicked()
{
    ui->Alarmes->hide();
    envoie_trame_config(7);
    ui->texte_alarme->clear();
    ui->widget->setStyleSheet("");
    ui->pression_max->setStyleSheet("");
    ui->pression_min->setStyleSheet("");
    ui->vt_max->setStyleSheet("");
    ui->vt_min->setStyleSheet("");
    ui->debit_max->setStyleSheet("");
    ui->debit_min->setStyleSheet("");
    ui->freq_max->setStyleSheet("");
    ui->freq_min->setStyleSheet("");
}
void MainWindow::update_date()
{
     etat_label->setText(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
     envoie_trame_config(7);
}
void MainWindow::test(QPointF pt)
{
    QMessageBox::about(this,"Point Clické:",
                       "X: " + QString().number(pt.x()) + " <br>"
                       "Y: " + QString().number(pt.y()) + " <br>");
}

void MainWindow::clear_series()
{
    xmax_temps=0;
    xmin_temps=100000;
    compteur=0;
    nbr=0;

    ymax_pression=0;
    ymin_pression=100000;
    axis_pression->setRange(-50000,65535);
    serie_pression->clear();

    ymax_debit=-100000;
    ymin_debit=100000;
    axis_debit->setRange(-50000,65535);
    serie_debit->clear();
#if COURBE_CO2 == 1
    ymax_co2=0;
    ymin_co2=100000;
    axis_co2->setRange(-50000,65535);
    serie_co2->clear();
#endif
}

void MainWindow::pt_pression_added(int index)
{
    qreal y = serie_pression->at(index).y();

    if(y< ymin_pression || y > ymax_pression)
    {
        if(y < ymin_pression)
            ymin_pression = y;
        if(y> ymax_pression)
            ymax_pression = y;
    }
    if(ymax_pression-ymin_pression<1)
    {
        ymax_pression=ymin_pression+1;
    }

/*    qreal x = serie_pression->at(index).x();
    if(x< xmin_temps || x > xmax_temps)
    {
        if(x < xmin_temps)
            xmin_temps = x;
        if(x> xmax_temps)
            xmax_temps = x;
    }
    if(xmax_temps-xmin_temps<1)
    {
        xmax_temps=xmin_temps+1;
    }*/
}

void MainWindow::pt_debit_added(int index)
{
    qreal y = serie_debit->at(index).y();

    if(y< ymin_debit || y > ymax_debit)
    {
        if(y < ymin_debit)
            ymin_debit = y;
        if(y> ymax_debit)
            ymax_debit = y;
    }
    if(ymax_debit-ymin_debit<1)
    {
        ymax_debit=ymin_debit+1;
    }


}

void MainWindow::pt_co2_added(int index)
{
    qreal y = serie_co2->at(index).y();

    if(y< ymin_co2 || y > ymax_co2)
    {
        if(y < ymin_co2)
            ymin_co2 = y;
        if(y> ymax_co2)
            ymax_co2 = y;
    }
    if(ymax_co2-ymin_co2<1)
    {
        ymax_co2=ymin_co2+1;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}

void MainWindow::serial_timeout()
{
    rcv_serie.rcv_ok=false;
    timer->stop();
}

void MainWindow::serialreceived()
{
    int i;
    timer->start(2000);
    serbuf=serial->readAll();
   // ui->textEdit->append(serbuf);
    for(i=0;i<serbuf.size();i++)
    {
        if ((serbuf.at(i)=='!')&&(rcv_serie.nb_char==0))
        {
            rcv_serie.nb_char=1;
            rcv_serie.info=0;
            rcv_serie.rcv_ok=false;
        }
        else if((serbuf.at(i)=='P')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='P';
        }
        else if((serbuf.at(i)=='D')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='D';
        }
        else if((serbuf.at(i)=='C')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='C';
        }
        else if((serbuf.at(i)=='c')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='c';
        }
        else if((serbuf.at(i)=='R')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='R';
        }
        else if((serbuf.at(i)=='I')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='I';
        }
        else if((serbuf.at(i)=='E')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='E';
        }
        else if((serbuf.at(i)=='V')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='V';
        }
        else if((serbuf.at(i)=='F')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='F';
        }
        else if((serbuf.at(i)=='M')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='M';
        }
        else if((serbuf.at(i)=='T')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='T';
        }
        else if((serbuf.at(i)=='m')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='m';
        }
        else if((serbuf.at(i)=='A')&&(rcv_serie.nb_char==1))
        {
            rcv_serie.nb_char=2;
            rcv_serie.info='A';
        }
        else if((serbuf.at(i)=='*')&&(rcv_serie.nb_char>1))
        {
            rcv_serie.stringtemp.remove("\r\n");
            rcv_serie.divers=rcv_serie.stringtemp.toFloat();
            rcv_serie.stringtemp.clear();
            timer->stop();
            rcv_serie.nb_char=0;
            rcv_serie.rcv_ok=true;
        }
        else if((serbuf.at(i)=='\r')||(serbuf.at(i)=='\n'))
        {
            rcv_serie.rcv_ok=false;

        }
        else
        {
            rcv_serie.stringtemp.append(serbuf.at(i));
            rcv_serie.rcv_ok=false;
        }

        if(rcv_serie.rcv_ok==true)
        {
            rcv_serie.rcv_ok=false;
           // rcv_serie.temp=heure.elapsed();
            if(rcv_serie.info=='P')
            {
               // rcv_serie.rcv_ok=false;
                rcv_serie.pression=rcv_serie.divers;
                if(rcv_serie.pression<ui->pression_min->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText("Pb: Pression < Pression Mini");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_pression)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                            ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                            ui->info->append("Pb: Pression < Pression Mini");
                            temps_aff_pression=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->pression_min->setStyleSheet(COLOR_rouge);
                }
                else if (rcv_serie.pression>ui->pression_max->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: Pression > Pression Maxi");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_pression)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append("Pb: Pression > Pression Maxi");
                        temps_aff_pression=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->pression_max->setStyleSheet(COLOR_rouge);
                }
                else
                {
                }
            }
            else if(rcv_serie.info=='D') // reception Debit instantanne
            {
               // rcv_serie.rcv_ok=false;
                rcv_serie.debit=rcv_serie.divers;
                rcv_serie.temp+=TIME_DATA_SENDING;
                tab_data.append(rcv_serie);   // ici data pour courbe prete on stocke ds tab_data pour affichage courbes
            }
            if(rcv_serie.info=='V') // on s'occupe du Volume VTE
            {
              //  rcv_serie.rcv_ok=false;
                rcv_serie.volume_tidal=rcv_serie.divers;
                ui->label_VTE->setText(QString::number(rcv_serie.volume_tidal,'f',0));
                if(rcv_serie.volume_tidal<ui->vt_min->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: VTE < VTE Mini");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_vt)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append(" Pb: VTE < VTE Mini");
                        temps_aff_vt=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->vt_min->setStyleSheet(COLOR_rouge);
                }
                else if (rcv_serie.volume_tidal>ui->vt_max->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: VTE > VTE Maxi");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_vt)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append("Pb: VTE > VTE Maxi");
                        temps_aff_vt=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->vt_max->setStyleSheet(COLOR_rouge);
                }
                else
                {
                }
            }
            if(rcv_serie.info=='F') // on s'occupe de la frequence
            {
                //rcv_serie.rcv_ok=false;
                rcv_serie.frequence=60.0*1000.0/rcv_serie.divers;
                ui->label_freq_reel->setText(QString::number(rcv_serie.frequence));
                if(rcv_serie.frequence<ui->freq_min->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: Freq < Freq Mini");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_freq)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append(" Pb: Freq < Freq Mini");
                        temps_aff_freq=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->freq_min->setStyleSheet(COLOR_rouge);
                }
                else if (rcv_serie.frequence>ui->freq_max->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: Freq > Freq Maxi");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_freq)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append("Pb: Freq > Freq Maxi");
                        temps_aff_freq=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->freq_max->setStyleSheet(COLOR_rouge);
                }
                else
                {
                }
            }
            if(rcv_serie.info=='M') // on s'occupe du debit moyen
            {
                //rcv_serie.rcv_ok=false;
                rcv_serie.debit_moy=rcv_serie.divers;
                ui->label_debit_moy->setText(QString::number(rcv_serie.debit_moy,'f',1));
                if(rcv_serie.debit_moy<ui->debit_min->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: Debit < Debit Mini");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_debit)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append(" Pb: Debit < Debit Mini");
                        temps_aff_debit=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->debit_min->setStyleSheet(COLOR_rouge);
                }
                else if (rcv_serie.debit_moy>ui->debit_max->value())
                {
                    ui->Alarmes->show();
                    ui->texte_alarme->setText(" Pb: Debit > Debit Maxi");
                    ui->widget->setStyleSheet(COLOR_rouge);
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_debit)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                        ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                        ui->info->append("Pb: debit > debit Maxi");
                        temps_aff_debit=QDateTime::currentSecsSinceEpoch();
                    }
                    ui->debit_max->setStyleSheet(COLOR_rouge);
                }
                else
                {
                }
            }
            else if(rcv_serie.info=='C')
            {
                ui->doubleSpinBox_cycle->blockSignals(true);
                ui->horizontalSlider_cycles->blockSignals(true);
                ui->doubleSpinBox_cycle->setValue(60000.0/rcv_serie.divers);
                ui->horizontalSlider_cycles->setValue((int)(100.0*(ui->doubleSpinBox_cycle->value()-ui->doubleSpinBox_cycle->minimum())/(ui->doubleSpinBox_cycle->maximum()-ui->doubleSpinBox_cycle->minimum())));
                ui->horizontalSlider_cycles->blockSignals(false);
                ui->doubleSpinBox_cycle->blockSignals(false);
            }
            else if(rcv_serie.info=='R')
            {
                ui->doubleSpinBox_ratio->blockSignals(true);
                ui->horizontalSlider_ratio->blockSignals(true);
                ui->doubleSpinBox_ratio->setValue(round(10*(100.0*rcv_serie.divers/100.0/(1.0-rcv_serie.divers/100.0)))/10.0);
                ui->horizontalSlider_ratio->setValue((int)((ui->doubleSpinBox_ratio->value()-ui->doubleSpinBox_ratio->minimum())*((float)ui->horizontalSlider_ratio->maximum()-(float)ui->horizontalSlider_ratio->minimum())/(ui->doubleSpinBox_ratio->maximum()-ui->doubleSpinBox_ratio->minimum())+(double)ui->horizontalSlider_ratio->minimum()));
                ui->horizontalSlider_ratio->blockSignals(false);
                ui->doubleSpinBox_ratio->blockSignals(false);
            }
            else if(rcv_serie.info=='I')
            {
                ui->doubleSpinBox_inspi->blockSignals(true);
                ui->horizontalSlider_inspi->blockSignals(true);
                ui->doubleSpinBox_inspi->setValue((double)rcv_serie.divers);
                ui->horizontalSlider_inspi->setValue((int)(100.0*(ui->doubleSpinBox_inspi->value()-ui->doubleSpinBox_inspi->minimum())/(ui->doubleSpinBox_inspi->maximum()-ui->doubleSpinBox_inspi->minimum())));
                ui->horizontalSlider_inspi->blockSignals(false);
                ui->doubleSpinBox_inspi->blockSignals(false);
            }
            else if(rcv_serie.info=='E')
            {
                ui->doubleSpinBox_expi->blockSignals(true);
                ui->horizontalSlider_expi->blockSignals(true);
                ui->doubleSpinBox_expi->setValue(rcv_serie.divers);
                ui->horizontalSlider_expi->setValue((int)(100.0*(ui->doubleSpinBox_expi->value()-ui->doubleSpinBox_expi->minimum())/(ui->doubleSpinBox_expi->maximum()-ui->doubleSpinBox_expi->minimum())));
                ui->horizontalSlider_expi->blockSignals(false);
                ui->doubleSpinBox_expi->blockSignals(false);
            }
            else if(rcv_serie.info=='T')
            {
                ui->doubleSpinBox_trigger_vol->blockSignals(true);
                ui->horizontalSlider_trigger_vol->blockSignals(true);
                ui->doubleSpinBox_trigger_vol->setValue(rcv_serie.divers);
                ui->horizontalSlider_trigger_vol->setValue((int)(100.0*(ui->doubleSpinBox_trigger_vol->value()-ui->doubleSpinBox_trigger_vol->minimum())/(ui->doubleSpinBox_trigger_vol->maximum()-ui->doubleSpinBox_trigger_vol->minimum())));
                ui->horizontalSlider_trigger_vol->blockSignals(false);
                ui->doubleSpinBox_trigger_vol->blockSignals(false);
            }
            else if(rcv_serie.info=='m')
            {
             //   mode_combo->blockSignals(true);
                if(rcv_serie.divers>=3)
                {
                  mode_combo->setCurrentIndex(3);
                }
                else
                {
                    mode_combo->setCurrentIndex(rcv_serie.divers);
                }
              //  mode_combo->blockSignals(false);
            }
            else if(rcv_serie.info=='c')
            {
                ui->lcdnumber->setText(QString::number(rcv_serie.divers));
            }
            else if(rcv_serie.info=='A')
            {
                if(rcv_serie.divers!=0)
                {
                    if((QDateTime::currentSecsSinceEpoch()-temps_aff_alarm)>TEMPS_INTERVALLE_AFF_ALARME)
                    {
                    ui->Alarmes->show();
                    ui->widget->setStyleSheet(COLOR_rouge);
                    temps_aff_alarm=QDateTime::currentSecsSinceEpoch();
                        if((int)rcv_serie.divers & 0x01)
                        {
                            ui->texte_alarme->setText("Pb Capteurs");
                            ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                            ui->info->append("Pb: Capteurs");
                        }
                        if ((int)rcv_serie.divers & 0x02)
                        {
                            ui->texte_alarme->setText("Pb: Pression Motrice Potentiometre trop faible");
                            ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                            ui->info->append("Pb: Pression Motrice Potentiometre");
                        }
                        if ((int)rcv_serie.divers & 0x04)
                        {
                            ui->texte_alarme->setText("Pb: Respiration de Sauvegarde -Apnée");
                            ui->info->append(heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss"));
                            ui->info->append("Pb: Respiration de Sauvegarde - Apnée");
                        }

                    }
                }
                else
                {
                  //ui->Alarmes->hide();
                }
            }
        }
   }

}

void MainWindow::envoie_trame_config(uint state)
{
    //state 1 => Cycle, 2=> rapport, 3 => Pinspi, 4 Pexpi, 5 Trigger exp,6 mode, 7alarme
    QString temp_frame;
    double temp_value;
    temp_frame.clear();
    switch(state)
    {
        case 1:
            temp_frame.append("!C");
            temp_frame.append(QString::number(60000/ui->doubleSpinBox_cycle->value()));
            temp_frame.append('*');
        break;
        case 2:
            temp_frame.append("!R");
            //conversion de I/E a I/C
            temp_value= 100.0*(ui->doubleSpinBox_ratio->value()/100.0)/(1+(ui->doubleSpinBox_ratio->value()/100.0));
            temp_frame.append(QString::number(temp_value));//,'f',5));
            temp_frame.append('*');
        break;
        case 3:
            temp_frame.append("!I");
            temp_frame.append(QString::number(ui->doubleSpinBox_inspi->value()));
            temp_frame.append('*');
        break;
        case 4:
            temp_frame.append("!E");
            temp_frame.append(QString::number(ui->doubleSpinBox_expi->value()));
            temp_frame.append('*');
        break;
        case 5:
            temp_frame.append("!T");
            temp_frame.append(QString::number(ui->doubleSpinBox_trigger_vol->value()));
            temp_frame.append('*');
        break;
        case 6:
            temp_frame.append("!M");
            temp_frame.append(QString::number(mode_combo->currentIndex()));
            temp_frame.append('*');
        break;
        case 7:
            temp_frame.append("!A");
            if(ui->Alarmes->isVisible())
            {
                temp_frame.append('1');
            }
            else
            {
                temp_frame.append('0');
            }
            temp_frame.append('*');
        break;
        case 0:
        default:
        break;
    }
    if(state>=1)
    {
        serial->write(QByteArray::fromStdString(temp_frame.toStdString()));
        etat_label->setText("Envoie des données");
    }
    else
    {

    }
}


void MainWindow::dev_label_clicked()
{
    QMessageBox::about(this,"OMYXAir",
                       "<h4>Respirateur Open Source - Open Hardware</h4>\n\n"
                       "Ventilation Pression Controlée + Aide Inspiratoire <br>"
                       "Equipe: Oc-Mp-Mb-Yc-Xg  <br>"
                       "<a href='url'> https://github.com/smile5/OMYXAir </a>");
}

void MainWindow::serial_label_clicked()
{
    if(serial->isOpen())
    {

    }
    else
    {
        connect_serial(1);
    }
}

void MainWindow::connect_serial(bool checked)
{
    if(!serial->isOpen())
    {


    if(checked)
    {
        QString port_name;
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            /*  qDebug() << "Name : " << info.portName();
                qDebug() << "Description : " << info.description();
                qDebug() << "Manufacturer: " << info.manufacturer();
                qDebug() << "VID " << info.vendorIdentifier();
                qDebug() << "PID" << info.productIdentifier(); */
            if((info.vendorIdentifier()==0x16C0)&&(info.productIdentifier()==0x0483))  // VID PID Teensy3.2
            {
                port_name=info.portName();
            }
            else if((info.vendorIdentifier()==0x2341)&&(info.productIdentifier()==0x0043))  // VID PID Arduino Uno
            {
                port_name=info.portName();
            }
            if((info.vendorIdentifier()==0x0483)&&(info.productIdentifier()==0x374b))  // VID PID Teensy3.2
            {
                port_name=info.portName();
            }
        }
        if(serial->isOpen())
        {
            serial->disconnect(serial,SIGNAL(readyRead()),this,SLOT(serialreceived()));
            serial->flush();
            serbuf.clear();
            serial->close();
        }
        rcv_serie.nb_char=0;
        rcv_serie.rcv_ok=false;
#if OS_LINUX == 1
        //port_name="ttyACM0"; // a modifier avec valeur Teensy ou r'ajout selection portcom
        serial->setPortName("/dev/"+port_name);
        //serial->setPortName("/dev/pts/1"); // only for debug
#else
        serial->setPortName(port_name);
#endif
        if(port_name=="")
        {
            serial_port_label->setText("Port Série: Clos");
        }
        else
        {
            tab_data.clear();
            serbuf.clear();
            serial->setBaudRate(115200);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setReadBufferSize(0);
            serial->open(QIODevice::ReadWrite);
            serial->connect(serial,SIGNAL(readyRead()),this,SLOT(serialreceived()),Qt::UniqueConnection);
            serial_port_label->setText("Port série: "+serial->portName());
            chart_update->start(100);
         //   envoie_trame_config(1);
        }
    }
    else
    {
        serial->disconnect(serial,SIGNAL(readyRead()),this,SLOT(serialreceived()));
        chart_update->stop();
        serial_port_label->setText("Port Série: Clos");
        if(serial->isOpen())
        {
            serial->putChar('S');
            while(!serial->flush());
            serial->clear(QSerialPort::AllDirections);
            serbuf.clear();
            serial->close();
            envoie_trame_config(0);
        }
    }
    }
}
void MainWindow::append_point()
{
    int cpt;
    QVector<rcv_message> tmp;
    tmp=tab_data;
    tab_data.clear();
    if(tmp.size()==0)
    {return;}
    for(cpt=0;cpt<(tmp.size());cpt++)
    {
            serie_pression->append(20*qreal(tmp.at(cpt).temp)/1000.0,qreal(tmp.at(cpt).pression));
            serie_debit->append(20*qreal(tmp.at(cpt).temp)/1000.0,qreal(tmp.at(cpt).debit));
#if COURBE_CO2 == 1
            serie_co2->append(20*qreal(tmp.at(cpt).temp)/1000.0,qreal(tmp.at(cpt).co2));
#endif
    }
    if(serie_pression->count()>NB_PT_SCROLLING)
    {
        serie_pression->removePoints(0,serie_pression->count()-NB_PT_SCROLLING);
        serie_debit->removePoints(0,serie_debit->count()-NB_PT_SCROLLING);
#if COURBE_CO2 == 1
        serie_co2->removePoints(0,serie_co2->count()-NB_PT_SCROLLING);
#endif
    }
    axe_temps_pression->setRange(serie_pression->at(0).x(),serie_pression->at(0).x()+50);
    axis_pression->setRange(ymin_pression,ymax_pression);

    axe_temps_debit->setRange(serie_pression->at(0).x(),serie_pression->at(0).x()+50);
    axis_debit->setRange(ymin_debit,ymax_debit);

#if COURBE_CO2 == 1
    axe_temps_co2->setRange(serie_pression->at(0).x(),serie_pression->at(0).x()+50);
    axis_co2->setRange(ymin_co2,ymax_co2);
#endif

    this->repaint();
}
void MainWindow::on_doubleSpinBox_cycle_valueChanged(double arg1)
{
    ui->horizontalSlider_cycles->blockSignals(true);
    ui->horizontalSlider_cycles->setValue((int)(100.0*(arg1-ui->doubleSpinBox_cycle->minimum())/(ui->doubleSpinBox_cycle->maximum()-ui->doubleSpinBox_cycle->minimum())));
    ui->horizontalSlider_cycles->blockSignals(false);
    envoie_trame_config(1);
}

void MainWindow::on_horizontalSlider_cycles_valueChanged(int value)
{
    ui->doubleSpinBox_cycle->setValue(round(20.0*(ui->doubleSpinBox_cycle->minimum()+value*(ui->doubleSpinBox_cycle->maximum()-ui->doubleSpinBox_cycle->minimum())/100.0))/20.0);
}


void MainWindow::on_doubleSpinBox_trigger_vol_valueChanged(double arg1)
{
    ui->horizontalSlider_trigger_vol->blockSignals(true);
    ui->horizontalSlider_trigger_vol->setValue((int)(100.0*(arg1-ui->doubleSpinBox_trigger_vol->minimum())/(ui->doubleSpinBox_trigger_vol->maximum()-ui->doubleSpinBox_trigger_vol->minimum())));
    ui->horizontalSlider_trigger_vol->blockSignals(false);
    envoie_trame_config(5);
}

void MainWindow::on_horizontalSlider_trigger_vol_valueChanged(int value)
{
    ui->doubleSpinBox_trigger_vol->setValue(round(20.0*(ui->doubleSpinBox_trigger_vol->minimum()+value*(ui->doubleSpinBox_trigger_vol->maximum()-ui->doubleSpinBox_trigger_vol->minimum())/100.0))/20.0);
}

void MainWindow::on_doubleSpinBox_ratio_valueChanged(double arg1)
{
    ui->horizontalSlider_ratio->blockSignals(true);
   // ui->horizontalSlider_ratio->setValue((int)((arg1-ui->doubleSpinBox_ratio->minimum())*(ui->horizontalSlider_ratio->maximum()-ui->horizontalSlider_ratio->minimum())/(ui->doubleSpinBox_ratio->maximum()-ui->doubleSpinBox_ratio->minimum())+ui->horizontalSlider_ratio->minimum()));
    ui->horizontalSlider_ratio->setValue((int)(100.0*(arg1-ui->doubleSpinBox_ratio->minimum())/(ui->doubleSpinBox_ratio->maximum()-ui->doubleSpinBox_ratio->minimum())));
    ui->horizontalSlider_ratio->blockSignals(false);
    envoie_trame_config(2);
}

void MainWindow::on_horizontalSlider_ratio_valueChanged(int value)
{
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    ui->doubleSpinBox_ratio->setValue(round(20.0*((value-ui->horizontalSlider_ratio->minimum())*(ui->doubleSpinBox_ratio->maximum()-ui->doubleSpinBox_ratio->minimum())/(ui->horizontalSlider_ratio->maximum()-ui->horizontalSlider_ratio->minimum())+ui->doubleSpinBox_ratio->minimum())/20.0));
}


void MainWindow::on_doubleSpinBox_inspi_valueChanged(double arg1)
{
    ui->horizontalSlider_inspi->blockSignals(true);
    if(ui->doubleSpinBox_inspi->value()<(ui->doubleSpinBox_expi->value()+6))
    {
        ui->doubleSpinBox_expi->setValue(ui->doubleSpinBox_inspi->value()-6);
    }
    ui->horizontalSlider_inspi->setValue((int)(100.0*(arg1-ui->doubleSpinBox_inspi->minimum())/(ui->doubleSpinBox_inspi->maximum()-ui->doubleSpinBox_inspi->minimum())));
    ui->horizontalSlider_inspi->blockSignals(false);
    envoie_trame_config(3);
}

void MainWindow::on_horizontalSlider_inspi_valueChanged(int value)
{
    ui->doubleSpinBox_inspi->setValue(round(20.0*(ui->doubleSpinBox_inspi->minimum()+value*(ui->doubleSpinBox_inspi->maximum()-ui->doubleSpinBox_inspi->minimum())/100.0))/20.0);
}

void MainWindow::on_doubleSpinBox_expi_valueChanged(double arg1)
{
    ui->horizontalSlider_expi->blockSignals(true);
    if(ui->doubleSpinBox_expi->value()>(ui->doubleSpinBox_inspi->value()-6))
    {
        ui->doubleSpinBox_inspi->setValue(ui->doubleSpinBox_expi->value()+6);
    }
    ui->horizontalSlider_expi->setValue((int)(100.0*(arg1-ui->doubleSpinBox_expi->minimum())/(ui->doubleSpinBox_expi->maximum()-ui->doubleSpinBox_expi->minimum())));
    ui->horizontalSlider_expi->blockSignals(false);
    envoie_trame_config(4);
}

void MainWindow::on_horizontalSlider_expi_valueChanged(int value)
{
    ui->doubleSpinBox_expi->setValue(round(20.0*(ui->doubleSpinBox_expi->minimum()+value*(ui->doubleSpinBox_expi->maximum()-ui->doubleSpinBox_expi->minimum())/100.0))/20.0);
}

//void MainWindow::clear_clicked()
//{
//    clear_series();
//}

void MainWindow::on_Enregistrer_courbes_clicked()
{
    int i;
    QFile fichiercsv;
    QString filename;
    filename=QFileDialog::getSaveFileName();// fd->directory().path()+"/fichiercsv.csv");
    fichiercsv.setFileName(filename);

    if (fichiercsv.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream stream(&fichiercsv);
        //stream.setLocale(QLocale("fr"));
        stream << "OMYXAir \r\n" << heure.currentDateTime().toString("dd MMMM yyyy - hh:mm:ss")<<"\r\n";

        stream << "temps (sec); Pression (cmH2O); Debit (L/min)\r\n"          ;
        for(i=0;i<serie_pression->count();i++)
        {
            stream << static_cast<double>(serie_pression->at(i).x())<<";"<< static_cast<double>(serie_pression->at(i).y())<<";"<< static_cast<double>(serie_debit->at(i).y())<<";"<<"\r\n" ;
        }
                stream << ui->info->toPlainText(); //.replace("\n\n"," - ") <<"\r\n" ;
        fichiercsv.close();
    }
}


//Gestion affichage alarme min max
void MainWindow::on_freq_min_editingFinished()
{
    if(ui->freq_min->value()>ui->freq_max->value())
    {
        ui->freq_min->setValue(ui->freq_max->value());
        ui->label_freq->setStyleSheet(COLOR_orange);
        ui->freq_min->setStyleSheet(COLOR_orange);
        ui->freq_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_freq->setStyleSheet("");
        ui->freq_min->setStyleSheet("");
        ui->freq_max->setStyleSheet("");
    }
}

void MainWindow::on_freq_max_editingFinished()
{
    if(ui->freq_max->value()<ui->freq_min->value())
    {
        ui->freq_max->setValue(ui->freq_min->value());
        ui->label_freq->setStyleSheet(COLOR_orange);
        ui->freq_min->setStyleSheet(COLOR_orange);
        ui->freq_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_freq->setStyleSheet("");
        ui->freq_min->setStyleSheet("");
        ui->freq_max->setStyleSheet("");
    }
}

void MainWindow::on_vt_min_editingFinished()
{
    if(ui->vt_min->value()>ui->vt_max->value())
    {
        ui->vt_min->setValue(ui->vt_max->value());
        ui->label_vt->setStyleSheet(COLOR_orange);
        ui->vt_min->setStyleSheet(COLOR_orange);
        ui->vt_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_vt->setStyleSheet("");
        ui->vt_min->setStyleSheet("");
        ui->vt_max->setStyleSheet("");
    }
}
void MainWindow::on_vt_max_editingFinished()
{
    if(ui->vt_max->value()<ui->vt_min->value())
    {
        ui->vt_max->setValue(ui->vt_min->value());
        ui->label_vt->setStyleSheet(COLOR_orange);
        ui->vt_min->setStyleSheet(COLOR_orange);
        ui->vt_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_vt->setStyleSheet("");
        ui->vt_min->setStyleSheet("");
        ui->vt_max->setStyleSheet("");
    }

}

void MainWindow::on_pression_min_editingFinished()
{
    if(ui->pression_min->value()>ui->pression_max->value())
    {
        ui->pression_min->setValue(ui->pression_max->value());
        ui->label_pression->setStyleSheet(COLOR_orange);
        ui->pression_min->setStyleSheet(COLOR_orange);
        ui->pression_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_pression->setStyleSheet("");
        ui->pression_min->setStyleSheet("");
        ui->pression_max->setStyleSheet("");
    }
}

void MainWindow::on_pression_max_editingFinished()
{
    if(ui->pression_max->value()<ui->pression_min->value())
    {
        ui->pression_max->setValue(ui->pression_min->value());
        ui->label_pression->setStyleSheet(COLOR_orange);
        ui->pression_min->setStyleSheet(COLOR_orange);
        ui->pression_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_pression->setStyleSheet("");
        ui->pression_min->setStyleSheet("");
        ui->pression_max->setStyleSheet("");
    }
}

void MainWindow::on_debit_min_editingFinished()
{
    if(ui->debit_min->value()>ui->debit_max->value())
    {
        ui->debit_min->setValue(ui->debit_max->value());
        ui->label_debit->setStyleSheet(COLOR_orange);
        ui->debit_min->setStyleSheet(COLOR_orange);
        ui->debit_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_debit->setStyleSheet("");
        ui->debit_min->setStyleSheet("");
        ui->debit_max->setStyleSheet("");
    }
}

void MainWindow::on_debit_max_editingFinished()
{
    if(ui->debit_max->value()<ui->debit_min->value())
    {
        ui->debit_max->setValue(ui->debit_min->value());
        ui->label_debit->setStyleSheet(COLOR_orange);
        ui->debit_min->setStyleSheet(COLOR_orange);
        ui->debit_max->setStyleSheet(COLOR_orange);
    }
    else
    {
        ui->label_debit->setStyleSheet("");
        ui->debit_min->setStyleSheet("");
        ui->debit_max->setStyleSheet("");
    }
}
