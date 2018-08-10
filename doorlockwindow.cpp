#include "doorlockwindow.h"
#include "doorlock.h"
#include "ui_doorlockwindow.h"

doorlockwindow::doorlockwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doorlockwindow)
{
   ui->setupUi(this);
   socket = new QTcpSocket;

   QString filename = "setting2.txt"; // 도어락은 setting2번 파일에 저장
   QFile file(filename);
   QTextStream in(&file);
   file.open(QIODevice::ReadWrite);
   int lines = 0;
   while(!in.atEnd()) {
       QString line = in.readLine();
       switch(lines){
       case 0:
           dark = line.toDouble();
           ui->spinBox->setValue(dark);
           break;
       case 1:
           flash = line.toDouble();
           ui->spinBox_2->setValue(flash);
           break;
       case 2:
           trainnum = line.toInt();
           ui->spinBox_6->setValue(trainnum);
           break;
       case 3:
           testnum = line.toInt();
           ui->spinBox_7->setValue(testnum);
           break;
       case 4:
           repeat = line.toInt();
           ui->spinBox_8->setValue(repeat);
           break;
       case 5:
           one = line.toInt();
           ui->spinBox_9->setValue(one);
           break;
       case 6:
           two = line.toInt();
           ui->spinBox_10->setValue(two);
           break;
       case 7:
           three = line.toInt();
           ui->spinBox_11->setValue(three);
           break;
       case 8:
           ip = line;
           ui->lineEdit->setText(ip);
           break;
        }
       lines++;
   }
   if(lines == 0){
       qDebug() << "excess";
       file.resize(0);
       in << dark <<"\n";
       in << flash <<"\n";
       in << trainnum <<"\n";
       in << testnum <<"\n";
       in << repeat <<"\n";
       in << one <<"\n";
       in << two <<"\n";
       in << three<<"\n";
       in << ip;


   }
   file.close();
   lines = 0;
   serverstart();
}
doorlockwindow::~doorlockwindow()
{
    disconnect(doo, SIGNAL(opensignal()), this, SLOT(opencatch()));
    disconnect(doo, SIGNAL(triggersignal1()),this, SLOT(send1()));
    disconnect(doo, SIGNAL(triggersignal2()),this, SLOT(send2()));
    disconnect(doo, SIGNAL(triggersignal3()),this, SLOT(send3()));
    disconnect(doo, SIGNAL(triggersignal4()),this, SLOT(send4()));
    disconnect(doo, SIGNAL(triggersignal11()),this, SLOT(send11()));
    disconnect(doo, SIGNAL(triggersignal12()),this, SLOT(send12()));
    disconnect(doo, SIGNAL(triggersignal13()),this, SLOT(send13()));
    disconnect(doo, SIGNAL(end()), this, SLOT(restart()));
    disconnect(doo,SIGNAL(triggersignal25()),this,SLOT(send25()));
    disconnect(this, SIGNAL(started()), this, SLOT(dooronoff_sequence()));
    disconnect(doo,SIGNAL(destroyed()),this, SLOT(destroyed()));
    delete ui;
}
void doorlockwindow::serverstart(){
    server = new QTcpServer(this);
    client = new QTcpSocket();
    if(!server->listen(QHostAddress::Any,23)){
        qDebug() << "TCPserver could not start";
    }
    else{
        qDebug() << "TCPserver start";

    }
    connect(server,SIGNAL(newConnection()), this, SLOT(newConnection()));
}
void doorlockwindow::newConnection(){
    client = server->nextPendingConnection();
   client->waitForBytesWritten(3000);
    qDebug() << "connect with TCPclient";
   connect(client, SIGNAL(readyRead()),this, SLOT(readyRead()));
}
void doorlockwindow::readyRead(){
    qDebug() <<"come";
       QByteArray byte = client->readAll();
       QString DataAsString(byte);
       result=DataAsString.toInt();
       qDebug() <<result<< "line";
       if(result == 6){
           emit doo->startagain();
       }
       else if(result == 8){
           disconnect(doo, SIGNAL(opensignal()), this, SLOT(opencatch()));
           disconnect(doo, SIGNAL(triggersignal1()),this, SLOT(send1()));
           disconnect(doo, SIGNAL(triggersignal2()),this, SLOT(send2()));
           disconnect(doo, SIGNAL(triggersignal3()),this, SLOT(send3()));
           disconnect(doo, SIGNAL(triggersignal4()),this, SLOT(send4()));
           disconnect(doo, SIGNAL(triggersignal11()),this, SLOT(send11()));
           disconnect(doo, SIGNAL(triggersignal12()),this, SLOT(send12()));
           disconnect(doo, SIGNAL(triggersignal13()),this, SLOT(send13()));
           disconnect(doo, SIGNAL(end()), this, SLOT(restart()));
           disconnect(doo,SIGNAL(triggersignal25()),this,SLOT(send25()));
           disconnect(this, SIGNAL(started()), this, SLOT(dooronoff_sequence()));
           disconnect(doo,SIGNAL(destroyed()),this, SLOT(destroyed()));
           doo->deleteLater();
           doo = new doorlock(ui->pushButton);
           nowtraining = true;
           isEND = 0;
           wait = false;
           connect(doo, SIGNAL(opensignal()), this, SLOT(opencatch()));
           connect(doo, SIGNAL(triggersignal1()),this, SLOT(send1()));
           connect(doo, SIGNAL(triggersignal2()),this, SLOT(send2()));
           connect(doo, SIGNAL(triggersignal3()),this, SLOT(send3()));
           connect(doo, SIGNAL(triggersignal4()),this, SLOT(send4()));
           connect(doo, SIGNAL(triggersignal11()),this, SLOT(send11()));
           connect(doo, SIGNAL(triggersignal12()),this, SLOT(send12()));
           connect(doo, SIGNAL(triggersignal13()),this, SLOT(send13()));
           connect(doo,SIGNAL(triggersignal25()),this,SLOT(send25()));
           connect(doo, SIGNAL(end()), this, SLOT(restart()));
           connect(this, SIGNAL(started()), this, SLOT(dooronoff_sequence()));
           connect(doo,SIGNAL(destroyed()),this, SLOT(destroyed()));
           emit started();
       }
       else if(result > 100){
           repeat = result -100;
           ui->spinBox_8->setValue(repeat);
       }
       else{
           doo->received = true;
           doo->take_info(dark, flash, nowtraining, isEND, status,repeat, wait, result);
           emit doo->receiving();
       }
}
void doorlockwindow::on_spinBox_valueChanged(double arg1)
{
    dark = arg1;
}

void doorlockwindow::on_spinBox_2_valueChanged(double arg1)
{
    flash = arg1;
}
void doorlockwindow::on_spinBox_6_valueChanged(int arg1)
{
    trainnum = arg1;
}

void doorlockwindow::on_spinBox_7_valueChanged(int arg1)
{
    testnum = arg1;
}
void doorlockwindow::on_spinBox_8_valueChanged(int arg1)
{
    repeat = arg1;
}
void doorlockwindow::on_spinBox_9_valueChanged(int arg1)
{
    one = arg1;
}
void doorlockwindow::on_spinBox_10_valueChanged(int arg1)
{
    two = arg1;
}
void doorlockwindow::on_spinBox_11_valueChanged(int arg1)
{
    three = arg1;
}
void doorlockwindow::on_pushButton_clicked()
{
    ip = ui->lineEdit->text();
    socket -> connectToHost(ip, 1662);
    srand(time(NULL));
    randsequence = rand()%6;
    QFile file("setting2.txt");
    QTextStream in(&file);
    file.open(QIODevice::ReadWrite);
    file.resize(0);
    in << dark <<"\n";
    in << flash <<"\n";
    in << trainnum <<"\n";
    in << testnum << "\n";
    in << repeat << "\n";
    in << one << "\n";
    in << two << "\n";
    in << three<< "\n";
    in << ip;
    file.close();
    doo = new doorlock(ui->pushButton);
    connect(doo, SIGNAL(opensignal()), this, SLOT(opencatch()));
    connect(doo, SIGNAL(triggersignal1()),this, SLOT(send1()));
    connect(doo, SIGNAL(triggersignal2()),this, SLOT(send2()));
    connect(doo, SIGNAL(triggersignal3()),this, SLOT(send3()));
    connect(doo, SIGNAL(triggersignal4()),this, SLOT(send4()));
    connect(doo, SIGNAL(triggersignal11()),this, SLOT(send11()));
    connect(doo, SIGNAL(triggersignal12()),this, SLOT(send12()));
    connect(doo, SIGNAL(triggersignal13()),this, SLOT(send13()));
    connect(doo, SIGNAL(end()), this, SLOT(restart()));
    connect(doo,SIGNAL(triggersignal25()),this,SLOT(send25()));
    connect(doo, SIGNAL(destroyed()),this, SLOT(destroyed()));
    connect(this, SIGNAL(started()), this, SLOT(dooronoff_sequence()));
    emit started();
}
void doorlockwindow::on_pushButton_2_clicked()
{
    this->close();
}
void doorlockwindow::opencatch(){
    if(status){
        status = false;
    }
    else{
        status = true;
    }
}
void doorlockwindow::destroyed(){
    qDebug() << "destroyed";
    nowtraining = true;
    isEND = 0;
}

void doorlockwindow::dooronoff_sequence(){

    if (isEND == trainnum){
        qDebug() << "wait start";
        nowtraining = false;
        wait = true;
    }
    if(isEND - trainnum == 0){

        switch(randsequence){
        case 0:
           repeat = one;
            break;
        case 1:
            repeat = one;
            break;
        case 2:
            repeat = two;
            break;
        case 3:
            repeat = two;
            break;
        case 4:
            repeat = three;
            break;
        case 5:
            repeat = three;
            break;
        }
    }
    if(isEND - trainnum  == 30){
        switch(randsequence){
        case 0:
           repeat = two;
            break;
        case 1:
            repeat = three;
            break;
        case 2:
            repeat = one;
            break;
        case 3:
            repeat = three;
            break;
        case 4:
            repeat = one;
            break;
        case 5:
            repeat = two;
            break;
        }
    }
    if(isEND - trainnum  == 60){
        switch(randsequence){
        case 0:
           repeat = three;
            break;
        case 1:
            repeat = two;
            break;
        case 2:
            repeat = three;
            break;
        case 3:
            repeat = one;
            break;
        case 4:
            repeat = two;
            break;
        case 5:
            repeat = one;
            break;
        }
    }
    qDebug () << "start";
    doo->take_info(dark, flash, nowtraining, isEND, status,repeat, wait, result);
    doo->show();
    doo->blink_rand();
    wait = false;
    if(isEND ==  trainnum+testnum){
        delete doo;
    }
    isEND++;
}
void doorlockwindow::restart(){
    emit started();
}
void doorlockwindow::send11(){
    qDebug() << "send 11";
    QByteArray data;
    data = "11";
    socket->write(data);
}
void doorlockwindow::send12(){
    qDebug() << "send 12";
    QByteArray data;
    data = "12";
    socket->write(data);
}
void doorlockwindow::send13(){
    qDebug() << "send 13";
    QByteArray data;
    data = "13";
    socket->write(data);
}
void doorlockwindow::send1(){
    qDebug() << "send 1";
    QByteArray data;
    data = "1";
    socket->write(data); //write the data itself
}

void doorlockwindow::send2(){
    qDebug() << "send 2";
    QByteArray data;
    data = "2";
    socket->write(data); //write the data itself
}
void doorlockwindow::send3(){
    qDebug() << "send 3";
    QByteArray data;
    data = "3";
    socket->write(data); //write the data itself
}
void doorlockwindow::send4(){
    qDebug() << "send 4";
    QByteArray data;
    data = "4";
    socket->write(data); //write the data itself
}
void doorlockwindow::send25(){
    qDebug() << "send 25";
    QByteArray data;
    data = "25";
    socket->write(data); //write the data itself
}
