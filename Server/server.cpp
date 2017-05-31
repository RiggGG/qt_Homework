#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ip = getIP();
    ui->textEdit_ip->append(ip);
    ui->textEdit_ip->setReadOnly(true);
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
}
Server::~Server()
{
    delete ui;
}
void Server::init()
{
    int i = 8000;
    tcpServer->listen(QHostAddress::Any, i);
}

void Server::newConnectSlot()
{
    QTcpSocket *tcp = tcpServer->nextPendingConnection();
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessage()));
    userList << tcp;
    connect(tcp,SIGNAL(disconnected()),this,SLOT(removeUserFormList()));
}


//等待用户消息；
void Server::readMessage()
{
    QByteArray tmp;
    QString bb;
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    //qDebug() << socket->readAll();
    tmp.append(socket->readAll());

    if(tmp[0] == '%'){

        QString tmptmp(tmp);
        ipname = tmptmp.split("%");

        ips.append(ipname.at(1));
        ips.append("^");
        names.append(ipname.at(2));
        names.append("^");

        ipss = ips.split("^");
        namess = names.split("^");

        list();



    }else{
        for(int i = 0; i < userList.count(); i++)
        {
                 userList.at(i)->write(tmp);
        }
    }
}

QString Server::getIP()  //获取ip地址
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

void Server::on_pushButton_clicked()  //开启服务器；
{
    init();
}

void Server::removeUserFormList()
{
    QString tmp;

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
//    QTcpSocket *tcp = tcpServer->nextPendingConnection();

    socket->peerAddress().toString();

    if(userList.removeOne(socket)){
        list();
    }
}



void Server::list()
{
    QByteArray msg;
    QString aa;
    for(int i = 0; i < userList.count() && userList.at(i)->peerAddress().toString() != aa; i++){
        msg.append( userList.at(i)->peerAddress().toString());
         for(int k = 0; k <ipss.count(); k++){
             if( userList.at(i)->peerAddress().toString()== ipss.at(k)){
                 msg.append("\n");
                 msg.append(namess.at(k));
                 break;
             }
         }
        msg.append("   @");
        aa =  userList.at(i)->peerAddress().toString();
    }
    for(int j = 0; j <userList.count(); j++){
        userList.at(j)->write(msg);
    }
    msg.clear();
}
