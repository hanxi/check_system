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

#include "db.h"
#include "globalVar.h"
#include "log.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>


QSqlDatabase gdb;

bool DB::start()
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

void DB::stop()
{
    gdb.close();
}


// 操作worktime表
// 插入数据
bool DB::worktimeInsert(int empId, const char* time, const char* photo)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("INSERT INTO [work_time] (emp_id, check_time, check_photo) VALUES(?,?,?)");
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
            log << ((query.lastQuery()).toAscii()).data() << Log::endl;
            log << (((query.lastError()).text()).toAscii()).data() << Log::endl;
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
bool DB::worktimeAltTime(int worktimeId, const char* time)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("UPDATE [work_time] SET check_time=? WHERE work_time_id=?");
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
            log << ((query.lastQuery()).toAscii()).data() << Log::endl;
            log << (((query.lastError()).text()).toAscii()).data() << Log::endl;
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
bool DB::worktimeAltEmpId(int worktimeId, int empId)
{
    Log log(__LOGARG__,1);
	QSqlQuery query;
	query.exec("UPDATE [work_time] SET emp_id=? WHERE work_time_id=?");
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
            log << ((query.lastQuery()).toAscii()).data() << Log::endl;
            log << (((query.lastError()).text()).toAscii()).data() << Log::endl;
            return false;
        }
    }
    catch(...)
    {
        log << "Add New Node error! Unable to add a new Node!" << Log::endl;
    }
    return true;
}

