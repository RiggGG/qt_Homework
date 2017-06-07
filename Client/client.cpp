#include "client.h"
#include "ui_client.h"
#include "connection.h"



client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
}

client::~client()
{
    delete ui;
}

void client::on_pushButton_clicked()
{
    QString a = ui->lineEdit_2->text();
    QString b = ui->lineEdit->text();
    QSqlQuery query;

    query.prepare("insert into usr(usrName,passWord)"
                  "values(:name, :pwd)");
    query.bindValue(":name", a);
    query.bindValue(":pwd", b);
    query.exec();

    this->hide();
    ch->sendData(ui->lineEdit_2->text());
    ch->show();
}
