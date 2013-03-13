/*=============================================================================
#     FileName: log.cpp
#         Desc: 为了初始化静态变量而建立的文件
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-11 12:55:11
#      History:
=============================================================================*/

#include "log.h"

// 初始化静态成员变量
std::ofstream     Log::ms_file;
const char       *Log::ms_path = NULL;       //log文件路径
int               Log::ms_logLevel = 0;      //小于logLevel的log将被打印出来
int               Log::ms_logFileType = 0;   //log文件类型

