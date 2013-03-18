/*=============================================================================
#     FileName: protInitTool.cpp
#         Desc: 生成protInit.h文件工具的实现
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-16 14:11:07
#      History:
=============================================================================*/

#include "log.h"

#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iostream>
#include <algorithm>
#include <functional>


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
        if(!isdigit(str[i]) && '-'!=str[i])
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

typedef enum FileType
{
    ANSI = 0,
    UNICODE,
    UTF8,
}FILETYPE;

// 判断文件类型，ANSI,UTF8,UNICODE
FILETYPE getTextFileType(const char *fileName)
{
    FILETYPE fileType = ANSI;
    std::ifstream file;
    file.open(fileName, std::ios_base::in);

    if (file.good())
    {
        char szFlag[3] = {0};
        file.read(szFlag, sizeof(char) * 3);
        if ((unsigned char)szFlag[0] == 0xFF 
            && (unsigned char)szFlag[1] == 0xFE)
        {
            fileType = UNICODE;
        }
        else if ((unsigned char)szFlag[0] == 0xEF 
            && (unsigned char)szFlag[1] == 0xBB 
            && (unsigned char)szFlag[2] == 0xBF)
        {
            fileType = UTF8;
        }
    }
    file.close();

    return fileType;
}

// 读取协议文件
void readProfileWriteProtInit(const char *profileName, const char* path)
{
    Log log(__LOGARG__, 1);
    std::string protInitPath = std::string(path)+"protInit.h";
    std::string protInitStr("");
    std::string protIdDefine("");
    std::string cur_section;    //[当前段]

    // 基本字符串
    std::string headStr = "/*=============================================================================\n\
#     FileName: protInit.h\n\
#         Desc: 由protInitTool工具生成的协议初始化文件,用于实现Prot::s_init();\n\
#       Author: hanxi\n\
#        Email: hanxi.com@gmail.com\n\
#     HomePage: http://hanxi.cnblogs.com\n\
#      Version: 0.0.1\n\
=============================================================================*/\n\
#ifndef __PROT_INIT_H_\n#define __PROT_INIT_H_\n\n#include \"prot.h\"\n\ninline\nvoid Prot::s_init()\n{\n    S2A        s2a;\n    AutoType   a;\n    String     s;\n    int        protId;\n";
    std::string tailStr = "\n#endif\n\n";
    protInitStr += headStr;
    std::string s2aInsertStr = "    s2a.insert(S2A::value_type(s,a));\n";
    std::string smInsertStr = "    sm_protDic.insert(I2M::value_type(protId,s2a));\n    s2a.clear();\n";
    std::string protIdDefineHead = "const int ";
    
    // 写入key-value格式
    // s = "name";
    // a = "hanxi";
    std::string pStr = "\n    protId = ";
    std::string sStr = "    s = ";
    std::string aStr = "    a = ";
    std::string protIdStr;

	std::ifstream profile(profileName);
    FILETYPE fileType = getTextFileType(profileName);
    if (fileType==ANSI) {
        log << "ANSI格式的文件" << Log::endl;
    }
    else if (fileType==UNICODE) {
        log << "UNICODE格式的文件" << Log::endl;
        char fileHead[sizeof(wchar_t)];
        profile.read(fileHead,sizeof(wchar_t));
    }
    else if (fileType==UTF8) {
        log << "UTF8格式的文件" << Log::endl;
        char fileHead[3*sizeof(char)];
        profile.read(fileHead,3*sizeof(char));
    }
    else {
        log << "不认识的文件格式，请修改文件格式" << Log::endl;
    }
	char buffer[1024];
    int protId = 0;
    int line = 0;
	while(profile.getline(buffer,1024)) {
        line++;
		std::string temp = buffer;
		temp = trim(temp);
        log << "line[" << line << "]:" << temp << Log::endl;
		if (temp.length()<2) continue;
		if (temp[0]=='\\' && temp[1]=='\\') continue;
		if (temp[0]=='/' && temp[1]=='/') continue;
		if (temp[0]==';') continue;
		if (temp[0]=='#') continue;
        for (unsigned int i=0; i<temp.length(); i++)
        {
            std::cout << temp[i] << std::endl;
        }
		if (temp[0]=='[') {//section changed
            protId++;
            if (protId!=1) {
                protInitStr += smInsertStr;
            }
            num2str(protId,protIdStr);
            protInitStr += pStr + protIdStr + ";\n";   // "protId = 1;"
            temp = temp.substr(1,temp.length()-2);
            log << "取子串后，temp=" << temp << Log::endl;
			cur_section = trim(temp);
            protIdDefine += protIdDefineHead + cur_section + " = " + protIdStr + ";\n";
            log << "当前段[" << cur_section << "]" << Log::endl;
			continue;
		}
		assert(cur_section.length()>0);
		std::string key,value;
		split(temp,key,value,'=');
        if (key.length()<=0 || value.length()<=0) continue;
        if ((value[0]=='\"' && value[value.length()-1]=='\"')
            || (isAllDigit(value))) {
            protInitStr += sStr + "\"" + key + "\"" + ";\n";   // s = "name";
            protInitStr += aStr + value + ";\n"; // a = "hanxi";
            protInitStr += s2aInsertStr;
        }
        else {
            log << "协议配置文件中出现错误格式,line=" << line << Log::endl;
            continue;
        }
	}
    protInitStr += smInsertStr + "}\n\n" + protIdDefine + tailStr;
	profile.close();

    log << protInitStr.c_str() << Log::endl;
    // 写入文件
    std::ofstream protInitHead(protInitPath.c_str());  // 生成ANSI文件格式
    protInitHead.write(protInitStr.c_str(),protInitStr.length());
}

int main(int argc, const char **argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    if (argc==1) {
        readProfileWriteProtInit("./profile.txt", "./");
    }
    Log::s_stop();
    return 0;
}

