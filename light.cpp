#include "light.h"
#include "ui_light.h"

#include <QFile>
light::light(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::light)
{
    ////////////////////////////////////////////////////////////
    /// 시작시 실행되는 프로그램 부분
    ui->setupUi(this); // ui 세팅, 기본 제공
    /////////////////////
    /// 파일 저장
    QString filename = "result.txt"; //결과 파일에 시간 저장
    QFile file(filename); // 파일 저장 프로세스
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream in(&file);
    //qDebug()<< currentDateTime(); //현재 시간 표시
    in <<'\r' <<'\n' << currentDateTime() <<'\r' <<'\n'; // \r\n은 메모장의 엔터, 현재 시간 파일에 기록
    file.close();

    srand(time(NULL)); // 난수 변경
    /////////////////////
    /// 화면 조정
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint); // 테두리없음
    this->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0)); // 화면 색은 흑색
    this->showMaximized(); //전체화면
    /////////////////////
    /// 시작 프로그램 함수
    Init_QLabels(); // 라벨들 생성
    set_answer_sheet(); //정답 세팅
    ///시작시 질행되는 프로그램 부분 종료
    ////////////////////////////////////////////////////////////
}

light::~light()
{
    delete ui; // 클래스 디스트럭터
}

void light::closeEvent(QCloseEvent * event)
{
    ////////////////////////////////////////////////////////////
    /// 자극 화면 강종 실행 코드
    emit destroyeverything(); // lightwindow에 종료 출력
    delete this; // alt + f4로 끌 시 종료. 없으면 겉보기는 없지만 계속 실행됨
}
void light::blink_rand(){ // 깜빡임 함수
    if(wait && Finl != 0){ // 테스트 시작 처음에만 실행
        waitscreen->show();// 대기 화면 출력, 트레이닝->테스트 전환 화면
        connect(this,SIGNAL(startagain()),this,SLOT(before_blinking())); // 매트랩에서 6번(트레이닝 데이터 처리 완료)이 들어오면 트레이닝->테스트 전환 화면 종료
    }
    else{
        before_blinking(); // 바로 다름 것으로
    }
}
void light::before_blinking(){
    /////////////////////////////////////////////
    ///자극 점멸 전까지 프로세스
    disconnect(this,SIGNAL(startagain()),this,SLOT(before_blinking())); //매트랩 6번 연결 해제
    waitscreen->hide(); // 기다림 화면 숨기기
    setans(); // 정답 생성
    allocate_image(anslist[Finl]%24); // 정답에 맞춰 이미지 세팅. 가짓수는 24가지
    setting_target_label(ans); // 타겟을 정답에 맞춰서 세팅
    if(Finl == 0){ // 첫 트레이닝 일 경우.
        prepare->show();
        interval = 3000; // 처음에 준비 화면 표시 3초
        timer->singleShot(interval,prepare,SLOT(hide())); // 준비 화면 가리기
        timer->singleShot(interval,Xcross,SLOT(show())); // 십자 표시

    }
    else{ // 첫 트레이닝이 아닐경우
        interval = 0; // 그 외는 바로 다음것 실행
        timer->singleShot(interval,prepare,SLOT(hide())); // 준비 화면 가리기
        timer->singleShot(interval,Xcross,SLOT(show())); // 십자 표시
    }
    interval += 500; // 500ms 후 실행, 여기까지 500ms
    timer->singleShot(interval,Xcross,SLOT(hide()));
    timer->singleShot(interval,this,SLOT(target_show()));
    //qDebug() << "answer = " << ans; // answer 디버그 코드
    switch(ans){ // 정답별로 정답위치 보여주기
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
    timer->singleShot(interval,cameralight,SLOT(start())); // 카메라 시작
    timer->singleShot(interval,this,SLOT(emit11())); // 목표 줄때 트리거 11
    //portDataa++;
//////////////////////////////////////////////////////////////////////
    interval += 500; // 500ms 후 실행, 여기까지 1000ms
    switch(ans){
    case 0:
        timer->singleShot(interval,this,SLOT(emit1()));
        break;
    case 1:
        timer->singleShot(interval,this,SLOT(emit2()));
        break;
    case 2:
        timer->singleShot(interval,this,SLOT(emit3()));
        break;
    case 3:
        timer->singleShot(interval,this,SLOT(emit4()));
        break;
    }
    interval += 500; // 500ms 후 실행, 여기까지 1500ms
    timer->singleShot(interval,this,SLOT(sendans()));
    interval += 1000; // 1000ms 후 실행, 여기까지 2500ms
    timer->singleShot(interval,this,SLOT(target_hide())); // 정답 지시 숨기기
    timer->singleShot(interval,this,SLOT(hideall())); //
    timer->singleShot(interval,this,SLOT(emit12())); // 자극 시작 트리거 12
    interval += 500; // 500ms 후 실행, 여기까지 3000ms
    interval+= Dark; // Dark delay 처음에 실행. 여기까지 3000ms + Dark
    //portDataa++;
//////////////////////////////////////////////////////////////////////
    timer->singleShot(interval,this,SLOT(part1()));
    IDX = 0;
}
void light::part1(){
    connect(this,SIGNAL(nextblink()),this,SLOT(blink()));
    connect(this,SIGNAL(endblin()),this,SLOT(part15()));
    emit nextblink();
}
void light::part15(){

    disconnect(this,SIGNAL(nextblink()),this,SLOT(blink()));
     received = false;
     if(!nowtraining && !received){
        connect(this,SIGNAL(receiving()),this,SLOT(part2()));
    }
    else{
        //qDebug() << "go part 2";
        part2();
    }

}
void light::part2(){
    disconnect(this,SIGNAL(nextblink()),this,SLOT(blink()));
    disconnect(this,SIGNAL(endblin()),this,SLOT(part15()));
    disconnect(this,SIGNAL(receiving()),this,SLOT(part2()));
    //qDebug() << " endblink passed";
    timer->start();
    interval =0; // 간격 리셋
    timer->singleShot(interval,after,SLOT(show()));
    interval += 300; //300ms 후 실행, 현재까지 500ms
    //////////////////////////////////////////////////////////////////
    if(nowtraining){ //트레이닝시에만 제어, 테스트시에는 MATLAB쪽에서 제어
        switch(ans){
        case 0:
            timer->singleShot(interval,this,SLOT(positionone()));
            break;
        case 1:
            timer->singleShot(interval,this,SLOT(positiontwo()));
            break;

        case 2:
            timer->singleShot(interval,this,SLOT(positionthree()));
            break;
        case 3:
            timer->singleShot(interval,this,SLOT(positionfour()));
            break;
        }
    }
    interval += 200; //200ms 후 실행, 현재까지 500ms
    timer->singleShot(interval,after,SLOT(hide()));
    timer->singleShot(interval,Final,SLOT(show()));
    interval += 2000;//2000ms 후 실행, 현재까지 2500ms
    timer->singleShot(interval,Final,SLOT(hide()));
    interval += 200;//200ms 후 실행, 현재까지 2700ms
    timer->singleShot(interval+200,this,SLOT(restart()));
}
void light::take_info(int dark, int flash,  bool nowtrain, int nowtime, int stat, int repeat, bool wai)
{ //정보 가져오기
    Dark = dark;
    Flash = flash;
    nowtraining = nowtrain;
    Finl = nowtime;
    status = stat;
    repeats = repeat;
    wait = wai;
}

void light::setans(){ // 깜빡임 표 만들기

    ran_num = new int[repeats * 4];
    int i,j;
    for(i=0; i<repeats; i++)
    {
        for(j=0; j<4; j++)
        {
            int idx = i*4+j;
            ran_num[idx] = j;
        }
    }
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
    ////////////////////////////////
    ///정답 세팅
    ans = rand()%4;
}

void light::blink(){ // 깜빡임 함수
    if(IDX == 4 * repeats){ // 4번 * 총 깜빡일 횟수 넘을경우
      int interval = 0;
      interval += Flash; // Flash시간만큼 마지막으로 지연
      timer->singleShot(interval, this, SLOT(finish())); // 깜빡임 종료
      interval += 2000; // 13번 트리거까지의 거리가 멀어야 하므로
      timer->singleShot(interval,this,SLOT(emit13())); // 트라이얼 끝난 후 트리거
      //qDebug() << "end trigger";
      return;
    }
    switch(check){ // check가 true이면 켜짐, check가 false이면 꺼짐
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
        break;
    case false:
        //IDX = 이 자극에서 깜빡인 횟수
        timer->setInterval(Flash);
        if(ran_num[IDX]==0)
        {
            i1->hide();
            v1->show();
            emit1();
        }
        else if(ran_num[IDX]==1)
        {
            i2->hide();
            v2->show();
            emit2();
        }
        else if(ran_num[IDX]==2)
        {
            i3->hide();
            v3->show();
            emit3();
        }
        else if(ran_num[IDX]==3)
        {
            i4->hide();
            v4->show();
            emit4();
        check = true;
        IDX++;
         break;
        }
    }
    switch(portData){ // 내보낼 데이터에 따라서 switch,
    case 0:
        break;
    case 1:
        emit1();
        break;
    case 2:
        emit2();
        break;
    case 3:
        emit3();
        break;
    case 4:
        emit4();
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

void light::finish(){ // 깜빡임 종료 함수. emit endblin으로 다음 프로세스 실행
    v1->hide();
    v2->hide();
    v3->hide();
    v4->hide();
    i1->hide();
    i2->hide();
    i3->hide();
    i4->hide();
  //  qDebug() <<"emit endblink";
    emit endblin();
}
void light::Init_QLabels()
{
    anslist = new int[training+90];
    nowroute= QCoreApplication::applicationDirPath();
    //qDebug() << nowroute;
    timer = new QTimer(this);
    screen = QGuiApplication::primaryScreen();
    screenGeo = screen->geometry();
    Hscreen = screenGeo.height();
    Wscreen = screenGeo.width();
    vwin5 = new QVideoWidget(this);
    cameralight = new QCamera(this);
    cameralight->setViewfinder(vwin5);
    vwin5->setGeometry(0,0,Wscreen,Hscreen);
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
    ///////////////////////////////////////////////////////////////
    /// 메인 이미지 로드, 로드는 후에
    i111->load(nowroute + "/../image/lightfullon.png");
    i222->load(nowroute + "/../image/lighthalfon.png");
    i333->load(nowroute + "/../image/lightonoff.png");
    i444->load(nowroute + "/../image/color.png");
    v111->load(nowroute + "/../image/lightfullonB.png");
    v222->load(nowroute + "/../image/lighthalfonB.png");
    v333->load(nowroute + "/../image/lightonoffB.png");
    v444->load(nowroute + "/../image/colorB.png");
    ///////////////////////////////////////
    /// 사용할 크기에 맞춰서 버퍼 조정
    *i11=i111->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *i22=i222->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *i33=i333->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *i44=i444->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *v11=v111->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *v22=v222->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *v33=v333->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    *v44=v444->scaled(Hscreen /3, Hscreen /3, Qt::KeepAspectRatio);
    //////////////////////////////////////
    /// 이미지 위치 세팅
    v1->setGeometry(screenGeo.x(), screenGeo.y(),Hscreen /3,Hscreen /3);
    v2->setGeometry(Wscreen - Hscreen /3,screenGeo.y() ,Hscreen /3,Hscreen /3);
    v3->setGeometry(screenGeo.x() ,(Hscreen * 2)/3,Hscreen /3,Hscreen /3);
    v4->setGeometry(Wscreen - Hscreen /3,(Hscreen * 2)/3,Hscreen /3,Hscreen /3);
    i1->setGeometry(screenGeo.x() , screenGeo.y() ,Hscreen /3,Hscreen /3);
    i2->setGeometry(Wscreen - Hscreen /3,screenGeo.y() ,Hscreen /3,Hscreen /3);
    i3->setGeometry(screenGeo.x() ,(Hscreen * 2)/3,Hscreen /3,Hscreen /3);
    i4->setGeometry(Wscreen - Hscreen /3,(Hscreen * 2)/3,Hscreen /3,Hscreen /3);
    /////////////////////////////////////////////////////
    /// 준비화면
    prepare = new QLabel(this);
    prepare->setText("잠시 뒤에 시작 됩니다. + 를 봐주세요");
    QFont font("Arial", 36);
    prepare->setFont(font);
    prepare->setStyleSheet("QLabel {background-color : white; color : black;}");
    prepare->setGeometry(this->geometry());
    prepare->setAlignment(Qt::AlignCenter);
    //////////////////////////////////////////////
    ///십자 화면
    Xcross = new QLabel(this);
    Xcross->setText("+");
    QFont xfont("Arial", 150);
    Xcross->setFont(xfont);
    Xcross->setStyleSheet("QLabel {background-color : black; color : white;}");
    Xcross->setGeometry(0,0,Wscreen,Hscreen);
    Xcross->setAlignment(Qt::AlignCenter);
    //////////////////////////////////////////////
    /// 흑색 화면
    after = new QLabel(this);
    after->setAlignment(Qt::AlignCenter);
    after->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(0).arg(0).arg(0));
    after->setGeometry(prepare->geometry());
    ////////////////////////////////////////////
    /// 동작중 안내 화면
    Final = new QLabel(this);
    Final->setStyleSheet("QLabel {background-color : black; color : white;}");
    Final->setFont(font);
    Final->setText("동작 중입니다.");
    Final->setGeometry(screenGeo.x(),screenGeo.y()+Hscreen - 140,Wscreen,120);
    Final->setAlignment(Qt::AlignCenter);
    ////////////////////////////////////////////
    /// 십자가가 가려지지않도록 앞으로 끌어당기기
    Xcross->raise();
    Xcross->raise();
    Xcross->raise();
    ////////////////////////////////////////////////
    /// 대기 화
    waitscreen = new QLabel(this);
    waitscreen->setAlignment(Qt::AlignCenter);
    waitscreen->setStyleSheet("QLabel {background-color : black; color : white;}");
    waitscreen->setText("사용자의 패턴을 학습중입니다 \n 잠시만 기다려주세요");
    waitscreen-> setFont(font);
    waitscreen->setGeometry(this->geometry());
    ////////////////////////////////////////////
}


////////////////////////////////////////////
/// 정답 관련 함수
////////////////////
/// \brief light::setting_target_label
/// 정답 빨간 테두리 label의 위치 조정
/// \param answer
/// 정답 위치 0123 변수
void light::set_answer_sheet(){
    for(int i = 0; i < training+90; i++){
        anslist[i] = i;
    }
    for(int i = 0; i < 1000; i++){

        int a = rand()%training;
        int b= rand()%training;
        int temp;
        if(a != b){
            temp = anslist[a];
            anslist[a] = anslist[b];
            anslist[b] = temp;
        }
    }
}
void light::setting_target_label(int answer){ //타겟 표시 빨간 테두리 위치조정
    int x = 0;
    int y = 0;
    switch(answer){ // 직사각형 한 변 길이는 세로 화면의 1/3만큼
    case 0:   //왼쪽 위 위치로 조정
        x = 0;
        y = 0;
        break;
    case 1:
        x = 0 + Wscreen -Hscreen /3; // 오른쪽 위 위치로 조정
        y = 0;
        break;
    case 2:
        x = 0;
        y = 0 + (Hscreen * 2)/3; // 왼쪽 아래 위치로 조정
        break;
    case 3:
        x = 0 + Wscreen - Hscreen /3; // 오른쪽 아래 위치로 조정
        y = 0 + (Hscreen * 2)/3;
        break;
    }
    t11->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t12->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t21->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t22->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t31->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t32->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t41->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0));
    t42->setStyleSheet(QString("background-color : rgb(%1,%2,%3);").arg(255).arg(0).arg(0)); // 모두 적색으로

    t11->setGeometry(x, y, Hscreen / 9,Hscreen/54);
    t12->setGeometry(x  , y  ,  Hscreen/54 , Hscreen / 9);
    t21->setGeometry(x+ Hscreen * 2 / 9, y ,  Hscreen / 9, Hscreen/54 );
    t22->setGeometry(x+ Hscreen * 17 /54, y  ,  Hscreen/54 , Hscreen / 9);
    t31->setGeometry(x  , y+ Hscreen * 17 /54,  Hscreen / 9, Hscreen/54 );
    t32->setGeometry(x  , y+ Hscreen * 2 / 9,  Hscreen/54 , Hscreen / 9);
    t41->setGeometry(x+ Hscreen * 2 / 9, y+ Hscreen * 17 /54,  Hscreen / 9, Hscreen/54 );
    t42->setGeometry(x+ Hscreen * 17 /54, y+ Hscreen * 2 / 9,  Hscreen/54  , Hscreen / 9); // 위치 조정. 자동 조정 함수가 필요함
}
void light::target_show( ){ // 타겟 빨간 테두리 보여주기
    t11->show();
    t12->show();
    t21->show();
    t22->show();
    t31->show();
    t32->show();
    t41->show();
    t42->show();
}
void light::showans1(){//정답 1번 표시
    v1->show();
}
void light::showans2(){//정답 2번 표시
    v2->show();
}
void light::showans3(){//정답 3번 표시
    v3->show();
}
void light::showans4(){//정답 4번 표시
    v4->show();
}
void light::hideall(){ // 모두 숨기기. 초기화
    v1->hide();
    v2->hide();
    v3->hide();
    v4->hide();

}
////////////////////////////////////////////////
/// \brief light::target_hide
/// 지시용 빨간 테두리 및 정답 숨기기
void light::target_hide( ){
    // 타겟 빨간 테두리 숨기기
    t11->hide();
    t12->hide();
    t21->hide();
    t22->hide();
    t31->hide();
    t32->hide();
    t41->hide();
    t42->hide();
    switch(ans){ //정답 숨기기
    case 0:
        v1->hide();
        break;
    case 1:
        v2->hide();
        break;
    case 2:
        v3->hide();
        break;
    case 3:
        v4->hide();
        break;
    }
}
/////////////////////////////////////////////////
/// \brief light::allocate_image
/// 이미지 위치를 표시하는 함수
/// \param trial
/// 0~23 기입가능,
void light::allocate_image(int trial){ // 정답 세팅
    ////////////////////////////////////
    ///0: 1234 6: 2134
    ///1: 1243 7: 2143
    ///2: 1324 8: 2314
    ///3: 1342 ...
    ///4: 1423
    ///5: 1432
    /////////////////////////////////////
    int acase = (trial/6) + 1; //24개 케이스중 1번자리는 24를 6으로 나눈 몫 + 1과 같다
    int bcase = (trial%6) / 2 + 1; //24개 케이스중 2번자리는 24를 6으로 나눈 나머지를 2로 나눈 값 + 1과 같다
    int ccase = trial %2; // 홀짝 구분

    bool abcd[4];
    for(int i =0; i < 4; i++){ //1234 존재 기록 표
        abcd[i] = true;
    }
    results[0] = acase;
    results[1] = bcase; // 대입
    if(results[0] <= results[1]) results[1]++; // 1번자리와 2번자리가 같을경우 b를 1 늘린다. a = 1~4, b = 1~3
    abcd[results[0]-1] = false;
    abcd[results[1]-1] = false; // 존재 기록 표에 기록
    for(int i = 0; i < 4; i++){ //1~4까지 존재할경우 실행
        if(abcd[i]){
            if(ccase == 0){ //짝수일경우
                results[2] = i+1; // i + 1 기록, i = 0~3, result = 1~4
                ccase = 1;
            }
            else{// 홀수일경우
                results[3] = i+1;  // i+1 기록
                ccase = 0;
            }
        }
        abcd[i] = false;
    }
    for(int i = 0; i <4; i++){
        imageset(i + 1, results[i]); // 각 경우 이미지 세팅
    }

    //qDebug() << "results = " << results[0] << results[1] << results[2] <<results[3];
    //qDebug() << "abcd = " << abcd[0] << abcd[1] << abcd[2] <<abcd[3];
    i1->show();
    i2->show();
    i3->show();
    i4->show();
    v1->hide();
    v2->hide();
    v3->hide();
    v4->hide(); // 자극 초기화
}
///////////////////////////////////////////////////
/// \brief light::imageset
/// 이미지 세팅 함수
/// \param location
/// 1234 입력 가능, 위치 결정, 1은 왼쪽위 2는 오른쪽 위, 3은 왼쪽 아래, 4는 오른쪽 아래
/// \param imagefile
/// 1234 입력 가능, 적용할 이미지 파일, 1은 다 켜짐, 2는 반 켜짐, 3은 꺼짐, 4는 색깔 변경
///
void light::imageset(int location, int imagefile){
    //qDebug() << "location = " << location << ", imagefile = " << imagefile; // 뭘로 기입하는지 보는 디버그 코
    switch(location){
    case 1://1번위치조정
        switch(imagefile){
        case 1:
            i1->setPixmap(QPixmap::fromImage(*i11));
            v1->setPixmap(QPixmap::fromImage(*v11));
            break;
        case 2:
            i1->setPixmap(QPixmap::fromImage(*i22));
            v1->setPixmap(QPixmap::fromImage(*v22));
            break;
        case 3:
            i1->setPixmap(QPixmap::fromImage(*i33));
            v1->setPixmap(QPixmap::fromImage(*v33));
            break;
        case 4:
            i1->setPixmap(QPixmap::fromImage(*i44));
            v1->setPixmap(QPixmap::fromImage(*v44));
            break;
        }

        break;
    case 2://2번위치조정
        switch(imagefile){
        case 1:
            i2->setPixmap(QPixmap::fromImage(*i11));
            v2->setPixmap(QPixmap::fromImage(*v11));
            break;
        case 2:
            i2->setPixmap(QPixmap::fromImage(*i22));
            v2->setPixmap(QPixmap::fromImage(*v22));
            break;
        case 3:
            i2->setPixmap(QPixmap::fromImage(*i33));
            v2->setPixmap(QPixmap::fromImage(*v33));
            break;
        case 4:
            i2->setPixmap(QPixmap::fromImage(*i44));
            v2->setPixmap(QPixmap::fromImage(*v44));
            break;
        }

        break;
    case 3://3번위치조정
        switch(imagefile){
        case 1:
            i3->setPixmap(QPixmap::fromImage(*i11));
            v3->setPixmap(QPixmap::fromImage(*v11));
            break;
        case 2:
            i3->setPixmap(QPixmap::fromImage(*i22));
            v3->setPixmap(QPixmap::fromImage(*v22));
            break;
        case 3:
            i3->setPixmap(QPixmap::fromImage(*i33));
            v3->setPixmap(QPixmap::fromImage(*v33));
            break;
        case 4:
            i3->setPixmap(QPixmap::fromImage(*i44));
            v3->setPixmap(QPixmap::fromImage(*v44));
            break;
        }
        break;
    case 4://4번위치조정
        switch(imagefile){
        case 1:
            i4->setPixmap(QPixmap::fromImage(*i11));
            v4->setPixmap(QPixmap::fromImage(*v11));
            break;
        case 2:
            i4->setPixmap(QPixmap::fromImage(*i22));
            v4->setPixmap(QPixmap::fromImage(*v22));
            break;
        case 3:
            i4->setPixmap(QPixmap::fromImage(*i33));
            v4->setPixmap(QPixmap::fromImage(*v33));
            break;
        case 4:
            i4->setPixmap(QPixmap::fromImage(*i44));
            v4->setPixmap(QPixmap::fromImage(*v44));
            break;
        }
        break;
    }
}
///////////////////////////////////////////////
/// 자극 트리거 코드
/// connect 함수 안의 SLOT에는 패러미터를 넣을 수 없으므로 각 패러미터를 미리 세팅한 함수를 생성해둠
/// emit 신호 형식으로 신호를 발동, 실제로 트리거를 발동하는 함수는 lightwindow 클래스에 있음.
void light::emit11(){
    emit triggersignal11();
}
void light::emit12(){
    emit triggersignal12();
}
void light::emit13(){
    emit triggersignal13();
}
void light::emit1(){
    emit triggersignal1();
}
void light::emit2(){
    emit triggersignal2();
}
void light::emit3(){
    emit triggersignal3();
}
void light::emit4(){
    emit triggersignal4();
}
void light::emitblink(){
     emit nextblink();
}
/////////////////
/// 정답 전송 코드
void light::positionone(){ //왼쪽 위
    emit signalone();
}
void light::positiontwo(){ // 오른쪽 위
    emit signaltwo();
}
void light::positionthree(){ // 왼쪽 아래
    emit signalthree();
}
void light::positionfour(){ // 오른쪽 아래
    emit signalfour();
}
/////////////////
/// \brief light::restart
///다음 트라이얼 시작 코드
void light::restart(){
    emit end();
}
//////////////////////////////////////////
/// \brief light::sendans
/// 현재 몇번째 트라이얼인지 저장하는 함수.
/// 현재 위치의 result.txt 파일에 따로 저장해둔다.
void light::sendans(){// 정답 보내기 + 파일로 기록하기
    QString filename = "result.txt";
    QFile file(filename);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream in(&file);
    if(nowtraining){//트레이닝일경우
        in << "trial : " << Finl + 1 << '\r' <<'\n';
    }
    else{ // 테스트일경우 테스트 1번부터 기록
        in << " test : " << Finl + 1 - training << '\r' <<'\n';
    }
    in<< results[0] << results[1] << results[2] << results[3] << '\r' <<'\n'; //정답의 위치 기록
    in << "answer = " << ans << '\r' <<'\n';
    file.close();

    emit sendanswer(); // 그 이후 정답 보내기 실행. 실행위치는 lightwindow
}
QString light::currentDateTime() {
    //////////////////////////////////////////////////////////
    /// 시간 저장 함수
    time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

    return buf;
}

