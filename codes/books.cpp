#include "books.h"
#include "teenminal.h"
#include <fstream>
#include <iostream>
using namespace std;
namespace fs = filesystem;
namespace teen
{
    static fs::path book_dir(const fs::path &base)
    {
        fs::path dir = base / "books";
        if (!fs::exists(dir))
            fs::create_directories(dir);
        return dir;
    }
    void book_add(const fs::path &base, const string &title, int rating, const string &review)
    {
        string s = sanitize_filename(title);
        fs::path file = book_dir(base) / (s + ".txt");
        ofstream ofs(file, ios::trunc);
        ofs << "Title: " << title << "\n";
        ofs << "Rating: " << rating << "\n";
        ofs << "Review: " << review << "\n";
        cout << green << title << " book added" << reset << "\n";
    }
    void book_list(const fs::path &base)
    {
        fs::path dir = book_dir(base);
        int count = 1;
        for (auto &f : fs::directory_iterator(dir))
        {
            if (f.is_regular_file())
            {
                cout << count++ << ". " << f.path().stem().string() << "\n";
            }
        }
    }
    void book_view(const fs::path &base, const string &title)
    {
        string s = sanitize_filename(title);
        fs::path file = book_dir(base) / (s + ".txt");
        if (!fs::exists(file))
        {
            cout << "Book not added to read books\n";
            return;
        }
        ifstream ifs(file);
        string line;
        while (getline(ifs, line))
            cout << line << "\n";
    }

}