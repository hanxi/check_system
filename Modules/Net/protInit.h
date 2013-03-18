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
    s = "imgBin";
    a = "0101010001010101001010";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 2;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 3;
    s = "imgBin";
    a = "0101010101011010101010";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();

    protId = 4;
    s = "result";
    a = -1;
    s2a.insert(S2A::value_type(s,a));
    s = "resultInfo";
    a = "";
    s2a.insert(S2A::value_type(s,a));
    sm_protDic.insert(I2M::value_type(protId,s2a));
    s2a.clear();
}

const int protCheckIn_C2S = 1;
const int protCheckIn_S2C = 2;
const int protSearch_C2S = 3;
const int protSearch_S2C = 4;

#endif

