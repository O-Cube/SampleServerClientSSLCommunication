#include "myserver.h"

#include "myserver.h"

#include <QSslServer>
#include <QSslConfiguration>
#include <QSslKey>
#include <QFile>
#include <memory>



MySslServer::MySslServer(QObject *parent)
    : QSslServer( parent )
{
    QSslConfiguration config = sslConfiguration();
    QList<QSslCertificate> certificateList = QSslCertificate::fromPath( QString( "/home/oyandut/SampleClientServerCommunicationWithSSL/certificates/server.crt" ) );
    QSslCertificate serverCertificate = certificateList.at( 0 );
    /* simply to test if the certificate was properly loaded */
    qDebug() << serverCertificate.expiryDate().toString();

    config.setLocalCertificate( serverCertificate );

    QByteArray keyByteArray;

    QFile file( QString("/home/oyandut/SampleClientServerCommunicationWithSSL/certificates/server.key") );
    if ( !file.open( QIODeviceBase::ReadOnly | QIODeviceBase::Text )) {
        qDebug() << "Opening server key was not succesful!";
        file.close();
    } else {
        keyByteArray = file.readAll();
        file.close();
    }

    QSslKey key( keyByteArray, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "oyandut" );

    config.setPrivateKey( key );
    config.setProtocol( QSsl::TlsV1_2OrLater );
    setSslConfiguration( config );

    connect( this, &QSslServer::pendingConnectionAvailable, this, [=] () {
        std::unique_ptr<QTcpSocket> socket( nextPendingConnection() );
        QByteArray message;
        QDataStream stream( &message, QIODeviceBase::WriteOnly );
        stream << "Hello World! /nYou are connected to my SSL Server. The weather today is very bright today. /nI hope it stays like this all the time.";
        socket->write( message, message.size() );
        socket->flush();
    });

    listen( QHostAddress( "127.0.0.1"), 60001 );
}

MySslServer::~MySslServer()
{
    close();
}

MyClient::MyClient(QObject *parent)
    : QObject( parent )
    , m_socket( new QSslSocket( this ) )
{
    QSslConfiguration config = m_socket->sslConfiguration();
    QString caPath( "/home/oyandut/SampleClientServerCommunicationWithSSL/certificates/ca.crt" );
    config.addCaCertificates( caPath );

    QByteArray ca;
    QFile file( "/home/oyandut/SampleClientServerCommunicationWithSSL/certificates/ca.key" );
    if ( !file.open( QIODeviceBase::ReadOnly | QIODeviceBase::Text ) ) {
        qDebug() << "Opening CA key was unsuccessful!";
        file.close();
    } else {
        ca = file.readAll();
        file.close();
    }
    QSslKey caKey( ca, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, QByteArray( "oyandut" ) );
    config.setProtocol( QSsl::TlsV1_2OrLater );
    config.setPrivateKey( caKey );

    m_socket->setSslConfiguration( config );

    m_socket->bind( QHostAddress( "127.0.0.1" ), 60002 );

    connect( m_socket, &QSslSocket::readyRead, this, [=] () {
        qDebug() << "Received message: " << m_socket->readAll();
    });

    m_socket->connectToHostEncrypted( QString( "127.0.0.1" ), 60001 );
}

MyClient::~MyClient()
{
    m_socket->close();
    delete m_socket;
}
