/*=============================================================================
#     FileName: conf.h
#         Desc: 读取配置文件
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-19 09:27:26
#      History:
=============================================================================*/
#ifndef __CONF_H_
#define __CONF_H_

#include <map>
#include <string>
#include <algorithm>
#include <sstream>

typedef std::map<std::string, std::string>   S2S;
typedef S2S::iterator                        S2SIter;
typedef std::map<std::string, S2S>           S2M;
typedef S2M::iterator                        S2MIter;

typedef enum FileType
{
    ANSI = 0,
    UNICODE,
    UTF8,
}FILETYPE;

// 去除字符串前后空格
inline std::string& lTrim(std::string &ss)
{
    std::string::iterator p=std::find_if(ss.begin(),ss.end(),std::not1(std::ptr_fun(isspace)));
    ss.erase(ss.begin(),p);
    return ss;
}
inline std::string& rTrim(std::string &ss)
{
    std::string::reverse_iterator p=std::find_if(ss.rbegin(),ss.rend(),std::not1(std::ptr_fun(isspace)));
    ss.erase(p.base(),ss.end());
    return ss;
}
inline std::string& trim(std::string &st)
{ 
    lTrim(rTrim(st));
    return st;
}

// 分割字符串
inline void split(std::string& str, std::string& str1, std::string& str2, char splitChar)
{
    int idx = str.find(splitChar);
    str1 = str.substr(0,idx-1);
    str1 = trim(str1);
    str2 = str.substr(idx+1,str.length());
    str2 = trim(str2);
}

// 是否全部是数字
inline bool isAllDigit(const std::string& str)
{
    for(unsigned int i=0; i!=str.length(); i++)
    {
        if(!isdigit(str[i]) && '-'!=str[0] && '+'!=str[0])
        {
            return false;
        }
    }
    return true;
}

// 字符串转整数
inline int str2num(std::string& s)
{
    int num;
    std::stringstream ss(s);
    ss >> num;
    return num;
}

// 整数转字符串
inline void num2str(int num, std::string& o_s)
{
    std::ostringstream convert;// stream used for the conversion
    convert << num;    // insert the textual representation of 'Number' in the characters in the stream
    o_s = convert.str();
}

// 判断文件类型，ANSI,UTF8,UNICODE
FILETYPE getTextFileType(const char *fileName);

// 读取配置文件
void readConfFile(const char *confFileName, S2M& confMap);

#endif

