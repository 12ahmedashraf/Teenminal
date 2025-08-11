#include "achievements.h"
#include "teenminal.h"
#include <fstream>
#include <iostream>
using namespace std;
namespace fs = filesystem;
namespace teen
{
    static fs::path achievement_dir(const fs::path &base)
    {
        fs::path dir = base / "achievements";
        if (!fs::exists(dir))
            fs::create_directories(dir);
        return dir;
    }
    void achievement_add(const fs::path &base, const string &title, const string &description)
    {
        string s = sanitize_filename(title);
        fs::path file = achievement_dir(base) / (s + ".txt");
        ofstream ofs(file, ios::trunc);
        ofs << "Achievement: " << title << "\n";
        ofs << "Description: " << description << "\n";
        cout << green << "Achievement added , congrats :))" << title << reset << "\n";
    }
    void achievement_list(const fs::path &base)
    {
        fs::path dir = achievement_dir(base);
        int count = 1;
        for (auto &f : fs::directory_iterator(dir))
        {
            if (f.is_regular_file())
                cout << count++ << ". " << f.path().stem().string() << "\n";
        }
    }
    void achievement_view(const fs::path &base, const string &title)
    {
        string s = sanitize_filename(title);
        fs::path file = achievement_dir(base) / (s + ".txt");
        if (!fs::exists(file))
        {
            cout << "Achievement not found.\n";
            return;
        }
        ifstream ifs(file);
        
        string line;
        while (getline(ifs, line))
            cout<<line<<"\n";
    }
}
