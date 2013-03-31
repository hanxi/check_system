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
#include "prot.h"

const int PROT_BUF_HEAD_SIZE = 8;     //8byte协议头
const int PROT_BUF_MAXSIZE = 10240;   //最大协议长度为10k
typedef void (*handlerFunc)(int,int); // 协议handler函数格式

void Net::handleNewConnection()
{
    Log log(__LOGARG__,1);
    QTcpSocket* cliSck = m_tcpServer->nextPendingConnection();
    int sockId = cliSck->socketDescriptor();
    connect(cliSck, SIGNAL(readyRead()), this, SLOT(handleReceive()));
    connect(cliSck, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    m_cliConns.insert(ConnContainer::value_type(sockId,cliSck));
    log << "有新连接,sockId=" << sockId << Log::endl;
    log << "现连接总数：" << m_cliConns.size() << Log::endl;
}

void Net::handleReceive()
{
    Log log(__LOGARG__,1);
    log << "接收到消息" << Log::endl;
    QTcpSocket* cliSck = qobject_cast<QTcpSocket*>(sender());
    int sockId = cliSck->socketDescriptor();

    int dataSize = cliSck->bytesAvailable();
    while (dataSize>=PROT_BUF_HEAD_SIZE) {
        static char peekBuf[PROT_BUF_HEAD_SIZE];//8byte协议头
        int protId = -1;
        int protLen = 0;
        if (cliSck->peek(peekBuf, sizeof(peekBuf)) != sizeof(peekBuf)) {
            return;
        }

        Prot::peekBufferInfo(peekBuf,sizeof(int)*2,protId,protLen);
        if (dataSize<protLen) { // 不足一个prot,下次再读
            return;
        }
        log << "接收到完整包：protId=" << protId << ",protLen=" << protLen << Log::endl;

        Prot prot(protId);
        static char buf[PROT_BUF_MAXSIZE];
        int readLen = cliSck->read(buf,protLen);
        if (readLen < protLen) {
            // 不会执行到这里的，如果执行到这里了，则下次再读数据。
            log << "读取数据到buf出错，readLen=" << readLen << Log::endl;
            return;
        }

        if (!prot.isRightProt()) {
            log << "未知的协议号：protId=" << protId << ",protLen=" << protLen << Log::endl;
            return;
        }
        int ret = prot.unSerialize(buf,protLen);
        if (ret>0) {
            log << "在这里调用注册函数." << Log::endl;
            prot.printProt();
            void* func = Prot::getHandler(protId);
            if (func==0) {
                log << "协议号未注册." << Log::endl;
            }
            else {
                handlerFunc handler = (handlerFunc)func;
                handler(sockId,protId);
            }
        }
        log << "读取数据并解析数据到prot完毕." << Log::endl;
        dataSize = cliSck->bytesAvailable();
    }
}

void Net::handleDisconnected()
{
    Log log(__LOGARG__,1);
    QTcpSocket* cliSck = qobject_cast<QTcpSocket*>(sender());
    for (ConnContainer::iterator iter=m_cliConns.begin(); iter!=m_cliConns.end();) {
        if (iter->second==cliSck) {
            log << "客户端断开连接,sockId=" << iter->first << Log::endl;
            m_cliConns.erase(iter++); // 移除连接
        }
        else {
            ++iter;
        }
    }
    //释放内存
    cliSck->disconnect();
}

void Net::sendProt(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    if (!prot.isRightProt()) {
        log << "未知的协议号：protId=" << protId << Log::endl;
        return;
    }
    char buf[PROT_BUF_MAXSIZE];
    int protLen = prot.serialize(buf,sizeof(buf));
    int writeLen = 0;
    QTcpSocket* cliSck = (m_cliConns.find(sockId))->second;
    while (writeLen<protLen) {
        writeLen += cliSck->write(buf,protLen-writeLen);
        log << "发送数据给客户端,sockId=" << sockId << Log::endl;
    }
}


