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
void sendProtToSignIn(const AutoType& name, const AutoType& dep, const AutoType& photo, int idx)
{
    Log log(__LOGARG__,1);
    log << "注册新用户" << Log::endl;
    Prot prot(protSignIn_C2S);
    prot.setField("name",name);
    prot.setField("dep",dep);
    prot.setField("photo",photo);
    prot.setField("idx",idx);
    log << "name=" << name.getStr() << Log::endl;
    log << "dep=" << dep.getStr() << Log::endl;
    Net* net = getNet();
    net->sendProt(gSockId,protSignIn_C2S);
}
void msgOnSignIn(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& result = prot.getField("result");
    log << "注册" << ((result.getNum()==0)?"成功":"失败") << Log::endl;
    win->toCheckFace();
}

// 获取照片详细信息
void sendProtGetPhotoInfo(const AutoType& photo)
{
    Prot prot(protGetPhotoInfo_C2S);
    prot.setField("photo",photo);
    Net* net = getNet();
    net->sendProt(gSockId,protGetPhotoInfo_C2S);
}
void msgOnGetPhotoInfo(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& result = prot.getField("result");
    AutoType& dep    = prot.getField("dep");
    AutoType& name   = prot.getField("name");
    AutoType& id     = prot.getField("id");
    log << "查询" << ((result.getNum()==0)?"成功":"失败") << Log::endl;
    log << "id=" << id.getNum() << Log::endl;
}

void sendProtCheckIn(const AutoType& photo)
{
    Prot prot(protCheckIn_C2S);
    prot.setField("photo",photo);
    Net* net = getNet();
    net->sendProt(gSockId,protCheckIn_C2S);
}

void msgOnCheckIn(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& result = prot.getField("result");
    AutoType& dep    = prot.getField("dep");
    AutoType& name   = prot.getField("name");
    AutoType& id     = prot.getField("id");
    log << "查询" << ((result.getNum()==0)?"成功":"失败") << Log::endl;
    log << "id=" << id.getNum() << Log::endl;
    if (result.getNum()==-1) {
        QString info(QString::fromLocal8Bit("未找到"));
        win->setLabelCheckInfo(info);
    }
    else {
        QString info("姓名：");
        info += name.getStr();
        info += "\n";
        info += "部门：";
        info += dep.getStr();
        info = QString::fromLocal8Bit(info.toAscii());
        win->setLabelCheckInfo(info);
    }
}

void sendProtToUpdateModel()
{
    Log log(__LOGARG__,1);
    log << "更新相片模板" << Log::endl;
    Net* net = getNet();
    net->sendProt(gSockId,protUpdateFaceModel_C2S);
}

void regAllHandler()
{
    Prot::regHandler(protGetTime_S2C, (void*)msgOnGetTime);
    Prot::regHandler(protSignIn_S2C, (void*)msgOnSignIn);
    Prot::regHandler(protGetPhotoInfo_S2C, (void*)msgOnGetPhotoInfo);
    Prot::regHandler(protCheckIn_S2C, (void*)msgOnCheckIn);
}

