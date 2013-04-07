/*=============================================================================
#     FileName: protInit.h
#         Desc: 由protInitTool工具生成的协议初始化文件,用于实现Prot::s_init();
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
=============================================================================*/
#ifndef __PROT_INIT_H_
#define __PROT_INIT_H_

#include "prot.h"

inline
void Prot::s_init()
{
    S2A        s2a;
    AutoType   a;
    String     s;
    int        protId;

    protId = 1;
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 2;
    s = "time";
    a = "2013-3-30 10:48";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 3;
    s = "name";
    a = "名字";
    s2a.insert(S2A::value_type(s,a));
    s = "dep";
    a = "所属部门";
    s2a.insert(S2A::value_type(s,a));
    s = "photo";
    a = "010";
    s2a.insert(S2A::value_type(s,a));
    s = "idx";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 4;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 5;
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 6;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 7;
    s = "photo";
    a = "010";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 8;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    s = "dep";
    a = "所属部门";
    s2a.insert(S2A::value_type(s,a));
    s = "name";
    a = "名字";
    s2a.insert(S2A::value_type(s,a));
    s = "id";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 9;
    s = "imgBin";
    a = "0101010001010101001010";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 10;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 11;
    s = "imgBin";
    a = "0101010101011010101010";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 12;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    s = "resultInfo";
    a = "";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();
}

const int protGetTime_C2S = 1;
const int protGetTime_S2C = 2;
const int protSignIn_C2S = 3;
const int protSignIn_S2C = 4;
const int protUpdateFaceModel_C2S = 5;
const int protUpdateFaceModel_S2C = 6;
const int protGetPhotoInfo_C2S = 7;
const int protGetPhotoInfo_S2C = 8;
const int protCheckIn_C2S = 9;
const int protCheckIn_S2C = 10;
const int protSearch_C2S = 11;
const int protSearch_S2C = 12;

#endif

