/********************************************************************************
** Form generated from reading UI file 'SERVER.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SERVERClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SERVERClass)
    {
        if (SERVERClass->objectName().isEmpty())
            SERVERClass->setObjectName("SERVERClass");
        SERVERClass->resize(600, 400);
        centralWidget = new QWidget(SERVERClass);
        centralWidget->setObjectName("centralWidget");
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(160, 130, 141, 61));
        SERVERClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SERVERClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        SERVERClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SERVERClass);
        mainToolBar->setObjectName("mainToolBar");
        SERVERClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SERVERClass);
        statusBar->setObjectName("statusBar");
        SERVERClass->setStatusBar(statusBar);

        retranslateUi(SERVERClass);

        QMetaObject::connectSlotsByName(SERVERClass);
    } // setupUi

    void retranslateUi(QMainWindow *SERVERClass)
    {
        SERVERClass->setWindowTitle(QCoreApplication::translate("SERVERClass", "SERVER", nullptr));
        pushButton->setText(QCoreApplication::translate("SERVERClass", "Project 01", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SERVERClass: public Ui_SERVERClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
