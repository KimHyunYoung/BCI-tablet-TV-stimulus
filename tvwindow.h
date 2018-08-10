#ifndef TVWINDOW_H
#define TVWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QFile>
#include "on_off.h"
#include "motion_onset.h"
namespace Ui {
class tvWindow;
}

class tvWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tvWindow(QWidget *parent = 0);
    QTcpServer *tcpServer;
    QTcpSocket *client;
    QUdpSocket *udpsocket;
    On_Off *onoff;
    bool rowcol = false;
     QTimer *timer,*emittimer;
    void server_start();
    ~tvWindow();
public slots:
    void start_next();
    void setting_flick();
private slots:
    void init_flick_labels();

    void set_flicker_color();
    void set_BGW_color();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_radioButton_clicked();
    void on_radioButton_3_clicked();

    void on_spinBox_valueChanged(double arg1);
    void on_spinBox_2_valueChanged(double arg1);

    void newConnection();

private slots:
    void delaystart();
    void update_BGscale();
    void on_spinBox_6_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void on_spinBox_8_valueChanged(int arg1);
    void on_spinBox_9_valueChanged(int arg1);
    void on_spinBox_10_valueChanged(int arg1);
    void on_spinBox_11_valueChanged(int arg1);
    void destroyed();

    void onoff_sequence();
    void readyRead();
signals:
    void started();
    void startagain();
private:
    Ui::tvWindow *ui;
    bool sti_type; //true == On-Off, false == Motion-Onset//
    bool ba = true;
    bool debug = false;

    bool training = true;
    int velo = 500;
    int active = 150;
    int inactive = 150;
    int trainnum = 50;
    int testnum = 30;
    int Fin = 0;
    int randoms = 0;
    int randsequence = 0;
    bool TCP = true;
    bool teststart = false;
    bool wait;
    int trial = 10;
    qint64 playingonoff = 0;
    QString filepath;
    QString portname = "C010";


    Motion_Onset *mo;
    int time_interval;

    int isEND = 0;

    double dark = 150;
    double flash = 150;

    int FGscale = 255;
    int BGscale = 0;
    int one = 10;
    int two = 7;
    int three = 3;

    int result = 0;
    bool alreadystart = false;
    QSlider *flicker, *BGW;
    QLabel *F_label, *B_label;

};

#endif // TVWINDOW_H
