#include "ideas.h"
#include <fstream>
#include <iostream>
#include "teenminal.h"
using namespace std;

namespace teen
{

    void idea_add(const fs::path &base, const string &idea)
    {
        fs::path f = base / "ideas.txt";
        ofstream ofs(f, ios::app);
        ofs << "[" << now_timestamp() << "] " << idea << "\n";
        cout << green << "idea saved" << reset << "\n";
    }
    void idea_list(const fs::path &base)
    {
        fs::path f = base / "ideas.txt";
        if (!fs::exists(f))
        {
            cout << "No ideas\n";
            return;
        }
        ifstream ifs(f);
        string l;
        int i = 1;
        cout << cyan << "Ideas:" << reset << "\n";
        while (getline(ifs, l))
        {
            cout << i++ << ". " << l << "\n";
        }
    }
}