#ifndef journal_h
#define journal_h

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void journal_add(const std::filesystem::path &base, const std::string &text, const std::string &date = "");
    void journal_read(const std::filesystem::path &base, const std::string &date);
}
#endif
