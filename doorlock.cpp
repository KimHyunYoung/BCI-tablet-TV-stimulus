#include "doorlock.h"
#include "ui_doorlock.h"

doorlock::doorlock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doorlock)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showMaximized();
    Init_QLabels();
    port = new QSerialPort();
    port->setPortName("COM3");
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    if(!port->open(QIODevice::ReadWrite)){
        qDebug() << "not connected";
    }
    else{
        qDebug() << "connected";
    }
}

void doorlock::closeEvent(QCloseEvent * event)
{
    delete this;
}
doorlock::~doorlock()
{
    port->close();
    delete ui;
}
void doorlock::setanswer(int repeats){
    ran_num = new int[repeats*4];
    int i,j;
    for(i=0; i<repeats; i++)
    {
        for(j=0; j<4; j++)
        {
            int idx = i*4+j;
            ran_num[idx] = j;
        }
    }
    srand(time(NULL));
    for(i=0; i<repeats; i++)
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

    for(i=1; i<repeats; i++)
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
}

void doorlock::blink_rand(){

    if(wait && FinD != 0){
        waitscreen->show();
        connect(this,SIGNAL(startagain()),this,SLOT(part0()));
    }
    else{
        part0();
    }
}
void doorlock::part0(){
    disconnect(this,SIGNAL(startagain()),this,SLOT(part0()));
    waitscreen->hide();
    wait = false;
    qDebug() << "this trial is " << FinD + 1 << "th time";
     this->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
    setanswer(repeats);
    allocate_image(ans);
    setting_target_label(ans);
     if(FinD == 0)
     prepare->show();
     //portDataa++;
 ////////////////////////////////////////////////////////////////////
     if(FinD == 0){
         interval = 3000;
         timer->singleShot(interval,prepare,SLOT(hide()));
         timer->singleShot(interval,Xcross,SLOT(show()));

     }
     else{
         interval = 0;
         timer->singleShot(interval,prepare,SLOT(hide()));
         timer->singleShot(interval,Xcross,SLOT(show()));
     }
     //portDataa++;
 //////////////////////////////////////////////////////////////////////
     interval += 500;
     timer->singleShot(interval,Xcross,SLOT(hide()));
     timer->singleShot(interval,this,SLOT(target_show()));
     switch(ans){
     case 0:
         timer->singleShot(interval,this,SLOT(showans1()));
         break;
     case 1:
         timer->singleShot(interval,this,SLOT(showans2()));
         break;
     case 2:
         timer->singleShot(interval,this,SLOT(showans3()));
         break;
     case 3:
         timer->singleShot(interval,this,SLOT(showans4()));
         break;
     }
     timer->singleShot(interval,camera,SLOT(start()));
     timer->singleShot(interval,this,SLOT(emit11())); // 목표 줄때 트리거
     switch(ans){
     case 0:
         timer->singleShot(interval+500,this,SLOT(emit1()));
         break;
     case 1:
         timer->singleShot(interval+500,this,SLOT(emit2()));
         break;
     case 2:
         timer->singleShot(interval+500,this,SLOT(emit3()));
         break;
     case 3:
         timer->singleShot(interval+500,this,SLOT(emit4()));
         break;
     }
     //portDataa++;
 //////////////////////////////////////////////////////////////////////
     interval += 2500;
     timer->singleShot(interval,this,SLOT(target_hide()));
     timer->singleShot(interval,this,SLOT(emit12()));
     interval+= Dark;
     //portDataa++;
 //////////////////////////////////////////////////////////////////////

     IDX = 0;

     timer->singleShot(interval,this,SLOT(part1()));

}
void doorlock::part1(){
    connect(this,SIGNAL(nextblink()),this,SLOT(blink()));
    connect(this,SIGNAL(endblink()),this,SLOT(part15()));
    emit nextblink();
}
void doorlock::part15(){
    timer->singleShot(1000,this,SLOT(emit13()));
    qDebug() << "nowtrining = " << nowtraining;
    if(!nowtraining){
        connect(this,SIGNAL(receiving()),this,SLOT(part2()));
    }
    else{
        received = false;
        part2();
    }
}
void doorlock::part2(){
    disconnect(this,SIGNAL(nextblink()),this,SLOT(blink()));
    disconnect(this,SIGNAL(endblink()),this,SLOT(part15()));
    disconnect(this,SIGNAL(receiving()),this,SLOT(part2()));
    qDebug() << " endblink passed";
    timer->start();
    interval =0;
    timer->singleShot(interval,after,SLOT(show()));


    interval += 500;
    qDebug() << " ans " << result << " rannum" << ran_num[0];
    if(ran_num[0] == result || nowtraining){
        timer->singleShot(interval+300,this,SLOT(open_close()));
        timer->singleShot(interval+800,this,SLOT(correct()));
    }
    else{
        timer->singleShot(interval+800,this,SLOT(incorrect()));
    }
    timer->singleShot(interval,after,SLOT(hide()));
    timer->singleShot(interval,Final,SLOT(show()));

    interval += 2000;
    timer->singleShot(interval,Final,SLOT(hide()));
    FinD++;
    timer->singleShot(interval+200,this,SLOT(emittingend()));
}
//////////////////////////////////////////////////////////////////////////////////network function
void doorlock::open_close(){
    emit emit25();
    emit opensignal();
    qDebug() << " send";
}
void doorlock::correct(){
    emit triggersignal1();
}
void doorlock::incorrect(){
    emit triggersignal2();
}
void doorlock::connectionend(){
    port->close();
}
void doorlock::emittingend(){
    emit end();
}
/////////////////////////////////////////////////////////////////////////////////qlabel blink function
///
void doorlock::showans1(){
    v1->show();
}
void doorlock::showans2(){
    v2->show();
}
void doorlock::showans3(){
    v3->show();
}
void doorlock::showans4(){
    v4->show();
}

void doorlock::blink(){
    if(IDX == 4 * repeats){
    timer->singleShot(Flash, this, SLOT(finish()));
    qDebug() << "end trigger";
    return;
    }
    switch(check){
    case true:
        v1->hide();
        v2->hide();
        v3->hide();
        v4->hide();
        i1->show();
        i2->show();
        i3->show();
        i4->show();
        check = false;
        portData = 0;
        break;
    case false:
        timer->setInterval(Flash);
        if(ran_num[IDX]==0)
        {
            i1->hide();
            v1->show();
            portData = 1;
        }
        else if(ran_num[IDX]==1)
        {
            i2->hide();
            v2->show();
            portData = 2;
        }
        else if(ran_num[IDX]==2)
        {
            i3->hide();
            v3->show();
            portData = 3;
        }
        else if(ran_num[IDX]==3)
        {
            i4->hide();
            v4->show();
            portData = 4;
        }
        check = true;
        IDX++;
         break;
    }
    switch(portData){
    case 0:
        break;
    case 1:
        emit triggersignal1();
        break;
    case 2:
        emit triggersignal2();
        break;
    case 3:
        emit triggersignal3();
        break;
    case 4:
        emit triggersignal4();
        break;
    }
    portData = 0;
    switch(check){
    case false:
        timer->singleShot(Flash,this,SLOT(emitblink()));
        break;
    case true:
        timer->singleShot(Dark,this,SLOT(emitblink()));
        break;
    }
}
void doorlock::emitblink(){
    emit nextblink();
}

void doorlock::finish(){
    v1->hide();
    v2->hide();
    v3->hide();
    v4->hide();
    i1->hide();
    i2->hide();
    i3->hide();
    i4->hide();
    emit endblink();
}
void doorlock::target_show(){
    t11->show();
    t12->show();
    t21->show();
    t22->show();
    t31->show();
    t32->show();
    t41->show();
    t42->show();

}
void doorlock::target_hide(){
    t11->hide();
    t12->hide();
    t21->hide();
    t22->hide();
    t31->hide();
    t32->hide();
    t41->hide();
    t42->hide();
}
////////////////////////////////////////////////////////////////////////////////////////////////initialize
///
void doorlock::take_info(int dark, int flash, bool nowtrain, int nowtime, bool stat, int repeat, bool wai, int resu)
{
    Dark = dark;
    Flash = flash;
    nowtraining = nowtrain;
    FinD = nowtime;
    qDebug() <<FinD << "find";
    status = stat;
    repeats = repeat;
    wait = wai;
    result = resu;
}
void doorlock::Init_QLabels()
{
    QFont font("Arial", 36);
    screen = QGuiApplication::primaryScreen();
    screenGeo = screen->geometry();
    Hscreen = screenGeo.height();
    Wscreen = screenGeo.width();
    vwin5 = new QVideoWidget(this);
    vwin5->setGeometry(Hscreen/7,Hscreen/7,Wscreen- Hscreen* 2/7,Hscreen*5/7);
    camera = new QCamera(this);
    camera->setViewfinder(vwin5);
    vwin5->show();
    this->resize(Wscreen,Hscreen);
    i1 = new QLabel(this);
    i2 = new QLabel(this);
    i3 = new QLabel(this);
    i4 = new QLabel(this);
    v1 = new QLabel(this);
    v2 = new QLabel(this);
    v3 = new QLabel(this);
    v4 = new QLabel(this);
    i11 = new QImage();
    i22 = new QImage();
    i33 = new QImage();
    i44 = new QImage();
    v11 = new QImage();
    v22 = new QImage();
    v33 = new QImage();
    v44 = new QImage();
    i111 = new QImage();
    i222 = new QImage();
    i333 = new QImage();
    i444 = new QImage();
    v111 = new QImage();
    v222 = new QImage();
    v333 = new QImage();
    v444 = new QImage();
    t11 = new QLabel(this);
    t12 = new QLabel(this);
    t21 = new QLabel(this);
    t22 = new QLabel(this);
    t31 = new QLabel(this);
    t32 = new QLabel(this);
    t41 = new QLabel(this);
    t42 = new QLabel(this);
    i111->load("image/doorlock.png");
    i222->load("image/dooropen.png");
    i333->load("image/nothing.png");
    i444->load("image/nothing.png");
    v111->load("image/doorlockB.png");
    v222->load("image/dooropenB.png");
    v333->load("image/nothingB.png");
    v444->load("image/nothingB.png");
    *i11=i111->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *i22=i222->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *i33=i333->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *i44=i444->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *v11=v111->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *v22=v222->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *v33=v333->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);
    *v44=v444->scaled(Hscreen/7, Hscreen/7, Qt::KeepAspectRatio);

    v1->setGeometry(screenGeo.x(), screenGeo.y(),Hscreen/7,Hscreen/7);
    v2->setGeometry(Wscreen - Hscreen/7,screenGeo.y() ,Hscreen/7,Hscreen/7);
    v3->setGeometry(screenGeo.x() ,Hscreen  - Hscreen/7,Hscreen/7,Hscreen/7);
    v4->setGeometry(Wscreen - Hscreen/7,Hscreen  - Hscreen/7,Hscreen/7,Hscreen/7);
    i1->setGeometry(screenGeo.x() , screenGeo.y() ,Hscreen/7,Hscreen/7);
    i2->setGeometry(Wscreen - Hscreen/7,screenGeo.y() ,Hscreen/7,Hscreen/7);
    i3->setGeometry(screenGeo.x() ,Hscreen  - Hscreen/7,Hscreen/7,Hscreen/7);
    i4->setGeometry(Wscreen - Hscreen/7,Hscreen  - Hscreen/7,Hscreen/7,Hscreen/7);

    Final = new QLabel(this);
    Final->setStyleSheet("QLabel {background-color : black; color : white;}");
    Final->setFont(font);
    Final->setText("동작 중입니다.");
    Final->setGeometry(screenGeo.x(),screenGeo.y()+Hscreen - 140,Wscreen,120);
    Final->setAlignment(Qt::AlignCenter);
    timer = new QTimer(this);

    prepare = new QLabel(this);
    prepare->setText("잠시 뒤에 시작 됩니다. + 를 봐주세요");

    prepare->setFont(font);
    prepare->setStyleSheet("QLabel {background-color : white; color : black;}");
    prepare->setGeometry(this->geometry());
    prepare->setAlignment(Qt::AlignCenter);
    after = new QLabel(this);
    after->setAlignment(Qt::AlignCenter);
    after->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
    after->setGeometry(prepare->geometry());
    Xcross = new QLabel(this);
    Xcross->setText("+");
    QFont xfont("Arial", 70);
    Xcross->setFont(xfont);
    Xcross->setStyleSheet("QLabel {background-color : black; color : white;}");
    Xcross->setGeometry(Hscreen/7,Hscreen/7,Wscreen- Hscreen* 2/7,Hscreen*5/7);
    Xcross->setAlignment(Qt::AlignCenter);
    waitscreen = new QLabel(this);
    waitscreen->setAlignment(Qt::AlignCenter);
    waitscreen->setStyleSheet("QLabel {background-color : black; color : white;}");
    waitscreen->setText("사용자의 패턴을 학습중입니다 \n 잠시만 기다려주세요");
    waitscreen-> setFont(font);
    waitscreen->setGeometry(this->geometry());
}
void doorlock::allocate_image(int answer){

    qDebug() <<"status = " << status << " and " << answer;
    switch(answer){
    case 0:
        if(status){
            i1->setPixmap(QPixmap::fromImage(*i11));
            i2->setPixmap(QPixmap::fromImage(*i44));
            i3->setPixmap(QPixmap::fromImage(*i33));
            i4->setPixmap(QPixmap::fromImage(*i22));
            v1->setPixmap(QPixmap::fromImage(*v11));
            v2->setPixmap(QPixmap::fromImage(*v44));
            v3->setPixmap(QPixmap::fromImage(*v33));
            v4->setPixmap(QPixmap::fromImage(*v22));
        }
        else{
            i1->setPixmap(QPixmap::fromImage(*i22));
            i2->setPixmap(QPixmap::fromImage(*i44));
            i3->setPixmap(QPixmap::fromImage(*i33));
            i4->setPixmap(QPixmap::fromImage(*i11));
            v1->setPixmap(QPixmap::fromImage(*v22));
            v2->setPixmap(QPixmap::fromImage(*v44));
            v3->setPixmap(QPixmap::fromImage(*v33));
            v4->setPixmap(QPixmap::fromImage(*v11));
        }
        break;
    case 1:
        if(status){
            i1->setPixmap(QPixmap::fromImage(*i44));
            i2->setPixmap(QPixmap::fromImage(*i11));
            i3->setPixmap(QPixmap::fromImage(*i22));
            i4->setPixmap(QPixmap::fromImage(*i33));
            v1->setPixmap(QPixmap::fromImage(*v44));
            v2->setPixmap(QPixmap::fromImage(*v11));
            v3->setPixmap(QPixmap::fromImage(*v22));
            v4->setPixmap(QPixmap::fromImage(*v33));
        }
        else{
            i1->setPixmap(QPixmap::fromImage(*i44));
            i2->setPixmap(QPixmap::fromImage(*i22));
            i3->setPixmap(QPixmap::fromImage(*i11));
            i4->setPixmap(QPixmap::fromImage(*i33));
            v1->setPixmap(QPixmap::fromImage(*v44));
            v2->setPixmap(QPixmap::fromImage(*v22));
            v3->setPixmap(QPixmap::fromImage(*v11));
            v4->setPixmap(QPixmap::fromImage(*v33));
        }
        break;
    case 2:
        if(status){
            i1->setPixmap(QPixmap::fromImage(*i44));
            i2->setPixmap(QPixmap::fromImage(*i22));
            i3->setPixmap(QPixmap::fromImage(*i11));
            i4->setPixmap(QPixmap::fromImage(*i33));
            v1->setPixmap(QPixmap::fromImage(*v44));
            v2->setPixmap(QPixmap::fromImage(*v22));
            v3->setPixmap(QPixmap::fromImage(*v11));
            v4->setPixmap(QPixmap::fromImage(*v33));
        }
        else{
            i1->setPixmap(QPixmap::fromImage(*i44));
            i2->setPixmap(QPixmap::fromImage(*i11));
            i3->setPixmap(QPixmap::fromImage(*i22));
            i4->setPixmap(QPixmap::fromImage(*i33));
            v1->setPixmap(QPixmap::fromImage(*v44));
            v2->setPixmap(QPixmap::fromImage(*v11));
            v3->setPixmap(QPixmap::fromImage(*v22));
            v4->setPixmap(QPixmap::fromImage(*v33));

        }
        break;
    case 3:
        if(status){
            i1->setPixmap(QPixmap::fromImage(*i22));
            i2->setPixmap(QPixmap::fromImage(*i44));
            i3->setPixmap(QPixmap::fromImage(*i33));
            i4->setPixmap(QPixmap::fromImage(*i11));
            v1->setPixmap(QPixmap::fromImage(*v22));
            v2->setPixmap(QPixmap::fromImage(*v44));
            v3->setPixmap(QPixmap::fromImage(*v33));
            v4->setPixmap(QPixmap::fromImage(*v11));
        }
        else{
            i1->setPixmap(QPixmap::fromImage(*i11));
            i2->setPixmap(QPixmap::fromImage(*i44));
            i3->setPixmap(QPixmap::fromImage(*i33));
            i4->setPixmap(QPixmap::fromImage(*i22));
            v1->setPixmap(QPixmap::fromImage(*v11));
            v2->setPixmap(QPixmap::fromImage(*v44));
            v3->setPixmap(QPixmap::fromImage(*v33));
            v4->setPixmap(QPixmap::fromImage(*v22));
        }
        break;


    }
    i1->show();
    i2->show();
    i3->show();
    i4->show();
    if(status == true){
        status = false;
    }
    else{
        status = true;
    }
}
void doorlock::setting_target_label(int answer){
    int x = 0;
    int y = 0;
    switch(answer){
    case 0:
        x = 0;
        y = 0;
        break;
    case 1:
        x = 0 + Wscreen -Hscreen/7;
        y = 0;
        break;
    case 2:
        x = 0;
        y = 0 + Hscreen -Hscreen/7;
        break;
    case 3:
        x = 0 + Wscreen -Hscreen/7;
        y = 0 + Hscreen -Hscreen/7;
        break;
    }
    t11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t12->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t21->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t31->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t32->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t41->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t42->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));

    t11->setGeometry(x, y, Hscreen/21,Hscreen/126);
    t12->setGeometry(x  , y  ,  Hscreen/126 , Hscreen/21);
    t21->setGeometry(x+ Hscreen*2 / 21, y  ,  Hscreen/21, Hscreen/126 );
    t22->setGeometry(x+ Hscreen*17/ 126, y  ,  Hscreen/126 , Hscreen/21);
    t31->setGeometry(x  , y+ Hscreen*17/ 126,  Hscreen/21, Hscreen/126 );
    t32->setGeometry(x  , y+ Hscreen*2 / 21,  Hscreen/126 , Hscreen/21);
    t41->setGeometry(x+ Hscreen*2 / 21, y+ Hscreen*17/126,  Hscreen/21, Hscreen/126 );
    t42->setGeometry(x+ Hscreen*17/ 126, y+ Hscreen*2/21,  Hscreen/126 , Hscreen/21);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////trigger
void doorlock::emit1(){
    emit triggersignal1();
}
void doorlock::emit2(){
    emit triggersignal2();
}
void doorlock ::emit3(){
    emit triggersignal3();
}
void doorlock::emit4(){
    emit triggersignal4();
}
void doorlock::emit11(){
    emit triggersignal11();
}
void doorlock::emit12(){
    emit triggersignal12();
}
void doorlock::emit13(){
    emit triggersignal13();
}
void doorlock::emit25(){
    emit triggersignal25();
}
