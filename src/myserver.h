#ifndef MYSERVER_H
#define MYSERVER_H

#include <QSslServer>
class QSslSocket;

class MySslServer : public QSslServer
{
    Q_OBJECT
public:
    explicit MySslServer(QObject *parent = nullptr);
    ~MySslServer();
};

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient( QObject *parent = nullptr );
    ~MyClient();
private:
    QSslSocket *m_socket;
};

#endif // MYSERVER_H
