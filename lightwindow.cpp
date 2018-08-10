#include "lightwindow.h"
#include "light.h"
#include "ui_lightwindow.h"
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QTimer>

#include <QtWidgets/QApplication>

#include <QtConcurrent/QtConcurrentRun>
void lightwindow::closeEvent(QCloseEvent * event)
{
    delete this; // alt + f4로 끌 시 종료. 없으면 겉보기는 없지만 계속 실행됨
}
lightwindow::lightwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lightwindow)
{
    ui->setupUi(this);
    totaltimer = new QElapsedTimer;
    totaltimer->start();
    qDebug() << "socket connect";
    QString filename = "setting3.txt";//세팅 불러올 파일 이름
    QFile file(filename); // 파일 위치
    QTextStream in(&file); // 파일 열기
    file.open(QIODevice::ReadWrite); // 읽고쓰기 모드
    int lines = 0; // 0으로 시작
    while(!in.atEnd()) { // 파일이 끝날때까지
        QString line = in.readLine();
        switch(lines){ // 줄 수에 따라서 값 기입
        case 0:
            dark = line.toDouble();
            ui->spinBox->setValue(dark);
            break;
        case 1:
            flash = line.toDouble();
            ui->spinBox_2->setValue(flash);
            break;
        case 2:
            training = line.toInt();
            ui->spinBox_6->setValue(training);
            break;
        case 3:
            testing = line.toInt();
            ui->spinBox_7->setValue(testing);
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
    if(lines <= 7){ // 받은 파일이 빈 파일 혹은 8줄 이하라 결과값이 없는 경우 (파일이 없을 경우도)
        qDebug() << "excess";
        file.resize(0);//초기화
        in << dark <<"\n";
        in << flash <<"\n";
        in << training <<"\n";
        in << testing <<"\n";
        in << repeat <<"\n";
        in << one <<"\n";
        in << two <<"\n";
        in << three<<"\n";
        in << ip;
    }//재기록
    file.close(); // 파일 닫기
    lines = 0; // 초기화
    serverstart(); //서버 시작
}
void lightwindow::serverstart(){
    server = new QTcpServer(this);// 서버 생성
    client = new QTcpSocket(); // 수신용 소켓 생성
    socket = new QTcpSocket; // 전송용 소켓 생성
    if(!server->listen(QHostAddress::Any,23)){ //이 프로그램이 받는 서버 포트 = 23
        qDebug() << "TCPserver could not start";
    }
    else{
        qDebug() << "TCPserver start";

    }
    connect(server,SIGNAL(newConnection()), this, SLOT(newConnection())); // 새 클라이언트가 들어오는지 수신
}
void lightwindow::newConnection(){ // 네트워크 실행시 실행 함수
    qDebug() << "connection with client"; //이것이 나온다면 접속 시도중
    client = server->nextPendingConnection();  // 다음 접속 시도중인 것에 클라이언트 배분
    client->waitForBytesWritten(3000); // 3초간 수신 기다림
    qDebug() << "connect with TCPclient"; // 접속 완료
    connect(client, SIGNAL(readyRead()),this, SLOT(readyRead())); // 이제 클라이언트에서 보낼때마다 함수 실행 연결
}
void lightwindow::readyRead(){ // 수신시 실행 함수
       //qDebug() <<"come";// 수신시 작동 디버그 코드
       QByteArray byte = client->readAll(); // 모두 읽기
       QString DataAsString(byte); // string으로 데이터 전환
       result=DataAsString.toInt(); // 결과를 int형으로 변환
       //qDebug() <<result<< "line"; 들어온 결과 표시 디버그 코드, line이라는 글씨 붙혀서 수신부라고 확인
       if(result == 6){ // 트레이닝 종료 완료, 테스트시
           emit lig->startagain(); // 재시작 신호 발신
       }
       else if(result == 8){ // 모든것을 삭제 후 재실행 코드
           disconnect(lig, SIGNAL(opensignal()), this, SLOT(opencatch()));
           disconnect(lig, SIGNAL(emit1()),this, SLOT(send1()));
           disconnect(lig, SIGNAL(emit2()),this, SLOT(send2()));
           disconnect(lig, SIGNAL(emit3()),this, SLOT(send3()));
           disconnect(lig, SIGNAL(emit4()),this, SLOT(send4()));
           disconnect(lig, SIGNAL(emit11()),this, SLOT(send11()));
           disconnect(lig, SIGNAL(emit12()),this, SLOT(send12()));
           disconnect(lig, SIGNAL(emit13()),this, SLOT(send13()));
           disconnect(lig, SIGNAL(end()), this, SLOT(restart()));
           disconnect(this, SIGNAL(started()), this, SLOT(ligronoff_sequence()));
           disconnect(lig,SIGNAL(destroyed()),this, SLOT(destroyed())); // 현재 신호 기다림 모두 종료
           lig->deleteLater(); // 삭제
           lig = new light(ui->pushButton); // 새로 할당
           nowtraining = true;
           isEND = 0;
           wait = false;//초기화
           connect(lig, SIGNAL(opensignal()), this, SLOT(opencatch()));
           connect(lig, SIGNAL(emit1()),this, SLOT(send1()));
           connect(lig, SIGNAL(emit2()),this, SLOT(send2()));
           connect(lig, SIGNAL(emit3()),this, SLOT(send3()));
           connect(lig, SIGNAL(emit4()),this, SLOT(send4()));
           connect(lig, SIGNAL(emit11()),this, SLOT(send11()));
           connect(lig, SIGNAL(emit12()),this, SLOT(send12()));
           connect(lig, SIGNAL(emit13()),this, SLOT(send13()));
           connect(lig, SIGNAL(end()), this, SLOT(restart()));
           connect(this, SIGNAL(started()), this, SLOT(ligronoff_sequence()));
           connect(lig,SIGNAL(destroyed()),this, SLOT(destroyed())); // 재연결
           emit started(); // 재시작
       }
       else if(result > 100){ // 100  + 반복횟수를 보내 반복횟수 조정가능
           repeat = result -100; // 100 빼기
           ui->spinBox_8->setValue(repeat); //반복횟수 조절
       }
       else{ // 그 외 신호는 그냥 받았다라는 신호만. 테스트 다음 회차 진행
           lig->received = true; // 받음
           lig->ans = result;//정답 결과 전송
           emit lig->receiving(); // 전송받음 신호 전송
       }
}

lightwindow::~lightwindow()
{
    delete ui;//디스트럭터
}
void lightwindow::destroyed(){//alt + f4로 강종시 및 자체 종료시 시작
    QString filename = "result.txt"; //result.txt파일에 저장
    QFile file(filename); // 파일 위치 세팅
    file.open(QIODevice::Append | QIODevice::Text); //저장타입 : 계속 이어서
    QTextStream in(&file);  // 스트림
    in << "in this time, breaked or ended" << '\r' << '\n';
    file.close();// 파일 닫기
   // qDebug() << "destroyed";
    training = true;
    isEND = 0; // 값 초기화
}
/////////////////////////////////////////////////////////////
/// 값 변경시 작동하는 함수들
void lightwindow::on_spinBox_valueChanged(double arg1)
{
    dark = arg1;
}

void lightwindow::on_spinBox_2_valueChanged(double arg1)
{
    flash = arg1;
}
void lightwindow::on_spinBox_6_valueChanged(int arg1)
{
    training = arg1;
}
void lightwindow::on_spinBox_7_valueChanged(int arg1)
{
    testing = arg1;
}
void lightwindow::on_spinBox_8_valueChanged(int arg1)
{
    repeat = arg1;
}
void lightwindow::on_spinBox_9_valueChanged(int arg1)
{
    one = arg1; // 첫 랜덤 반복횟수
}
void lightwindow::on_spinBox_10_valueChanged(int arg1)
{
    two = arg1; // 두번째 랜덤 반복횟수
}
void lightwindow::on_spinBox_11_valueChanged(int arg1)
{
    three = arg1;// 세번째 랜덤 반복횟
}
/////////////////////////////////////////////////////////


void lightwindow::on_pushButton_clicked() // 자극 시작 버튼 눌렀을때
{
    ip = ui->lineEdit->text(); //ip 얻기
    socket -> connectToHost(ip, 1667); // 얻은 ip로 tcp통신 시작
    srand(time(NULL)); //난수 조정
    randsequence = rand()%6; //
    QFile file("setting3.txt"); // 세팅 변수에서 세팅값 불러오기
    QTextStream in(&file);
    file.open(QIODevice::ReadWrite); // 읽고쓰기
    file.resize(0); // 초기화
    in << dark <<"\n";
    in << flash <<"\n";
    in << training <<"\n";
    in << testing << "\n";
    in << repeat << "\n";
    in << one << "\n";
    in << two << "\n";
    in << three<<"\n";
    in << ip;
    file.close();//파일 닫기
    lig = new light(ui->pushButton); //자극용 새 창 생성
    connect(lig, SIGNAL(signalone()), this, SLOT(positionone()));
    connect(lig, SIGNAL(signaltwo()), this, SLOT(positiontwo()));
    connect(lig, SIGNAL(signalthree()), this, SLOT(positionthree()));
    connect(lig, SIGNAL(signalfour()), this, SLOT(positionfour()));
    connect(lig, SIGNAL(triggersignal1()),this, SLOT(send1()));
    connect(lig, SIGNAL(triggersignal2()),this, SLOT(send2()));
    connect(lig, SIGNAL(triggersignal3()),this, SLOT(send3()));
    connect(lig, SIGNAL(triggersignal4()),this, SLOT(send4()));
    connect(lig, SIGNAL(sendanswer()), this, SLOT(sendansw()));
    connect(lig, SIGNAL(triggersignal11()),this, SLOT(send11()));
    connect(lig, SIGNAL(triggersignal12()),this, SLOT(send12()));
    connect(lig, SIGNAL(triggersignal13()),this, SLOT(send13()));
    connect(lig, SIGNAL(destroyed()), this, SLOT(destroyed()));
    connect(lig, SIGNAL(end()), this, SLOT(restart()));
    connect(this,SIGNAL(start()),this, SLOT(lightonoff_sequence()));
    connect(lig,SIGNAL(destroyeverything()), this, SLOT(ifdistroyed())); // 필요한 함수 연결
    this->hide(); // 설정창 숨기기
    emit start(); // 자극 시작 신호
}
void lightwindow::on_pushButton_2_clicked() // 종료 버튼
{
    this->close();
}
void lightwindow::lightonoff_sequence(){ //깜빡이는 자극 제어부
    if (isEND == training){ // 트레이닝이 종료 됫을경우 1번만 작동
       // qDebug() << "wait start";
        QString filename = "result.txt";
        QFile file(filename);
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream in(&file);
        in << "test start : " << '\r' <<'\n';
        file.close();

        nowtraining = false;
        wait = true;
    }
    else{ //그 이외 케이스
        wait = false;
    }

    if(isEND - training == 0){ // 0~30번의 반복횟수, 이하는 테스트에서만 작동

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
    if(isEND - training  == 30){//30~60번의 반복횟수
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
    if(isEND - training  == 60){ //60~90번의 반복횟수
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
    lig->take_info(dark, flash, nowtraining, isEND, status, repeat, wait); // 값은 private, 함수로 불러오기
    lig->training = training; // 함수수정 귀찮아서 따로 public으로
    lig->show(); // 혹시 숨겨졌을지도 모르니
    lig->blink_rand(); // 깜빡임
    isEND++; // 현재 진행 횟수 추가
}
void lightwindow::positionone(){ //왼쪽 위
    //qDebug() <<"position one";
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
 //   qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed); //지연시간 측정
    data = temp + "#A#";// A = 1위치 정답. 데이터간 구별은 #으로
  //  qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::positiontwo(){ //오른쪽 위
    qDebug() <<"position two";
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
  //  qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data = temp + "#B#"; //B = 2위치 정답
  //  qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::positionthree(){ // 왼쪽 아래
    qDebug() <<"position three";
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
//    qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data =  temp + "#C#"; // C = 3위치 정답
   // qDebug() << "data = " << data;
    socket->write(data);
}

void lightwindow::positionfour(){
    qDebug() <<"position four";
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
  //  qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data =  temp + "#D#"; // D = 4위치 정답
   // qDebug() << "data = " << data;
     socket->write(data);
}
void lightwindow::send1(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
  //  qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data = temp + "#a#"; // 자극1 전달
 //   qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send2(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
//    qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data =  temp + "#b#"; // 자극 2 전달
//    qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send3(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
//    qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data = temp+ "#c#"; // 자극 3 전달
    //qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send4(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
    //qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data =  temp + "#d#"; // 자극 4 전달
    //qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send11(){
    QByteArray data;
    totaltimer->restart();
    timercheck = totaltimer->elapsed();
    nowtime = 0;
    elapsed = 0;
    timedebug = 0;
    //qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    data = "0#x#"; // 11번 트리거 전달 및 시간 초기화
   // qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send12(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    timedebug += elapsed;
//    qDebug() << "elapse = " << elapsed << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data = temp + "#y#"; // 12번 트리거 전달
   // qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::send13(){
    QByteArray data;
    nowtime = totaltimer->elapsed();
    elapsed = nowtime - timercheck;
    //qDebug() << "elapse = " << elapsed << "nowtime" << totaltimer->elapsed() << ", totaltime = " << timercheck << ",  debug" << timedebug;
    timercheck = nowtime;
    QByteArray temp = QByteArray::number(elapsed);//지연시간 측정
    data = temp + "#z#";
   // qDebug() << "data = " << data;
    socket->write(data);
}
void lightwindow::sendansw(){
    QByteArray data;
    QByteArray a = QByteArray::number(lig->results[0]);
    QByteArray b = QByteArray::number(lig->results[1]);
    QByteArray c = QByteArray::number(lig->results[2]);
    QByteArray d = QByteArray::number(lig->results[3]); // 배열 결정
    data =  a + "#&1#" + b + "#&2#" + c + "#&3#" + d +"#&4#"; // 배열 전달
    //qDebug() << "answer = " <<a << b << c << d;// 디버그용 코드, 배열출력
    socket->write(data);// 전송
}
void lightwindow::restart(){
    emit start();
}
void lightwindow::ifdistroyed(){
    this->show();
}
