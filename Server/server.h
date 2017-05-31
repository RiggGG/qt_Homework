#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>


namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
    QTcpServer *tcpServer;
    void init();
    QString getIP();
    void uselist();
    void NAME(QTcpSocket* ,QByteArray);
    void list();

private slots:
    void on_pushButton_clicked();
    void newConnectSlot();
    void readMessage();
    void removeUserFormList();

private:
    Ui::Server *ui;
    QString ip;
    QList < QTcpSocket *> userList;
    QList <QByteArray> userName;
    QList <QString> userIP;
    QStringList ipname,ipss,namess;
    int ii;
    QString ips,names;
};

#endif // SERVER_H
