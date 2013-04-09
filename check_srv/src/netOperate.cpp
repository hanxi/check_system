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
#include "faceRecognition.h"
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
    AutoType& idx = prot.getField("idx");
    log << "name=" << name.getStr() << Log::endl;
    log << "dep=" << dep.getStr() << Log::endl;
    log << "photoLen=" << photo.getLen() << Log::endl;

    // 保存数据到数据库
    QDateTime t = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = t.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式

    static std::map<std::string,int> name2Id;
    std::string nameStr(name.getStr());
    if (name2Id.end()==name2Id.find(nameStr)) {
        int empId = DB::book_info_insert(name.getStr(), dep.getStr(), (strTime.toStdString()).c_str(), photo);
        log << "empId=" << empId << Log::endl;
        name2Id[nameStr] = empId;
    }
    int model_img_id = DB::model_img_insert(name2Id[nameStr], photo);
    log << "model_img_id=" << model_img_id << Log::endl;

    if (idx.getNum()==19) { // 注册发19张照片
        name2Id.erase(nameStr);
    }

    prot.setProt(protSignIn_S2C);
    prot.setField("result",(long)0);
    Net* net = getNet();
    net->sendProt(sockId,protSignIn_S2C);
}

void msgOnUpdateFaceModel(int sockId, int protId)
{
    bool ret = updateFaceLibrary();
    int result = -1;
    if (ret) {
        result = 0;
    }
    Prot prot(protUpdateFaceModel_S2C);
    prot.setField("result",result);
    Net* net = getNet();
    net->sendProt(sockId,protUpdateFaceModel_S2C);
}

void msgOnGetPhotoInfo(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& photo = prot.getField("photo");
    cv::Mat image = AutoType2Mat(photo);
    log << "image:channels=" << image.channels() << Log::endl;
    cv::imwrite("tmp2.jpg",image);

    AutoType dep("empty");
    AutoType name("empty");
    int result = 0;
    int id = faceRecognition(image);

    if (-1==id) {
        result = -1;
    }
    else {
        std::vector<DB::book_info_Rec> recs;
        bool ret = book_info_select_by_emp_id(id, recs);
        if (!ret || recs.size()<1) {
            result = -1;
            dep = "hao";
            name = "hanxi";
        }
        else {
            result = 0;
            dep = recs[0].dep_name;
            name = recs[0].emp_name;
        }
    }

    prot.setProt(protGetPhotoInfo_S2C);
    prot.setField("result",AutoType(result));
    prot.setField("dep",dep);
    prot.setField("name",name);
    prot.setField("id",AutoType(id));
    Net* net = getNet();
    net->sendProt(sockId,protGetPhotoInfo_S2C);
}

void msgOnCheckIn(int sockId, int protId)
{
    Log log(__LOGARG__,1);
    Prot prot(protId);
    AutoType& photo = prot.getField("photo");
    cv::Mat image = AutoType2Mat(photo);
    log << "image:channels=" << image.channels() << Log::endl;
    cv::imwrite("tmp2.jpg",image);

    AutoType dep("empty");
    AutoType name("empty");
    int result = 0;
    int id = faceRecognition(image);
    if (-1==id) {
        result = -1;
    }
    else {
        std::vector<DB::book_info_Rec> recs;
        bool ret = book_info_select_by_emp_id(id, recs);
        if (!ret || recs.size()<1) {
            result = -1;
            dep = "hao";
            name = "hanxi";
        }
        else {
            result = 0;
            dep = recs[0].dep_name;
            name = recs[0].emp_name;
        }
    }
    QDateTime t = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = t.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    DB::work_time_insert(id, (strTime.toStdString()).c_str(), photo);

    prot.setProt(protCheckIn_S2C);
    prot.setField("result",AutoType(result));
    prot.setField("dep",dep);
    prot.setField("name",name);
    prot.setField("id",AutoType(id));
    Net* net = getNet();
    net->sendProt(sockId,protCheckIn_S2C);
}

void regAllHandler()
{
    Prot::regHandler(protGetTime_C2S, (void*)msgOnGetTime);
    Prot::regHandler(protSignIn_C2S, (void*)msgOnSignIn);
    Prot::regHandler(protUpdateFaceModel_C2S, (void*)msgOnUpdateFaceModel);
    Prot::regHandler(protGetPhotoInfo_C2S, (void*)msgOnGetPhotoInfo);
    Prot::regHandler(protCheckIn_C2S,(void*)msgOnCheckIn);
}

