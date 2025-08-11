#include "todo.h"
#include <fstream>
#include <iostream>

using namespace std;
namespace teen
{
      string today_date()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        return oss.str();
    }
    static fs::path todo_day_path(const fs::path &base, const string &date)
    {
        string y = date.substr(0, 4), m = date.substr(5, 2), d = date.substr(8, 2);
        fs::path p = base / y / m / d;
        if (!fs::exists(p))
            fs::create_directories(p);
        return p / ("todolist.txt");
    }
    void todo_add(const fs::path &base, const string &task, const string &date)
    {
        string d = date.empty() ? today_date() : date;
        fs::path f = todo_day_path(base, d);
        ofstream ofs(f, ios::app);
        if (!ofs)
        {
            cerr << "Can't open todo list!\n";
            return;
        }
        ofs << "[ ] " << task << "\n";
        cout << green << "Added a todo for " << d << reset << "\n";
    }
    void todo_list(const fs::path &base, const string &date)
    {
        string d = date.empty() ? today_date() : date;
        fs::path f = todo_day_path(base, d);
        if (!fs::exists(f))
        {
            cout << "No todos for " << d << "\n";
            return;
        }
        ifstream ifs(f);
        string l;
        int i = 1;
        cout << cyan << "Todos " << d << reset << "\n";
        while (getline(ifs, l))
            cout << i++ << ". " << l << "\n";
    }
    void todo_done(const fs::path &base, int index, const string &date)
    {
        string d = date.empty() ? today_date() : date;
        fs::path f = todo_day_path(base, d);
        if (!fs::exists(f))
        {

            cout << "No todos\n";
            return;
        }
        vector<string> lines;
        string l;
        ifstream ifs(f);
        while (getline(ifs, l))
        {
            lines.push_back(l);
        }
        if (index < 1 || index > (int)lines.size())
        {
            cout << "Invalid index\n";
            return;
        }
        if (lines[index - 1].rfind("[x]", 0) == 0)
        {
            cout << "Already done\n";
            return;
        }
        lines[index - 1].replace(0, 3, "[x]");
        ofstream ofs(f, ios::trunc);
        for (auto &s : lines)
        {
            ofs << s << "\n";
        }
        cout << green << "Marked done" << reset << "\n";
    }
}