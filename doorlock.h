#ifndef DOORLOCK_H
#define DOORLOCK_H

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
#include <QMediaRecorder>
#include <QCamera>
#include <Qimage>
#include <stdlib.h>
#include <QPixmap>
#include <QtSerialPort/QSerialPort>


typedef short _stdcall(*inpfuncPtr)(short portaddr);
typedef void _stdcall(*oupfuncPtr)(short portaddr, short datnum);

namespace Ui {
class doorlock;
}

class doorlock : public QMainWindow
{
    Q_OBJECT
signals:
    void receiving();
    void end();
    void startagain();
    void opensignal();
    void triggersignal1();
    void triggersignal2();
    void triggersignal3();
    void triggersignal4();
    void triggersignal11();
    void triggersignal12();
    void triggersignal13();
    void triggersignal25();
    void nextblink();
    void endblink();
public:
    explicit doorlock(QWidget *parent = 0);
    /////////////////////////////////////////
    /// function
    void Init_QLabels();
    void blink_rand();
    void setting_target_label(int answer);
    void take_info(int dark, int flash,  bool nowtrain, int nowtime, bool status, int repeat, bool wai, int resu);
    void writedata();

    int ans;
    ///////////////////////////////////////////
    /// object
    QVideoWidget *vwin5;
    QCamera *camera;
    QLabel *v1, *v2, *v3, *v4, *i1, *i2, *i3, *i4;
    QLabel *t11, *t12, *t21, *t22, *t31, *t32, *t41, *t42;
    QPixmap *p1, *p2, *p3, *p4;
    QImage *i11, *i22, *i33, *i44, *v11, *v22, *v33, *v44, *i111, *i222, *i333, *i444, *v111, *v222, *v333, *v444;
    QTimer *timer;
    /////////////////////////////////////////////
    /// variable
    int interval = 0;
    bool received = false;
    int result;
    ////////////////////////////////////////////
    ~doorlock();
private slots:
    void closeEvent(QCloseEvent * event);
    void blink();
    void finish();
    void open_close();
    void part0();
    void part1();
    void part15();
    void part2();
    void connectionend();
    void allocate_image(int answer);
    void setanswer(int repeat);
    void target_show();
    void target_hide();
    void emittingend();
    void emit11();
    void emit12();
    void emit13();
    void emit1();
    void emit2();
    void emit3();
    void emit4();
    void emit25();
    void showans1();
    void showans2();
    void showans3();
    void showans4();
    void emitblink();
    void correct();
    void incorrect();
private:
    Ui::doorlock *ui;
    ////////////////////////////////////////////
    /// variable
    QRect screenGeo;
    short portData;
    int portNumber;
    // variable for port interface
    bool errorFlag;
    int Dark = 75, Flash = 75;
    int Hscreen, Wscreen;
    int repeats = 10;
    int *ran_num;
    bool check = false;
    int IDX, FinD;
    bool wait;
    bool status = false;
    bool nowtraining = false;
    QSerialPort *port;
    //////////////////////////////////////////
    /// object
    QLabel *prepare, *Xcross, *AnsWin, *after, *Final , *waitscreen;
    QScreen *screen;
    //////////////////////////////////////////
};

#endif // DOORLOCK_H
