#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "chat.h"
#include <QString>



namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();  

private slots:
    void on_pushButton_clicked();

private:
    Ui::client *ui;
    chat *ch = new chat;
};

#endif // CLIENT_H
