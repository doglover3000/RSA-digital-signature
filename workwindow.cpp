#include "ui_workwindow.h"
#include "workwindow.h"
workwindow::workwindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::workwindow)
{
ui->setupUi(this);
mes = new QMessageBox();
mes->setWindowIcon(QIcon(":img/img/icon.png"));
mes->setWindowTitle("ЭЦП Ханнановой Э.");
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost\\SQLEXPRESS; DATABASE=rsa;Trusted_Connection=yes");
db.setUserName("test");
db.setPassword("123456789");
QSqlQuery q;
if(db.open())
{
q.exec("select name from users order by name");
while(q.next())
ui->chooseBox->addItem(q.value(0).toString());
}
combochoice = 0;
}
workwindow::~workwindow()
{
delete ui;
}
void workwindow::on_backButton_clicked()
{
QApplication::quit();
}
void workwindow::on_chooseBox_currentIndexChanged(int index)
{
combochoice = index;
}

void workwindow::on_SignFileButton_clicked()
{
QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для подписи", QDir::currentPath(), tr("PDF файлы (*.pdf);; Документы Word (*.doc, *.docx);; Текстовые файлы (*.txt)"));
ui->SignFileEdit->setText(filename);
}
void workwindow::on_CheckSignButton_clicked()
{
QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для подписи", QDir::currentPath(), tr("Файлы подписи (*.sig)"));
ui->CheckSignEdit->setText(filename);
}
void workwindow::on_CheckFileButton_clicked()
{
QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для подписи", QDir::currentPath(), tr("PDF файлы (*.pdf);; Документы Word (*.doc, *.docx);; Текстовые файлы (*.txt)"));
ui->CheckFileEdit->setText(filename);
}
void workwindow::on_SignButton_clicked()
{
RSA r;

if (r.Encrypt(ui->SignFileEdit->text(), this->sexp, this->mod) == OK)
{
QFile f(ui->SignFileEdit->text());
QString sign = QFileInfo(f).fileName();
mes->setText("Файл успешно подписан! \nПодпись: " + sign + ".sig");
mes->setIcon(QMessageBox::Information);
mes->show();
}
}
void workwindow::on_checkSignButton_clicked()
{
RSA r;
qDebug() << this->combochoice;
QSqlQuery qr;
qr.exec("select name, modul, exp from users order by name ");
for(int i = 0; i<=this->combochoice; i++)
qr.next();
uint64_t mod = qr.value(1).toULongLong();
uint64_t exp = qr.value(2).toULongLong();
std::string res = r.Decipher(ui->CheckSignEdit->text(), exp, mod);
qDebug() << res;
QFile chfile(ui->CheckFileEdit->text());
if(chfile.open(QFile::ReadOnly))
{
QCryptographicHash h(QCryptographicHash::Sha1);
h.addData(&chfile);
chfile.close();
QString hash = QString("%1").arg(QString(h.result().toHex()));
qDebug()<<hash;
std::string file_h = hash.toStdString();
if(file_h == res)
{
mes->setText("Подпись верна!");
mes->setIcon(QMessageBox::Information);
mes->show();
}
else
{
mes->setText("Подпись не совпадает!");
mes->setIcon(QMessageBox::Warning);
mes->show();
}
}
else {
mes->setText("Невозможно открыть файл!");
mes->setIcon(QMessageBox::Critical);
mes->show();
}
}
void workwindow::on_updateButton_clicked()
{
QMessageBox::StandardButton reply = QMessageBox::question(this, "Поддтверждение", "При обновлении ваш аккаунт сохраниться, но все ваши прошлые подписи станут недействительными", QMessageBox::Ok | QMessageBox::Cancel);
if (reply == QMessageBox::Ok)
{
RSA r;
r.GenerateKey();
QSqlQuery qr;
qDebug() << this->oexp;
QString pas = QString::number(r.secret_exp);
QByteArray byteArray;
byteArray.append(pas.toLocal8Bit());
QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
QString strMD5 = hash.toHex();
//("insert into users (name, login, password, modul, exp)
//values (\'"+ name +"\', \'"+ login +"\', \'"+ strMD5 +"\',
//\'"+ QVariant(r.modulus).toString() +"\', \'"+ QVariant(r.open_exp).toString() +"\')"))
if(qr.exec("update users set password=\'"+ strMD5 +"\', modul=\'"+ QVariant(r.modulus).toString() +"\', exp=\'"+ QVariant(r.open_exp).toString() +"\' where modul=\'"+ QVariant(this->mod).toString() +"\'"))
{
mes->setText("Подпись обновлена!\nВаш новый пароль: " + QVariant(pas).toString());
mes->setIcon(QMessageBox::Information);
mes->show();
}
}
else
qDebug() << "cancel";
}