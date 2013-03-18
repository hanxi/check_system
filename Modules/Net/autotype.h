/*=============================================================================
#     FileName: autotype.h
#         Desc: 自定义类型，支持long和sting
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-10 13:28:20
#      History:
=============================================================================*/
#ifndef __AUTOTYPE_H_
#define __AUTOTYPE_H_

#include <climits>
#include <cstring>
#include <cassert>

const char VALUE_TYPE_NUMBER = 'n';
const char VALUE_TYPE_STRING = 's';

class AutoType {
private:
    char type;
    char *buffer;

public:
    AutoType();
    AutoType(long num);
    AutoType(const char *str);
    AutoType(const char* str, int len);

    AutoType(const AutoType& at);
    AutoType& operator=(const AutoType& at);
    virtual ~AutoType() {delete [] buffer;}

    char getType() {return type;}
    const char* getStr();
    long getNum();
};

inline
AutoType::AutoType()
:type(VALUE_TYPE_STRING),buffer(0)
{
}

inline
AutoType::AutoType(long num)
:type(VALUE_TYPE_NUMBER),buffer(0)
{
    buffer = new char[sizeof(num)];
    memmove(buffer,(const void*)(&num), sizeof(num));
}

inline
AutoType::AutoType(const char* str)
:type(VALUE_TYPE_STRING),buffer(0)
{
    if (str != 0) {
        buffer = new char[strlen(str)+1];
        strcpy(buffer,str);
    }
}

inline
AutoType::AutoType(const char* str, int len)
:type(VALUE_TYPE_STRING),buffer(0)
{
    if (str != 0) {
        buffer = new char[len+1];
        strncpy(buffer,str,len);
        buffer[len] = '\0';
    }
}

inline
AutoType::AutoType(const AutoType& at)
{
    buffer = 0;
    *this = at;
}

inline
AutoType& AutoType::operator=(const AutoType& at)
{
    if (buffer!=at.buffer) {
        delete [] buffer;
        type = at.type;
        if (at.buffer) {
            if (type==VALUE_TYPE_NUMBER) {
                long num = *((long*)at.buffer);
                buffer = new char[sizeof(num)];
                memmove(buffer,(const void*)(&num),sizeof(num));
            }
            else if (type==VALUE_TYPE_STRING) {
                buffer = new char[strlen(at.buffer)+1];
                strcpy(buffer,at.buffer);
            }
        }
        else {
            buffer = 0;
        }
    }
    return *this;
}

inline
const char* AutoType::getStr()
{
    if (type!=VALUE_TYPE_STRING) {
        assert(false&&"type is not string.");
        return 0;
    }
    return buffer;
}

inline
long AutoType::getNum() {
    if (type!=VALUE_TYPE_NUMBER) {
        assert(false&&"type is not number.");
        return LONG_MAX;
    }
    return *((long*)buffer);
}

#endif

