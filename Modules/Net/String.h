/*=============================================================================
#     FileName: String.h
#         Desc: 自己实现的简单字符串类
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-10 00:21:01
#      History:
=============================================================================*/
#ifndef __STRING_H_
#define __STRING_H_

#include <cstring>

class String
{
public:
    String(const char *s = 0);
    String(const String &s);
    String& operator=(const String& s);
    ~String() {delete [] str;}

    const char* c_str() const {return str;}

private:
    char *str;
};

inline
String::String(const char *s)
: str(0)
{
    if (s != 0) {
        str = new char[strlen(s)+1];
        strcpy(str,s);
    }
}

inline
String::String(const String &s)
: str(0)
{
    if (s.str) {
        str = new char[strlen(s.str)+1];
        strcpy(str,s.str);
    }
}

inline
String& String::operator=(const String& s)
{
    if (str != s.str) {
        delete [] str;
        if (s.str) {
            str = new char[strlen(s.str)+1];
            strcpy(str,s.str);
        }
        else str = 0;
    }
    return *this;
}

#endif

