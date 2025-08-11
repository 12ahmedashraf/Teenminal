#include "shell.h"
#include "journal.h"
#include "todo.h"
#include "exam.h"
#include "hw.h"
#include "ideas.h"
#include "movies.h"
#include "books.h"
#include "achievements.h"
#include "projects.h"
#include "series.h"
#include "snake.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace teen
{
    using namespace std;
    static const char *LOGO = R"( 
_________  _______   _______   ________   _____ ______   ___  ________   ________  ___          
|\___   ___\\  ___ \ |\  ___ \ |\   ___  \|\   _ \  _   \|\  \|\   ___  \|\   __  \|\  \         
\|___ \  \_\ \   __/|\ \   __/|\ \  \\ \  \ \  \\\__\ \  \ \  \ \  \\ \  \ \  \|\  \ \  \        
     \ \  \ \ \  \_|/_\ \  \_|/_\ \  \\ \  \ \  \\|__| \  \ \  \ \  \\ \  \ \   __  \ \  \       
      \ \  \ \ \  \_|\ \ \  \_|\ \ \  \\ \  \ \  \    \ \  \ \  \ \  \\ \  \ \  \ \  \ \  \____  
       \ \__\ \ \_______\ \_______\ \__\\ \__\ \__\    \ \__\ \__\ \__\\ \__\ \__\ \__\ \_______\
        \|__|  \|_______|\|_______|\|__| \|__|\|__|     \|__|\|__|\|__| \|__|\|__|\|__|\|_______|
                                                                                                 
                                                                                                 
                                                                                                 )";
    void print_lg()
    {
        cout << bold << cyan << LOGO << reset << "\n";
    }
    void print_help()
    {
        cout << bold << yellow << "Teenminal Guide" << reset << "\n\n";
        cout << cyan << "                  -- Productivity -- " << reset << "\n";
        cout << " journal add \"text\" [YYYY-MM-DD] " << "Add journal entry (deafult today)\n";
        cout << " journal read YYYY-MM-DD            " << "Read day journal\n";
        cout << " journal list YYYY-MM               " << "Your journals for the month\n";
        cout << " todo add \"task\" [YYYY-MM-DD]     " << "Add a task todo for the day\n";
        cout << " todo list [YYYY-MM-DD]             " << "List todos\n";
        cout << " todo done INDEX [YYYY-MM-DD]       " << "Mark todo done\n";
        cout << " exam add \"name\" YYYY-MM-DD       " << "Add exam\n";
        cout << " exam list                          " << "List exams and days left\n";
        cout << " hw add \"description\" YYYY-MM-DD  " << "Add homework\n";
        cout << " hw list                            " << "List homeworks\n";
        cout << " idea add \"text\"                  " << "Record your idea!\n";
        cout << " idea list                          " << "List your ideas!\n\n";
        cout
            << cyan << "                   -- Media & Learning --" << reset << "\n";
        cout << " movie add \"title\" <rating> \"review\"   " << "Add your movies to remember them! (rating 1-10)\n";
        cout << " movie list                                " << "List saved movies (by title)\n";
        cout << " movie view \"title\"                      " << "Remember movie details (by title)\n\n";

        cout << " book add \"title\" <rating> \"review\"    " << "Add a book you read (rating 1-10)\n";
        cout << " book list                                 " << "List read books details\n";
        cout << " book view \"title\"                       " << "Show series details\n\n";

        cout << " series add \"title\" <rating> \"review\"  " << "Add TV series (rating 1-10)\n";
        cout << " series list                               " << "List saved series\n";
        cout << " series view \"title\"                     " << "Show series details\n\n";

        cout << cyan << "                -- Projects & Achievements --" << reset << "\n";
        cout << " project add \"title\" \"description\"      " << "Save a project with description\n";
        cout << " project list                               " << "List projects\n";
        cout << " project view \"title\"                     " << "Show a project details\n\n";

        cout << " achievement add \"title\" \"description\"  " << "Record an achievement\n";
        cout << " achievement list                           " << "List achievements\n";

        cout << cyan << "                    -- FUN --" << reset << "\n";
        cout << " play                     " << "Have fun and play a game!\n\n";
        cout << cyan << "                  -- System --" << reset << "\n";
        cout << " mk path/to/dir                     " << "Create directories\n";
        cout << " run <cmd>                          " << "Run external command (system)\n";
        cout << " history                            " << "Show command history\n";
        cout << " help                               " << "Show this help\n";
        cout << " exit                               " << "Exit Teenminal\n";
    }
    void save_history(const fs::path &base, const string &line)
    {
        fs::path f = base / "history.txt";
        ofstream ofs(f, ios::app);
        if (!ofs)
            return;
        ofs << now_timestamp() << " | " << line << "\n";
    }
    void show_history(const fs::path &base)
    {
        fs::path f = base / "history.txt";
        if (!fs::exists(f))
        {
            cout << "No history.\n";
            return;
        }
        ifstream ifs(f);
        string l;
        int i = 1;
        while (getline(ifs, l))
        {
            cout << i++ << ". " << l << "\n";
        }
    }
    void dispatch(const vector<string> &args, const fs::path &base)
    {
        if (args.empty())
        {
            cout << "Error: No command provided\n";
            return;
        }

        string cmd = args[0];
        cout << cmd << "\n";
        if (cmd == "help")
        {
            print_help();
            cout.flush();
        }
        else if (cmd == "history")
        {
            show_history(base);
        }
        else if (cmd == "journal")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                {
                    journal_add(base, args[2], (args.size() >= 4 ? args[3] : string()));
                    cout << "Journal entry added\n";
                }
                else
                {
                    cout << "Usage: journal add \"text\" [YYYY-MM-DD]\n";
                }
            }
            else if (args.size() >= 3 && args[1] == "read")
            {
                journal_read(base, args[2]);
            }
            else
            {
                cout << "journal commands: add/read/list\n";
            }
        }
        else if (cmd == "exam")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 4)
                {
                    exam_add(base, args[2], args[3]);
                    cout << "Exam added\n";
                }
                else
                {
                    cout << "Usage: exam add \"name\" YYYY-MM-DD\n";
                }
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                exam_list(base);
            }
            else
            {
                cout << "exam commands: add/list\n";
            }
        }
        else if (cmd == "todo")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                {
                    todo_add(base, args[2], (args.size() >= 4 ? args[3] : string()));
                    cout << "Todo added\n";
                }
                else
                {
                    cout << "Usage: todo add \"task\" [YYYY-MM-DD]\n";
                }
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                todo_list(base, (args.size() >= 3 ? args[2] : string()));
            }
            else if (args.size() >= 3 && args[1] == "done")
            {
                todo_done(base, stoi(args[2]), (args.size() >= 4 ? args[3] : string()));
                cout << "Todo marked as done\n";
            }
            else
            {
                cout << "todo commands: add/list/done\n";
            }
        }
        else if (cmd == "hw")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 4)
                {
                    hw_add(base, args[2], args[3]);
                    cout << "Homework added\n";
                }
                else
                {
                    cout << "Usage: hw add \"description\" YYYY-MM-DD\n";
                }
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                hw_list(base);
            }
            else
            {
                cout << "hw commands: add/list\n";
            }
        }
        else if (cmd == "idea")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                {
                    idea_add(base, args[2]);
                    cout << "Idea recorded\n";
                }
                else
                {
                    cout << "Usage: idea add \"text\"\n";
                }
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                idea_list(base);
            }
            else
            {
                cout << "idea commands: add/list\n";
            }
        }
        else if (cmd == "mkdir")
        {
            if (args.size() >= 2)
            {
                fs::create_directories(args[1]);
                cout << "Directory created\n";
            }
            else
            {
                cout << "Error: No path provided\n";
            }
        }
        else if (cmd == "run")
        {
            if (args.size() >= 2)
            {
                int rc = system(join_from(args, 1).c_str());
                cout << "Command exited with code: " << rc << "\n";
            }
            else
            {
                cout << "Usage: run <command>\n";
            }
        }
        else if (cmd == "play")
        {
            play_snake();
        }
        else if (cmd == "movie")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                {
                    movie_add(base, args[2], stoi(args[3]), args[4]);
                }
                else
                {
                    cout << "Usage: movie add \"name\" rating \"review\"\n";
                }
            }
            else if (args.size() >= 3 && args[1] == "view")
            {
                movie_view(base, args[2]);
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                movie_list(base);
            }
            else
            {
                cout << "movie commands: add/view/list\n";
            }
        }
        else if (cmd == "series")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                {
                    series_add(base, args[2], stoi(args[3]), args[4]);
                    cout << "Series added\n";
                }
                else
                {
                    cout << "Usage: series add \"name\" rating \"review\"\n";
                }
            }
            else if (args.size() >= 3 && args[1] == "view")
            {
                series_view(base, args[2]);
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                series_list(base);
            }
            else
            {
                cout << "series commands: add/view/list\n";
            }
        }
        else if (cmd == "book")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                {
                    book_add(base, args[2], stoi(args[3]), args[4]);
                    cout << "Book added\n";
                }
                else
                {
                    cout << "Usage: book add \"name\" rating \"review\"\n";
                }
            }
            else if (args.size() >= 3 && args[1] == "view")
            {
                book_view(base, args[2]);
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                book_list(base);
            }
            else
            {
                cout << "book commands: add/view/list\n";
            }
        }
        else if (cmd == "project")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 4)
                {
                    project_add(base, args[2], args[3]);
                    cout << "Project added\n";
                }
                else
                {
                    cout << "Usage: project add \"name\" \"description\"\n";
                }
            }
            else if (args.size() >= 2 && args[1] == "list")
            {
                project_list(base);
            }
            else if (args.size() >= 3 && args[1] == "view")
            {
                project_view(base, args[2]);
            }
            else
            {
                cout << "project commands: add/list/view\n";
            }
        }
        else
        {
            int rc = system(join_from(args, 0).c_str());
            if (rc == -1)
            {
                cout << "Failed to execute command\n";
            }
        }
    }
}
