/********************************************************************************
** Form generated from reading UI file 'doorlock.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOORLOCK_H
#define UI_DOORLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_doorlock
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *doorlock)
    {
        if (doorlock->objectName().isEmpty())
            doorlock->setObjectName(QStringLiteral("doorlock"));
        doorlock->resize(800, 600);
        menubar = new QMenuBar(doorlock);
        menubar->setObjectName(QStringLiteral("menubar"));
        doorlock->setMenuBar(menubar);
        centralwidget = new QWidget(doorlock);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        doorlock->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(doorlock);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        doorlock->setStatusBar(statusbar);

        retranslateUi(doorlock);

        QMetaObject::connectSlotsByName(doorlock);
    } // setupUi

    void retranslateUi(QMainWindow *doorlock)
    {
        doorlock->setWindowTitle(QApplication::translate("doorlock", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class doorlock: public Ui_doorlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOORLOCK_H
