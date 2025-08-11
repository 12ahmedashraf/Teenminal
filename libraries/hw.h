#ifndef hw_h
#define hw_h

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void hw_add(const std::filesystem::path &base, const std::string &description, const std::string &deadline);
    void hw_list(const std::filesystem::path &base);
    void nearest_hw(const std::filesystem::path &base);
}
#endif