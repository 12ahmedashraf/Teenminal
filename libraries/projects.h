#ifndef projects_h
#define project_h

#include "teenminal.h"
#include <string>
#include <filesystem>
namespace teen
{
    
    void project_add(const filesystem::path &base, const string &title, const string &description);
    void project_list(const filesystem::path &base);
    void project_view(const filesystem::path &base, const string &title);
}

#endif
