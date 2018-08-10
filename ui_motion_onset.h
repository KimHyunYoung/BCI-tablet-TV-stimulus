/********************************************************************************
** Form generated from reading UI file 'motion_onset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTION_ONSET_H
#define UI_MOTION_ONSET_H

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

class Ui_Motion_Onset
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Motion_Onset)
    {
        if (Motion_Onset->objectName().isEmpty())
            Motion_Onset->setObjectName(QStringLiteral("Motion_Onset"));
        Motion_Onset->resize(800, 600);
        centralwidget = new QWidget(Motion_Onset);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Motion_Onset->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Motion_Onset);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Motion_Onset->setMenuBar(menubar);
        statusbar = new QStatusBar(Motion_Onset);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Motion_Onset->setStatusBar(statusbar);

        retranslateUi(Motion_Onset);

        QMetaObject::connectSlotsByName(Motion_Onset);
    } // setupUi

    void retranslateUi(QMainWindow *Motion_Onset)
    {
        Motion_Onset->setWindowTitle(QApplication::translate("Motion_Onset", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Motion_Onset: public Ui_Motion_Onset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTION_ONSET_H
