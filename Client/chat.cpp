#include "chat.h"
#include "ui_chat.h"
#include "connection.h"
#include <QFile>
#include <QTextStream>
chat::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    ip = getIP();
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this, SLOT(connectedSlot()));
    connect(ui->lineEdit_send,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
}

chat::~chat()
{
    delete ui;
}

void chat::connectToServer(QString server)                  //与服务器建立连接；
{
    tcpSocket->connectToHost(server,8000);
}

void chat::readMessage()                            //读消息；
{
    QString tmp;
    tmp = tcpSocket->readAll();

    if(tmp.contains("   @") ){
        ui->listWidget->clear();
        tm = tmp.split("   @");
        for(int i = 0; i < tm.count(); i ++){
                ui->listWidget->addItem(tm.at(i));
        }
    }
    else{
    ui->textEdit->append( tmp );
    }
}

void chat::connectedSlot()
{
    qDebug()<<"connect OK!";
    QMessageBox::warning(this,tr("Congradulation"),tr("succeed！"),QMessageBox::Yes);
}


void chat::on_pushButton_send_clicked()
{
    QByteArray tmp,name;
    QString a = ui->lineEdit_name->text();
    QString b = ui->lineEdit_send->text();
    QSqlQuery query1;
    name.append(ui->lineEdit_name->text());
    name.append(": ");
    tmp.append( /*ip + "  "+ */"["+name+"]" + ui->lineEdit_send->text() );
    tcpSocket->write(  tmp + '\n' );

    tcpSocket->flush();
    ui->lineEdit_send->clear();
    ui->lineEdit_send->setFocus();


    query1.prepare("insert into chat(usrName,chatValue)"
                  "values(:name, :value)");
    query1.bindValue(":name", a);
    query1.bindValue(":value", b);
    query1.exec();
}


QString chat::getIP()  //获取ip地址
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list){
       if(address.protocol() == QAbstractSocket::IPv4Protocol){
           if (address.toString().contains("127.0.")){
               continue;
           }
           return address.toString();
       }
    }
    return 0;
}


void chat::on_pushButton_con_clicked()
{
    QString serverIP = ui->lineEdit_ip->text();
    connectToServer(serverIP);
    ipname.append("%");
    ipname.append(ip);
    ipname.append("%");
    ipname.append(ui->lineEdit_name->text());
    tcpSocket->write(ipname);
    connect(tcpSocket,SIGNAL(readyRead()),this, SLOT(readMessage()));
}



void chat::on_pushButton_dis_clicked()
{
    tcpSocket->disconnectFromHost();
    ui->pushButton_con->setDisabled(false);
    ui->listWidget->clear();
}

void chat::sendData(QString data)
{
    ui->lineEdit_name->setText(data);
}



void chat::on_pushButton_clicked()
{
    QFile file("chat.txt");
    if (!file.open(QIODevice::WriteOnly)) {
    return;
    }
    QTextStream out(&file);
    QSqlQuery query;
    bool ok;
    QString chatn;
    QString chatt;
    ok=query.exec("select * from chat");
    while(query.next())
    {
        chatn=query.value(0).toString();
        chatt=query.value(1).toString();
        out<<chatn<<":"<<chatt<<endl;
    }
    if(ok){
        QMessageBox::information(this,"notice","add successed!!");
    }
    else{
        QMessageBox::information(this,"notice","add failed！");
    }
}
