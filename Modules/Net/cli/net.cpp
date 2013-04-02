/*=============================================================================
#     FileName: net.cpp
#         Desc: 客户端网络消息模块
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-15 02:53:22
#      History:
=============================================================================*/

#include "net.h"
#include "prot.h"

const int PROT_BUF_HEAD_SIZE = 8;      //8byte协议头
const int PROT_BUF_MAXSIZE = 102400;   //最大协议长度为100k
typedef void (*handlerFunc)(int,int);  // 协议handler函数格式

void Net::handleReceive()
{
    Log log(__LOGARG__,5);
    log << "接收到消息" << Log::endl;
    QTcpSocket* cliSck = qobject_cast<QTcpSocket*>(sender());
    int sockId = 1; // 客户端，固定为1

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
    Log log(__LOGARG__,5);
    QTcpSocket* cliSck = qobject_cast<QTcpSocket*>(sender());
    log << "连接已经断开" << Log::endl;

    //释放内存
    cliSck->disconnect();
}

void Net::sendProt(int sockId, int protId)
{
    sockId = 1; // 客户端，固定为1
    Log log(__LOGARG__,5);
    Prot prot(protId);
    if (!prot.isRightProt()) {
        log << "未知的协议号：protId=" << protId << Log::endl;
        return;
    }
    char buf[PROT_BUF_MAXSIZE];
    int protLen = prot.serialize(buf,sizeof(buf));
    log << "protLen=" << protLen << Log::endl;
    int writeLen = 0;
    while (writeLen<protLen) {
        writeLen += m_tcpSocket->write(buf,protLen-writeLen);
        log << "发送数据给客户端,sockId=" << sockId << Log::endl;
        log << "writeLen=" << writeLen << Log::endl;
        log << "protLen=" << protLen << Log::endl;
    }
}


