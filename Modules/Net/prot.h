/*=============================================================================
#     FileName: prot.h
#         Desc: 协议模块
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-09 15:36:56
#      History:
=============================================================================*/

#ifndef __PROT_H_
#define __PROT_H_

#include <map>
#include <iostream>
#include <cassert>
#include <string>

#include "autotype.h"
#include "String.h"
#include "log.h"


void testSerializeIntValueUnserializeIntValue();
void testSerializeStringValue();
void testSerializeUnserialize();

// sm_protDic结构
// key---------------prot
// <id,           map         >
//         <string,  AutoType >
//              
// <1, 
//         <"name", {2,"hanxi"}>
//         <"pass", {1,12345}  > 
// >

class StrCmp:std::less<String>
{
public:                                   
    bool operator()(const String &str1, const String &str2) const{
        std::string strA = std::string(str1.c_str());
        std::string strB = std::string(str2.c_str());
        return strA<strB;
    }
};

typedef std::map<String, AutoType, StrCmp>     S2A;
typedef S2A::iterator                          S2AIter;
typedef std::map<int, S2A>                     I2M;
typedef I2M::iterator                          I2MIter;
typedef std::map<int, void*>                   I2V;
typedef I2V::iterator                          I2VIter;

class Prot
{
private:
    static I2M sm_protDic;      //协议词典 
    static I2V sm_protFunc;     //协议handler函数

    I2MIter m_prot;             //当前协议

public:
    static void s_init();       //初始化协议词典
    static bool peekBufferInfo(char* bufferAddr, int bufferLength, int& o_protId, int& o_protLen);
    static void regHandler(int protId, void *func);
    static void* getHandler(int protId);

    Prot(int protId);
    virtual ~Prot();

    bool setProt(int protId);
    bool isRightProt() const;

    bool setField(const char* fieldName, long value);
    bool setField(const char* fieldName, const char *value);
    AutoType& getField(const char* fieldName);

    void printProt();

    int serialize(char* bufferAddr, int bufferLength);
    int unSerialize(char* bufferAddr, int bufferLength);
};

inline
Prot::Prot(int protId)
{
    m_prot = sm_protDic.find(protId);
    if (m_prot==sm_protDic.end()) {
        // 失败，没有该协议
        std::cout << "protId=" << protId << std::endl;
//        assert(false&&"设置协议失败，协议不存在");
    }
}

inline
Prot::~Prot()
{
}

inline
bool Prot::setProt(int protId)
{
    m_prot = sm_protDic.find(protId);
    if (m_prot==sm_protDic.end()) {
        std::cout << "protId=" << protId << std::endl;
//        assert(false&&"设置协议失败，协议不存在");
        return false;
    }
    return true;
}

inline
bool Prot::isRightProt() const
{
    if (m_prot==sm_protDic.end()) {
        return false;
    }
    return true;
}

inline
bool Prot::setField(const char* fieldName, long value)
{
    if (m_prot==sm_protDic.end()) {
        return false;
//        assert(false&&"协议不存在");
        // 失败，没有该协议
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    if ((iter->second).getType() != VALUE_TYPE_NUMBER) {
        return false;
//        assert(false&&"协议类型初始化后，不能修改.");
    }
    iter->second = value;
    return true;
}

inline
bool Prot::setField(const char* fieldName, const char *value)
{
    if (m_prot==sm_protDic.end()) {
        return false;
        // 失败，没有该协议
//        assert(false&&"协议不存在");
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    if ((iter->second).getType() != VALUE_TYPE_STRING) {
        return false;
//        assert(false&&"协议类型初始化后，不能修改.");
    }
    iter->second = value;
    return true;
}

inline
AutoType& Prot::getField(const char* fieldName)
{
    if (m_prot==sm_protDic.end()) {
        static AutoType a(-1);
        return a;
        // 失败，没有该协议
//        assert(false&&"协议不存在");
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    return iter->second;
}

// typedef std::map<int,long> I2L;    // 用于保存protId和handle函数
// typedef I2L::iterator      I2LIter;
// bool protRegHandler(protId,func); // 如果协议号已被注册则返回false，否则返回true
// bool protGetHandler(protId,o_func); // 如果协议号没有注册，则返回false，否则返回true

inline
void Prot::printProt()
{
    Log log(__LOGARG__,1);
    S2A &prot = m_prot->second;
    int i=0;
    for (S2AIter iter=prot.begin(); iter!=prot.end(); ++iter) {
        i++;
        log << "[" << i << "]";
        log << (iter->first).c_str() << "=";
        if ((iter->second).getType()==VALUE_TYPE_NUMBER) {
            log << (iter->second).getNum();
        }
        else if ((iter->second).getType()==VALUE_TYPE_STRING) {
            log << (iter->second).getStr();
        }
        log << Log::endl;
    }
}

#include "protInit.h"      // 由工具生成的协议初始化文件
#endif

