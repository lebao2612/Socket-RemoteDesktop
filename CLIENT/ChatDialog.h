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
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>







#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 1024
#pragma comment(lib, "ws2_32.lib")
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <cstring>
#include <Windows.h>
#include <thread>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <conio.h>





SOCKET server, client;

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget* parent = nullptr) : QDialog(parent)
    {
        // Create QTextEdit for displaying messages
        messageTextEdit = new QTextEdit(this);
        messageTextEdit->setReadOnly(true);

        // Create QLineEdit for typing messages
        inputLineEdit = new QLineEdit(this);

        // Create QPushButton for sending messages
        sendButton = new QPushButton("All Disk", this);
        connect(sendButton, &QPushButton::clicked, this, &ChatDialog::onSendClicked);

        chooseButton = new QPushButton("Choose Folder", this);
        connect(chooseButton, &QPushButton::clicked, this, &ChatDialog::onChooseClicked);

        // Set up the layout
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(messageTextEdit);
        layout->addWidget(inputLineEdit);
        layout->addWidget(sendButton);
        layout->addWidget(chooseButton);

        // Set the window title
        setWindowTitle("File Window");
    }

public slots:
    void onSendClicked()
    {
        messageTextEdit->clear();

        std::string request = "LIST_DRIVES";

        int result = send(server, request.c_str(), request.size(), 0);

        

        // Receive and process the server's response
        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        result = recv(server, recvbuf, recvbuflen, 0);


        if (result > 0) {
            std::string driveInfo(recvbuf, result);

            if (driveInfo == "EMPTY") {
                messageTextEdit->append("This folder is empty.\n");
            }
            else {
                std::cout << "Received drive information: " << driveInfo << "\n";

                // Process the drive information as needed (display in UI, etc.)
                // For example, you can display the information in your QTextEdit
                messageTextEdit->append("Available Drives:\n" + QString::fromStdString(driveInfo));
            }
            
        }
        else if (result == 0) 
            std::cout << "Connection closed\n";
            
        
        else 
            std::cerr << "Recv failed: " << WSAGetLastError() << "\n";
    }

    void onChooseClicked() {
        messageTextEdit->clear();
        QString message = inputLineEdit->text();
        // Send the message to the server using your communication logic
        // ...

        std::string request = message.toStdString();
        int result = send(server, request.c_str(), request.size(), 0);

        // Receive and process the server's response
        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        result = recv(server, recvbuf, recvbuflen, 0);

        if (result > 0) {
            std::string driveInfo(recvbuf, result);

            if (driveInfo.empty() || driveInfo == "\n") {
                messageTextEdit->append("This folder is empty.\n");
            }
            else {
                std::cout << "Received drive information: " << driveInfo << "\n";
                messageTextEdit->append("Available Drives:\n" + QString::fromStdString(driveInfo));
            }

        }
        else if (result == 0) {
            messageTextEdit->append("This folder is empty.\n");
        }
        else
            std::cerr << "Recv failed: " << WSAGetLastError() << "\n";
    }

private:
    QTextEdit* messageTextEdit;
    QLineEdit* inputLineEdit;
    QPushButton* sendButton;
    QPushButton* chooseButton;
};
