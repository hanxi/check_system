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
#include <vector>

#include <cstdio>

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

int book_info_insert(const char* emp_name, const char* dep_name, const char* hire_time, AutoType& photo) {
	sqlite3_prepare(conn, "insert into book_info(emp_name, dep_name, hire_time, photo)values(?, ?, ?, ?);",-1,&stmt,0);
	sqlite3_bind_text(stmt,1,emp_name, 1+strlen(emp_name), NULL);
	sqlite3_bind_text(stmt,2,dep_name, 1+strlen(dep_name), NULL);
	sqlite3_bind_text(stmt,3,hire_time, 1+strlen(hire_time), NULL);
	sqlite3_bind_blob(stmt,4,photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	return sqlite3_last_insert_rowid(conn);
}

int model_img_insert(int emp_id, AutoType& photo) {
	sqlite3_prepare(conn, "insert into model_img(emp_id, photo)values(?, ?);",-1,&stmt,0);
	sqlite3_bind_int(stmt,1,emp_id);
	sqlite3_bind_blob(stmt,2,photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	return sqlite3_last_insert_rowid(conn);
}

int work_time_insert(int emp_id, const char* check_time, AutoType& check_photo) {
	sqlite3_prepare(conn, "insert into work_time(emp_id, check_time, check_photo)values(?, ?, ?);",-1,&stmt,0);
	sqlite3_bind_int(stmt,1,emp_id);
	sqlite3_bind_text(stmt,2,check_time, 1+strlen(check_time), NULL);
	sqlite3_bind_blob(stmt,3,check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_step(stmt);
	return sqlite3_last_insert_rowid(conn);
}

bool book_info_select_all(std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool model_img_select_all(std::vector<model_img_Rec>& recs) {
	sqlite3_prepare(conn, "select * from model_img",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			model_img_Rec rec;
			int bytes=0;
			int model_img_id_t = sqlite3_column_int(stmt,0);
			rec.model_img_id = model_img_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const void* photo_t = sqlite3_column_blob(stmt,2);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_select_all(std::vector<work_time_Rec>& recs) {
	sqlite3_prepare(conn, "select * from work_time",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			work_time_Rec rec;
			int bytes=0;
			int work_time_id_t = sqlite3_column_int(stmt,0);
			rec.work_time_id = work_time_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* check_time_t = sqlite3_column_text(stmt,2);
			rec.check_time = AutoType(check_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const void* check_photo_t = sqlite3_column_blob(stmt,3);
			rec.check_photo = AutoType(check_photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_primarys(std::vector<int>& primarys) {
	sqlite3_prepare(conn, "select emp_id from book_info;",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			int primary = sqlite3_column_int(stmt,0);
			primarys.push_back(primary);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool model_img_primarys(std::vector<int>& primarys) {
	sqlite3_prepare(conn, "select model_img_id from model_img;",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			int primary = sqlite3_column_int(stmt,0);
			primarys.push_back(primary);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_primarys(std::vector<int>& primarys) {
	sqlite3_prepare(conn, "select work_time_id from work_time;",-1,&stmt,0);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			int primary = sqlite3_column_int(stmt,0);
			primarys.push_back(primary);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_select_by_emp_id(int emp_id, std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info where emp_id=?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_select_by_emp_name(const char* emp_name, std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info where emp_name=?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_select_by_dep_name(const char* dep_name, std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info where dep_name=?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_select_by_hire_time(const char* hire_time, std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info where hire_time=?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_select_by_photo(AutoType& photo, std::vector<book_info_Rec>& recs) {
	sqlite3_prepare(conn, "select * from book_info where photo=?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			book_info_Rec rec;
			int bytes=0;
			int emp_id_t = sqlite3_column_int(stmt,0);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,1);
			const unsigned char* emp_name_t = sqlite3_column_text(stmt,1);
			rec.emp_name = AutoType(emp_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* dep_name_t = sqlite3_column_text(stmt,2);
			rec.dep_name = AutoType(dep_name_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const unsigned char* hire_time_t = sqlite3_column_text(stmt,3);
			rec.hire_time = AutoType(hire_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,4);
			const void* photo_t = sqlite3_column_blob(stmt,4);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool model_img_select_by_model_img_id(int model_img_id, std::vector<model_img_Rec>& recs) {
	sqlite3_prepare(conn, "select * from model_img where model_img_id=?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, model_img_id);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			model_img_Rec rec;
			int bytes=0;
			int model_img_id_t = sqlite3_column_int(stmt,0);
			rec.model_img_id = model_img_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const void* photo_t = sqlite3_column_blob(stmt,2);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool model_img_select_by_emp_id(int emp_id, std::vector<model_img_Rec>& recs) {
	sqlite3_prepare(conn, "select * from model_img where emp_id=?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			model_img_Rec rec;
			int bytes=0;
			int model_img_id_t = sqlite3_column_int(stmt,0);
			rec.model_img_id = model_img_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const void* photo_t = sqlite3_column_blob(stmt,2);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool model_img_select_by_photo(AutoType& photo, std::vector<model_img_Rec>& recs) {
	sqlite3_prepare(conn, "select * from model_img where photo=?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			model_img_Rec rec;
			int bytes=0;
			int model_img_id_t = sqlite3_column_int(stmt,0);
			rec.model_img_id = model_img_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const void* photo_t = sqlite3_column_blob(stmt,2);
			rec.photo = AutoType(photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_select_by_work_time_id(int work_time_id, std::vector<work_time_Rec>& recs) {
	sqlite3_prepare(conn, "select * from work_time where work_time_id=?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, work_time_id);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			work_time_Rec rec;
			int bytes=0;
			int work_time_id_t = sqlite3_column_int(stmt,0);
			rec.work_time_id = work_time_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* check_time_t = sqlite3_column_text(stmt,2);
			rec.check_time = AutoType(check_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const void* check_photo_t = sqlite3_column_blob(stmt,3);
			rec.check_photo = AutoType(check_photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_select_by_emp_id(int emp_id, std::vector<work_time_Rec>& recs) {
	sqlite3_prepare(conn, "select * from work_time where emp_id=?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			work_time_Rec rec;
			int bytes=0;
			int work_time_id_t = sqlite3_column_int(stmt,0);
			rec.work_time_id = work_time_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* check_time_t = sqlite3_column_text(stmt,2);
			rec.check_time = AutoType(check_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const void* check_photo_t = sqlite3_column_blob(stmt,3);
			rec.check_photo = AutoType(check_photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_select_by_check_time(const char* check_time, std::vector<work_time_Rec>& recs) {
	sqlite3_prepare(conn, "select * from work_time where check_time=?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			work_time_Rec rec;
			int bytes=0;
			int work_time_id_t = sqlite3_column_int(stmt,0);
			rec.work_time_id = work_time_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* check_time_t = sqlite3_column_text(stmt,2);
			rec.check_time = AutoType(check_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const void* check_photo_t = sqlite3_column_blob(stmt,3);
			rec.check_photo = AutoType(check_photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool work_time_select_by_check_photo(AutoType& check_photo, std::vector<work_time_Rec>& recs) {
	sqlite3_prepare(conn, "select * from work_time where check_photo=?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	while (1) {
		int s = sqlite3_step(stmt);
		if (s==SQLITE_ROW) {
			work_time_Rec rec;
			int bytes=0;
			int work_time_id_t = sqlite3_column_int(stmt,0);
			rec.work_time_id = work_time_id_t;
			int emp_id_t = sqlite3_column_int(stmt,1);
			rec.emp_id = emp_id_t;
			bytes = sqlite3_column_bytes(stmt,2);
			const unsigned char* check_time_t = sqlite3_column_text(stmt,2);
			rec.check_time = AutoType(check_time_t,bytes);
			bytes = sqlite3_column_bytes(stmt,3);
			const void* check_photo_t = sqlite3_column_blob(stmt,3);
			rec.check_photo = AutoType(check_photo_t,bytes);
			recs.push_back(rec);
		}
		else if (s==SQLITE_DONE) {
			break;
		}
		else {
			printf("\nselect failed.\n");
			return false;
		}
	}
	return true;
}

bool book_info_update_emp_name_by_emp_id(const char* emp_name, int emp_id) {
	sqlite3_prepare(conn,"update book_info set emp_name=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_emp_name_by_dep_name(const char* emp_name, const char* dep_name) {
	sqlite3_prepare(conn,"update book_info set emp_name=? where dep_name?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_emp_name_by_hire_time(const char* emp_name, const char* hire_time) {
	sqlite3_prepare(conn,"update book_info set emp_name=? where hire_time?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_emp_name_by_photo(const char* emp_name, AutoType& photo) {
	sqlite3_prepare(conn,"update book_info set emp_name=? where photo?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_dep_name_by_emp_id(const char* dep_name, int emp_id) {
	sqlite3_prepare(conn,"update book_info set dep_name=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_dep_name_by_emp_name(const char* dep_name, const char* emp_name) {
	sqlite3_prepare(conn,"update book_info set dep_name=? where emp_name?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_dep_name_by_hire_time(const char* dep_name, const char* hire_time) {
	sqlite3_prepare(conn,"update book_info set dep_name=? where hire_time?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_dep_name_by_photo(const char* dep_name, AutoType& photo) {
	sqlite3_prepare(conn,"update book_info set dep_name=? where photo?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_hire_time_by_emp_id(const char* hire_time, int emp_id) {
	sqlite3_prepare(conn,"update book_info set hire_time=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_hire_time_by_emp_name(const char* hire_time, const char* emp_name) {
	sqlite3_prepare(conn,"update book_info set hire_time=? where emp_name?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_hire_time_by_dep_name(const char* hire_time, const char* dep_name) {
	sqlite3_prepare(conn,"update book_info set hire_time=? where dep_name?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_hire_time_by_photo(const char* hire_time, AutoType& photo) {
	sqlite3_prepare(conn,"update book_info set hire_time=? where photo?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_photo_by_emp_id(AutoType& photo, int emp_id) {
	sqlite3_prepare(conn,"update book_info set photo=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_photo_by_emp_name(AutoType& photo, const char* emp_name) {
	sqlite3_prepare(conn,"update book_info set photo=? where emp_name?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_text(stmt,1, emp_name, 1+strlen(emp_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_photo_by_dep_name(AutoType& photo, const char* dep_name) {
	sqlite3_prepare(conn,"update book_info set photo=? where dep_name?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_text(stmt,1, dep_name, 1+strlen(dep_name), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool book_info_update_photo_by_hire_time(AutoType& photo, const char* hire_time) {
	sqlite3_prepare(conn,"update book_info set photo=? where hire_time?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_text(stmt,1, hire_time, 1+strlen(hire_time), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool model_img_update_emp_id_by_model_img_id(int emp_id, int model_img_id) {
	sqlite3_prepare(conn,"update model_img set emp_id=? where model_img_id?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_bind_int(stmt,1, model_img_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool model_img_update_emp_id_by_photo(int emp_id, AutoType& photo) {
	sqlite3_prepare(conn,"update model_img set emp_id=? where photo?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool model_img_update_photo_by_model_img_id(AutoType& photo, int model_img_id) {
	sqlite3_prepare(conn,"update model_img set photo=? where model_img_id?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_int(stmt,1, model_img_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool model_img_update_photo_by_emp_id(AutoType& photo, int emp_id) {
	sqlite3_prepare(conn,"update model_img set photo=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, photo.getStr(), photo.getLen(), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_emp_id_by_work_time_id(int emp_id, int work_time_id) {
	sqlite3_prepare(conn,"update work_time set emp_id=? where work_time_id?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_bind_int(stmt,1, work_time_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_emp_id_by_check_time(int emp_id, const char* check_time) {
	sqlite3_prepare(conn,"update work_time set emp_id=? where check_time?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_emp_id_by_check_photo(int emp_id, AutoType& check_photo) {
	sqlite3_prepare(conn,"update work_time set emp_id=? where check_photo?;",-1,&stmt,0);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_time_by_work_time_id(const char* check_time, int work_time_id) {
	sqlite3_prepare(conn,"update work_time set check_time=? where work_time_id?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	sqlite3_bind_int(stmt,1, work_time_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_time_by_emp_id(const char* check_time, int emp_id) {
	sqlite3_prepare(conn,"update work_time set check_time=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_time_by_check_photo(const char* check_time, AutoType& check_photo) {
	sqlite3_prepare(conn,"update work_time set check_time=? where check_photo?;",-1,&stmt,0);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_photo_by_work_time_id(AutoType& check_photo, int work_time_id) {
	sqlite3_prepare(conn,"update work_time set check_photo=? where work_time_id?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_bind_int(stmt,1, work_time_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_photo_by_emp_id(AutoType& check_photo, int emp_id) {
	sqlite3_prepare(conn,"update work_time set check_photo=? where emp_id?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_bind_int(stmt,1, emp_id);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}

bool work_time_update_check_photo_by_check_time(AutoType& check_photo, const char* check_time) {
	sqlite3_prepare(conn,"update work_time set check_photo=? where check_time?;",-1,&stmt,0);
	sqlite3_bind_blob(stmt,1, check_photo.getStr(), check_photo.getLen(), NULL);
	sqlite3_bind_text(stmt,1, check_time, 1+strlen(check_time), NULL);
	sqlite3_step(stmt);
	int s = sqlite3_step(stmt);
	if (s == SQLITE_DONE) {
		return true;
	}
	return false;
}


}// end namespace DB
#endif // #ifdef __USE_SQLITE__
