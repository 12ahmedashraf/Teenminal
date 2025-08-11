#ifndef SHELL_H
#define SHELL_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void print_lg();
    void print_help();
    void save_history(const fs::path &base, const std::string &line);
    void print_history(const fs::path &base);
    void dispatch(const std::vector<std::string> &args, const fs::path &base);
}

#endif
