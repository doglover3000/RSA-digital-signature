#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "loginwindow.h"
#include "registerwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
private:
Ui::MainWindow *ui;
LoginWindow *loginW;
RegisterWindow *regW;
private slots:
void openAuth();
void openReg();
};
#endif // MAINWINDOW_H
Файл «mainwindow.cpp»
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
ui->setupUi(this);
loginW = new LoginWindow();
regW = new RegisterWindow();
connect(loginW, &LoginWindow::openMain, this, &MainWindow::show);
connect(regW, &RegisterWindow::openMain, this, &MainWindow::show);
//registerWindow = new AnotherWindow()
}
void MainWindow::openAuth()
{
loginW->show();
this->close();
}
void MainWindow::openReg()
{
regW->show();
this->close();
}
MainWindow::~MainWindow()
{
delete ui;
}