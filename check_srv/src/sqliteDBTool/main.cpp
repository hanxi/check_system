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
#include <sstream>
#include <sqlite3.h>
using namespace std;

//select tbl_name from sqlite_master;

sqlite3* conn = NULL;
sqlite3_stmt *stmt = NULL;

bool start()
{
    // 打开数据库
    int result = sqlite3_open("worktime.db",&conn);
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

string productInsertFunc(string& tbl_name, vector<string>& fieldNames, vector<string>& fieldTypes,S2S& type2args, S2S& type2bind)
{
    string insertFunc;
    string insertFuncName = "int "+tbl_name+"_insert";
    string args = "(";
    string sql = "insert into " + tbl_name +"(";
    string sqlq = "values(";
    string bindStr;
    string prepare = "sqlite3_prepare(conn, \"";
    string insertFuncReturn = "return sqlite3_last_insert_rowid(conn);\n}\n";

   vector<string>::iterator name=fieldNames.begin();
    vector<string>::iterator type=fieldTypes.begin();
    for (;name!=fieldNames.end(); ++name,++type) {
        args += type2args[*type]+*name;
        if (name!=--(fieldNames.end())) {
            args += ", ";
        }
    }
    args += ") {\n\t";
    name=fieldNames.begin();
    for (;name!=fieldNames.end(); ++name,++type) {
        sql += *name;
        sqlq += "?";
        if (name!=--(fieldNames.end())) {
            sql += ", ";
            sqlq += ", ";
        }
    }
    sql += ")";
    sqlq += ");";
    prepare += sql + sqlq + "\",-1,&stmt,0);\n\t";

    name=fieldNames.begin();
    type=fieldTypes.begin();
    int i=1;
    for (;name!=fieldNames.end(); ++name,++type) {
        string stri;
        num2str(i,stri);
        bindStr += type2bind[*type] + stri + "," + *name;
        if (*type=="TEXT") {
            bindStr += ", 1+strlen("+*name+"), NULL);";
        }
        else if (*type=="BLOB") {
            bindStr += ".getStr(), " + *name+".getLen(), NULL);";
        }
        else {
            bindStr += ");";
        }
        i++;
        bindStr += "\n\t";
    }
    bindStr += "sqlite3_step(stmt);\n\t";

    insertFunc = insertFuncName+args+prepare+bindStr+insertFuncReturn;
    return insertFunc;
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

    string buff;
    vector<string> tbl_names;
    tbl_names.push_back("book_info");
    string insertFunc;
    string selectFunc;
    string updateFunc;
    for (vector<string>::iterator iter=tbl_names.begin(); iter!=tbl_names.end(); ++iter) {
        vector<string> fieldNames;
        vector<string> fieldTypes;
        fieldNames.push_back("emp_name");
        fieldNames.push_back("dep_name");
        fieldNames.push_back("hire_time");
        fieldNames.push_back("photo");
        fieldTypes.push_back("TEXT");
        fieldTypes.push_back("TEXT");
        fieldTypes.push_back("TEXT");
        fieldTypes.push_back("BLOB");

        insertFunc += productInsertFunc(*iter,fieldNames,fieldTypes,type2args,type2bind);
        //selectFunc += productSelectFunc(*iter,fieldNames,fieldTypes);
        //updateFunc += productUpdateFunc();
    }
    buff += insertFunc;
    log << buff << Log::endl;
    Log::s_stop();
    return 0;
}
