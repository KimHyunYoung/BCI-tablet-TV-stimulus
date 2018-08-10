#ifndef MOTION_ONSET_H
#define MOTION_ONSET_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaControl>
#include <QVideoWidget>
#include <QLabel>
#include <cstdlib>
#include <QTimer>
#include <ctime>
#include <QLayout>
#include <QScreen>
#include <windows.h>
#include <QMessageBox>
#include <stdlib.h>
#include <QPropertyAnimation>

typedef short _stdcall(*inpfuncPtr)(short portaddr);
typedef void _stdcall(*oupfuncPtr)(short portaddr, short datnum);

namespace Ui {
class Motion_Onset;
}

class Motion_Onset : public QMainWindow
{
    Q_OBJECT

public:
    explicit Motion_Onset(QWidget *parent = 0);
    void take_info(int VELO, int ACTIVE, int INACTIVE, QString PORTNAME, bool bar, bool bug);
    void init_Video();
    void init_VideoWidget();
    void AssignLoc();
    void init_label();
    void move_rand();
    void target_set(int answer, int wid, int hei);
    int interval = 0;
    QPropertyAnimation *v1, *v2, *v3, *v4;
    QLabel *Q1, *Q2, *Q3, *Q4;
    QLabel *Q11, *Q22, *Q33, *Q44;
    QLabel *t11, *t12, *t21, *t22, *t31, *t32, *t41, *t42;
    QMediaPlayer *video1, *video2, *video3, *video4, *video5;
    QVideoWidget *vwin1, *vwin2, *vwin3, *vwin4, *vwin5, *vwin6, *vwin7, *vwin8;
    QTimer *timer;
    ~Motion_Onset();
private slots:
    void move();
    void off();
    void vWindow_show();
    void target_show();
    void target_hide();
    void trigger1();
    void trigger2();
    void trigger3();

private:
    Ui::Motion_Onset *ui;
    int Ind, ans;
    int V, Active, Inactive;
    bool check = false;
    bool bar = true;
    bool debug = false;
    int *ran_num;
    QLabel *prepare, *Xcross, *AnsWin, *after, *Final, *number;
    QScreen *screen;
    QRect screenGeo;
    int Hscreen, Wscreen;
    QString filePath;
    HINSTANCE hLib;
    inpfuncPtr inp32;
    oupfuncPtr oup32;
    QString portName;
    bool errorFlag;
    short portData;
    int portNumber;
};

#endif // MOTION_ONSET_H
