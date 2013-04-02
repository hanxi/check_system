/*=============================================================================
#     FileName: sqlitedb.cpp
#         Desc: 操作sqlite3数据库
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-04-02 15:38:16
#      History:
=============================================================================*/
#ifdef __USE_SQLITE__

#include "db.h"
#include "log.h"
#include <sqlite3.h>
#include <opencv2/opencv.hpp>

namespace DB
{

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

//insert
int book_info_insert(const char* name, const char* depName, AutoType& photo)
{
    //Log log(__LOGARG__,5);
    //cv::Mat mat = AutoType2Mat(photo);
    //imwrite("tmp.jpg",mat);
    //log << "写入：size=" << photo.getLen() << Log::endl;

    sqlite3_prepare(conn, "insert into book_info (emp_name,dep_name,hire_time,photo)\
    values (?,?,datetime('now','localtime'),?);", -1, &stmt, 0);
    sqlite3_bind_blob(stmt, 1, name, strlen(name)+1, NULL);
    sqlite3_bind_blob(stmt, 2, depName, strlen(depName)+1, NULL);
    sqlite3_bind_blob(stmt, 3, photo.getStr(), photo.getLen(), NULL);
    sqlite3_step(stmt);

    // 测试写入是否成功
    //sqlite3_prepare(conn, "select * from book_info;", -1, &stmt, 0);
    //sqlite3_step(stmt);
    //const void *test = sqlite3_column_blob(stmt, 4);
    //int size = sqlite3_column_bytes(stmt, 4);
    //log << "读取：size=" << size << Log::endl;
    //photo = AutoType(test,size);
    //mat = AutoType2Mat(photo);
    //imwrite("tmp2.jpg",mat);

    return sqlite3_last_insert_rowid(conn);
}

typedef struct _book_info_Rec{
    AutoType emp_id;
    AutoType emp_name;
    AutoType dep_name;
    AutoType hire_time;
    AutoType photo;
}boo_info_Rec;

//select
//void book_info_select_by_emp_name(const char* emp_name, vector<book_info_Rec>& rec)
void book_info_select_by_emp_id(int emp_id, vector<book_info_Rec>& rec)
{
    sqlite3_prepare(conn, "select * from book_info where emp_id=?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, emp_id);
    while (1) {
        int s;
        s = sqlite3_step (stmt);
        if (s == SQLITE_ROW) {
            int bytes = 0;
            int emp_id_t = sqlite3_column_int(stmt, 0);
            rec.emp_id = AutoType(emp_id_t);
            const char *emp_name_t  = sqlite3_column_text(stmt, 1);
            rec.emp_name = AutoType(emp_name_t);
            const char *dep_name_t  = sqlite3_column_text(stmt, 2);
            rec.dep_name = AutoType(dep_name_t);
            const char *hire_time_t  = sqlite3_column_text(stmt, 3);
            rec.hire_time = AutoType(hire_time_t);
            bytes = sqlite3_column_bytes(stmt, 4);
            const char *photo_t = sqlite3_column_text(stmt, 4);
            rec.photo = AutoType(photo_t,bytes);
        }
        else if (s == SQLITE_DONE) {
            break;
        }
        else {
            printf("\nselect failed.\n");
            exit (1);
        }
    }
}

//update
void book_info_update_emp_name(int emp_id, const char* emp_name)
{
}

}// end namespace DB
#endif // #ifdef __USE_SQLITE__

