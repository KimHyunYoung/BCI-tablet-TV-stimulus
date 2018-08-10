/********************************************************************************
** Form generated from reading UI file 'network_test.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORK_TEST_H
#define UI_NETWORK_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_network_test
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QSpinBox *spinBox;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *network_test)
    {
        if (network_test->objectName().isEmpty())
            network_test->setObjectName(QStringLiteral("network_test"));
        network_test->resize(800, 600);
        centralwidget = new QWidget(network_test);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(290, 80, 101, 61));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 320, 91, 71));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(280, 170, 101, 22));
        spinBox->setMaximum(65535);
        spinBox->setValue(6112);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(310, 140, 56, 12));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 320, 81, 31));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(240, 360, 81, 31));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 230, 71, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(360, 230, 71, 16));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 260, 113, 20));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(340, 260, 113, 20));
        network_test->setCentralWidget(centralwidget);
        menubar = new QMenuBar(network_test);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        network_test->setMenuBar(menubar);
        statusbar = new QStatusBar(network_test);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        network_test->setStatusBar(statusbar);

        retranslateUi(network_test);

        QMetaObject::connectSlotsByName(network_test);
    } // setupUi

    void retranslateUi(QMainWindow *network_test)
    {
        network_test->setWindowTitle(QApplication::translate("network_test", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("network_test", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">server</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("network_test", "send", Q_NULLPTR));
        label_3->setText(QApplication::translate("network_test", "port", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("network_test", "server start", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("network_test", "server stop", Q_NULLPTR));
        label_5->setText(QApplication::translate("network_test", "ip address", Q_NULLPTR));
        label_6->setText(QApplication::translate("network_test", "receive", Q_NULLPTR));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class network_test: public Ui_network_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORK_TEST_H
