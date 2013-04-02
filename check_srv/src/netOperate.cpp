/*=============================================================================
#     FileName: netOperate.cpp
#         Desc: 网络相关操作
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-31 09:00:51
#      History:
=============================================================================*/
#include "netOperate.h"
#include "globalVar.h"
#include "protInit.h"
#include "log.h"
#include "db.h"

void msgOnGetTime(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    log << "接收到获取服务器时间的消息" << Log::endl;
    QDateTime t = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = t.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式

    Prot prot(protGetTime_S2C);
    prot.setField("time",(strTime.toStdString()).c_str());
    Net* net = getNet();
    net->sendProt(sockId,protGetTime_S2C);
    log << "time=" << strTime.toStdString() << Log::endl;
}

void msgOnSignIn(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& name = prot.getField("name");
    AutoType& dep = prot.getField("dep");
    AutoType& photo = prot.getField("photo");
    log << "name=" << name.getStr() << Log::endl;
    log << "dep=" << dep.getStr() << Log::endl;
    log << "photoLen=" << photo.getLen() << Log::endl;

    // 保存数据到数据库
    int empId = DB::bookInfoInsert(name.getStr(), dep.getStr(), photo);
    log << "empId=" << empId << Log::endl;
    //bool ret = DB::modelImgInsert(empId, photo);

    prot.setProt(protSignIn_S2C);
    prot.setField("result",(long)0);
    Net* net = getNet();
    net->sendProt(sockId,protSignIn_S2C);
}

void regAllHandler()
{
    Prot::regHandler(protGetTime_C2S, (void*)msgOnGetTime);
    Prot::regHandler(protSignIn_C2S, (void*)msgOnSignIn);
}

