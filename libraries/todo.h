#ifndef todo_h
#define todo_h

#include "teenminal.h"

namespace teen
{
    void todo_add(const fs::path &base, const string &task, const string &date = "");
    void todo_list(const fs::path &base, const string &date);
    void todo_done(const fs::path &base, int index, const string &date);
}

#endif