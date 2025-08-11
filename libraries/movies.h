#ifndef movies_h
#define movies_h

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void movie_add(const std::filesystem::path &base, const std::string &title, int rating, const std::string &review);
    void movie_list(const std::filesystem::path &base);
    void movie_view(const std::filesystem::path &base, const std::string &title);
}

#endif