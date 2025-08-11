#ifndef BOOKS_H
#define BOOKS_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void book_add(const std::filesystem::path &base, const std::string &title, int rating, const std::string &review);
    void book_list(const std::filesystem::path &base);
    void book_view(const std::filesystem::path &base, const std::string &title);
}
#endif