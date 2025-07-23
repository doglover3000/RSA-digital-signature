#include "loginwindow.h"
#include "ui_loginwindow.h"
LoginWindow::LoginWindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::LoginWindow)
{
ui->setupUi(this);
ui->passwordEdit->setEchoMode(QLineEdit::Password);
mes = new QMessageBox();
mes->setWindowIcon(QIcon(":img/img/icon.png"));
mes->setWindowTitle("ЭЦП Ханнановой Э.");
wrW = new workwindow();
}
LoginWindow::~LoginWindow()
{
delete ui;
db.close();
}
void LoginWindow::back_button()
{
this->close();
emit openMain();
}
void LoginWindow::on_loginButton_clicked()
{
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost\\SQLEXPRESS; DATABASE=rsa;Trusted_Connection=yes");
db.setUserName("test");
db.setPassword("123456789");
db.open();
QString login, password;
login = ui->loginEdit->text();
password = ui->passwordEdit->text();
QSqlQuery q;
QByteArray byteArray;
byteArray.append(password.toLocal8Bit());
//byteArray.append(password.toLocal8Bit());
QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
QString strMD5 = hash.toHex();
if(q.exec("select login, password from users where login=\'"+ login +"\' and password=\'"+ strMD5 +"\'"))
{
if(q.next())
{
q.exec("select modul, exp from users where login=\'"+ login +"\'");
q.next();
wrW->mod = q.value(0).toULongLong();
wrW->oexp = q.value(1).toULongLong();
wrW->sexp = password.toULongLong();
wrW->show();
this->close();
} else
{
mes->setText("Неверные данные для входа!");
mes->setIcon(QMessageBox::Critical);
mes->show();
}
} else {
mes->setText("Не удалось выполнить запрос!");
mes->setIcon(QMessageBox::Critical);
mes->show();
}
}
Файл «registerwindow.h»
#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include "rsa.h"
#include <openssl/sha.h>
#include <QCryptographicHash>
namespace Ui {
class RegisterWindow;
}
class RegisterWindow : public QWidget
{
Q_OBJECT
public:
explicit RegisterWindow(QWidget *parent = nullptr);
QMessageBox *mb;
~RegisterWindow();
private:
Ui::RegisterWindow *ui;
QSqlDatabase db;
signals:
void openMain();
private slots:
void back_button();
void on_pushButton_clicked();
};
#endif // REGISTERWINDOW_H