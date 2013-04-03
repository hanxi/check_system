/*=============================================================================
#     FileName: db.h
#         Desc: 操作数据库
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-04-02 16:58:36
#      History:
=============================================================================*/
#ifndef __DB_H_
#define __DB_H_

#include "autotype.h"

namespace DB
{
bool start();
void stop();

typedef struct _book_info_Rec{
	int emp_id;
	AutoType emp_name;
	AutoType dep_name;
	AutoType hire_time;
	AutoType photo;
}book_info_Rec;

typedef struct _model_img_Rec{
	int model_img_id;
	int emp_id;
	AutoType photo;
}model_img_Rec;

typedef struct _work_time_Rec{
	int work_time_id;
	int emp_id;
	AutoType check_time;
	AutoType check_photo;
}work_time_Rec;

int book_info_insert(const char* emp_name, const char* dep_name, const char* hire_time, AutoType& photo);
int model_img_insert(int emp_id, AutoType& photo);
int work_time_insert(int emp_id, const char* check_time, AutoType& check_photo);
bool book_info_select_by_emp_id(int emp_id, std::vector<book_info_Rec>& recs);
bool book_info_select_by_emp_name(const char* emp_name, std::vector<book_info_Rec>& recs);
bool book_info_select_by_dep_name(const char* dep_name, std::vector<book_info_Rec>& recs);
bool book_info_select_by_hire_time(const char* hire_time, std::vector<book_info_Rec>& recs);
bool book_info_select_by_photo(AutoType& photo, std::vector<book_info_Rec>& recs);
bool model_img_select_by_model_img_id(int model_img_id, std::vector<model_img_Rec>& recs);
bool model_img_select_by_emp_id(int emp_id, std::vector<model_img_Rec>& recs);
bool model_img_select_by_photo(AutoType& photo, std::vector<model_img_Rec>& recs);
bool work_time_select_by_work_time_id(int work_time_id, std::vector<work_time_Rec>& recs);
bool work_time_select_by_emp_id(int emp_id, std::vector<work_time_Rec>& recs);
bool work_time_select_by_check_time(const char* check_time, std::vector<work_time_Rec>& recs);
bool work_time_select_by_check_photo(AutoType& check_photo, std::vector<work_time_Rec>& recs);
bool book_info_update_emp_name_by_emp_id(const char* emp_name, int emp_id);
bool book_info_update_emp_name_by_dep_name(const char* emp_name, const char* dep_name);
bool book_info_update_emp_name_by_hire_time(const char* emp_name, const char* hire_time);
bool book_info_update_emp_name_by_photo(const char* emp_name, AutoType& photo);
bool book_info_update_dep_name_by_emp_id(const char* dep_name, int emp_id);
bool book_info_update_dep_name_by_emp_name(const char* dep_name, const char* emp_name);
bool book_info_update_dep_name_by_hire_time(const char* dep_name, const char* hire_time);
bool book_info_update_dep_name_by_photo(const char* dep_name, AutoType& photo);
bool book_info_update_hire_time_by_emp_id(const char* hire_time, int emp_id);
bool book_info_update_hire_time_by_emp_name(const char* hire_time, const char* emp_name);
bool book_info_update_hire_time_by_dep_name(const char* hire_time, const char* dep_name);
bool book_info_update_hire_time_by_photo(const char* hire_time, AutoType& photo);
bool book_info_update_photo_by_emp_id(AutoType& photo, int emp_id);
bool book_info_update_photo_by_emp_name(AutoType& photo, const char* emp_name);
bool book_info_update_photo_by_dep_name(AutoType& photo, const char* dep_name);
bool book_info_update_photo_by_hire_time(AutoType& photo, const char* hire_time);
bool model_img_update_emp_id_by_model_img_id(int emp_id, int model_img_id);
bool model_img_update_emp_id_by_photo(int emp_id, AutoType& photo);
bool model_img_update_photo_by_model_img_id(AutoType& photo, int model_img_id);
bool model_img_update_photo_by_emp_id(AutoType& photo, int emp_id);
bool work_time_update_emp_id_by_work_time_id(int emp_id, int work_time_id);
bool work_time_update_emp_id_by_check_time(int emp_id, const char* check_time);
bool work_time_update_emp_id_by_check_photo(int emp_id, AutoType& check_photo);
bool work_time_update_check_time_by_work_time_id(const char* check_time, int work_time_id);
bool work_time_update_check_time_by_emp_id(const char* check_time, int emp_id);
bool work_time_update_check_time_by_check_photo(const char* check_time, AutoType& check_photo);
bool work_time_update_check_photo_by_work_time_id(AutoType& check_photo, int work_time_id);
bool work_time_update_check_photo_by_emp_id(AutoType& check_photo, int emp_id);
bool work_time_update_check_photo_by_check_time(AutoType& check_photo, const char* check_time);

} //end namespace DB
#endif // #ifndef __DB_H_
