#ifndef shell_h
#define shell_h
#include "teenminal.h"
#include <vector>

namespace teen
{
    void print_lg();
    void print_help();
    void save_history(const fs::path &base, const string &line);
    void print_history(const fs::path &base);
    void dispatch(const vector<string> &args, const fs::path &base);
}
#endif