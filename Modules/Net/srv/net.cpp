/*=============================================================================
#     FileName: net.cpp
#         Desc:  实现tcp服务器
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-13 11:51:11
#      History:
=============================================================================*/

#include "net.h"
#include <QTranslator>
#include <iostream>
#include "log.h"

void Net::start(int port)
{
    Log log(__LOGARG__,1);
    if (m_tcpServer!=0) {
        delete m_tcpServer;
    }
    m_tcpServer = new QTcpServer(0);
    log<<"新建tcpserver成功"<<Log::endl;
    if (!m_tcpServer->listen(QHostAddress::LocalHost,port)) {
        log << "启动服务器错误,port=" << port << Log::endl;
    }
    log<<"监听端口成功,port=" << port <<Log::endl;
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
    log<<"绑定新连接消息成功,connect" <<Log::endl;
}

void Net::handleNewConnection()
{
    Log log(__LOGARG__,1);
    m_mutexConn.lock();
    QTcpSocket *cliSocket = m_tcpServer->nextPendingConnection();
    connect(cliSocket, SIGNAL(readyRead()), this, SLOT(handleReceive()));  
    connect(cliSocket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    m_cliConns.insert(ConnContainer::value_type(cliSocket,0));

    log << "有新连接" << Log::endl;
    m_mutexConn.unlock();
}

void Net::handleReceive()
{
    Log log(__LOGARG__,1);
    log << "接收到消息" << Log::endl;
    QTcpSocket* cliConn = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(cliConn);
    in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里客户端和服务器端相同

    int protLen = m_cliConns.find(cliConn)->second;
    if (protLen==0) { // 开始接收包
        // 根据定义的协议格式，取前8byte 
        if(tcpSocket->bytesAvailable() < 2*sizeof(int)) return;
        int protId;
        in >> protId >> protLen;
        log << "protId=" << protId << Log::endl;
        log << "protLen=" << protLen << Log::endl;
    }
    if(tcpSocket->bytesAvailable() < protLen) return;
    //如果没有得到全部的数据，则返回，继续接收数据  
    in >> message;
    //将接收到的数据存放到变量中  
    ui->messageLabel->setText(message);  
    //显示接收到的数据  
}

void Net::handleDisConnected()
{
    Log log(__LOGARG__,1);
    log << "断开连接" << Log::endl;
    QTcpSocket* cliConn = qobject_cast<QTcpSocket*>(sender());
    m_mutexConn.lock();
    m_cliConns.remove(cliConn);
    m_mutexConn.unlock();
    cliConn->disconnect();
}


