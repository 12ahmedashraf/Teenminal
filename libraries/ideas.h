#ifndef ideas_h
#define ideas_h

#include <filesystem>
#include <string>
#include <vector>

namespace teen
{
    void idea_add(const std::filesystem::path &base, const std::string &idea);
    void idea_list(const std::filesystem::path &base);
}

#endif