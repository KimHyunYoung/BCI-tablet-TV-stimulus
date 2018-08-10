#ifndef LIGHTWINDOW_H
#define LIGHTWINDOW_H

#include <QMainWindow>
#include <light.h>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <Qstring>
#include <QElapsedTimer>
namespace Ui {
class lightwindow;
}

class lightwindow : public QMainWindow
{
    Q_OBJECT
signals:
    void start();
    void received();
    void started();
public:
    explicit lightwindow(QWidget *parent = 0);
    /////////////////////////////////////////
    //function

    ///////////////////////////////////////
    ~lightwindow();

private slots:
    /////////////////////////////
    /// slot function
    void closeEvent(QCloseEvent * event);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_spinBox_valueChanged(double arg1);
    void on_spinBox_2_valueChanged(double arg1);
    void on_spinBox_6_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void on_spinBox_8_valueChanged(int arg1);
    void on_spinBox_9_valueChanged(int arg1);
    void on_spinBox_10_valueChanged(int arg1);
    void on_spinBox_11_valueChanged(int arg1);
    void lightonoff_sequence();
    void destroyed();
    void positionone();
    void positiontwo();
    void positionthree();
    void positionfour();
    void send1();
    void send2();
    void send3();
    void send4();
    void send11();
    void send12();
    void send13();
    void restart();
    void serverstart();
    void newConnection();
    void readyRead();
    void sendansw();
    void ifdistroyed();
private:
    Ui::lightwindow *ui;
    ////////////////////////////
    /// object
    QTimer *timer;
    QElapsedTimer *totaltimer;
    light *lig;
    //////////////////////////////
    /// variable
    int isEND = 0;
    float dark = 75;
    float flash = 75;
    int training = 50;
    int testing = 30;
    int repeat = 10;
    int timercheck = 0;
    int nowtime = 0;
    int elapsed = 0;
    int timedebug = 0;
    bool wait = false;
    bool nowtraining = true;
    QString ip = "192.168.0.6";
    int status = 0;
    int result;
    bool receive = false;
    int one = 10;
    int two = 7;
    int three = 3;
    int randsequence;
    QTcpSocket *socket;
    QTcpServer *server;
    QTcpSocket *client;
    ///////////////////////////////


};

#endif // LIGHTWINDOW_H
