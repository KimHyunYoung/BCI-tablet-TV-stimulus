#ifndef ON_OFF_H
#define ON_OFF_H

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
#include <sys/time.h>
#include <stdlib.h>
#include <QMessageBox>

typedef short _stdcall(*inpfuncPtr)(short portaddr);
typedef void _stdcall(*oupfuncPtr)(short portaddr, short datnum);

namespace Ui {
class On_Off;
}

class On_Off : public QMainWindow
{
    Q_OBJECT

public:
    explicit On_Off(QWidget *parent = 0);
    ~On_Off();
    void take_info(int dark, int flash, QString PORTNAME, QString FILEPATH,bool RC , bool debug, int control, bool training, int trials);
    void init_Video();
    void init_VideoWidget();
    void AssignLoc();
    void Init_QLabels();
    void take_color_info(int Fcolor,int Bcolor);
    void show_rand();
    void target_set(int answer, int wid, int hei);
    int interval = 0;
    int result = 0;
    bool received = false;
    int Fin = 0;
    int randoms = 0;
    bool wait = false;
    bool endtag = false;
    qint64 playingonoff = 0;
    QMediaPlayer *video1, *video2, *video3, *video4;
    QVideoWidget *vwin1, *vwin2, *vwin3, *vwin4;
    QLabel *v11, *v12, *v21, *v22, *v31, *v32, *v41, *v42;
    QLabel *t11, *t12, *t21, *t22, *t31, *t32, *t41, *t42;
    QTimer *timer;
signals:
    void emitting();
    void end();
    void receiving();
    void shutdown();
    void blinkend();
    void startagain();
private slots:
    void blink();
    void part1();
    void finish();
    void target_show();
    void target_hide();
    void vWindow_show();
    void resultpage();
    void setting_answer();
    void starting();
    void trainingdivider();
    void emitblink();
    void trigger1();
    void trigger2();
    void trigger3();
    void triggerans0();
    void triggerans1();
    void triggerans2();
    void triggerans3();
    void triggercorrect();
    void triggerincorrect();
    void stim_delay();
    void stim_trigger(int val);
    void closeEvent(QCloseEvent * event);
    void randomans(int trial);
private:

    //QLibrary pPortDLL;
    int IDX, ans;
    QRect screenGeo;

    int Hscreen, Wscreen;
    int *ran_num;
    Ui::On_Off *ui;
    double Dark, Flash;
    int fgscale, bgscale;
    int prev=-1;
    int timeflash = 0;
    int timedark = 0;
    int timeone = 0;
    int timetwo = 0;
    int check = 0;
    int trial = 10;
    bool debug = false;
    bool rowcol = false;
    bool training = true;

    QLabel *prepare, *Xcross, *AnsWin, *after, *Final, *number, *number2, *waitscreen;
    QScreen *screen;

    QString filePath;
    HINSTANCE hLib;
    inpfuncPtr inp32;
    oupfuncPtr oup32;

    QString portName = "C010";
    short portData;
    int portNumber;
    bool errorFlag;
    clock_t clock1, clock2;
};

#endif // ON_OFF_H
