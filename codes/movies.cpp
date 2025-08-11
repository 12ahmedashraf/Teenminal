#include "movies.h"
#include "teenminal.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace teen
{
 

    static fs::path movie_dir(const fs::path &base)
    {
        fs::path dir = base / "movies";
        if (!fs::exists(dir))
            fs::create_directories(dir);
        return dir;
    }
    void movie_add(const fs::path &base, const string &title, int rating, const string &review)
    {
        string s = sanitize_filename(title);
        fs::path file = movie_dir(base) / (s + ".txt");
        ofstream ofs(file, ios::trunc);
        ofs << "Title: " << title << "\n";
        ofs << "Rating: " << rating << "\n";
        ofs << "Review: " << review << "\n";
        cout << green << "Movie added: " << title << reset << "\n";
    }
    void movie_list(const fs::path &base)
    {
        fs::path dir = movie_dir(base);
        int count = 1;
        for (auto &f : fs::directory_iterator(dir))
        {
            if (f.is_regular_file())
            {
                cout << count++ << ". " << f.path().stem().string() << "\n";
            }
        }
    }
    void movie_view(const fs::path &base, const string &title)
    {
        string s = sanitize_filename(title);
        fs::path file = movie_dir(base) / (s + ".txt");
        if (!fs::exists(file))
        {
            cout << "You have't added this movie to the movies you watched yet!\n";
            return;
        }

        ifstream ifs(file);
        string line;
        while (getline(ifs, line))
            cout << line << endl;
    }
}