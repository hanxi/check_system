/*=============================================================================
#     FileName: test.cpp
#         Desc: 测试prot
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-10 12:48:36
#      History:
=============================================================================*/

#include "prot.h"
#include "autotype.h"

#include "log.h"

#include <iostream>
using namespace std;


int main(int argc, const char** argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    //Log::s_init("./log.txt",1,TXT_LOG);
    char T1 = 0xF1; // 正,8位
    int t = T1;
    Log log(__LOGARG__,1);
    cout << hex << t << endl;

    AutoType s("12345asdcv");
    cout << s.getType() << "," << s.getStr() << endl;
    AutoType s2(12345);
    cout << s2.getType() << "," << s2.getNum() << endl;

    Prot::s_init();
    Prot prot(1);
    AutoType s3 = prot.getField("name");
    cout << s3.getType() << "," << s3.getStr() << endl;
    prot.setProt(2);
    s3 = prot.getField("count");
    cout << s3.getType() << "," << s3.getNum() << endl;
    cout << __LINE__ << __FUNCTION__ << endl;

    testSerializeIntValueUnserializeIntValue();
    testSerializeStringValue();

    testSerializeUnserialize();

    Log::s_stop();
    return 0;
}
