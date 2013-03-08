/*=============================================================================
#     FileName: test.cpp
#         Desc: 日志记录模块
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-07 19:45:54
#      History:
=============================================================================*/

#include "log.h"
#include "trace.h"

void test()
{
    Log log("test",1);
    log<<12345 << 123 << 567;
    log<<12345 << Log::endl;
    log<<12345;
    log<<12345 << Log::endl;


    Trace trace("test");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
}

int main(int argc, char** argv)
{
    Log::s_init("./log.txt",1,TXT_LOG);

    Trace::traceIsActive = true;

    test();
    Log::s_stop();
    return 0;
}

