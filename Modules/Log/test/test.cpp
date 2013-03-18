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
    Log log(__LOGARG__,1);
    log << hex<< 12345 << Log::endl;
    log << 321 << Log::endl;

/*
    Trace trace("test");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    trace.debug("123456");
    */
}

int main(int argc, char** argv)
{
    Log::s_init("./log.txt",1,TXT_LOG);
    //Log::s_init("./log.html",1,HTML_LOG);

    Trace::traceIsActive = true;

    test();
    Log::s_stop();


    std::cout << hex << 123 << std::endl;
    std::cout << dec << 123 << std::endl;
    return 0;
}

