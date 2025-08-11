#include "series.h"
#include "teenminal.h"
#include <fstream>
#include <iostream>

namespace fs = filesystem;
namespace teen
{
    static fs::path series_dir(const fs::path &base)
    {
        fs::path dir = base / "series";
        if (!fs::exists(dir))
            fs::create_directories(dir);
        return dir;
    }
    void series_add(const fs::path &base, const string &title, int rating, const string &review)
    {
        string s = sanitize_filename(title);
        fs::path file = series_dir(base) / (s + ".txt");
        ofstream ofs(file, ios::trunc);
        ofs << "Title: " << title << "\n";
        ofs << "Rating: " << rating << "\n";
        ofs << "Review: " << review << "\n";
        cout << green << title << " series added" << reset << "\n";
    }
    void series_list(const fs::path &base)
    {
        fs::path dir = series_dir(base);
        int count = 1;
        for (auto &f : fs::directory_iterator(dir))
        {
            if (f.is_regular_file())
                cout << count++ << ". " << f.path().stem().string() << "\n";
        }
    }
    void series_view(const fs::path &base, const string &title)
    {
        string s = sanitize_filename(title);
        fs::path file = series_dir(base) / (s + ".txt");
        if (!fs::exists(file))
        {
            cout << "Series not found.\n";
            return;
        }
        ifstream ifs(file);
        string line;
        while(getline(ifs,line))
            cout<<line<<"\n";
    }
}