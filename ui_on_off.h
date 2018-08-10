/********************************************************************************
** Form generated from reading UI file 'on_off.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ON_OFF_H
#define UI_ON_OFF_H

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

class Ui_On_Off
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *On_Off)
    {
        if (On_Off->objectName().isEmpty())
            On_Off->setObjectName(QStringLiteral("On_Off"));
        On_Off->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(On_Off->sizePolicy().hasHeightForWidth());
        On_Off->setSizePolicy(sizePolicy);
        On_Off->setAutoFillBackground(false);
        centralwidget = new QWidget(On_Off);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        On_Off->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(On_Off);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        On_Off->setStatusBar(statusbar);
        menubar = new QMenuBar(On_Off);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        On_Off->setMenuBar(menubar);

        retranslateUi(On_Off);

        QMetaObject::connectSlotsByName(On_Off);
    } // setupUi

    void retranslateUi(QMainWindow *On_Off)
    {
        On_Off->setWindowTitle(QApplication::translate("On_Off", "On-Off Control", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class On_Off: public Ui_On_Off {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ON_OFF_H
