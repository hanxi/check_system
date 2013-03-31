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

// 获取服务器时间
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

// 注册新用户
void sendProtToSignIn(const char *name, const char *dep, const char *photo)
{
    Log log(__LOGARG__,1);
    log << "注册新用户" << Log::endl;
    Prot prot(protSignIn_C2S);
    prot.setField("name",name);
    prot.setField("dep",dep);
    prot.setField("photo",photo);
    log << "name=" << name << Log::endl;
    log << "dep=" << dep << Log::endl;
    Net* net = getNet();
    net->sendProt(gSockId,protSignIn_C2S);
}
void msgOnSignIn(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& result = prot.getField("result");
    log << "注册" << ((result.getNum()==0)?"成功":"失败") << Log::endl;
}

// 获取照片详细信息
void sendProtGetPhotoInfo()
{
}
void msgOnGetPhotoInfo(int sockId, int protId)
{
}

void regAllHandler()
{
    Prot::regHandler(protGetTime_S2C, (void*)msgOnGetTime);
}

