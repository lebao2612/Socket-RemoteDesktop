/********************************************************************************
** Form generated from reading UI file 'khovl.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KHOVL_H
#define UI_KHOVL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_khovlClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *khovlClass)
    {
        if (khovlClass->objectName().isEmpty())
            khovlClass->setObjectName("khovlClass");
        khovlClass->resize(600, 400);
        menuBar = new QMenuBar(khovlClass);
        menuBar->setObjectName("menuBar");
        khovlClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(khovlClass);
        mainToolBar->setObjectName("mainToolBar");
        khovlClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(khovlClass);
        centralWidget->setObjectName("centralWidget");
        khovlClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(khovlClass);
        statusBar->setObjectName("statusBar");
        khovlClass->setStatusBar(statusBar);

        retranslateUi(khovlClass);

        QMetaObject::connectSlotsByName(khovlClass);
    } // setupUi

    void retranslateUi(QMainWindow *khovlClass)
    {
        khovlClass->setWindowTitle(QCoreApplication::translate("khovlClass", "khovl", nullptr));
    } // retranslateUi

};

namespace Ui {
    class khovlClass: public Ui_khovlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KHOVL_H
