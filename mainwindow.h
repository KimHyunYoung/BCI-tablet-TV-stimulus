#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tvwindow.h"
#include "doorlockwindow.h"
#include "lightwindow.h"
#include "ui_mainwindow.h"
#include "test.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();


private:
    bool started = false;
    tvWindow *TV;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
