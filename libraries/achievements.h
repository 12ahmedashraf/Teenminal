#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void achievements_add(const std::filesystem::path &base, const std::string &title, const std::string &description);
    void achievements_list(const std::filesystem::path &base);
    void achievements_view(const std::filesystem::path &base, const std::string &title);
}
#endif