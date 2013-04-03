/*=============================================================================
#     FileName: main.cpp
#         Desc: sqlite数据库生成操作函数
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-04-02 19:21:08
#      History:
=============================================================================*/
#include "log.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sqlite3.h>
using namespace std;

#define DBNAME "worktime.db"


sqlite3* conn = NULL;
sqlite3_stmt *stmt = NULL;

bool start()
{
    // 打开数据库
    int result = sqlite3_open(("../../../bin.check_srv/"+string(DBNAME)).c_str(),&conn);
    if (result != SQLITE_OK) {
        sqlite3_close(conn);
        return false;
    }
}

void stop()
{
    // 关闭数据库
    sqlite3_finalize(stmt);
    sqlite3_close(conn);
}

// sqlite的五种类型
//1.NULL：空值。
//2.INTEGER：带符号的整型，具体取决有存入数字的范围大小。
//3.REAL：浮点数字，存储为8-byte IEEE浮点数。
//4.TEXT：字符串文本。
//5.BLOB：二进制对象。

//int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
//int sqlite3_bind_double(sqlite3_stmt*, int, double);
//int sqlite3_bind_int(sqlite3_stmt*, int, int);
//int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int n, void(*)(void*));


// 整数转字符串
void num2str(int num, std::string& o_s)
{
    std::ostringstream convert;// stream used for the conversion
    convert << num;    // insert the textual representation of 'Number' in the characters in the stream
    o_s = convert.str();
}

typedef map<string,string> S2S;

// 生成插入数据函数
string productInsertFunc(string& tbl_name, vector<string>& fieldNames, vector<string>& fieldTypes,S2S& type2args, S2S& type2bind,string& o_insertFuncName)
{
    string insertFunc;
    string insertFuncName = "int "+tbl_name+"_insert";
    string args = "(";
    string sql = "insert into " + tbl_name +"(";
    string sqlq = "values(";
    string bindStr;
    string prepare = "sqlite3_prepare(conn, \"";
    string insertFuncReturn = "return sqlite3_last_insert_rowid(conn);\n}\n";

    for (int i=1;i<fieldNames.size(); ++i) {
        string name = fieldNames[i];
        string type = fieldTypes[i];
        args += type2args[type]+name;
        if ((i+1)!=fieldNames.size()) {
            args += ", ";
        }
    }
    args += ")";
    insertFuncName += args;
    o_insertFuncName += insertFuncName + ";\n";
    insertFuncName += " {\n\t";

    for (int i=1;i<fieldNames.size(); ++i) {
        string name = fieldNames[i];
        string type = fieldTypes[i];
        sql += name;
        sqlq += "?";
        if ((i+1)!=fieldNames.size()) {
            sql += ", ";
            sqlq += ", ";
        }
    }
    sql += ")";
    sqlq += ");";
    prepare += sql + sqlq + "\",-1,&stmt,0);\n\t";

    for (int i=1;i<fieldNames.size(); ++i) {
        string name = fieldNames[i];
        string type = fieldTypes[i];
        string stri;
        num2str(i,stri);
        bindStr += type2bind[type] + stri + "," + name;
        if (type=="TEXT") {
            bindStr += ", 1+strlen("+name+"), NULL);";
        }
        else if (type=="BLOB") {
            bindStr += ".getStr(), " + name+".getLen(), NULL);";
        }
        else {
            bindStr += ");";
        }
        bindStr += "\n\t";
    }
    bindStr += "sqlite3_step(stmt);\n\t";

    insertFunc = insertFuncName+prepare+bindStr+insertFuncReturn;
    return insertFunc;
}

// 生成结构体类型，一条记录
string productStruct(string& tbl_name, vector<string>& fieldNames, vector<string>& fieldTypes)
{
    string structStr("typedef struct _");
    structStr += tbl_name+"_Rec{\n\t";
    for (int i=0; i<fieldNames.size(); ++i) {
        if (fieldTypes[i]=="INTEGER") {
            structStr += "int " + fieldNames[i]+";\n";
        }
        else if (fieldTypes[i]=="REAL") {
            structStr += "double " + fieldNames[i]+";\n";
        }
        else {
            structStr += "AutoType " + fieldNames[i]+";\n";
        }
        if ((i+1)!=fieldNames.size()) {
            structStr += "\t";
        }
    }
    structStr += "}"+tbl_name+"_Rec;\n";
    return structStr;
}

// 生成查询数据函数
string productSelectFunc(string& tbl_name, int select, vector<string>& fieldNames,vector<string>& fieldTypes,S2S& type2args, S2S& type2bind, string& o_selectFuncName)
{
    string selectFunc;
    string selectFuncName("bool ");
    string selectName(fieldNames[select]);
    string selectType(fieldTypes[select]);
    string prepareStr("sqlite3_prepare(conn, ");
    string bindStr(type2bind[selectType]+"1, "+selectName);
    string whileStr("while (1) {\n\t\t");

    selectFuncName += tbl_name+"_select_by_"+selectName+"("+type2args[selectType]+selectName+", std::vector<"+tbl_name+"_Rec>& recs)";
    o_selectFuncName += selectFuncName + ";\n";
    selectFuncName += " {\n\t";

    prepareStr += "\"select * from "+tbl_name+" where "+selectName+"=?;\",-1,&stmt,0);\n\t";

    if (selectType=="TEXT") {
        bindStr += ", 1+strlen("+selectName+"), NULL);";
    }
    else if (selectType=="BLOB") {
        bindStr += ".getStr(), " +selectName+".getLen(), NULL);";
    }
    else {
        bindStr += ");";
    }
    bindStr += "\n\t";

    whileStr += "int s = sqlite3_step(stmt);\n\t\t";
    whileStr += "if (s==SQLITE_ROW) {\n\t\t\t";
    whileStr += tbl_name+"_Rec rec;\n\t\t\t";
    whileStr += "int bytes=0;\n\t\t\t";

    for (int i=0; i<fieldNames.size(); ++i) {
        string stri;
        num2str(i,stri);
        if (fieldTypes[i]=="INTEGER") {
            whileStr += "int "+fieldNames[i]+"_t = sqlite3_column_int(stmt,"+stri+");\n\t\t\t";
            whileStr += "rec."+fieldNames[i]+" = "+fieldNames[i]+"_t;\n\t\t\t";
        }
        else if (fieldTypes[i]=="REAL") {
            whileStr += "double "+fieldNames[i]+"_t = sqlite3_column_doulbe(stmt,"+stri+");\n\t\t\t";
            whileStr += "rec."+fieldNames[i]+" = "+fieldNames[i]+"_t;\n\t\t\t";
        }
        else if (fieldTypes[i]=="TEXT") {
            whileStr += "bytes = sqlite3_column_bytes(stmt,"+stri+");\n\t\t\t";
            whileStr += "const unsigned char* "+fieldNames[i]+"_t = sqlite3_column_text(stmt,"+stri+");\n\t\t\t";
            whileStr += "rec."+fieldNames[i]+" = AutoType("+fieldNames[i]+"_t,bytes);\n\t\t\t";
        }
        else if (fieldTypes[i]=="BLOB") {
            whileStr += "bytes = sqlite3_column_bytes(stmt,"+stri+");\n\t\t\t";
            whileStr += "const void* "+fieldNames[i]+"_t = sqlite3_column_blob(stmt,"+stri+");\n\t\t\t";
            whileStr += "rec."+fieldNames[i]+" = AutoType("+fieldNames[i]+"_t,bytes);\n\t\t\t";
        }
    }
    whileStr += "recs.push_back(rec);\n\t\t";
    whileStr += "}\n\t\t";
    whileStr += "else if (s==SQLITE_DONE) {\n\t\t\t";
    whileStr += "break;\n\t\t";
    whileStr += "}\n\t\t";
    whileStr += "else {\n\t\t\t";
    whileStr += "printf(\"\\nselect failed.\\n\");\n\t\t\t";
    whileStr += "return false;\n\t\t";
    whileStr += "}\n\t";
    whileStr += "}\n\t";
    whileStr += "return false;\n";
    whileStr += "}\n";

    selectFunc = selectFuncName+prepareStr+bindStr+whileStr;

   return selectFunc;
}

// 修改字段函数
string productUpdateFunc(string& tbl_name, string& updateName, string& updateType, string& updateByName, string& updateByType,S2S& type2args, S2S& type2bind, string& o_updateFuncName)
{
    string updateFunc;
    string updateFuncName("bool ");
    string prepareStr("sqlite3_prepare(conn,");

    updateFuncName += tbl_name+"_update_"+updateName+"_by_"+updateByName+"("+type2args[updateType]+updateName+", "+type2args[updateByType]+updateByName+")";
    o_updateFuncName += updateFuncName + ";\n";
    updateFuncName += " {\n\t";
    prepareStr += "\"update "+tbl_name+" set "+updateName+"=? where "+updateByName+"?;\",-1,&stmt,0);\n\t";
    prepareStr += type2bind[updateType]+"1, "+updateName;
    if (updateType=="TEXT") {
        prepareStr += ", 1+strlen("+updateName+"), NULL);";
    }
    else if (updateType=="BLOB") {
        prepareStr += ".getStr(), " +updateName+".getLen(), NULL);";
    }
    else {
        prepareStr += ");";
    }
    prepareStr += "\n\t";
    prepareStr += type2bind[updateByType]+"1, "+updateByName;
    if (updateByType=="TEXT") {
        prepareStr += ", 1+strlen("+updateByName+"), NULL);";
    }
    else if (updateByType=="BLOB") {
        prepareStr += ".getStr(), " +updateByName+".getLen(), NULL);";
    }
    else {
        prepareStr += ");";
    }
    prepareStr += "\n\t";
    prepareStr += "sqlite3_step(stmt);\n\t";
    prepareStr += "int s = sqlite3_step(stmt);\n\t";
    prepareStr += "if (s == SQLITE_DONE) {\n\t\t";
    prepareStr += "return true;\n\t";
    prepareStr += "}\n\t";
    prepareStr += "return false;\n";
    prepareStr += "}\n";
    updateFunc = updateFuncName+prepareStr;
    return updateFunc;
}

void productTalNames(vector<string>& tbl_names)
{
    sqlite3_prepare(conn, "select tbl_name from sqlite_master;", -1, &stmt, 0);
    while (1) {
        int s;
        s = sqlite3_step (stmt);
        if (s == SQLITE_ROW) {
            int bytes = sqlite3_column_bytes(stmt, 0);
            const unsigned char *name  = sqlite3_column_text(stmt, 0);
            string tbl_name((const char*)name,bytes);
            tbl_names.push_back(tbl_name);
        }
        else if (s == SQLITE_DONE) {
            break;
        }
        else {
            printf("\nselect failed.\n");
            return;
        }
    }
}

void productFields(string& tbl_name, vector<string>& fieldNames, vector<string>& fieldTypes)
{
    string sql("PRAGMA table_info(" +tbl_name+");");
    sqlite3_prepare(conn, sql.c_str(), -1, &stmt, 0);
    while (1) {
        int s;
        s = sqlite3_step (stmt);
        if (s == SQLITE_ROW) {
            int bytes = sqlite3_column_bytes(stmt, 1);
            const unsigned char *_name  = sqlite3_column_text(stmt, 1);
            string name((const char*)_name,bytes);
            fieldNames.push_back(name);
            bytes = sqlite3_column_bytes(stmt, 2);
            const unsigned char *_type  = sqlite3_column_text(stmt, 2);
            string type((const char*)_type,bytes);
            fieldTypes.push_back(type);
        }
        else if (s == SQLITE_DONE) {
            break;
        }
        else {
            printf("\nselect failed.\n");
            return;
        }
    }
}

int main(int argc, char** argv)
{
    Log::s_init("./log.txt",1,TXT_LOG);
    Log log(__LOGARG__,1);

    S2S type2args;
    type2args.insert(S2S::value_type("INTEGER","int "));
    type2args.insert(S2S::value_type("REAL","float "));
    type2args.insert(S2S::value_type("TEXT","const char* "));
    type2args.insert(S2S::value_type("BLOB","AutoType& "));
    S2S type2bind;
    type2bind.insert(S2S::value_type("INTEGER","sqlite3_bind_int(stmt,"));
    type2bind.insert(S2S::value_type("REAL","sqlite3_bind_double(stmt,"));
    type2bind.insert(S2S::value_type("TEXT","sqlite3_bind_text(stmt,"));
    type2bind.insert(S2S::value_type("BLOB","sqlite3_bind_blob(stmt,"));

    string buffcpp;
    string buffh;
    string headStrcpp("/*=============================================================================\n\
#     FileName: sqlitedb.cpp\n\
#         Desc: 操作sqlite3数据库\n\
#       Author: hanxi\n\
#        Email: hanxi.com@gmail.com\n\
#     HomePage: http://hanxi.cnblogs.com\n\
#      Version: 0.0.1\n\
#   LastChange: 2013-04-02 15:38:16\n\
#      History:\n\
=============================================================================*/\n\
#ifdef __USE_SQLITE__\n\n\
#include \"db.h\"\n\
#include \"log.h\"\n\
#include <sqlite3.h>\n\
#include <vector>\n\n\
namespace DB\n\
{\n\n\
sqlite3* conn = NULL;\n\
sqlite3_stmt *stmt = NULL;\n\n\
bool start()\n\
{\n\t\
// 打开数据库\n\t\
int result = sqlite3_open(\""+string(DBNAME)+"\",&conn);\n\t\
if (result != SQLITE_OK) {\n\t\t\
sqlite3_close(conn);\n\t\t\
return false;\n\t\
}\n\
}\n\n\
void stop()\n\
{\n\t\
// 关闭数据库\n\t\
sqlite3_finalize(stmt);\n\t\
sqlite3_close(conn);\n\
}");
    string tailStrcpp("\n}// end namespace DB\n\
#endif // #ifdef __USE_SQLITE__\n");
    string headStrh("/*=============================================================================\n\
#     FileName: db.h\n\
#         Desc: 操作数据库\n\
#       Author: hanxi\n\
#        Email: hanxi.com@gmail.com\n\
#     HomePage: http://hanxi.cnblogs.com\n\
#      Version: 0.0.1\n\
#   LastChange: 2013-04-02 16:58:36\n\
#      History:\n\
=============================================================================*/\n\
#ifndef __DB_H_\n\
#define __DB_H_\n\n\
#include \"autotype.h\"\n\n\
namespace DB\n\
{\n\
bool start();\n\
void stop();\n\n\
");
    string tailStrh("\n} //end namespace DB\n\
#endif // #ifndef __DB_H_\n");

    start();
    vector<string> tbl_names;
    productTalNames(tbl_names);
    string structStr;
    string insertFunc;
    string insertFuncName;
    string selectFunc;
    string selectFuncName;
    string updateFunc;
    string updateFuncName;
    for (vector<string>::iterator iter=tbl_names.begin(); iter!=tbl_names.end(); ++iter) {
        vector<string> fieldNames;
        vector<string> fieldTypes;
        productFields(*iter,fieldNames,fieldTypes);

        structStr += productStruct(*iter, fieldNames, fieldTypes);
        structStr += "\n";
        insertFunc += productInsertFunc(*iter,fieldNames,fieldTypes,type2args,type2bind,insertFuncName);
        insertFunc += "\n";
        for (int i=0; i<fieldNames.size(); ++i) {
            selectFunc += productSelectFunc(*iter,i, fieldNames,fieldTypes,type2args,type2bind,selectFuncName);
            selectFunc += "\n";
        }
        for (int i=1; i<fieldNames.size(); ++i) {
            for (int j=0; j< fieldNames.size(); ++j) {
                if (i!=j) {
                    updateFunc += productUpdateFunc(*iter,fieldNames[i],fieldTypes[i],fieldNames[j],fieldTypes[j],type2args,type2bind,updateFuncName);
                    updateFunc += "\n";
                }
            }
        }
    }
    stop();
    buffcpp += headStrcpp + insertFunc+selectFunc+updateFunc + tailStrcpp;
    buffh += headStrh + structStr + insertFuncName + selectFuncName + updateFuncName + tailStrh;
    log << buffcpp << Log::endl;
    Log::s_stop();

    // 写入文件
    std::ofstream writeFile("../sqlitedb.cpp");  // 生成ANSI文件格式
    writeFile.write(buffcpp.c_str(),buffcpp.length());
    writeFile.close();
    writeFile.open("../db.h");
    writeFile.write(buffh.c_str(),buffh.length());
    return 0;
}
