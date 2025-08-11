#ifndef achievement_h
#define achievemnets_h

#include "teenminal.h"
#include <filesystem>
#include <string>
#include <vector>
namespace teen
{
    void achievements_add(const filesystem::path &base, const string &title, const string &description);
    void achievements_list(const filesystem::path &base);
    void achievements_view(const filesystem::path &base, const string &title);
}
#endif