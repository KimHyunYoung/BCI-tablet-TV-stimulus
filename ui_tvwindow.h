/********************************************************************************
** Form generated from reading UI file 'tvwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVWINDOW_H
#define UI_TVWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tvWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *radioButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *label_4;
    QRadioButton *radioButton_3;
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *tvWindow)
    {
        if (tvWindow->objectName().isEmpty())
            tvWindow->setObjectName(QStringLiteral("tvWindow"));
        tvWindow->setEnabled(true);
        tvWindow->resize(1951, 1210);
        tvWindow->setFocusPolicy(Qt::TabFocus);
        centralwidget = new QWidget(tvWindow);
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
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(1440, 10, 581, 141));
        radioButton->setStyleSheet(QLatin1String("font: 18pt \"08SeoulHangang\";\n"
""));
        radioButton->setChecked(false);
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
        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(1440, 220, 581, 151));
        radioButton_3->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
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
        spinBox_6->setEnabled(false);
        spinBox_6->setGeometry(QRect(50, 690, 221, 101));
        spinBox_6->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_6->setMaximum(10000);
        spinBox_6->setValue(50);
        spinBox_7 = new QSpinBox(centralwidget);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setEnabled(false);
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
        spinBox_8->setEnabled(false);
        spinBox_8->setGeometry(QRect(660, 470, 251, 101));
        spinBox_8->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_8->setMaximum(10000);
        spinBox_8->setValue(10);
        spinBox_9 = new QSpinBox(centralwidget);
        spinBox_9->setObjectName(QStringLiteral("spinBox_9"));
        spinBox_9->setEnabled(false);
        spinBox_9->setGeometry(QRect(680, 680, 201, 81));
        spinBox_9->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_9->setMaximum(10000);
        spinBox_9->setValue(10);
        spinBox_10 = new QSpinBox(centralwidget);
        spinBox_10->setObjectName(QStringLiteral("spinBox_10"));
        spinBox_10->setEnabled(false);
        spinBox_10->setGeometry(QRect(680, 770, 201, 81));
        spinBox_10->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_10->setMaximum(10000);
        spinBox_10->setValue(7);
        spinBox_11 = new QSpinBox(centralwidget);
        spinBox_11->setObjectName(QStringLiteral("spinBox_11"));
        spinBox_11->setEnabled(false);
        spinBox_11->setGeometry(QRect(680, 860, 201, 101));
        spinBox_11->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_11->setMaximum(10000);
        spinBox_11->setValue(3);
        spinBox = new QDoubleSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setGeometry(QRect(50, 480, 231, 91));
        spinBox->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox->setMaximum(5000);
        spinBox->setSingleStep(10);
        spinBox->setValue(150);
        spinBox_2 = new QDoubleSpinBox(centralwidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setEnabled(false);
        spinBox_2->setGeometry(QRect(330, 470, 271, 101));
        spinBox_2->setStyleSheet(QStringLiteral("font: 18pt \"08SeoulHangang\";"));
        spinBox_2->setMaximum(5000);
        spinBox_2->setSingleStep(10);
        spinBox_2->setValue(150);
        tvWindow->setCentralWidget(centralwidget);
        label_4->raise();
        label_2->raise();
        label_3->raise();
        label->raise();
        radioButton->raise();
        pushButton->raise();
        pushButton_2->raise();
        radioButton_3->raise();
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
        statusbar = new QStatusBar(tvWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        tvWindow->setStatusBar(statusbar);

        retranslateUi(tvWindow);

        QMetaObject::connectSlotsByName(tvWindow);
    } // setupUi

    void retranslateUi(QMainWindow *tvWindow)
    {
        tvWindow->setWindowTitle(QApplication::translate("tvWindow", "TV Control", Q_NULLPTR));
        label->setText(QApplication::translate("tvWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">Choose Stimulus type</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("tvWindow", "<html><head/><body><p><span style=\" font-size:26pt;\">On-Off Setting</span></p></body></html>", Q_NULLPTR));
        radioButton->setText(QApplication::translate("tvWindow", "On-Off : one by one", Q_NULLPTR));
        pushButton->setText(QApplication::translate("tvWindow", "Next", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("tvWindow", "Cancel", Q_NULLPTR));
        label_3->setText(QApplication::translate("tvWindow", "Dark time", Q_NULLPTR));
        label_4->setText(QApplication::translate("tvWindow", "Flash Time", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("tvWindow", "On-Off : row column", Q_NULLPTR));
        label_11->setText(QApplication::translate("tvWindow", "training", Q_NULLPTR));
        label_12->setText(QApplication::translate("tvWindow", "testing", Q_NULLPTR));
        label_13->setText(QApplication::translate("tvWindow", "repeats", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tvWindow: public Ui_tvWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVWINDOW_H
