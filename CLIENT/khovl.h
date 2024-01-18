#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include "ui_khovl.h"
class khovl : public QMainWindow
{
    Q_OBJECT

public:
    khovl(QWidget* parent = nullptr) : QMainWindow(parent)
    {
        // Tạo ô trắng để nhập chữ
        QLineEdit* lineEdit = new QLineEdit(this);

        // Tạo nút Connect
        QPushButton* connectButton = new QPushButton("Connect", this);
        connect(connectButton, &QPushButton::clicked, this, &khovl::onConnectClicked);

        // Sắp xếp ô trắng và nút bằng QHBoxLayout
        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(lineEdit);
        layout->addWidget(connectButton);

        // Tạo một QWidget để chứa layout
        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        // Đặt QWidget làm trung tâm của cửa sổ
        setCentralWidget(centralWidget);

        // Thiết lập tiêu đề cho cửa sổ
        setWindowTitle("Connect Example");
    }

public slots:
    // Khi nút Connect được nhấn
    void onConnectClicked();
};


