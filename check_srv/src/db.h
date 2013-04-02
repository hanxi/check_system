/*=============================================================================
#     FileName: db.h
#         Desc: 操作数据库
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-04-02 16:58:36
#      History:
=============================================================================*/
#ifndef __DB_H_
#define __DB_H_

#include "autotype.h"

namespace DB
{
bool start();
void stop();

int bookInfoInsert(const char* name, const char* depName, AutoType& photo);
bool modelImgInsert(int empId, AutoType& photo);

bool worktimeInsert(int empId, const char* time, const char* photo);
bool worktimeAltTime(int worktimeId, const char* time);
bool worktimeAltEmpId(int worktimeId, int empId);
} //end namespace DB
#endif

