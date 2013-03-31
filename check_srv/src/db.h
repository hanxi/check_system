#ifndef __DB_H_
#define __DB_H_

namespace DB
{
    bool start();
    void stop();
    bool worktimeInsert(int empId, const char* time, const char* photo);
    bool worktimeAltTime(int worktimeId, const char* time);
    bool worktimeAltEmpId(int worktimeId, int empId);
}

#endif

