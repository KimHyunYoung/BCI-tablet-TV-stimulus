/********************************************************************************
** Form generated from reading UI file 'doorlockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOORLOCKWINDOW_H
#define UI_DOORLOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_doorlockwindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_7;
    QLabel *label_13;
    QSpinBox *spinBox_8;
    QSpinBox *spinBox_9;
    QSpinBox *spinBox_10;
    QSpinBox *spinBox_11;
    QDoubleSpinBox *spinBox;
    QDoubleSpinBox *spinBox_2;
    QLineEdit *lineEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *doorlockwindow)
    {
        if (doorlockwindow->objectName().isEmpty())
            doorlockwindow->setObjectName(QStringLiteral("doorlockwindow"));
        doorlockwindow->setEnabled(true);
        doorlockwindow->resize(1951, 1210);
        doorlockwindow->setFocusPolicy(Qt::TabFocus);
        centralwidget = new QWidget(doorlockwindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 1351, 241));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(16);
        label->setFont(font);
        label->setFocusPolicy(Qt::WheelFocus);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 290, 701, 91));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAutoFillBackground(false);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1510, 540, 281, 161));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1510, 780, 281, 151));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 420, 251, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(14);
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(390, 420, 251, 31));
        label_4->setFont(font1);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(100, 660, 251, 31));
        label_11->setFont(font1);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(410, 650, 251, 31));
        label_12->setFont(font1);
        spinBox_6 = new QSpinBox(centralwidget);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setEnabled(true);
        spinBox_6->setGeometry(QRect(50, 690, 221, 101));
        spinBox_6->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_6->setMaximum(10000);
        spinBox_6->setValue(50);
        spinBox_7 = new QSpinBox(centralwidget);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setEnabled(true);
        spinBox_7->setGeometry(QRect(320, 690, 281, 101));
        spinBox_7->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_7->setMaximum(10000);
        spinBox_7->setValue(80);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(700, 430, 371, 31));
        label_13->setFont(font1);
        spinBox_8 = new QSpinBox(centralwidget);
        spinBox_8->setObjectName(QStringLiteral("spinBox_8"));
        spinBox_8->setEnabled(true);
        spinBox_8->setGeometry(QRect(660, 470, 251, 101));
        spinBox_8->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_8->setMaximum(10000);
        spinBox_8->setValue(10);
        spinBox_9 = new QSpinBox(centralwidget);
        spinBox_9->setObjectName(QStringLiteral("spinBox_9"));
        spinBox_9->setEnabled(true);
        spinBox_9->setGeometry(QRect(680, 680, 201, 81));
        spinBox_9->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_9->setMaximum(10000);
        spinBox_9->setValue(10);
        spinBox_10 = new QSpinBox(centralwidget);
        spinBox_10->setObjectName(QStringLiteral("spinBox_10"));
        spinBox_10->setEnabled(true);
        spinBox_10->setGeometry(QRect(680, 770, 201, 81));
        spinBox_10->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_10->setMaximum(10000);
        spinBox_10->setValue(7);
        spinBox_11 = new QSpinBox(centralwidget);
        spinBox_11->setObjectName(QStringLiteral("spinBox_11"));
        spinBox_11->setEnabled(true);
        spinBox_11->setGeometry(QRect(680, 860, 201, 101));
        spinBox_11->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_11->setMaximum(10000);
        spinBox_11->setValue(3);
        spinBox = new QDoubleSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(true);
        spinBox->setGeometry(QRect(50, 480, 231, 91));
        spinBox->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox->setMaximum(5000);
        spinBox->setSingleStep(10);
        spinBox->setValue(150);
        spinBox_2 = new QDoubleSpinBox(centralwidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setEnabled(true);
        spinBox_2->setGeometry(QRect(330, 470, 271, 101));
        spinBox_2->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_2->setMaximum(5000);
        spinBox_2->setSingleStep(10);
        spinBox_2->setValue(150);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(1230, 160, 471, 161));
        lineEdit->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        doorlockwindow->setCentralWidget(centralwidget);
        label_4->raise();
        label_2->raise();
        label_3->raise();
        label->raise();
        pushButton->raise();
        pushButton_2->raise();
        label_11->raise();
        label_12->raise();
        spinBox_6->raise();
        spinBox_7->raise();
        label_13->raise();
        spinBox_8->raise();
        spinBox_9->raise();
        spinBox_10->raise();
        spinBox_11->raise();
        spinBox->raise();
        spinBox_2->raise();
        lineEdit->raise();
        statusbar = new QStatusBar(doorlockwindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        doorlockwindow->setStatusBar(statusbar);

        retranslateUi(doorlockwindow);

        QMetaObject::connectSlotsByName(doorlockwindow);
    } // setupUi

    void retranslateUi(QMainWindow *doorlockwindow)
    {
        doorlockwindow->setWindowTitle(QApplication::translate("doorlockwindow", "TV Control", Q_NULLPTR));
        label->setText(QApplication::translate("doorlockwindow", "<html><head/><body><p><span style=\" font-size:48pt;\">Choose Stimulus type</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("doorlockwindow", "<html><head/><body><p><span style=\" font-size:26pt;\">Doorlock Setting</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("doorlockwindow", "Next", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("doorlockwindow", "Cancel", Q_NULLPTR));
        label_3->setText(QApplication::translate("doorlockwindow", "Dark time", Q_NULLPTR));
        label_4->setText(QApplication::translate("doorlockwindow", "Flash Time", Q_NULLPTR));
        label_11->setText(QApplication::translate("doorlockwindow", "training", Q_NULLPTR));
        label_12->setText(QApplication::translate("doorlockwindow", "testing", Q_NULLPTR));
        label_13->setText(QApplication::translate("doorlockwindow", "repeats", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("doorlockwindow", "10.16.27.208", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class doorlockwindow: public Ui_doorlockwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOORLOCKWINDOW_H
