#ifndef LIGHT_H
#define LIGHT_H

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
#include <QMediaRecorder>
#include <QCamera>
#include <Qimage>
#include <QtextStream>
#include <QFile>
#include <QPixmap>

typedef short _stdcall(*inpfuncPtr)(short portaddr);
typedef void _stdcall(*oupfuncPtr)(short portaddr, short datnum);

namespace Ui {
class light;
}

class light : public QMainWindow
{
    Q_OBJECT
signals:
    void sendanswer();
    void receiving();
    void end();
    void triggersignal1();
    void triggersignal2();
    void triggersignal3();
    void triggersignal4();
    void triggersignal11();
    void triggersignal12();
    void triggersignal13();
    void signalone();
    void signaltwo();
    void signalthree();
    void signalfour();
    void gotopart2();
    void nextblink();
    void endblin();
    void startagain();
    void destroyeverything();
public:
    explicit light(QWidget *parent = 0);
    /////////////////////////////////////////
    /// function
    void Init_QLabels();
    void blink_rand();
    void setting_target_label(int answer);
    void take_info(int dark, int flash,  bool nowtrain, int nowtime, int stat, int repeat, bool wait);
    QString currentDateTime();
    ///////////////////////////////////////////
    /// object
    QVideoWidget *vwin5;
    QCamera *cameralight;
    QLabel *v1, *v2, *v3, *v4, *i1, *i2, *i3, *i4;
    QLabel *t11, *t12, *t21, *t22, *t31, *t32, *t41, *t42;
    QPixmap *p1, *p2, *p3, *p4;
    QImage *i11, *i22, *i33, *i44, *v11, *v22, *v33, *v44, *i111,*i222,*i333,*i444,*v111,*v222,*v333,*v444;
    QTimer *timer;
    /////////////////////////////////////////////
    /// variable
    QString nowroute;
    int results[4];
    int ans = 0;
    int interval = 0;
    int result = -1;
    bool received = false;
    int training = 50;
    ////////////////////////////////////////////
    ~light();
private slots:
    void closeEvent(QCloseEvent * event);
    void blink();
    void finish();
    void allocate_image(int trial);
    void set_answer_sheet();
    void imageset(int location, int imagefile);
    void target_show();
    void target_hide();
    void showans1();
    void showans2();
    void showans3();
    void showans4();
    void sendans();
    void hideall();
    void positionone();
    void positiontwo();
    void positionthree();
    void positionfour();
    void emit11();
    void emit12();
    void emit13();
    void emit1();
    void emit2();
    void emit3();
    void emit4();
    void restart();
    void setans();
    void before_blinking();
    void part1();
    void part15();
    void part2();
    void emitblink();
private:
    Ui::light *ui;
    ////////////////////////////////////////////
    /// variable
    QRect screenGeo;
    bool errorFlag;
    int Dark= 150, Flash= 150; // 단위 : ms
    int sender;
    int Hscreen, Wscreen;
    int *ran_num;
    bool check = false;

    bool nowtraining = true;
    bool wait = false;
    int IDX;
    int Finl = 0;
    int randomlight = 0;
    int repeats = 10;
    int status = 0; // 0 = off, 1 = halfon, 2 =full on
    int portData = 0;

    int *anslist;
    //////////////////////////////////////////
    /// object
    QLabel *prepare, *Xcross, *AnsWin, *after, *Final, *waitscreen;
    QScreen *screen;
    //////////////////////////////////////////
};

#endif // LIGHT_H
