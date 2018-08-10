#include "tvwindow.h"
#include "ui_tvwindow.h"

tvWindow::tvWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tvWindow)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);
    QString filename = "setting.txt"; // setting.txt파일 오픈
    QFile file(filename); //파일
    QTextStream in(&file); // 파일스트림
    file.open(QIODevice::ReadWrite); //파일 열기
    int lines = 0;
    while(!in.atEnd()) { //파일이 있을경우 읽기, 없으면 기본값으로만 기록됨
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
            trial = line.toInt();
            ui->spinBox_8->setValue(trial);
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
         }
        lines++;
    }
    if(lines == 0){ // 읽고도 라인이 0이다 = 빈파일이다
        qDebug() << "excess";
        file.resize(0); // 파일 리셋 및 기입
        in << dark <<"\n";
        in << flash <<"\n";
        in << trainnum <<"\n";
        in << testnum <<"\n";
        in << trial <<"\n";
        in << one <<"\n";
        in << two <<"\n";
        in << three;
    }
    file.close();//파일 닫기
    lines = 0; // 리셋
}

tvWindow::~tvWindow()
{
    disconnect(this, SIGNAL(started()), this, SLOT(onoff_sequence())); //키고 끄는 순서 끄기
    disconnect(onoff,SIGNAL(emitting()), this, SLOT(start_next()));
    disconnect(this,SIGNAL(startagain()), this, SLOT(delaystart()));
    disconnect(onoff,SIGNAL(destroyed()),this, SLOT(destroyed()));//alt + f4를 감지 끄기
    disconnect(tcpServer,SIGNAL(newConnection()), this, SLOT(newConnection())); //통신 들어오는것 체크 끄기
    delete ui;
}
void tvWindow::server_start(){
        tcpServer = new QTcpServer(this); // 서버 생성
        client = new QTcpSocket(); // 클라이언트 생성
        if(!tcpServer->listen(QHostAddress::Any,23)){ // 서버 포트 "23"
            qDebug() << "TCPserver could not start"; // 서버 생성 실패시
        }
        else{
            qDebug() << "TCPserver start"; // 서버 생성 성공시

        }
        connect(tcpServer,SIGNAL(newConnection()), this, SLOT(newConnection())); // 서버 연결

}

void tvWindow::onoff_sequence(){
    QFile file("setting.txt"); // setting.txt파일에 시작 할때 저장
    QTextStream in(&file); // 파일 스트림
    file.open(QIODevice::ReadWrite); // 파일 열기
    file.resize(0); // 파일 삭제
    in << dark <<"\n";
    in << flash <<"\n";
    in << trainnum <<"\n";
    in << testnum << "\n";
    in << trial << "\n";
    in << one << "\n";
    in << two << "\n";
    in << three; // 재기입
    file.close(); // 파일 닫기
    if(isEND == trainnum){ // 트레이닝 끝날시
        training = false; // 트레이닝 끝났다고 마킹
    }
    if(isEND - trainnum == 0){ //0번부터 30번 변경
        switch(randsequence){ //랜덤 케이스에 따라서 123중 하나 선택(1)
        case 0:
           trial = one;
            break;
        case 1:
            trial = one;
            break;
        case 2:
            trial = two;
            break;
        case 3:
            trial = two;
            break;
        case 4:
            trial = three;
            break;
        case 5:
            trial = three;
            break;
        }
    }
    if(isEND - trainnum  == 30){ //30번부터 60번 변경
        switch(randsequence){ // 랜덤 케이스에 따라서 123중 하나 선택(2)
        case 0:
           trial = two;
            break;
        case 1:
            trial = three;
            break;
        case 2:
            trial = one;
            break;
        case 3:
            trial = three;
            break;
        case 4:
            trial = one;
            break;
        case 5:
            trial = two;
            break;
        }
    }
    if(isEND - trainnum  == 60){ // 60번부터 90번 변경
        switch(randsequence){ // 랜덤 케이스에 따라서 123중 하나 선택(3)
        case 0:
           trial = three;
            break;
        case 1:
            trial = two;
            break;
        case 2:
            trial = three;
            break;
        case 3:
            trial = one;
            break;
        case 4:
            trial = two;
            break;
        case 5:
            trial = one;
            break;
        }
    }
    //qDebug()<<randsequence << " randsequence";
    //qDebug() <<trial << ", trial " << isEND <<" is End ";
    Fin = isEND; // 현재 숫자 대입
    playingonoff += (dark + flash) * 4 * trial + 6500; // 실행시간 조정
    if(playingonoff > 144000 - (dark + flash) * 4 * trial + 6500){ //플레이시간 조정으로 실제 TV흐르듯
        playingonoff = 0;
    }
    qDebug() << onoff->Fin <<" before vs after " << Fin;
    onoff->Fin = this->Fin;
    if(isEND == trainnum && !teststart){ // 테스트 시작 전 처음 정지 세팅
        teststart = true;
        onoff->wait = true;
        training = false;

    }
    onoff->playingonoff = playingonoff; //TVUI에 값 전송
    onoff->take_info(dark, flash, portname, filepath, rowcol ,debug, result, training, trial); // 값 전송
    onoff->take_color_info(FGscale, BGscale); //?
    onoff->show(); //UI 표시
    onoff->show_rand(); //시작
    qDebug() <<  trainnum << " = training,  " <<testnum << " = test :  isEND = "  << isEND;
    if(isEND == testnum + trainnum){ //끝날경우 UI끄기
        isEND = 0;
        delete onoff;
    }
        isEND++;
}
void tvWindow::delaystart(){ // 테스트에서 시작 전 값 넣기
    if(!training){
    onoff->playingonoff = playingonoff;
    onoff->take_info(dark, flash, portname, filepath, rowcol ,debug, result, training, trial);
    onoff->take_color_info(FGscale, BGscale);
    onoff->show();
    onoff->show_rand();
    }
}

void tvWindow::init_flick_labels()
{
    F_label->setText("Flicker Grayscale");
    QFont font("Arial", 14);
    F_label->setFont(font);
    F_label->setGeometry(240,370,150,40);
    F_label->show();
    B_label->setText("Background Grayscale");
    B_label->setFont(font);
    B_label->setGeometry(220,480,200,40);
    B_label->show();
}

void tvWindow::setting_flick()
{
    sti_type = true;
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->spinBox_6->setEnabled(true);
    ui->spinBox_7->setEnabled(true);
    ui->spinBox_8->setEnabled(true);
    ui->spinBox_9->setEnabled(true);
    ui->spinBox_10->setEnabled(true);
    ui->spinBox_11->setEnabled(true);
}


void tvWindow::on_pushButton_clicked()
{
    Fin = 0;
    playingonoff = 0;
    isEND = 0;
    if(sti_type)
    {
        srand(time(NULL));
        randsequence = rand()%6; // 6개중 하나. 시작시 결정(123을 나열하는 갯수)
        onoff = new On_Off(ui->pushButton);
        connect(this, SIGNAL(started()), this, SLOT(onoff_sequence()));
        connect(onoff,SIGNAL(emitting()), this, SLOT(start_next()));
        connect(this,SIGNAL(startagain()), this, SLOT(delaystart()));
        connect(onoff,SIGNAL(destroyed()),this, SLOT(destroyed()));
        emit started();
    }
    else
    {
        timer = new QTimer(this);
        time_interval = (active + inactive) * 40 + 10500; // 매 트라이얼 만큼 숫자 결정
        connect(timer, SIGNAL(timeout()), this, SLOT(motion_sequence()));
        timer->start();
    }
}
void tvWindow::destroyed(){  //alt + F4로 꺼질시
    qDebug() << "destroyed";
    if(result == 8){ // result 8로 인해서 재시작할 경우 연결 해제
    disconnect(this, SIGNAL(started()), this, SLOT(onoff_sequence()));
    disconnect(this,SIGNAL(startagain()), this, SLOT(delaystart()));
    }
    training = true; // 재시작
    playingonoff = 0;
    isEND = 0;
}
void tvWindow::readyRead(){ //데이터 받을시
    //qDebug() <<"come"; // 인풋
       QByteArray byte = client->readAll();
       QString DataAsString(byte);
       result=DataAsString.toInt();
       //qDebug() <<result<< "line"; // 인풋 결과
       if(result == 6){ // 6을 받을경우
           emit onoff->startagain(); // 테스트 시작
           teststart = true;
       }
       else if(result == 8){// 8을 받을경우 전체 리셋
           disconnect(this, SIGNAL(started()), this, SLOT(onoff_sequence()));
           disconnect(onoff,SIGNAL(emitting()), this, SLOT(start_next()));
           disconnect(this,SIGNAL(startagain()), this, SLOT(delaystart()));
           disconnect(onoff,SIGNAL(destroyed()),this, SLOT(destroyed()));
           onoff->deleteLater();
           onoff = new On_Off(ui->pushButton);
           training = true;
           playingonoff = 0;
           isEND = 0;
           connect(this, SIGNAL(started()), this, SLOT(onoff_sequence()));
           connect(onoff,SIGNAL(emitting()), this, SLOT(start_next()));
           connect(this,SIGNAL(startagain()), this, SLOT(delaystart()));
           connect(onoff,SIGNAL(destroyed()),this, SLOT(destroyed()));
           emit started(); //및 재시작
       }
       else if(result > 100){ // 100이상의 값이 나올경우 트라이얼의 값 변경
           trial = result -100;
           ui->spinBox_8->setValue(trial);
       }
       else if(sti_type){ // 받을 경우 받았다고 전송. 주로 1234
           onoff->received = true;
           onoff->result = result;
           emit onoff->receiving();
       }
}
void tvWindow::on_pushButton_2_clicked() // 종료
{
    this->close();
}
void tvWindow::start_next(){ // 재시작
    qDebug() << "restart";
    emit started();

}

void tvWindow::newConnection(){ //새로운 네트워크 들어올경우 연결
      client = tcpServer->nextPendingConnection();// 이전 클라이언트는 연결 해제
     client->waitForBytesWritten(3000);
      qDebug() << "connect with TCPclient";
     connect(client, SIGNAL(readyRead()),this, SLOT(readyRead())); // 연결
}
void tvWindow::on_radioButton_clicked() //On-Off button
{
    setting_flick();
    rowcol = false;
}

void tvWindow::on_radioButton_3_clicked() //On-Off rowcol button
{
    setting_flick();
    rowcol = true;
}
void tvWindow::on_spinBox_valueChanged(double arg1)
{
    dark = arg1;
}

void tvWindow::on_spinBox_2_valueChanged(double arg1)
{
    flash = arg1;
}
void tvWindow::on_spinBox_6_valueChanged(int arg1)
{
    trainnum = arg1;
}

void tvWindow::on_spinBox_7_valueChanged(int arg1)
{
    testnum = arg1;
}
void tvWindow::on_spinBox_8_valueChanged(int arg1)
{
    trial = arg1;
}
void tvWindow::on_spinBox_9_valueChanged(int arg1)
{
    one = arg1;
}

void tvWindow::on_spinBox_10_valueChanged(int arg1)
{
    two = arg1;
}
void tvWindow::on_spinBox_11_valueChanged(int arg1)
{
    three = arg1;
}

void tvWindow::set_flicker_color()
{
    flicker->show();
}


void tvWindow::set_BGW_color()
{
    BGW->show();
}

void tvWindow::update_BGscale()
{
    BGscale = BGW->value();
}
