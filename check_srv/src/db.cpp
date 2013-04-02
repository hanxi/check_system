/*=============================================================================
#     FileName: db.cpp
#         Desc: 操作数据库的接口
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-25 22:13:49
#      History:
=============================================================================*/
#ifdef __USE_QT_MYSQL__

#include "db.h"
#include "globalVar.h"
#include "log.h"
#include <opencv2/opencv.hpp>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>


QSqlDatabase gdb;
namespace DB{

cv::Mat QByteArray2Mat(QByteArray& qba, int len)
{
    std::vector<unsigned char> buff(len);
    for (int i=0; i<len; i++)
    {
        buff[i] = qba[i+8];
    }
    return cv::imdecode(cv::Mat(buff),CV_LOAD_IMAGE_COLOR);
}

QByteArray AutoType2QByteArray(AutoType& at)
{
    int len = at.getLen();
    return QByteArray::fromRawData(at.getStr(),len);
}

bool start()
{
    // ms QODBC
    // mysql QMYSQL
    S2M& confMap = getConfMap();

    S2S& dbConf = confMap["db"];
    const char *hostName = (dbConf["hostName"]).c_str();
    const char *dbName = (dbConf["dbName"]).c_str();
    const char *userName = (dbConf["userName"]).c_str();
    const char *passwd = (dbConf["passwd"]).c_str();

    gdb = QSqlDatabase::addDatabase("QMYSQL");
    gdb.setHostName(hostName);
    gdb.setDatabaseName(dbName);
    gdb.setUserName(userName);
    gdb.setPassword(passwd);
    return gdb.open();
}

void stop()
{
    gdb.close();
}

// 操作book_info表
int bookInfoInsert(const char* name, const char* depName, AutoType& photo)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("INSERT INTO book_info (emp_name, dep_name, hire_time, photo) VALUES(?,?,now(),?)");
	QVariantList emp_name;
	emp_name << name;
	query.addBindValue(emp_name);
	QVariantList dep_name;
	dep_name << depName;
	query.addBindValue(dep_name);
    QByteArray data(photo.getStr(),photo.getLen());
    QVariantList emp_photo;
    emp_photo << data;
	query.addBindValue(emp_photo);
    log << "len1=" << data.size() << Log::endl;
	try
    {
        if (!query.execBatch())
        {
            log << ((query.lastQuery()).toUtf8()).constData() << Log::endl;
            log << (((query.lastError()).text()).toUtf8()).constData() << Log::endl;
            return -1;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    //query.prepare("select emp_id from book_info where emp_id = (select max(emp_id) from book_info)");
    //query.exec();
    QVariant qvid = query.lastInsertId();
    int empId = qvid.toInt();
    query.prepare("select * from book_info");
    query.exec();
    QSqlRecord rec = query.record();
    int photoCol = rec.indexOf("photo");
    int empIdCol = rec.indexOf("emp_id");
    log << "empId=" << empId << Log::endl;
    int i=0;
    while (query.next()) {
        int id = (query.value(empIdCol)).toInt();
        log << "id=" << id << Log::endl;
        if (id==empId) {
        QByteArray data2 = (query.value(photoCol)).toByteArray();
        log << "len2=" << data2.size() << Log::endl;
        for (int j=0; j<data2.size(); j++)
        {
            char a=data[j];
            char b=data2[j];
            if (a!=b) {
                //log << "不相等" << j << ":" << a <<" , " << b << Log::endl;
            }
        }
        cv::Mat mat = QByteArray2Mat(data2,data2.size());
        std::string s;
        num2str(i, s);
        imwrite("tmp"+s+".jpg",mat);
        mat = AutoType2Mat(photo);
        imwrite("tmp2.jpg",mat);
        i++;
        }
    }
    return empId;
}

// 操作model_img表
bool modelImgInsert(int empId, AutoType& photo)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("INSERT INTO model_img (emp_id, emp_photo) VALUES(?,?)");
	QVariantList emp_id;
	emp_id << empId;
	query.addBindValue(emp_id);
	QVariantList emp_photo;
    QByteArray data(photo.getStr(),photo.getLen());
	emp_photo << data;
	query.addBindValue(emp_photo);
	try
    {
        if (!query.execBatch())
        {
            log << ((query.lastQuery()).toUtf8()).constData() << Log::endl;
            log << (((query.lastError()).text()).toUtf8()).constData() << Log::endl;
            return false;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    return true;
}


// 操作worktime表
// 插入数据
bool worktimeInsert(int empId, const char* time, const char* photo)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("INSERT INTO work_time (emp_id, check_time, check_photo) VALUES(?,?,?)");
	QVariantList emp_id;
	emp_id << empId;
	query.addBindValue(emp_id);
	QVariantList check_time;
	check_time << time;
	query.addBindValue(check_time);
	QVariantList check_photo;
	check_photo << photo;
	query.addBindValue(check_photo);
	try
    {
        if (!query.execBatch())
        {
            log << ((query.lastQuery()).toUtf8()).constData() << Log::endl;
            log << (((query.lastError()).text()).toUtf8()).constData() << Log::endl;
            return false;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    return true;
}

// 修改签到时间
bool worktimeAltTime(int worktimeId, const char* time)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("UPDATE work_time SET check_time=? WHERE work_time_id=?");
	QVariantList check_time;
	check_time << time;
	query.addBindValue(check_time);
	QVariantList work_time_id;
	work_time_id << worktimeId;
	query.addBindValue(work_time_id);
	try
    {
        if (!query.execBatch())
        {
            log << ((query.lastQuery()).toUtf8()).constData() << Log::endl;
            log << (((query.lastError()).text()).toUtf8()).constData() << Log::endl;
            return false;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    return true;
}

// 修改empId
bool worktimeAltEmpId(int worktimeId, int empId)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("UPDATE work_time SET emp_id=? WHERE work_time_id=?");
	QVariantList emp_id;
	emp_id << empId;
	query.addBindValue(emp_id);
	QVariantList work_time_id;
	work_time_id << worktimeId;
	query.addBindValue(work_time_id);
	try
    {
        if (!query.execBatch())
        {
            log << ((query.lastQuery()).toUtf8()).constData() << Log::endl;
            log << (((query.lastError()).text()).toUtf8()).constData() << Log::endl;
            return false;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    return true;
}

} //end namespace std
#endif // #ifdef __USE_QT_MYSQLDB__
