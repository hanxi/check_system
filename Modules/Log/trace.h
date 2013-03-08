/*=============================================================================
#     FileName: trace.h
#         Desc: 调试类
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-08 13:05:03
#      History:
=============================================================================*/
#ifndef __TRACE_H_ 
#define __TRACE_H_ 

#include <iostream>
using namespace std;

class Trace {
public:
    Trace (const char *name);
    ~Trace ();
    void debug (const string &msg);

    static bool traceIsActive;

private:
    string *theFunctionName;
};
bool Trace::traceIsActive = false;

inline
Trace::Trace(const char* name) : theFunctionName(0)
{
    if (traceIsActive) {
        //Conditional creation
        theFunctionName = new string(name);
        cout << "[Enter function]" << *theFunctionName << endl;
    }
}

inline
void Trace::debug(const string &msg)
{
    if (traceIsActive) {
        cout << msg << endl;
    }
}

inline
Trace::~Trace()
{
    if (traceIsActive) {
        cout << "[Exit function]" << *theFunctionName << endl;
        delete theFunctionName;
    }
}

#endif

