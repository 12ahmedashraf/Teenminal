#include "journal.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace teen
{
    static fs::path journal_day_path(const fs::path &base, const string &date)
    {
        if (date.size() != 10)
            throw runtime_error("date must be YYYY-MM-DD");
        string y = date.substr(0, 4), m = date.substr(5, 2), d = date.substr(8, 2);
        fs::path p = base / y / m / d;
        if (!fs::exists(p))
            fs::create_directories(p);
        return p / (d + ".txt");
    }
    void journal_add(const fs::path &base, const string &text, const string &date)
    {
        string d = date.empty() ? today_date() : date;
        fs::path f = journal_day_path(base, d);
        ofstream ofs(f, ios::app);
        if (!ofs)
        {
            cerr << "Can't open journal\n";
            return;
        }
        ofs << "[" << now_timestamp() << "] " << text << "\n";
        cout << green << "Saved journal for " << d << reset << "\n";
    }
    void journal_read(const fs::path &base, const string &date)
    {
        try
        {
            fs::path f = journal_day_path(base, date);
            if (!fs::exists(f))
            {
                cout << "NO journal for " << date << "\n";
                return;
            }
            ifstream ifs(f);
            string l;
            cout << cyan << "Journal " << date << reset << "\n";
            while (getline(ifs, l))
                cout << l << "\n";
        }
        catch (...)
        {
            cout << "Date format YYYY-MM-DD required\n";
        }
    }

}