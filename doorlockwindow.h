#ifndef DOORLOCKWINDOW_H
#define DOORLOCKWINDOW_H

#include <QMainWindow>
#include <doorlock.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QString>
namespace Ui {
class doorlockwindow;
}

class doorlockwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit doorlockwindow(QWidget *parent = 0);
    /////////////////////////////////////////
    //function

    ///////////////////////////////////////
    ~doorlockwindow();
signals:
   void started();
   void received();
private slots:
    /////////////////////////////
    /// slot function
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void dooronoff_sequence();
    void opencatch();
    void serverstart();
    void on_spinBox_valueChanged(double arg1);
    void on_spinBox_2_valueChanged(double arg1);
    void on_spinBox_6_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void on_spinBox_8_valueChanged(int arg1);
    void on_spinBox_9_valueChanged(int arg1);
    void on_spinBox_10_valueChanged(int arg1);
    void on_spinBox_11_valueChanged(int arg1);
    void newConnection();
    void readyRead();
    void send1();
    void send2();
    void send3();
    void send4();
    void send11();
    void send12();
    void send13();
    void send25();
    void restart();
    void destroyed();
private:
    Ui::doorlockwindow *ui;
    ////////////////////////////
    /// object
    QTimer *timer;
    doorlock *doo;
    QTcpServer *server;
    QTcpSocket *client;
    QTcpSocket *socket;
    //////////////////////////////
    /// variable
    int time_interval;
    int isEND = 0;
    double dark = 150;
    double flash = 150;
    QString ip = "10.16.27.208";
    bool status = false;
    bool nowtraining = true;
    bool wait;
    int repeat = 10;
    int result = 0;
    int one = 10;
    int two = 7;
    int three = 3;
    int trainnum = 50;
    int testnum = 30;
    int randsequence = 0;
    ///////////////////////////////


};

#endif // DOORLOCKWINDOW_H
