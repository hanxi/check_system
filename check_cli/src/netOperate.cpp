/*=============================================================================
#     FileName: netOperate.cpp
#         Desc: 网络交互操作
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-30 10:10:36
#      History:
=============================================================================*/
#include "netOperate.h"
#include "globalVar.h"
#include "protInit.h"
#include "log.h"

void sendProtGetTime()
{
    Net* net = getNet();
    net->sendProt(gSockId,protGetTime_C2S);
}

void msgOnGetTime(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    log << "接收到服务器时间" << Log::endl;
    Prot prot(protId);
    AutoType& time = prot.getField("time");
    log << "time=" << time.getStr() << Log::endl;
}

void regAllHandler()
{
    Prot::regHandler(protGetTime_S2C, (void*)msgOnGetTime);
}

