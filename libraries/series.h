#ifndef series_h
#define series_h

#include <string>
#include <filesystem>
#include "teenminal.h";
namespace teen
{
    void series_add(const filesystem::path &base, const string &title, int rating, const string &review);
    void series_list(const filesystem::path &base);
    void series_view(const filesystem::path &base, const string &title);
    
}

#endif