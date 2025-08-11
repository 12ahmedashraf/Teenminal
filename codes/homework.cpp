#include "hw.h"
#include <fstream>
#include <iostream>
namespace teen {
    using namespace std;
    void hw_add(const fs::path &base, const string &description, const string &due)
    {
        fs::path f = base/"homework.txt"; 
        ofstream ofs(f, ios::app);
        ofs<<description<<"|"<<due<<"\n";
        cout<<green<<"Homework added"<<reset<<"\n";
    }
    void hw_list(const fs::path &base)
    {
        fs::path f = base/"homework.txt";
        if(!fs::exists(f)){
            cout<<"No homework :)))\n";
            return;
        }
        ifstream ifs(f);
        string l;
        int i=1;
        cout<<cyan<<"Homework:"<<reset<<"\n";
        while(getline(ifs,l))
        {
            auto pos=l.find('|');
            if(pos==string::npos)
            continue;
            string description= l.substr(0,pos);
            string due=l.substr(pos+1);
            int d=days_until(due);
            cout<<i++<<". "<<description<<" - due"<<due<<" ("<<d<<" days)\n";
        }
    }

}