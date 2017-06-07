#ifndef CONNECTION_H
#define CONNECTION_H


#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("User.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    // 创建Usr表
    query.exec("create table usr (usrName varchar primary key, "
                       "pwd varchar)");

    // 创建chat表
    query.exec("create table chat (usrName varchar, "
                       "chatValue varchar,"
                        "FOREIGN KEY(usrName) REFERENCES usr(usrName))");


    return true;
}
#endif // CONNECTION_H
