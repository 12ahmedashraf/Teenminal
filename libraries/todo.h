#ifndef TODO_H
#define TODO_H

#include "teenminal.h"
#include <string>
#include <filesystem>

namespace teen
{
    void todo_add(const std::filesystem::path &base, const std::string &task, const std::string &date = "");
    void todo_list(const std::filesystem::path &base, const std::string &date);
    void todo_done(const std::filesystem::path &base, int index, const std::string &date);
}

#endif