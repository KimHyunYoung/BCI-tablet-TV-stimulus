#include "motion_onset.h"
#include "ui_motion_onset.h"

int Fins = 0;
int random = 0;
qint64 playing = 0;
Motion_Onset::Motion_Onset(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Motion_Onset)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showMaximized();
    /*hLib = LoadLibraryA("inpout32.dll");
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
*/
}

Motion_Onset::~Motion_Onset()
{
    delete ui;
}

void Motion_Onset::init_label(){
    Q1 = new QLabel(this);
    Q2 = new QLabel(this);
    Q3 = new QLabel(this);
    Q4 = new QLabel(this);
    Q11 = new QLabel(this);
    Q22 = new QLabel(this);
    Q33 = new QLabel(this);
    Q44 = new QLabel(this);
    int q1_1 = rand()%128 + 128;
    int q1_2 = rand()%128 + 128;
    int q1_3 = rand()%128 + 128;
    int q2_1 = rand()%128 + 128;
    int q2_2 = rand()%128 + 128;
    int q2_3 = rand()%128 + 128;
    int q3_1 = rand()%128 + 128;
    int q3_2 = rand()%128 + 128;
    int q3_3 = rand()%128 + 128;
    int q4_1 = rand()%128 + 128;
    int q4_2 = rand()%128 + 128;
    int q4_3 = rand()%128 + 128;
    Q1->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q1_1).arg(q1_2).arg(q1_3));
    Q2->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q2_1).arg(q2_2).arg(q2_3));
    Q3->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q3_1).arg(q3_2).arg(q3_3));
    Q4->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q4_1).arg(q4_2).arg(q4_3));
    Q11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q1_1).arg(q1_2).arg(q1_3));
    Q22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q2_1).arg(q2_2).arg(q2_3));
    Q33->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q3_1).arg(q3_2).arg(q3_3));
    Q44->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(q4_1).arg(q4_2).arg(q4_3));
    Q1->setGeometry(vwin5->x() + 20, vwin5->y() + vwin5->height() + 20 , 20, 40);
    Q2->setGeometry(vwin6->x() + 20, vwin6->y() + vwin6->height() + 20 , 20, 40);
    Q3->setGeometry(vwin7->x() + 20, vwin7->y() + vwin7->height() + 20 , 20, 40);
    Q4->setGeometry(vwin8->x() + 20, vwin8->y() + vwin8->height() + 20 , 20, 40);
    if(bar){
        Q11->setGeometry(vwin5->x(), vwin5->y() + vwin5->height() + 20 , 20, 40);
        Q22->setGeometry(vwin6->x(), vwin6->y() + vwin6->height() + 20 , 20, 40);
        Q33->setGeometry(vwin7->x(), vwin7->y() + vwin7->height() + 20 , 20, 40);
        Q44->setGeometry(vwin8->x(), vwin8->y() + vwin8->height() + 20 , 20, 40);
    }
    else{
        Q11->setGeometry(vwin5->x() + vwin5->width()/2 - 20, vwin5->y() + vwin5->height() + 20 , 40, 80);
        Q22->setGeometry(vwin6->x() + vwin6->width()/2 - 20, vwin6->y() + vwin6->height() + 20 , 40, 80);
        Q33->setGeometry(vwin7->x() + vwin7->width()/2 - 20, vwin7->y() + vwin7->height() + 20 , 40, 80);
        Q44->setGeometry(vwin8->x() + vwin8->width()/2 - 20, vwin8->y() + vwin8->height() + 20 , 40, 80);
    }
    v1 = new QPropertyAnimation(Q1, "geometry");
    v2 = new QPropertyAnimation(Q2, "geometry");
    v3 = new QPropertyAnimation(Q3, "geometry");
    v4 = new QPropertyAnimation(Q4, "geometry");
    v1->setDuration(Active);
    v2->setDuration(Active);
    v3->setDuration(Active);
    v4->setDuration(Active);
    if(bar){
        v1->setStartValue(QRect(vwin5->x() + 20, vwin5->y() + vwin5->height() + 20 , 20, 40));
        v2->setStartValue(QRect(vwin6->x() + 20, vwin6->y() + vwin6->height() + 20 , 20, 40));
        v3->setStartValue(QRect(vwin7->x() + 20, vwin7->y() + vwin7->height() + 20 , 20, 40));
        v4->setStartValue(QRect(vwin8->x() + 20, vwin8->y() + vwin8->height() + 20 , 20, 40));
        v1->setEndValue(QRect(vwin5->x() + ((V*vwin5->width())/640)/(1000/Active) + 20 ,vwin5->y() + vwin5->height() + 20 , 20, 40));
        v2->setEndValue(QRect(vwin6->x() + ((V*vwin6->width())/640)/(1000/Active) + 20 ,vwin6->y() + vwin6->height() + 20 , 20, 40));
        v3->setEndValue(QRect(vwin7->x() + ((V*vwin7->width())/640)/(1000/Active) + 20 ,vwin7->y() + vwin7->height() + 20 , 20, 40));
        v4->setEndValue(QRect(vwin8->x() + ((V*vwin8->width())/640)/(1000/Active) + 20 ,vwin8->y() + vwin8->height() + 20 , 20, 40));
    }
    else{
        v1->setStartValue(QRect(vwin5->x() + vwin5->width()/2 - 20, vwin5->y() + vwin5->height() + 20 , 40, 80));
        v2->setStartValue(QRect(vwin6->x() + vwin6->width()/2 - 20, vwin6->y() + vwin6->height() + 20 , 40, 80));
        v3->setStartValue(QRect(vwin7->x() + vwin7->width()/2 - 20, vwin7->y() + vwin7->height() + 20 , 40, 80));
        v4->setStartValue(QRect(vwin8->x() + vwin8->width()/2 - 20, vwin8->y() + vwin8->height() + 20 , 40, 80));
        v1->setEndValue(QRect(vwin5->x()+ vwin5->width()/2 - 40, vwin5->y() + 20 + vwin5->height() + 20 , 80, 40));
        v2->setEndValue(QRect(vwin6->x()+ vwin6->width()/2 - 40, vwin6->y() + 20 + vwin6->height() + 20 , 80, 40));
        v3->setEndValue(QRect(vwin7->x()+ vwin7->width()/2 - 40, vwin7->y() + 20 + vwin7->height() + 20 , 80, 40));
        v4->setEndValue(QRect(vwin8->x()+ vwin8->width()/2 - 40, vwin8->y() + 20 + vwin8->height() + 20 , 80, 40));
    }

}

void Motion_Onset::move(){
    if(check){
        timer->setInterval(Inactive);
        if(ran_num[Ind - 1]==0)
        {
            portData = 5;
        }
        else if(ran_num[Ind - 1]==1)
        {
            portData = 6;
        }
        else if(ran_num[Ind - 1]==2)
        {
            portData = 7;
        }
        else if(ran_num[Ind - 1]==3)
        {
            portData = 8;
        }
        check = false;
    }
    else{
        timer->setInterval(Active);
        timer->singleShot(0,Q1,SLOT(hide()));
        timer->singleShot(0,Q2,SLOT(hide()));
        timer->singleShot(0,Q3,SLOT(hide()));
        timer->singleShot(0,Q4,SLOT(hide()));
        timer->singleShot(0,Q11,SLOT(show()));
        timer->singleShot(0,Q22,SLOT(show()));
        timer->singleShot(0,Q33,SLOT(show()));
        timer->singleShot(0,Q44,SLOT(show()));
        if(ran_num[Ind]==0)
        {
            timer->singleShot(0,Q1,SLOT(show()));
            timer->singleShot(0,Q11,SLOT(hide()));
            timer->singleShot(0,v1,SLOT(start()));
            portData = 1;
        }
        else if(ran_num[Ind]==1)
        {
            timer->singleShot(0,Q2,SLOT(show()));
            timer->singleShot(0,Q22,SLOT(hide()));
            timer->singleShot(0,v2,SLOT(start()));
            portData = 2;
        }
        else if(ran_num[Ind]==2)
        {
            timer->singleShot(0,Q3,SLOT(show()));
            timer->singleShot(0,Q33,SLOT(hide()));
            timer->singleShot(0,v3,SLOT(start()));
            portData = 3;
        }
        else if(ran_num[Ind]==3)
        {
            timer->singleShot(0,Q4,SLOT(show()));
            timer->singleShot(0,Q44,SLOT(hide()));
            timer->singleShot(0,v4,SLOT(start()));
            portData = 4;
        }
        Ind++;
        check = true;
    }

    /*//portDataa++;
    (oup32)(portNumber,0);
    //portData = 0;
    (oup32)(portNumber,portData);*/

    if(Ind == 40){
        off();
        timer->stop();
    }
}

void Motion_Onset::trigger1()
{
    portData = 0;
    (oup32)(portNumber,portData);

    portData = 11;
    (oup32)(portNumber,portData);
}


void Motion_Onset::trigger2()
{
    portData = 0;
    (oup32)(portNumber,portData);

    portData = 12;
    (oup32)(portNumber,portData);
}


void Motion_Onset::trigger3()
{
    portData = 0;
    (oup32)(portNumber,portData);

    portData = 13;
    (oup32)(portNumber,portData);
}

void Motion_Onset::off(){
    v1->stop();
    v2->stop();
    v3->stop();
    v4->stop();
    Q1->hide();
    Q2->hide();
    Q3->hide();
    Q4->hide();
    Q11->hide();
    Q22->hide();
    Q33->hide();
    Q44->hide();
}
void Motion_Onset::vWindow_show()
{
    if(ans == 0)
    {
        vwin5->setGeometry(prepare->geometry());
    }
    else if(ans == 1)
    {
        vwin6->setGeometry(prepare->geometry());
    }
    else if(ans == 2)
    {
        vwin7->setGeometry(prepare->geometry());
    }
    else if(ans == 3)
    {
        vwin8->setGeometry(prepare->geometry());
    }
}
void Motion_Onset::move_rand(){
    srand(time(NULL));
    init_Video();
    init_VideoWidget();
    AssignLoc();
    init_label();

    video2->setPosition(playing);
    video2->play();
    video2->setMuted(true);
    video3->setPosition(playing);
    video3->play();
    video3->setMuted(true);
    video4->setPosition(playing);
    video4->play();
    video4->setMuted(true);
    video1->setPosition(playing);
    video1->play();
    video1->setMuted(true);
    playing += (Active + Inactive) * 40 + 10500;
    if(playing > 150000 - (Active + Inactive) * 40 + 10500){
        playing = 0;
    }
    timer = new QTimer(this);

    ran_num = new int[40];
    int i,j;
    bool ok;
    portNumber = portName.toInt(&ok,16);
    for(i=0; i<10; i++)
    {
        for(j=0; j<4; j++)
        {
            int idx = i*4+j;
            ran_num[idx] = j;
        }
    }
     for(i=0; i<10; i++)
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
     for(i=1; i<10; i++)
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
     ans = ran_num[0];

     QFont ansFont("Arial", 32);
     target_set(ans, Wscreen/3, Hscreen/3);
     number = new QLabel(this);
     number->setText(QString("%1").arg(Fins+1));
     number->setFont(ansFont);
     number->setStyleSheet("QLabel {background-color : black; color : white;}");
     number->setGeometry((vwin7->x() + vwin8->x())/2 + vwin7->width()/2 - 20, vwin7->y()+vwin7->height() - 100, 100, 100);

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
     Xcross->setGeometry(vwin5->x()+vwin5->width(),vwin5->y() + vwin5->height(), vwin6->x()-vwin5->x()-vwin5->width(),vwin7->y()-vwin5->y()-vwin5->height());
     Xcross->setAlignment(Qt::AlignCenter);

     if(Fins == 0)
     prepare->show();
     interval = 0;
//////////////////////////////////////////////////////////////
     if(Fins == 0){
         interval = 3000;
         timer->singleShot(interval,Xcross,SLOT(show()));
         timer->singleShot(interval,prepare,SLOT(hide()));
         if(debug)timer->singleShot(interval,number,SLOT(show()));

     }
     else{
         interval = 0;
         timer->singleShot(interval,Xcross,SLOT(show()));
         timer->singleShot(interval,prepare,SLOT(hide()));
         if(debug)timer->singleShot(interval,number,SLOT(show()));
     }
////////////////////////////////////////////////////////////////
     interval += 500;
     timer->singleShot(interval,this,SLOT(target_show()));
     timer->singleShot(interval,Xcross,SLOT(hide()));
     //timer->singleShot(interval,this,SLOT(trigger1())); // 목표 줄때 트리거
////////////////////////////////////////////////////////////////
     interval += 2500;
     timer->singleShot(interval,this,SLOT(target_hide()));
     if(debug)timer->singleShot(interval,number,SLOT(hide()));
     //timer->singleShot(interval,this,SLOT(trigger2())); // 목표 준 후 트리거
     interval+= Inactive;
////////////////////////////////////////////////////////////////
     Ind = 0;
     connect(timer, SIGNAL(timeout()), this, SLOT(move()));
     timer->start(Inactive + interval);
     interval += (Active + Inactive) * 40 + 1000;
     after = new QLabel(this);
     after->setAlignment(Qt::AlignCenter);
     after->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
     after->setGeometry(prepare->geometry());
     timer->singleShot(interval,after,SLOT(show()));
     timer->singleShot(interval,this, SLOT(off()));
     timer->singleShot(interval,video1,SLOT(pause()));
     timer->singleShot(interval,vwin5,SLOT(hide()));
     timer->singleShot(interval,video2,SLOT(pause()));
     timer->singleShot(interval,vwin6,SLOT(hide()));
     timer->singleShot(interval,video3,SLOT(pause()));
     timer->singleShot(interval,vwin7,SLOT(hide()));
     timer->singleShot(interval,video4,SLOT(pause()));
     timer->singleShot(interval,vwin8,SLOT(hide()));
     //timer->singleShot(interval,this,SLOT(trigger3()));
     //portDataa++;
     interval += 500;
     timer->singleShot(interval,after,SLOT(hide()));
     timer->singleShot(interval,this,SLOT(vWindow_show()));
     //portDataa++;
     if(ans == 0)
     {
         timer->singleShot(interval,vwin5,SLOT(show()));
         switch(random){
         case 0:
             timer->singleShot(interval,video1,SLOT(play()));
             break;
         case 1:
             timer->singleShot(interval,video4,SLOT(play()));
             break;
         case 2:
             timer->singleShot(interval,video3,SLOT(play()));
             break;
         case 3:
             timer->singleShot(interval,video2,SLOT(play()));
             break;
         }
     }
     else if(ans == 1)
     {
         timer->singleShot(interval,vwin6,SLOT(show()));
         switch(random){
         case 0:
             timer->singleShot(interval,video2,SLOT(play()));
             break;
         case 1:
             timer->singleShot(interval,video1,SLOT(play()));
             break;
         case 2:
             timer->singleShot(interval,video4,SLOT(play()));
             break;
         case 3:
             timer->singleShot(interval,video3,SLOT(play()));
             break;
         }
     }
     else if(ans == 2)
     {
        timer->singleShot(interval,vwin7,SLOT(show()));
        switch(random){
        case 0:
            timer->singleShot(interval,video3,SLOT(play()));
            break;
        case 1:
            timer->singleShot(interval,video2,SLOT(play()));
            break;
        case 2:
            timer->singleShot(interval,video1,SLOT(play()));
            break;
        case 3:
            timer->singleShot(interval,video4,SLOT(play()));
            break;
        }
     }
     else if(ans == 3)
     {
         timer->singleShot(interval, vwin8, SLOT(show()));
         switch(random){
         case 0:
             timer->singleShot(interval,video4,SLOT(play()));
             break;
         case 1:
             timer->singleShot(interval,video3,SLOT(play()));
             break;
         case 2:
             timer->singleShot(interval,video2,SLOT(play()));
             break;
         case 3:
             timer->singleShot(interval,video1,SLOT(play()));
             break;
         }
     }
     interval += 3000;
     if(ans == 0)
     {
         timer->singleShot(interval,vwin5,SLOT(hide()));
         switch(random){
         case 0:
             timer->singleShot(interval,video1,SLOT(pause()));
             break;
         case 1:
             timer->singleShot(interval,video4,SLOT(pause()));
             break;
         case 2:
             timer->singleShot(interval,video3,SLOT(pause()));
             break;
         case 3:
             timer->singleShot(interval,video2,SLOT(pause()));
             break;
         }
     }
     else if(ans == 1)
     {
         timer->singleShot(interval,vwin6,SLOT(hide()));
         switch(random){
         case 0:
             timer->singleShot(interval,video2,SLOT(pause()));
             break;
         case 1:
             timer->singleShot(interval,video1,SLOT(pause()));
             break;
         case 2:
             timer->singleShot(interval,video4,SLOT(pause()));
             break;
         case 3:
             timer->singleShot(interval,video3,SLOT(pause()));
             break;
         }
     }
     else if(ans == 2)
     {
        timer->singleShot(interval,vwin7,SLOT(hide()));
        switch(random){
        case 0:
            timer->singleShot(interval,video3,SLOT(pause()));
            break;
        case 1:
            timer->singleShot(interval,video2,SLOT(pause()));
            break;
        case 2:
            timer->singleShot(interval,video1,SLOT(pause()));
            break;
        case 3:
            timer->singleShot(interval,video4,SLOT(pause()));
            break;
        }
     }
     else if(ans == 3)
     {
         timer->singleShot(interval, vwin8, SLOT(hide()));
         switch(random){
         case 0:
             timer->singleShot(interval,video4,SLOT(pause()));
             break;
         case 1:
             timer->singleShot(interval,video3,SLOT(pause()));
             break;
         case 2:
             timer->singleShot(interval,video2,SLOT(pause()));
             break;
         case 3:
             timer->singleShot(interval,video1,SLOT(pause()));
             break;
         }
     }
     Fins++;
}

void Motion_Onset::take_info(int VELO, int ACTIVE, int INACTIVE, QString PORTNAME, bool ba, bool bug)
{
    V = VELO;
    Active = ACTIVE;
    Inactive = INACTIVE;
    portName = PORTNAME;
    bar = ba;
    debug = bug;
}


void Motion_Onset::init_Video()
{
    this->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
    vwin1 = new QVideoWidget(this);
    vwin2 = new QVideoWidget(this);
    vwin3 = new QVideoWidget(this);
    vwin4 = new QVideoWidget(this);
    vwin5 = new QVideoWidget(this);
    vwin6 = new QVideoWidget(this);
    vwin7 = new QVideoWidget(this);
    vwin8 = new QVideoWidget(this);
}
void Motion_Onset::init_VideoWidget(){
    video1 = new QMediaPlayer(this);
    video2 = new QMediaPlayer(this);
    video3 = new QMediaPlayer(this);
    video4 = new QMediaPlayer(this);

    video1->setMedia(QUrl::fromLocalFile("video/Newsroom.wmv"));
    video2->setMedia(QUrl::fromLocalFile("video/Drama.wmv"));
    video3->setMedia(QUrl::fromLocalFile("video/Entertain.wmv"));
    video4->setMedia(QUrl::fromLocalFile("video/Travel.wmv"));

    random = 0;

    switch(random){
     case 0:

        video2->setVideoOutput(vwin6);
        video3->setVideoOutput(vwin7);
        video4->setVideoOutput(vwin8);
        video1->setVideoOutput(vwin5);
        break;
    case 1:

        video2->setVideoOutput(vwin7);
        video3->setVideoOutput(vwin8);
        video4->setVideoOutput(vwin5);
        video1->setVideoOutput(vwin6);
        break;
    case 2:

        video2->setVideoOutput(vwin8);
        video3->setVideoOutput(vwin5);
        video4->setVideoOutput(vwin6);
        video1->setVideoOutput(vwin7);
        break;
    case 3:

        video2->setVideoOutput(vwin5);
        video3->setVideoOutput(vwin6);
        video4->setVideoOutput(vwin7);
        video1->setVideoOutput(vwin8);
        break;
    }
}


void Motion_Onset::AssignLoc()
{
    screen = QGuiApplication::primaryScreen();
    screenGeo = screen->geometry();
    Hscreen = screenGeo.height();
    Wscreen = screenGeo.width();
    this->resize(Wscreen,Hscreen);
    vwin5->show();
    vwin6->show();
    vwin7->show();
    vwin8->show();
    vwin5->show();
    vwin5->setGeometry((2*Wscreen/3)-20,screenGeo.y()+20,Wscreen/3,Hscreen/3);
    vwin6->setGeometry((2*Wscreen/3)-20,screenGeo.y()+20,Wscreen/3,Hscreen/3);
    vwin7->setGeometry(screenGeo.x()+20,(2*Hscreen/3)-120,Wscreen/3,Hscreen/3);
    vwin8->setGeometry((2*Wscreen)/3-20,(2*Hscreen/3)-120,Wscreen/3,Hscreen/3);
    vwin5->setGeometry(screenGeo.x()+20, screenGeo.y()+20, Wscreen/3,Hscreen/3);

}
void Motion_Onset::target_set(int answer,int wid, int hei){
    t11 = new QLabel(this);
    t12 = new QLabel(this);
    t21 = new QLabel(this);
    t22 = new QLabel(this);
    t31 = new QLabel(this);
    t32 = new QLabel(this);
    t41 = new QLabel(this);
    t42 = new QLabel(this);
    t11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t12->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t21->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t31->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t32->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t41->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t42->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));

    switch(answer){
    case 0:
        t11->setGeometry(vwin5->x(),vwin5->y(),20,hei*1/3);
        t12->setGeometry(vwin5->x(),vwin5->y(),wid*1/3,20);
        t21->setGeometry(vwin5->x()+wid-20,vwin5->y(),20,hei*1/3);
        t22->setGeometry(vwin5->x()+wid*2/3,vwin5->y(),wid*1/3,20);
        t31->setGeometry(vwin5->x(),vwin5->y()+hei*2/3,20,hei*1/3);
        t32->setGeometry(vwin5->x(),vwin5->y()+hei-20,wid/3,20);
        t41->setGeometry(vwin5->x()+wid-20,vwin5->y() + hei*2/3,20,hei/3);
        t42->setGeometry(vwin5->x()+wid*2/3,vwin5->y()+hei-20,wid/3,20);
        break;
    case 1:
        t11->setGeometry(vwin6->x(),vwin6->y(),20,hei*1/3);
        t12->setGeometry(vwin6->x(),vwin6->y(),wid*1/3,20);
        t21->setGeometry(vwin6->x()+wid-20,vwin6->y(),20,hei*1/3);
        t22->setGeometry(vwin6->x()+wid*2/3,vwin6->y(),wid*1/3,20);
        t31->setGeometry(vwin6->x(),vwin6->y()+hei*2/3,20,hei*1/3);
        t32->setGeometry(vwin6->x(),vwin6->y()+hei-20,wid/3,20);
        t41->setGeometry(vwin6->x()+wid-20,vwin6->y() + hei*2/3,20,hei/3);
        t42->setGeometry(vwin6->x()+wid*2/3,vwin6->y()+hei-20,wid/3,20);
        break;
    case 2:
        t11->setGeometry(vwin7->x(),vwin7->y(),20,hei*1/3);
        t12->setGeometry(vwin7->x(),vwin7->y(),wid*1/3,20);
        t21->setGeometry(vwin7->x()+wid-20,vwin7->y(),20,hei*1/3);
        t22->setGeometry(vwin7->x()+wid*2/3,vwin7->y(),wid*1/3,20);
        t31->setGeometry(vwin7->x(),vwin7->y()+hei*2/3,20,hei*1/3);
        t32->setGeometry(vwin7->x(),vwin7->y()+hei-20,wid/3,20);
        t41->setGeometry(vwin7->x()+wid-20,vwin7->y() + hei*2/3,20,hei/3);
        t42->setGeometry(vwin7->x()+wid*2/3,vwin7->y()+hei-20,wid/3,20);
        break;
    case 3:
        t11->setGeometry(vwin8->x(),vwin8->y(),20,hei*1/3);
        t12->setGeometry(vwin8->x(),vwin8->y(),wid*1/3,20);
        t21->setGeometry(vwin8->x()+wid-20,vwin8->y(),20,hei*1/3);
        t22->setGeometry(vwin8->x()+wid*2/3,vwin8->y(),wid*1/3,20);
        t31->setGeometry(vwin8->x(),vwin8->y()+hei*2/3,20,hei*1/3);
        t32->setGeometry(vwin8->x(),vwin8->y()+hei-20,wid/3,20);
        t41->setGeometry(vwin8->x()+wid-20,vwin8->y() + hei*2/3,20,hei/3);
        t42->setGeometry(vwin8->x()+wid*2/3,vwin8->y()+hei-20,wid/3,20);
        break;
    }
}
void Motion_Onset::target_show(){
    t11->show();
    t12->show();
    t21->show();
    t22->show();
    t31->show();
    t32->show();
    t41->show();
    t42->show();
}
void Motion_Onset::target_hide(){
    t11->hide();
    t12->hide();
    t21->hide();
    t22->hide();
    t31->hide();
    t32->hide();
    t41->hide();
    t42->hide();
}

