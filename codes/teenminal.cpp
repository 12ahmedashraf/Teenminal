#include "teenminal.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif

namespace teen
{
     using namespace std;

     const string reset = "\033[0m", red = "\033[31m", green = "\033[32m", yellow = "\033[33m", blue = "\033[34m", mag = "\033[35m", cyan = "\033[36m", bold = "\033[1m";

     string get_home_dir()
     {
#ifdef _WIN32
          const char *home = getenv("USERPROFILE");
#else
          const char *home = getenv("HOME");
#endif
          if (home)
               return string(home);
          return string(".");
     }
     string now_timestamp()
     {
          auto now = chrono::system_clock::now();
          time_t t = chrono::system_clock::to_time_t(now);
          char buf[64];
          tm *lt = localtime(&t);
          strftime(buf, sizeof(buf), "%F %T", lt);
          return string(buf);
     }
     void ensure_dir(const fs::path &p)
     {
          if (!fs::exists(p))
               fs::create_directories(p);
     }
     fs::path data_base()
     {
          fs::path base = fs::path(get_home_dir()) / ".teenminal";
          ensure_dir(base);
          return base;
     }
     vector<string> tokenize(const string &line)
     {
          vector<string> out;
          string cur;
          bool inq = false;
          for (size_t i = 0; i < line.size(); ++i)
          {
               char c = line[i];
               if (c == '"')
               {
                    inq = !inq;
                    continue;
               }
               if (!inq && isspace((unsigned char)c))
               {
                    if (!cur.empty())
                    {
                         out.push_back(cur);
                         cur.clear();
                    }
               }
               else
                    cur.push_back(c);
          }
          if (cur.empty())
               out.push_back(cur);
          return out;
     }
     string join_from(const vector<string> &v, size_t i)
     {
          string s;
          for (size_t j = i; j < v.size(); ++j)
          {
               if (j > i)
                    s += " ";
               s += v[j];
          }
          return s;
     }
     void enable_ansi()
     {
#ifdef _WIN32
          HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
          if (hOut == INVALID_HANDLE_VALUE)
               return;
          DWORD dwMode = 0;
          if (!GetConsoleMode(hOut, &dwMode))
               return;
          dwMode |= 0x0004;
          SetConsoleMode(hOut, dwMode);
#endif
     }

     bool parse_ymd(const string &s, tm &out)
     {
          if (s.size() != 10)
               return false;
          try
          {
               int y = stoi(s.substr(0, 4));
               int m = stoi(s.substr(5, 2));
               int d = stoi(s.substr(8, 2));
               out = {};
               out.tm_year = y - 1900;
               out.tm_mon = m - 1;
               out.tm_mday = d;
               out.tm_hour = 0;
               out.tm_min = 0;
               out.tm_sec = 0;
               return true;
          }
          catch (...)
          {
               return false;
          }
     }
     int days_until(const string &date)
     {
          tm tdate;
          if (!parse_ymd(date, tdate))
               return INT_MAX;
          time_t dd = mktime(&tdate);
          time_t now = time(nullptr);
          double diff = difftime(dd, now);
          int days = (int)floor(diff / (60 * 60 * 24));
          return days;
     }
}