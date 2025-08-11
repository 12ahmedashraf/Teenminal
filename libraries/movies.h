#ifndef movies_h
#define movies_h

#include <teenminal.h>
#include <string>
#include <filesystem>

namespace teen {
    void movie_add(const filesystem::path &base, const string &title,int rating,const string &review);
    void movie_list(const filesystem::path &base);
    void movie_view(const filesystem::path &base, const string &title);
}

#endif