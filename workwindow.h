#ifndef WORKWINDOW_H
#define WORKWINDOW_H
#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFileDialog>
#include <QMessageBox>
#include "rsa.h"
namespace Ui {
class workwindow;
}
class workwindow : public QWidget
{
Q_OBJECT
public:
explicit workwindow(QWidget *parent = nullptr);
int combochoice;
uint64_t sexp;
uint64_t oexp;
uint64_t mod;
QMessageBox *mes;
QMessageBox *yn;
~workwindow();
private slots:
void on_backButton_clicked();
void on_chooseBox_currentIndexChanged(int index);
void on_SignFileButton_clicked();
void on_CheckSignButton_clicked();
void on_CheckFileButton_clicked();
void on_SignButton_clicked();
void on_checkSignButton_clicked();
void on_updateButton_clicked();
private:
Ui::workwindow *ui;
QSqlDatabase db;
};
#endif // WORKWINDOW_H