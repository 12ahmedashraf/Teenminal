#ifndef PROJECTS_H
#define PROJECTS_H

#include <filesystem>
#include <string>
#include <vector>
#include "teenminal.h"

namespace teen
{
    void project_add(const std::filesystem::path &base, const std::string &title, const std::string &description);
    void project_list(const std::filesystem::path &base);
    void project_view(const std::filesystem::path &base, const std::string &title);
}

#endif
