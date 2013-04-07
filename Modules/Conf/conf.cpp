/*=============================================================================
#     FileName: conf.cpp
#         Desc: 读取配置文件的工具函数
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-19 09:10:45
#      History:
=============================================================================*/

#include "log.h"
#include "conf.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <functional>


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

// 读取配置文件
void readConfFile(const char *confFileName, S2M& confMap)
{
    Log log(__LOGARG__, 1);
    std::string cur_section;    //[当前段]

	std::ifstream confFile(confFileName);

    FILETYPE fileType = getTextFileType(confFileName);
    if (fileType==ANSI) {
        log << "ANSI格式的文件" << Log::endl;
    }
    else if (fileType==UNICODE) {
        log << "UNICODE格式的文件" << Log::endl;
        char fileHead[sizeof(wchar_t)];
        confFile.read(fileHead,sizeof(wchar_t));
    }
    else if (fileType==UTF8) {
        log << "UTF8格式的文件" << Log::endl;
        char fileHead[3*sizeof(char)];
        confFile.read(fileHead,3*sizeof(char));
    }
    else {
        log << "不认识的文件格式，请修改文件格式" << Log::endl;
        return;
    }

	char buffer[1024];
	while(confFile.getline(buffer,1024)) {
		std::string temp = buffer;
		temp = trim(temp);
		if (temp.length()<2) continue;
		if (temp[0]=='\\' && temp[1]=='\\') continue;
		if (temp[0]=='/' && temp[1]=='/') continue;
		if (temp[0]==';') continue;
		if (temp[0]=='#') continue;
        for (unsigned int i=0; i<temp.length(); i++)
        {
            log << temp[i] << Log::endl;
        }
		if (temp[0]=='[') {//section changed
            temp = temp.substr(1,temp.length()-2);
            log << "取子串后，temp=" << temp << Log::endl;
			cur_section = trim(temp);
            log << "当前段[" << cur_section << "]" << Log::endl;
			continue;
		}
		assert(cur_section.length()>0);
		std::string key,value;
		split(temp,key,value,'=');
        if (key.length()<=0 || value.length()<=0) continue;
        confMap[cur_section][key] = value;
	}
	confFile.close();
    for (S2MIter iter=confMap.begin(); iter!=confMap.end(); ++iter) {
        log << "[" << iter->first << "]" << Log::endl;
        for (S2SIter i=(iter->second).begin(); i!=(iter->second).end(); ++i) {
            log << i->first << " = " << i->second << Log::endl;
        }
    }
}


