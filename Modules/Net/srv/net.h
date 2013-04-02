/*=============================================================================
#     FileName: net.h
#         Desc: 网络发送接收模块，tcp服务器
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-12 18:34:44
#      History:
=============================================================================*/

#ifndef __NET_H_
#define __NET_H_

#include "log.h"
#include <QtNetwork>
#include <QObject>
#include <map>


class Net : public QObject
{
Q_OBJECT
private:
    typedef std::map<int, QTcpSocket*> ConnContainer;
    ConnContainer  m_cliConns;
    QTcpServer*           m_tcpServer;

public:
    Net(int port);
    virtual ~Net();

    void sendProt(int sockId, int protId);


private slots:
    void handleNewConnection();
    void handleReceive();
    void handleDisconnected();
};

inline
Net::Net(int port):m_tcpServer(0)
{
    Log log(__LOGARG__,5);
    if (m_tcpServer!=0) {
        log << "重启服务器中。。。" << Log::endl;
        delete m_tcpServer;
    }
    m_tcpServer = new QTcpServer(this);
    log<<"新建tcpserver成功"<<Log::endl;
    if (!m_tcpServer->listen(QHostAddress::LocalHost,port)) {
        log << "启动服务器错误,port=" << port << Log::endl;
    }
    log<<"监听端口成功,port=" << port <<Log::endl;
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
    log<<"绑定新连接消息成功,connect" <<Log::endl;
}

inline
Net::~Net()
{
    m_tcpServer->close();
    delete m_tcpServer;
}


#endif

