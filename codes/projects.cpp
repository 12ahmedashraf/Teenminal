#include "projects.h"
#include "teenminal.h"
#include <fstream>
#include <iostream>

namespace fs = filesystem;
namespace teen
{
    static fs::path project_dir(const fs::path &base)
    {
        fs::path dir = base / "projects";
        if (!fs::exists(dir))
            fs::create_directories(dir);
        return dir;
    }
    void project_add(const fs::path &base, const string &title, const string &description)
    {
        string s = sanitize_filename(title);
        fs::path file = project_dir(base) / (s + ".txt");
        ofstream ofs(file, ios::trunc);
        ofs << "Title: " << title << "\n";
        ofs << "Description: " << description << "\n";
        cout << green << "Project added: " << title << reset << "\n";
    }
    void project_list(const fs::path &base)
    {
        fs::path dir = project_dir(base);
        int count = 1;
        for (auto &f : fs::directory_iterator(dir))
        {
            if (f.is_regular_file())
            {
                cout << count++ << ". " << f.path().stem().string() << "\n";
            }
        }
    }
    void project_view(const fs::path &base, const string &title)
    {
        string s = sanitize_filename(title);
        fs::path file = project_dir(base) / (s + ".txt");
        if (!fs::exists(file))
        {
            cout << "Project not found\n";
            return;
        }
        ifstream ifs(file);
        string line;
        while(getline(ifs,line))
            cout<<line<<"\n";
    }
}