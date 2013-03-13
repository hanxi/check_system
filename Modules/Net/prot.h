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

class Prot
{
private:
    static I2M sm_protDic;      //协议词典 

    I2MIter m_prot;             //当前协议

public:
    static void s_init();       //初始化协议词典

    Prot(int protId);
    ~Prot();

    void setProt(int protId);

    void setField(const char* fieldName, long value);
    void setField(const char* fieldName, const char *value);
    AutoType& getField(const char* fieldName);

    int serialize(char* bufferAddr, int bufferLength);
    bool pickBufferInfo(char* bufferAddr, int bufferLength, int& o_protId, int& o_protLen);
    int unSerialize(char* bufferAddr, int bufferLength);
};

inline
Prot::Prot(int protId)
{
    m_prot = sm_protDic.find(protId);
    if (m_prot==sm_protDic.end()) {
        // 失败，没有该协议
        std::cout << "protId=" << protId << std::endl;
        assert(false&&"设置协议失败，协议不存在");
    }
}

inline
Prot::~Prot()
{
}

inline
void Prot::setProt(int protId)
{
    m_prot = sm_protDic.find(protId);
    if (m_prot==sm_protDic.end()) {
        std::cout << "protId=" << protId << std::endl;
        assert(false&&"设置协议失败，协议不存在");
    }
}

inline
void Prot::setField(const char* fieldName, long value)
{
    if (m_prot==sm_protDic.end()) {
        assert(false&&"协议不存在");
        // 失败，没有该协议
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    if ((iter->second).getType() != VALUE_TYPE_NUMBER) {
        assert(false&&"协议类型初始化后，不能修改.");
    }
    iter->second = value;
}

inline
void Prot::setField(const char* fieldName, const char *value)
{
    if (m_prot==sm_protDic.end()) {
        // 失败，没有该协议
        assert(false&&"协议不存在");
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    if ((iter->second).getType() != VALUE_TYPE_STRING) {
        assert(false&&"协议类型初始化后，不能修改.");
    }
    iter->second = value;
}

inline
AutoType& Prot::getField(const char* fieldName)
{
    if (m_prot==sm_protDic.end()) {
        // 失败，没有该协议
        assert(false&&"协议不存在");
    }
    S2AIter iter = (m_prot->second).find(fieldName);
    return iter->second;
}

#endif

