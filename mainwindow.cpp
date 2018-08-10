#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    lightwindow *Light = new lightwindow(ui->pushButton);
    Light->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    doorlockwindow *Door = new doorlockwindow(ui->pushButton);
    Door->show();
}

void MainWindow::on_pushButton_4_clicked()
{

    exit(1);
}

void MainWindow::on_pushButton_clicked()
{
    if(started){
        delete TV;
    }
    TV = new tvWindow(ui->pushButton);
    TV->setting_flick();
    TV->rowcol = false;
    TV->server_start();
    TV->show();
    started = true;
}
