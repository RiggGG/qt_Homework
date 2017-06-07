#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QLineEdit>

namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0);
    ~chat();
    void connectToServer(QString );
    QString getIP();
    void sendData(QString data);

private slots:
    void connectedSlot();
    void readMessage();

    void on_pushButton_send_clicked();

    void on_pushButton_con_clicked();

    void on_pushButton_dis_clicked();

    void on_pushButton_clicked();

private:
    Ui::chat *ui;
    QTcpSocket *tcpSocket;
    QStringList tm,rm,pps;
    QByteArray ipname;
    QString ip;
};

#endif // CHAT_H
