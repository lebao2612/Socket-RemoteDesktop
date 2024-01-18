#pragma once
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

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

HHOOK keyboardHook;

SOCKET serverSocket1, serverSocket2, serverSocket3, serverSocket4, clientSocket1, clientSocket2, clientSocket3, clientSocket4;

#include <QtWidgets/QMainWindow>
#include <QApplication>

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDialog>
#include <QTextEdit>
#include <QFileDialog>
#include <QDataStream>


//#include "include.h"


using namespace cv;
//using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::cerr;
using std::string;
std::mutex dataMutex;
std::vector<char> revbufKey(6000000);
std::vector<char> revbufImage(6000000);
Mat receivedImage;

struct Data {
    char ch;
    int isCtrl;
    int isShift;
    int isCapsLock;
};

struct mouseData {
    int mouseX;
    int mouseY;
    bool leftButtonDown;
    bool rightButtonDown;
    bool scroll;
    int scrollAmount;
};

void Connection(SOCKET& server, SOCKET& client, int port)
{
    // Kh?i t?o Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "Khoi tao WinSock that bai\n";
        return;
    }
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return;
    }

    // Thi?t l?p d?a ch? server d? k?t n?i t?i client
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Thay d?i s? c?ng theo c?u hình server
    serverAddr.sin_addr.s_addr = inet_addr("192.168.21.136"); //

    if (connect(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return;
    }
    else {
        cout << "Connection successful!" << endl;
    }
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        bool pressCap = false;
        Data data;



        if (kbdStruct->vkCode == VK_LEFT || kbdStruct->vkCode == VK_RIGHT ||
            kbdStruct->vkCode == VK_UP || kbdStruct->vkCode == VK_DOWN) {
            data.ch = '\0'; // Không có ký t? nào du?c gõ
            data.isCtrl = (GetAsyncKeyState(VK_CONTROL)) != 0;
            data.isShift = (GetAsyncKeyState(VK_SHIFT)) != 0;
            data.isCapsLock = (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
            // G?i s? ki?n nh?n phím mui tên d?n máy ch?
            send(serverSocket1, (char*)(&data), sizeof(data), 0);
        }


        WCHAR unicodeChar;
        BYTE keyboardState[256];
        GetKeyboardState(keyboardState);

        if (ToUnicodeEx(kbdStruct->vkCode, kbdStruct->scanCode, keyboardState, &unicodeChar, 1, 0, NULL) == 1) {
            //data.ch = char(unicodeChar);
            data.isCtrl = (GetAsyncKeyState(VK_CONTROL)) != 0;
            data.isShift = (GetAsyncKeyState(VK_SHIFT)) != 0;
            data.isCapsLock = (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
            if (data.isCapsLock == 1 && ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0))
                data.isCapsLock = 0;
            else if (data.isCapsLock == 0 && ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0)) {
                data.isCapsLock = 1;
            }
        }

        if ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) == 0)
            data.ch = char(unicodeChar);
        else
            data.ch = '\0';

        send(serverSocket1, (char*)(&data), sizeof(data), 0);
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void Key()
{
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        Sleep(100);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(keyboardHook);
}

void ReceiveImage()
{
    // t?o m?t c?a s? có th? hi?n th? hình ?nh
    namedWindow("Received Image", WINDOW_NORMAL);

    // thi?t l?p c?a s? che toàn b? màn hình
    setWindowProperty("Received Image", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

    while (1)
    {
        waitKey(1);
        int bytes = recv(serverSocket2, revbufImage.data(), 512000, 0);  // S? d?ng revbufImage cho d? li?u hình ?nh
        if (bytes <= 0) {
            cout << "failed to receive image data." << endl;
            closesocket(serverSocket2);
            WSACleanup();
            return;
        }
        else {
            Mat receivedImage = imdecode(Mat(1, bytes, CV_8UC1, (void*)revbufImage.data()), IMREAD_COLOR);
            if (receivedImage.empty()) {
                cout << "Failed to decode received image." << endl;
                //continue;
            }
            else {
                // l?y kích thu?c màn hình
                int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                int screenHeight = GetSystemMetrics(SM_CYSCREEN);

                // thay d?i kích thu?c hình ?nh d? phù h?p v?i màn hình
                resize(receivedImage, receivedImage, Size(screenWidth, screenHeight));

                // hi?n th? hình ?nh trên c?a s?
                imshow("Received Image", receivedImage);
            }
        }
    }
}

void Mouse()
{
    POINT mouse;
    while (1)
    {
        Sleep(100);
        GetCursorPos(&mouse);
        mouseData mData;
        mData.leftButtonDown = ((GetAsyncKeyState(VK_LBUTTON) & 0x8001) != 0);
        mData.rightButtonDown = ((GetAsyncKeyState(VK_RBUTTON) & 0x8001) != 0);
        mData.scroll = ((GetAsyncKeyState(VK_MBUTTON) & 0x8001) != 0);
        mData.mouseX = mouse.x;
        mData.mouseY = mouse.y;

        // Ki?m tra tr?ng thái cu?n chu?t
        mData.scrollAmount = 0;
        if (mData.scroll)
        {
            SHORT scrollDelta = GET_WHEEL_DELTA_WPARAM(GET_KEYSTATE_WPARAM(GetAsyncKeyState(VK_MBUTTON)));
            mData.scrollAmount = scrollDelta / WHEEL_DELTA;  // L?y giá tr? cu?n chu?t
        }

        send(serverSocket3, reinterpret_cast<char*>(&mData), sizeof(mData), 0);
    }
}




std::string generateScreenshotFilename() {
    // Lấy thời gian hiện tại
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Chuyển đổi thời gian thành struct tm để lấy thông tin về ngày và giờ
    struct tm timeInfo;
    localtime_s(&timeInfo, &time);

    // Tạo chuỗi ngày giờ định dạng
    std::stringstream ss;
    ss << std::put_time(&timeInfo, "%Y%m%d_%H%M%S");

    // Thêm phần mở rộng file (ví dụ: .png)
    ss << ".jpg";

    return ss.str();
}



void runConnect() {
    Connection(serverSocket1, clientSocket1, 8080);
    Connection(serverSocket2, clientSocket2, 5050);
    Connection(serverSocket3, clientSocket3, 1010);
    Connection(serverSocket4, clientSocket4, 2020);


    std::thread t1(Key);
    std::thread t2(ReceiveImage);
    std::thread t3(Mouse);
    t1.join();
    t2.join();
    t3.join();

    // Ðóng socket và gi?i phóng b? nh?
    closesocket(serverSocket1);
    closesocket(serverSocket2);
    closesocket(serverSocket3);
    closesocket(serverSocket4);
    WSACleanup();
}

class ChatDialog;

class CaptureScreenDialog : public QDialog
{
    Q_OBJECT

public:
    CaptureScreenDialog(QWidget* parent = nullptr) : QDialog(parent)
    {

    }

public slots:
    void onCaptureScreenClicked()
    {
        int bytes = recv(serverSocket2, revbufImage.data(), 512000, 0);
        if (bytes <= 0) {
            cout << "failed to receive image data." << endl;
            closesocket(serverSocket2);
            WSACleanup();
            return;
        }
        else {
            Mat receivedImage = imdecode(Mat(1, bytes, CV_8UC1, (void*)revbufImage.data()), IMREAD_COLOR);
            if (receivedImage.empty()) {
                cout << "Failed to decode received image." << endl;
                //continue;
            }
            else {
                std::string name = "D:\\" + generateScreenshotFilename();
                cv::imwrite(name, receivedImage);
            }
        }
    }

};

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget* parent = nullptr) : QDialog(parent)
    {
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

        int result = send(serverSocket4, request.c_str(), request.size(), 0);

        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        result = recv(serverSocket4, recvbuf, recvbuflen, 0);


        if (result > 0) {
            std::string driveInfo(recvbuf, result);


            std::cout << "Received drive information: " << driveInfo << "\n";

            messageTextEdit->append("Available Drives:\n" + QString::fromStdString(driveInfo));

        }
        else if (result == 0)
            std::cout << "Connection closed\n";


        else
            std::cerr << "Recv failed: " << WSAGetLastError() << "\n";
    }

    /*closesocket(serverSocket4);
    WSACleanup();*/


    void onChooseClicked() {
        messageTextEdit->clear();


        QString message = inputLineEdit->text();
        // Send the message to the server using your communication logic
        // ...

        std::string request = message.toStdString();
        int result = send(serverSocket4, request.c_str(), request.size(), 0);



        // Receive and process the server's response
        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        result = recv(serverSocket4, recvbuf, recvbuflen, 0);




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
    void onCaptureScreenClicked() {
        int bytes = recv(serverSocket2, revbufImage.data(), 512000, 0);
        if (bytes <= 0) {
            cout << "failed to receive image data." << endl;
            closesocket(serverSocket2);
            WSACleanup();
            return;
        }
        else {
            Mat receivedImage = imdecode(Mat(1, bytes, CV_8UC1, (void*)revbufImage.data()), IMREAD_COLOR);
            if (receivedImage.empty()) {
                cout << "Failed to decode received image." << endl;
                //continue;
            }
            else {
                string name = "D:/" + generateScreenshotFilename();
                //cv::imwrite("D:/received_image.jpg", receivedImage);
                cv::imwrite(name, receivedImage);
            }
        }

    }

    void onChatClicked() {
        ChatDialog* chatDialog = new ChatDialog(this);
        chatDialog->exec();
    }
    void onDisconnectClicked() {
        std::string request = "DISCONNECT";

        int result = send(serverSocket4, request.c_str(), request.size(), 0);
        closesocket(serverSocket1);
        closesocket(serverSocket2);
        closesocket(serverSocket3);
        closesocket(serverSocket4);
        WSACleanup();
        exit(0);
    }
private:
    QTextEdit* messageTextEdit;
    QLineEdit* inputLineEdit;
    QPushButton* sendButton;
};



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
//    // Khi nút Connect được nhấn
    void onConnectClicked()
    {
        // Run runConnect asynchronously
        std::thread t1([this] {
            runConnect();
        });

        // Detach the thread to allow it to run independently
        t1.detach();
        ChatandCapture* chatandCapture = new ChatandCapture(this);
        chatandCapture->exec();

    }
};



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    khovl mainWindow;
    mainWindow.show();
    return app.exec();
}

