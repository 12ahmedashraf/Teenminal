#ifndef books_h
#define teen_h

#include <teenminal.h>
#include <string>
#include <filesystem>

namespace teen
{
    void book_add(const filesystem::path &base, const string &title, int rating, const string &review);
    void book_list(const filesystem::path &base);
    void book_view(const filesystem::path &base, const string &title);
}
#endif