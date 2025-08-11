#ifndef EXAM_H
#define EXAM_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void exam_add(const std::filesystem::path &base, const std::string &name, const std::string &date);
    void exam_list(const std::filesystem::path &base);
    void nearest_exam(const std::filesystem::path &base);
}

#endif