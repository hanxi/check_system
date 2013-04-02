/*=============================================================================
#     FileName: net.h
#         Desc: 客户端网络模块
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-15 02:42:36
#      History:
=============================================================================*/

#ifndef __NET_H_
#define __NET_H_

#include "log.h"
#include <QtNetwork>
#include <QObject>
#include <QString>

class Net : public QObject
{
Q_OBJECT
private:
    QTcpSocket *m_tcpSocket;

public:
    Net(const char *ip, int port);
    virtual ~Net();

    void sendProt(int sockId, int protId);

private slots:
    void handleReceive();
    void handleDisconnected();
};

inline
Net::Net(const char *ip, int port)
{
    Log log(__LOGARG__,5);
    log << "连接服务器：ip = " << ip << ",port=" << port << Log::endl;
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(handleReceive()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));

    m_tcpSocket->connectToHost(QString(ip),port);
    log << "连接服务器成功" << Log::endl;
}

inline
Net::~Net()
{
    m_tcpSocket->close();
    delete m_tcpSocket;
}

#endif

