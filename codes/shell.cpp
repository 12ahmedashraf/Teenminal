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

namespace teen
{
    using namespace std;
    static const char *LOGO = R"(
████████╗███████╗███████╗███╗   ██╗███╗   ███╗██╗███╗   ██╗ █████╗ ██╗     
╚══██╔══╝██╔════╝██╔════╝████╗  ██║████╗ ████║██║████╗  ██║██╔══██╗██║     
   ██║   █████╗  █████╗  ██╔██╗ ██║██╔████╔██║██║██╔██╗ ██║███████║██║     
   ██║   ██╔══╝  ██╔══╝  ██║╚██╗██║██║╚██╔╝██║██║██║╚██╗██║██╔══██║██║     
   ██║   ███████╗███████╗██║ ╚████║██║ ╚═╝ ██║██║██║ ╚████║██║  ██║███████╗
   ╚═╝   ╚══════╝╚══════╝╚═╝  ╚═══╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝
)";
    void print_lg()
    {
        cout << bold << cyan << LOGO << reset << "\n";
    }
    void print_help()
    {
        cout << bold << yellow << "Teenminal Help" << reset << "\n";
        cout << cyan << "-- Productivity --" << reset << "\n";
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
        cout << " idea add \"text\"                  " << "Record your idea!";
        cout << " idea list                          " << "List your ideas!";
        cout << cyan << "-- Media & Learning --" << reset << "\n";
        cout << " movie add \"title\" <rating> \"review\"   " << "Add your movies to remember them! (rating 1-10)\n";
        cout << " movie list                                " << "List saved movies (by title)\n";
        cout << " movie view \"title\"                      " << "Remember movie details (by title)\n\n";

        cout << " book add \"title\" <rating> \"review\"    " << "Add a book you read (rating 1-10)\n";
        cout << " book list                                 " << "List read books details\n";
        cout << " book view \"title\"                       " << "Show series details\n\n";

        cout << " series add \"title\" <rating> \"review\"  " << "Add TV series (rating 1-10)\n";
        cout << " series list                               " << "List saved series\n";
        cout << " series view \"title\"                     " << "Show series details\n\n";

        cout << cyan << "-- Projects & Achievements --" << reset << "\n";
        cout << " project add \"title\" \"description\"      " << "Save a project with description\n";
        cout << " project list                               " << "List projects\n";
        cout << " project view \"title\"                     " << "Show a project details\n\n";

        cout << " achievement add \"title\" \"description\"  " << "Record an achievement\n";
        cout << " achievement list                           " << "List achievements\n";

        cout << cyan << "-- FUN --" << reset << "\n";
        cout << " play                     " << "Have fun and play a game!";
        cout << cyan << "-- System --" << reset << "\n";
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
            return;
        string cmd = args[0];
        if (cmd == "help")
        {
            print_help();
            return;
        }
        if (cmd == "history")
        {
            show_history(base);
            return;
        }
        if (cmd == "journal")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                    journal_add(base, args[2], (args.size() >= 4 ? args[3] : string()));
                else
                    cout << "Usage: journal add \"text\" [YYYY-MM-DD]\n";
                return;
            }
            if (args.size() >= 3 && args[1] == "read")
            {
                journal_read(base, args[2]);
                return;
            }
            cout << "journal commands: add/read/list\n";
            return;
        }
        if (cmd == "exam")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 4)
                    exam_add(base, args[2], args[3]);
                else
                    cout << "Usage: exam add \"name\" YYYY-MM-DD\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                exam_list(base);
                return;
            }
            cout << "exam commands: add/list\n";
            return;
        }
        if (cmd == "todo")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                {
                    todo_add(base, args[2], (args.size() >= 4 ? args[3] : string()));
                }
                else
                    cout << "Usage: todo add \"task\" [YYYY-MM-DD]\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                todo_list(base, (args.size() >= 3 ? args[2] : string()));
                return;
            }
            if (args.size() >= 3 && args[1] == "done")
            {
                int idx = stoi(args[2]);
                todo_done(base, idx, (args.size() >= 4 ? args[3] : string()));
                return;
            }
            cout << "todo commands: add/list/done\n";
            return;
        }
        if (cmd == "hw")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 4)
                {
                    hw_add(base, args[2], args[3]);
                }
                else
                    cout << "Usage: hw add \"description\" YYYY-MM-DD\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                hw_list(base);
                return;
            }
            cout << "hw commands: add/list\n";
            return;
        }
        if (cmd == "idea")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 3)
                {
                    idea_add(base, args[2]);
                }
                else
                    cout << "Usage: idea recorded \"text\"\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                idea_list(base);
                return;
            }
            cout << "idea commands: add/list\n";
            return;
        }
        if (cmd == "mkdir")
        {
            if (args.size() >= 2)
            {
                fs::create_directories(fs::path(args[1]));
                cout << green << "Directory is created successfully!";
            }
            else
                cout << red << "No path provide\n";
            return;
        }
        if (cmd == "run")
        {
            string c = join_from(args, 1);
            if (c.empty())
            {
                cout << "command is missing: run <command>\n";
                return;
            }
            int rc = system(c.c_str());
            cout << "(exit: " << rc << ")\n";
            return;
        }
        if (cmd == "play")
        {
            play_snake();
            return;
        }

        if (cmd == "movie")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                    movie_add(base, args[2], stoi(args[3]), args[4]);
                else
                    cout << "Usage: movie add \"name\" rating \"review\" \n";
                return;
            }
            if (args.size() >= 2 && args[1] == "view")
            {
                if (args.size() >= 3)
                    movie_view(base, args[2]);
                else
                    cout << "Usage: movie view \"name\"\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                movie_list(base);
                return;
            }
            cout << "movie commands: add/list/view\n";
            return;
        }
        if (cmd == "series")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                    series_add(base, args[2], stoi(args[3]), args[4]);
                else
                    cout << "Usage: series add \"name\" <rating> \"review\" \n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                series_list(base);
                return;
            }
            if (args.size() >= 2 && args[1] == "view")
            {
                if (args.size() >= 3)
                    series_view(base, args[2]);
                else
                    cout << "Usage: series view \"name\" \n";
                return;
            }
            cout << "series commands: add/list/view\n";
            return;
        }
        if (cmd == "book")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                {
                    book_add(base, args[2], stoi(args[3]), args[4]);
                }
                else
                    cout << "Usage: book add \"name\" rating \"review\" \n";
                return;
            }
            if (args.size() >= 2 && args[1] == "view")
            {
                if (args.size() >= 3)
                {
                    book_view(base, args[2]);
                }
                else
                    cout << "Usage: book view \"name\"\n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                book_list(base);
                return;
            }
            cout << "book commands: add/list/view\n";
        }
        if (cmd == "project")
        {
            if (args.size() >= 2 && args[1] == "add")
            {
                if (args.size() >= 5)
                {
                    project_add(base, args[2], args[3]);
                }
                else
                    cout << "Usage: project add \"name\" \"description\" \n";
                return;
            }
            if (args.size() >= 2 && args[1] == "list")
            {
                project_list(base);
                return;
            }
            if (args.size() >= 2 && args[1] == "view")
            {
                if (args.size() >= 3)
                {
                    project_view(base, args[2]);
                }
                else
                    cout << "Usage: project view \"name\" \n";
            }
        }
        string attempt = join_from(args, 0);
        int rc = system(attempt.c_str());
        if (rc == -1)
            cerr << "Failed to execute.\n";
    }
}