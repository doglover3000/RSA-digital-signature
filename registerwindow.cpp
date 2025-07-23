#include "registerwindow.h"
#include "ui_registerwindow.h"
RegisterWindow::RegisterWindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::RegisterWindow)
{
ui->setupUi(this);
mb = new QMessageBox;
mb->setWindowIcon(QIcon(":img/img/icon.png"));
mb->setWindowTitle("ЭЦП Ханнановой Э.");
}
RegisterWindow::~RegisterWindow()
{
delete ui;
db.close();
}
void RegisterWindow::back_button()
{
this->close();
emit openMain();
}
void RegisterWindow::on_pushButton_clicked()
{
RSA r;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost\\SQLEXPRESS; DATABASE=rsa;Trusted_Connection=yes");
db.setUserName("test");
db.setPassword("123456789");
db.open();
QString login, name;
login = ui->loginEdit->text();
name = ui->nameEdit->text();
QSqlQuery q;
r.GenerateKey();
QString pas = QString::number(r.secret_exp);
QByteArray byteArray;
byteArray.append(pas.toLocal8Bit());
QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
QString strMD5 = hash.toHex();
if(q.exec("insert into users (name, login, password, modul, exp) values (\'"+ name +"\', \'"+ login +"\', \'"+ strMD5 +"\', \'"+ QVariant(r.modulus).toString() +"\', \'"+ QVariant(r.open_exp).toString() +"\')"))
{
mb->setText("Вы успешно зарегестрированы!\nВаш пароль: " + QVariant(pas).toString());
mb->setIcon(QMessageBox::Information);
mb->show();
this->close();
emit openMain();
}
else {
mb->setText("Не удалось выполнить запрос!");
mb->setIcon(QMessageBox::Critical);
mb->show();
}
}