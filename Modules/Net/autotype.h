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

#include "log.h"

#include <climits>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

const char VALUE_TYPE_NUMBER = 'n';
const char VALUE_TYPE_STRING = 's';

class AutoType {
private:
    char type;
    char *buffer;
    int  bufLen;

public:
    AutoType();
    AutoType(long num);
    AutoType(const char *str);
    AutoType(const void* str, int len);
    AutoType(std::vector<unsigned char>& vuchar);

    AutoType(const AutoType& at);
    AutoType& operator=(const AutoType& at);
    virtual ~AutoType() {delete [] buffer;}

    const char getType() const {return type;}
    const char* getStr() const;
    char* begin();
    char* end();
    int getLen() const {return bufLen;}
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
    bufLen = sizeof(num);
    buffer = new char[bufLen];
    memmove(buffer,(const void*)(&num), bufLen);
}

inline
AutoType::AutoType(const char* str)
:type(VALUE_TYPE_STRING),buffer(0)
{
    bufLen = strlen(str)+1;
    if (str != 0) {
        buffer = new char[bufLen];
        memmove(buffer,str,bufLen);
    }
}

inline
AutoType::AutoType(const void* str, int len)
:type(VALUE_TYPE_STRING),buffer(0)
{
    bufLen = len;
    if (str != 0) {
        buffer = new char[bufLen];
        memmove(buffer,str,len);
    }
}

inline
AutoType::AutoType(std::vector<unsigned char>& vuchar)
:type(VALUE_TYPE_STRING),buffer(0)
{
    bufLen = vuchar.size();
    buffer = new char[bufLen];
    std::copy(vuchar.begin(), vuchar.end(), buffer);
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
        bufLen = at.bufLen;
        if (at.buffer) {
            if (type==VALUE_TYPE_NUMBER) {
                long num = *((long*)at.buffer);
                buffer = new char[sizeof(num)];
                memmove(buffer,(const void*)(&num),sizeof(num));
            }
            else if (type==VALUE_TYPE_STRING) {
                buffer = new char[bufLen];
                memmove(buffer,at.buffer,bufLen);
            }
        }
        else {
            buffer = 0;
        }
    }
    return *this;
}

inline
const char* AutoType::getStr() const
{
    if (type!=VALUE_TYPE_STRING) {
        assert(false&&"type is not string.");
        return 0;
    }
    return buffer;
}

inline
char* AutoType::begin()
{
    if (type!=VALUE_TYPE_STRING) {
        assert(false&&"type is not string.");
        return 0;
    }
    return buffer;
}

inline
char* AutoType::end()
{
    if (type!=VALUE_TYPE_STRING) {
        assert(false&&"type is not string.");
        return 0;
    }
    return buffer+bufLen;
}

inline
long AutoType::getNum() {
    if (type!=VALUE_TYPE_NUMBER) {
        assert(false&&"type is not number.");
        return LONG_MAX;
    }
    return *((long*)buffer);
}

inline
AutoType Mat2AutoType(cv::Mat& mat)
{
    std::vector<unsigned char> buff;
    std::vector<int> param = std::vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]=95;//default(95) 0-100
    cv::imencode(".jpg",mat,buff,param);
    return AutoType(buff);
}

inline
cv::Mat AutoType2Mat(AutoType& at)
{
    Log log(__LOGARG__,5);
    if (at.getType()==VALUE_TYPE_STRING) {
        int len = at.getLen();
        std::vector<unsigned char> buff(at.begin(),at.end());
        return cv::imdecode(cv::Mat(buff),CV_LOAD_IMAGE_COLOR);
    }
    return cv::Mat();
}

#endif

