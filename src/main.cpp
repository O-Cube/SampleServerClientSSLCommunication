#include <QCoreApplication>

#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MySslServer server;
    MyClient client;
    return a.exec();
}
