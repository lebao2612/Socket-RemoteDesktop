#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SERVER.h"

class SERVER : public QMainWindow
{
    Q_OBJECT

public:
    SERVER(QWidget *parent = nullptr);
    ~SERVER();

private:
    Ui::SERVERClass ui;
};
