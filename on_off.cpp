#include "on_off.h"
#include "ui_on_off.h"
#include <QDebug>
#include <QThread>


On_Off::On_Off(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::On_Off)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showMaximized();
    connect(this, SIGNAL(blinkend()), this, SLOT(blink()));
    connect(this, SIGNAL(end()),this,SLOT(resultpage()));
     srand(time(NULL));
     init_Video();
     init_VideoWidget();
    AssignLoc();
    Init_QLabels();
    hLib = LoadLibraryA("inpout32.dll");
    if(hLib == NULL)
    {
        errorFlag = true;
        QMessageBox::warning(this,"Error", "LoadLibrary Failed: inpout32.dll");
        return;
    }

    inp32 = (inpfuncPtr) GetProcAddress(hLib, "Inp32");

    if(inp32 == NULL)
    {
        errorFlag = true;
        QMessageBox::warning(this,"Error", "GetProcAddress for Inp32 Failed");
        return;
    }

    oup32 = (oupfuncPtr) GetProcAddress(hLib, "Out32");

    if(oup32 == NULL)
    {
        errorFlag = true;
        QMessageBox::warning(this,"Error","GetProcAddress for Out32 Failed");
    }
    bool ok;
    portNumber = portName.toInt(&ok,16);
}

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

On_Off::~On_Off()
{
    disconnect(this, SIGNAL(blinkend()), this, SLOT(blink()));
    disconnect(this, SIGNAL(end()),this,SLOT(resultpage()));
        delete ran_num;
        delete number;
        delete number2;
        delete prepare;
        delete Xcross;
        delete after;
        delete video1;
        delete video2;
        delete video3;
        delete video4;
        delete vwin1;
        delete vwin2;
        delete vwin3;
        delete vwin4;
    delete ui;
}

void On_Off::closeEvent(QCloseEvent * event)
{

    delete this;
}
void On_Off::Init_QLabels()
{
    v11 = new QLabel(this);
    v12 = new QLabel(this);
    v21 = new QLabel(this);
    v22 = new QLabel(this);
    v31 = new QLabel(this);
    v32 = new QLabel(this);
    v41 = new QLabel(this);
    v42 = new QLabel(this);

    v11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v12->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v21->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v31->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v32->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v41->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    v42->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));

    v11->setGeometry(0,0,Hscreen/50,vwin1->geometry().height()*2/3);
    v12->setGeometry(0,0,vwin1->geometry().height()*2/3,Hscreen/50);
    v21->setGeometry(Wscreen-Hscreen/50,0,Hscreen/50,vwin2->geometry().height()*2/3);
    v22->setGeometry(Wscreen-(vwin2->geometry().height()*2/3),0,vwin2->geometry().height()*2/3,Hscreen/50);
    v31->setGeometry(0,Hscreen-(vwin3->geometry().height()*2/3),Hscreen/50,vwin3->geometry().height()*2/3);
    v32->setGeometry(0,Hscreen-Hscreen/50,vwin3->geometry().height()*2/3,Hscreen/50);
    v41->setGeometry(Wscreen-Hscreen/50,Hscreen-(vwin4->geometry().height()*2/3),Hscreen/50,vwin4->geometry().height()*2/3);
    v42->setGeometry(Wscreen-(vwin4->geometry().height()*2/3),Hscreen-Hscreen/50,vwin4->geometry().height()*2/3,Hscreen/50);

    QFont ansFont("Arial", 32);
    QFont ansFont2("Arial", 20);
    number = new QLabel(this); // 현재 횟수 세팅
    number2 = new QLabel(this); // 시간 디버그
    number->setFont(ansFont);
    number->setStyleSheet("QLabel {background-color : black; color : white;}");
    number->setGeometry(vwin3->x()+vwin3->width()+20, vwin3->y(), vwin3->width()- 80, vwin3->height()/2);
    number->setAlignment(Qt::AlignCenter);
    number2->setText(QString("time\n flash = %1ms, dark = %2ms").arg(timeflash).arg(timedark));
    number2->setFont(ansFont2);
    number2->setStyleSheet("QLabel {background-color : black; color : white;}");
    number2->setGeometry(vwin3->x()+vwin3->width()+20, vwin3->y()+ vwin3->height()/2, vwin3->width()- 80, vwin3->height()/2);
    number2->setAlignment(Qt::AlignCenter);
    prepare = new QLabel(this);
    prepare->setText("잠시 뒤에 시작 됩니다. + 를 봐주세요");
    QFont font("Arial", 36);
    prepare->setFont(font);
    prepare->setStyleSheet("QLabel {background-color : white; color : black;}");
    prepare->setGeometry(this->geometry());
    prepare->setAlignment(Qt::AlignCenter);
    Xcross = new QLabel(this);
    Xcross->setText("+");
    QFont xfont("Arial", 70);
    Xcross->setFont(xfont);
    Xcross->setStyleSheet("QLabel {background-color : black; color : white;}");
    Xcross->setGeometry(vwin1->x()+vwin1->width(),vwin1->y() + vwin1->height(), vwin2->x()-vwin1->x()-vwin1->width(),vwin3->y()-vwin1->y()-vwin1->height());
    Xcross->setAlignment(Qt::AlignCenter);
    after = new QLabel(this);
    after->setAlignment(Qt::AlignCenter);
    after->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
    after->setGeometry(prepare->geometry());
    waitscreen = new QLabel(this);
    waitscreen->setAlignment(Qt::AlignCenter);
    waitscreen->setStyleSheet("QLabel {background-color : black; color : white;}");
    waitscreen->setText("사용자의 패턴을 학습중입니다 \n 잠시만 기다려주세요");
    waitscreen-> setFont(ansFont);
    waitscreen->setGeometry(this->geometry());
    timer = new QTimer(this);
    ran_num = new int[100 * 4];
}
void On_Off::stim_trigger(int trigval)
{
    (oup32)(portNumber,trigval);
    Sleeper::msleep(2);
    (oup32)(portNumber,0);
    Sleeper::msleep(2);
}

void On_Off::stim_delay()
{
    Sleeper::msleep(5);
    (oup32)(portNumber,0);
    Sleeper::msleep(5);
}
void On_Off::trigger1()
{
    (oup32)(portNumber,11);
    stim_delay();
}
void On_Off::trigger2()
{
    (oup32)(portNumber,12);
    stim_delay();
}
void On_Off::trigger3()
{
    (oup32)(portNumber,13);
    stim_delay();
}
void On_Off::triggerans0(){
    (oup32)(portNumber,1);
    stim_delay();
}
void On_Off::triggerans1(){
    (oup32)(portNumber,2);
    stim_delay();
}
void On_Off::triggerans2(){
    (oup32)(portNumber,3);
    stim_delay();
}
void On_Off::triggerans3(){
    (oup32)(portNumber,4);
    stim_delay();
}
void On_Off::triggercorrect(){
    (oup32)(portNumber,1);
    stim_delay();
}
void On_Off::triggerincorrect(){
   (oup32)(portNumber,2);
    stim_delay();
}

void On_Off::show_rand()
{
    if(wait && Fin != 0){
        qDebug() << "wait";
        waitscreen->show();
       connect(this,SIGNAL(startagain()),this,SLOT(part1()));
    }
    else{
        part1();
    }
}
void On_Off::randomans(int trial){
    int i,j;
    for(i=0; i<trial; i++)
    {
        for(j=0; j<4; j++)
        {
            int idx = i*4+j;
            ran_num[idx] = j;
        }
    }
    srand(time(NULL));
    for(i=0; i<trial; i++)
    {
        for(j=0; j<4; j++)
        {
            int idx = i*4+j;
            int randIdx = i*4+(rand()%4);
            int t = ran_num[idx];
            ran_num[idx] = ran_num[randIdx];
            ran_num[randIdx] = t;
        }
    }

    for(i=1; i<trial; i++)
    {
        int prevIdx = (i-1)*4 + 3;
        int presIdx = i*4;
        if(ran_num[prevIdx] == ran_num[presIdx])
        {
            int t= ran_num[presIdx];
            ran_num[presIdx] = ran_num[presIdx+1];
            ran_num[presIdx+1] = t;
        }
    }

}
void On_Off::part1(){
    disconnect(this,SIGNAL(startagain()),this,SLOT(part1()));
    waitscreen->hide();
    wait = false;
    AssignLoc();
    video1->setPosition(playingonoff);
    video1->play();
    video1->setMuted(true);
    video2->setPosition(playingonoff);
    video2->play();
    video2->setMuted(true);
    video3->setPosition(playingonoff);
    video3->play();
    video3->setMuted(true);
    video4->setPosition(playingonoff);
    video4->play();
    video4->setMuted(true);
    randomans(trial);
    ////////////////////////////////////////////////////////
    ans = ran_num[0];
    qDebug() << ans;
    target_set(ans, Wscreen/3, Hscreen/3);
    if(training)number->setText(QString("training\n%1").arg(Fin+1));
    else number->setText(QString("testing\n%1").arg(Fin+1));
///////////////////////////////////////////////////////////////////////////////
    if(Fin == 0 && training){
        timer->singleShot(interval,prepare,SLOT(show()));
        interval = 3000;
        timer->singleShot(interval,prepare,SLOT(hide()));
        timer->singleShot(interval,Xcross,SLOT(show()));
    }
    else{
        interval = 10;
        timer->singleShot(interval,Xcross,SLOT(show()));
    }
    if(debug)timer->singleShot(interval,number,SLOT(show()));
    if(debug)timer->singleShot(interval,number2,SLOT(show()));
//////////////////////////////////////////////////////////////////////
    interval += 500;
    timer->singleShot(interval,Xcross,SLOT(hide()));
    timer->singleShot(interval,vwin1,SLOT(show()));
    timer->singleShot(interval,vwin2,SLOT(show()));
    timer->singleShot(interval,vwin3,SLOT(show()));
    timer->singleShot(interval,vwin4,SLOT(show()));
    timer->singleShot(interval,this,SLOT(target_show()));
    Sleeper::msleep(5);
    timer->singleShot(interval,this,SLOT(trigger1()));//목표 줄때 트리거
//////////////////////////////////////////////////////////////////////
    interval +=500;
    switch(ans){
    case 0:
        timer->singleShot(interval,this,SLOT(triggerans0()));
        break;
    case 1:
        timer->singleShot(interval,this,SLOT(triggerans1()));
        break;
    case 2:
        timer->singleShot(interval,this,SLOT(triggerans2()));
        break;
    case 3:
        timer->singleShot(interval,this,SLOT(triggerans3()));
        break;
    }
    interval += 2000;
    timer->singleShot(interval,this,SLOT(target_hide()));
    if(debug) timer->singleShot(interval,number,SLOT(hide()));
    interval += Dark;
    timer->singleShot(interval,v11,SLOT(hide()));
    timer->singleShot(interval,v12,SLOT(hide()));
    timer->singleShot(interval,v21,SLOT(hide()));
    timer->singleShot(interval,v22,SLOT(hide()));
    timer->singleShot(interval,v31,SLOT(hide()));
    timer->singleShot(interval,v32,SLOT(hide()));
    timer->singleShot(interval,v41,SLOT(hide()));
    timer->singleShot(interval,v42,SLOT(hide()));
    timer->singleShot(interval,this,SLOT(trigger2())); //목표 준 후 트리거
    IDX = 0;
    timer->singleShot(interval,this,SLOT(emitblink()));
}
void On_Off::emitblink(){
    emit blinkend();
}
void On_Off::resultpage(){
    timer->start(0);
    interval = 100;

    timer->singleShot(interval,after,SLOT(show()));
    timer->singleShot(interval,video1,SLOT(pause()));
    timer->singleShot(interval,vwin1,SLOT(hide()));
    timer->singleShot(interval,video2,SLOT(pause()));
    timer->singleShot(interval,vwin2,SLOT(hide()));
    timer->singleShot(interval,video3,SLOT(pause()));
    timer->singleShot(interval,vwin3,SLOT(hide()));
    timer->singleShot(interval,video4,SLOT(pause()));
    timer->singleShot(interval,vwin4,SLOT(hide()));

    interval += 500;
    timer->singleShot(interval+500,this,SLOT(trigger3())); // 트라이얼 끝난 후 트리거
    timer->singleShot(interval,this,SLOT(setting_answer()));
    Fin++;
}

void On_Off::setting_answer(){
    qDebug() << training << " training ";
    if(training == false && received == false ) {
      connect(this, SIGNAL(receiving()),this,SLOT(trainingdivider()));
    }
    else {
        trainingdivider();
    }
}

void On_Off::trainingdivider(){
    if(training == false ) {
      disconnect(this, SIGNAL(receiving()),this,SLOT(trainingdivider()));
    }
    qDebug() <<"setting answer : ";
    if(training == false) ans = result;
    qDebug() << ans;
    received = false;
    interval = 10;
    timer->start(0);
        ////////////////////////////////////////////////////////////
        timer->singleShot(interval,after,SLOT(hide()));
        if(debug)timer->singleShot(interval,number2,SLOT(hide()));
        timer->singleShot(interval,this,SLOT(vWindow_show()));
        if(!training){
            if(ans == ran_num[0]){
                timer->singleShot(interval+1500,this,SLOT(triggercorrect()));
            }
            else{
                timer->singleShot(interval+1500,this,SLOT(triggerincorrect()));
            }
        }
        ////////////////////////////////////////////////////////////

        if(ans == 0)
        {
            timer->singleShot(interval,vwin1,SLOT(show()));
        }
        else if(ans == 1)
        {
            timer->singleShot(interval,vwin2,SLOT(show()));
        }
        else if(ans == 2)
        {
           timer->singleShot(interval,vwin3,SLOT(show()));
        }
        else if(ans == 3)
        {
            timer->singleShot(interval, vwin4, SLOT(show()));
        }
        timer->singleShot(interval,video1,SLOT(play()));
        timer->singleShot(interval,video2,SLOT(play()));
        timer->singleShot(interval,video3,SLOT(play()));
        timer->singleShot(interval,video4,SLOT(play()));
        interval += 3000;
        if(ans == 0)
        {
            timer->singleShot(interval,vwin1,SLOT(hide()));
        }
        else if(ans == 1)
        {
            timer->singleShot(interval,vwin2,SLOT(hide()));
        }
        else if(ans == 2)
        {
           timer->singleShot(interval,vwin3,SLOT(hide()));
        }
        else if(ans == 3)
        {
            timer->singleShot(interval, vwin4, SLOT(hide()));
        }
        timer->singleShot(interval,video1,SLOT(pause()));
        timer->singleShot(interval,video2,SLOT(pause()));
        timer->singleShot(interval,video3,SLOT(pause()));
        timer->singleShot(interval,video4,SLOT(pause()));
        timer->singleShot(interval,this,SLOT(starting()));
}

void On_Off::starting(){
    qDebug() <<"start trigger";
    wait = false;
    delete video1;
    delete video2;
    delete video3;
    delete video4;
    delete vwin1;
    delete vwin2;
    delete vwin3;
    delete vwin4;
    init_Video();
    init_VideoWidget();
    emit emitting();
}

void On_Off::vWindow_show()
{
    if(ans == 0)
    {
        vwin1->setGeometry(prepare->geometry());
    }
    else if(ans == 1)
    {
        vwin2->setGeometry(prepare->geometry());
    }
    else if(ans == 2)
    {
        vwin3->setGeometry(prepare->geometry());
    }
    else if(ans == 3)
    {
        vwin4->setGeometry(prepare->geometry());
    }
}

void On_Off::finish()
{
    v11->hide();
    v12->hide();
    v21->hide();
    v22->hide();
    v31->hide();
    v32->hide();
    v41->hide();
    v42->hide();
     emit end();
}



void On_Off::blink()
{
    if(IDX == 4 * trial){
    timer->singleShot(Flash, this, SLOT(finish()));
    qDebug() << "end trigger";
    return;
    }
    switch(check){
    case 0:
        v11->hide();
        v12->hide();
        v21->hide();
        v22->hide();
        v31->hide();
        v32->hide();
        v41->hide();
        v42->hide();
        check = 1;
        portData = 0;

        break;
    case 1:
        if(rowcol){
            switch(ran_num[IDX]){
            case 0:
                v11->show();
                v12->show();
                v21->show();
                v22->show();
                triggerans0();
                break;
            case 1:
                v31->show();
                v32->show();
                v41->show();
                v42->show();
                triggerans1();
                break;
            case 2:
                v11->show();
                v12->show();
                v31->show();
                v32->show();
                triggerans2();
                break;
            case 3:
                v21->show();
                v22->show();
                v41->show();
                v42->show();
                triggerans3();
                break;
            }
            check = 0;
            IDX++;
        }
        else
        {
            switch(ran_num[IDX]){
                case 0:
                v11->show();
                v12->show();
                triggerans0();
                break;
            case 1:
                v21->show();
                v22->show();
                triggerans1();
                break;
            case 2:
                v31->show();
                v32->show();
                triggerans2();
                break;
            case 3:
                v41->show();
                v42->show();
                triggerans3();
                break;
            }
            check = 0;
            IDX++;

        }
        break;
    }
    switch(check){
    case 0:
        timer->singleShot(Flash,this,SLOT(emitblink()));
        break;
    case 1:
        timer->singleShot(Dark,this,SLOT(emitblink()));
        break;
    }
}
void On_Off::take_color_info(int Fcolor, int Bcolor)
{
    fgscale = Fcolor;
    bgscale = Bcolor;
}

void On_Off::take_info(int dark, int flash, QString PORTNAME, QString FILEPATH, bool RC ,bool bug, int control, bool train, int trials)
{
    Dark = dark;
    Flash = flash;
    portName = PORTNAME;
    filePath = FILEPATH;
    rowcol = RC;
    debug = bug;
    result = control;
    training = train;
    trial = trials;
}

void On_Off::init_Video()
{
    this->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
                                     //////////////////////////////////////////////
    video1 = new QMediaPlayer(this); //VIDEO1                              VIDEO2//
    video2 = new QMediaPlayer(this); //                                          //
    video3 = new QMediaPlayer(this); //VIDEO3                              VIDEO4//
    video4 = new QMediaPlayer(this); //////////////////////////////////////////////
    vwin1 = new QVideoWidget(this);
    vwin2 = new QVideoWidget(this);
    vwin3 = new QVideoWidget(this);
    vwin4 = new QVideoWidget(this);
}

void On_Off::init_VideoWidget()
{

    randoms = rand()%4;
    switch(randoms){
    case 0:
        video1->setVideoOutput(vwin1);
        video2->setVideoOutput(vwin2);
        video3->setVideoOutput(vwin3);
        video4->setVideoOutput(vwin4);
        break;
    case 1:
        video2->setVideoOutput(vwin1);
        video3->setVideoOutput(vwin2);
        video4->setVideoOutput(vwin3);
        video1->setVideoOutput(vwin4);
        break;
    case 2:
        video3->setVideoOutput(vwin1);
        video4->setVideoOutput(vwin2);
        video1->setVideoOutput(vwin3);
        video2->setVideoOutput(vwin4);
        break;
    case 3:
        video4->setVideoOutput(vwin1);
        video1->setVideoOutput(vwin2);
        video2->setVideoOutput(vwin3);
        video3->setVideoOutput(vwin4);
        break;
    }
    video2->setMedia(QUrl::fromLocalFile("video/Drama.wmv"));
    video3->setMedia(QUrl::fromLocalFile("video/Entertain.wmv"));
    video4->setMedia(QUrl::fromLocalFile("video/Travel.wmv"));
    video1->setMedia(QUrl::fromLocalFile("video/Newsroom.wmv"));

}

void On_Off::AssignLoc()
{
    screen = QGuiApplication::primaryScreen();
    screenGeo = screen->geometry();
    Hscreen = screenGeo.height();
    Wscreen = screenGeo.width();
    this->resize(Wscreen,Hscreen);

    vwin1->setGeometry(screenGeo.x()+Hscreen/50, screenGeo.y()+Hscreen/50, Wscreen/3, Hscreen/3);
    vwin2->setGeometry((2*Wscreen/3)-Hscreen/50,screenGeo.y()+Hscreen/50,Wscreen/3,Hscreen/3);
    vwin3->setGeometry(screenGeo.x()+Hscreen/50,(2*Hscreen/3)-Hscreen/50,Wscreen/3,Hscreen/3);
    vwin4->setGeometry((2*Wscreen)/3-Hscreen/50,(2*Hscreen/3)-Hscreen/50,Wscreen/3,Hscreen/3);
}

void On_Off::target_set(int answer,int wid, int hei){
    t11 = new QLabel(this);
    t12 = new QLabel(this);
    t21 = new QLabel(this);
    t22 = new QLabel(this);
    t31 = new QLabel(this);
    t32 = new QLabel(this);
    t41 = new QLabel(this);
    t42 = new QLabel(this);
    t11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t12->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t21->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t31->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t32->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t41->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));
    t42->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(234).arg(230).arg(70));

    switch(answer){
    case 0:
        t11->setGeometry(vwin1->x(),vwin1->y(),Hscreen/50,hei*1/3);
        t12->setGeometry(vwin1->x(),vwin1->y(),wid*1/3,Hscreen/50);
        t21->setGeometry(vwin1->x()+wid-Hscreen/50,vwin1->y(),Hscreen/50,hei*1/3);
        t22->setGeometry(vwin1->x()+wid*2/3,vwin1->y(),wid*1/3,Hscreen/50);
        t31->setGeometry(vwin1->x(),vwin1->y()+hei*2/3,Hscreen/50,hei*1/3);
        t32->setGeometry(vwin1->x(),vwin1->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        t41->setGeometry(vwin1->x()+wid-Hscreen/50,vwin1->y() + hei*2/3,Hscreen/50,hei/3);
        t42->setGeometry(vwin1->x()+wid*2/3,vwin1->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        break;
    case 1:
        t11->setGeometry(vwin2->x(),vwin2->y(),Hscreen/50,hei*1/3);
        t12->setGeometry(vwin2->x(),vwin2->y(),wid*1/3,Hscreen/50);
        t21->setGeometry(vwin2->x()+wid-Hscreen/50,vwin2->y(),Hscreen/50,hei*1/3);
        t22->setGeometry(vwin2->x()+wid*2/3,vwin2->y(),wid*1/3,Hscreen/50);
        t31->setGeometry(vwin2->x(),vwin2->y()+hei*2/3,Hscreen/50,hei*1/3);
        t32->setGeometry(vwin2->x(),vwin2->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        t41->setGeometry(vwin2->x()+wid-Hscreen/50,vwin2->y() + hei*2/3,Hscreen/50,hei/3);
        t42->setGeometry(vwin2->x()+wid*2/3,vwin2->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        break;
    case 2:
        t11->setGeometry(vwin3->x(),vwin3->y(),Hscreen/50,hei*1/3);
        t12->setGeometry(vwin3->x(),vwin3->y(),wid*1/3,Hscreen/50);
        t21->setGeometry(vwin3->x()+wid-Hscreen/50,vwin3->y(),Hscreen/50,hei*1/3);
        t22->setGeometry(vwin3->x()+wid*2/3,vwin3->y(),wid*1/3,Hscreen/50);
        t31->setGeometry(vwin3->x(),vwin3->y()+hei*2/3,Hscreen/50,hei*1/3);
        t32->setGeometry(vwin3->x(),vwin3->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        t41->setGeometry(vwin3->x()+wid-Hscreen/50,vwin3->y() + hei*2/3,Hscreen/50,hei/3);
        t42->setGeometry(vwin3->x()+wid*2/3,vwin3->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        break;
    case 3:
        t11->setGeometry(vwin4->x(),vwin4->y(),Hscreen/50,hei*1/3);
        t12->setGeometry(vwin4->x(),vwin4->y(),wid*1/3,Hscreen/50);
        t21->setGeometry(vwin4->x()+wid-Hscreen/50,vwin4->y(),Hscreen/50,hei*1/3);
        t22->setGeometry(vwin4->x()+wid*2/3,vwin4->y(),wid*1/3,Hscreen/50);
        t31->setGeometry(vwin4->x(),vwin4->y()+hei*2/3,Hscreen/50,hei*1/3);
        t32->setGeometry(vwin4->x(),vwin4->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        t41->setGeometry(vwin4->x()+wid-Hscreen/50,vwin4->y() + hei*2/3,Hscreen/50,hei/3);
        t42->setGeometry(vwin4->x()+wid*2/3,vwin4->y()+hei-Hscreen/50,wid/3,Hscreen/50);
        break;
    }
}
void On_Off::target_show(){
    t11->show();
    t12->show();
    t21->show();
    t22->show();
    t31->show();
    t32->show();
    t41->show();
    t42->show();
}
void On_Off::target_hide(){
    t11->hide();
    t12->hide();
    t21->hide();
    t22->hide();
    t31->hide();
    t32->hide();
    t41->hide();
    t42->hide();
}
