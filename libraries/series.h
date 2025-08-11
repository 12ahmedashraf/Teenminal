#ifndef SERIES_H
#define SERIES_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void series_add(const std::filesystem::path &base, const std::string &title, int rating, const std::string &review);
    void series_list(const std::filesystem::path &base);
    void series_view(const std::filesystem::path &base, const std::string &title);
}

#endif
