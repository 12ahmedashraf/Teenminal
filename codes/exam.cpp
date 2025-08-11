#include "exam.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace teen
{
    void exam_add(const fs::path &base, const string &name, const string &date)
    {
        fs::path f = base / "exams.txt";
        ofstream ofs(f, ios::app);
        ofs << name << "|" << date << "\n";
        cout << green << "Exam added" << reset << "\n";
    }
    void exam_list(const fs::path &base)
    {
        fs::path f = base / "exams.txt";
        if (!fs::exists(f))
        {
            cout << "No exams\n";
            return;
        }
        ifstream ifs(f);
        string l;
        cout << cyan << "Exams:" << reset << "\n";
        while (getline(ifs, l))
        {
            auto pos = l.find('|');
            if (pos == string::npos)
                continue;
            string name = l.substr(0, pos);
            string date = l.substr(pos + 1);
            int d = days_until(date);
            cout << name << " - " << date << " (" << d << " days)\n";
        }
    }
}
