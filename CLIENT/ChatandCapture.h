#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDialog>
#include <QTextEdit>

class ChatandCapture : public QDialog
{
    Q_OBJECT

public:
    ChatandCapture(QWidget* parent = nullptr) : QDialog(parent)
    {
        // Tạo nút "Capture Screen"
        QPushButton* captureScreenButton = new QPushButton("Capture Screen", this);
        connect(captureScreenButton, &QPushButton::clicked, this, &ChatandCapture::onCaptureScreenClicked);

        // Tạo nút "Chat"
        QPushButton* chatButton = new QPushButton("Chat", this);
        connect(chatButton, &QPushButton::clicked, this, &ChatandCapture::onChatClicked);

        QPushButton* disButton = new QPushButton("Disconnect", this);
        connect(disButton, &QPushButton::clicked, this, &ChatandCapture::onDisconnectClicked);


        // Sắp xếp nút "Capture Screen" và "Chat" bằng QVBoxLayout
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(captureScreenButton);
        layout->addWidget(chatButton);
        layout->addWidget(disButton);

        // Thiết lập tiêu đề cho cửa sổ
        setWindowTitle("Capture Screen and Chat");
    }

public slots:
    void onCaptureScreenClicked();

    void onChatClicked();

    void onDisconnectClicked();
};

