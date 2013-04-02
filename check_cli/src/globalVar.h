/*=============================================================================
#     FileName: globalVar.h
#         Desc: 全局变量相关
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-31 09:06:56
#      History:
=============================================================================*/
#ifndef __GLOBAL_VAR_H_
#define __GLOBAL_VAR_H_

#include "mainwindowimpl.h"
#include "net.h"

Net* getNet();
extern int  gSockId;
extern MainWindowImpl *win;

#endif

