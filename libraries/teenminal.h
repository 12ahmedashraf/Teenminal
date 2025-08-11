#ifndef TEENMINAL_H
#define TEENMINAL_H

#include <string>
#include <filesystem>
#include <vector>

namespace teen
{
    static std::string sanitize_filename(const std::string &input)
    {
        std::string output;
        for (char c : input)
        {
            if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.')
            {
                output += c;
            }
            else
            {
                output += '_';
            }
        }
        return output;
    }

    namespace fs = std::filesystem;

    extern const std::string reset, red, green, yellow, blue, mag, cyan, bold;

    std::string get_home_dir();
    std::string now_timestamp();
    std::string today_date();
    void ensure_dir(const fs::path &p);
    fs::path data_base();
    std::vector<std::string> tokenize(const std::string &line);
    std::string join_from(const std::vector<std::string> &v, size_t i);
    void enable_ansi();
    bool parse_ymd(const std::string &s, tm &out);
    int days_until(const std::string &date);
}

#endif
