/********************************************************************************
** Form generated from reading UI file 'light.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHT_H
#define UI_LIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_light
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *light)
    {
        if (light->objectName().isEmpty())
            light->setObjectName(QStringLiteral("light"));
        light->setEnabled(true);
        light->resize(1951, 1210);
        light->setFocusPolicy(Qt::TabFocus);
        centralwidget = new QWidget(light);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        light->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(light);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        light->setStatusBar(statusbar);

        retranslateUi(light);

        QMetaObject::connectSlotsByName(light);
    } // setupUi

    void retranslateUi(QMainWindow *light)
    {
        light->setWindowTitle(QApplication::translate("light", "TV Control", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class light: public Ui_light {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHT_H
