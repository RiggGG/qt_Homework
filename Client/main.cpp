#include "client.h"
#include "connection.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    if (!createConnection())
        return 1;
    client w;
    w.show();

    return a.exec();
}
