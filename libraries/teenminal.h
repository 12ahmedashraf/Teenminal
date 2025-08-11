#ifndef teenminal_h
#define teenminal_h

#include <string>
#include <filesystem>
#include <vector>
using namespace std;
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
    namespace fs = filesystem;
    extern const string reset, red, green, yellow, blue, mag, cyan, bold;
    string get_home_dir();
    string now_timestamp();
    string today_date();
    void ensure_dir(const fs::path &p);
    fs::path data_base();
    vector<string> tokenize(const string &line);
    string join_from(const vector<string> &v, size_t i);
    void enable_ansi();
    bool parse_ymd(const string &s, tm &out);
    int days_until(const string &date);
}
#endif