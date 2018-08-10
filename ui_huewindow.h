/********************************************************************************
** Form generated from reading UI file 'huewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUEWINDOW_H
#define UI_HUEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_huewindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *huewindow)
    {
        if (huewindow->objectName().isEmpty())
            huewindow->setObjectName(QStringLiteral("huewindow"));
        huewindow->resize(800, 600);
        centralwidget = new QWidget(huewindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 310, 231, 141));
        huewindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(huewindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        huewindow->setMenuBar(menubar);
        statusbar = new QStatusBar(huewindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        huewindow->setStatusBar(statusbar);

        retranslateUi(huewindow);

        QMetaObject::connectSlotsByName(huewindow);
    } // setupUi

    void retranslateUi(QMainWindow *huewindow)
    {
        huewindow->setWindowTitle(QApplication::translate("huewindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("huewindow", "start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class huewindow: public Ui_huewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUEWINDOW_H
