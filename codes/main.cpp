#include "teenminal.h"
#include "shell.h"
#include <iostream>
using namespace std;

int main()
{
    teen::enable_ansi();
    auto base = teen::data_base();
    teen::print_lg();
    cout << teen::yellow << teen::bold << "Welcome to Teenminal!\n\n"
         << teen::reset;
    teen::print_help();
    string line;
    while (true)
    {
        cout << teen::green << teen::bold << "teenminal> " << teen::reset;
        cout.flush();
        if (!getline(cin, line))
            break;

        if (line.empty())
            continue;
        teen::save_history(base, line);

        auto args = teen::tokenize(line);
        if (args.empty())
            continue;
        if (args[0] == "exit")
            break;

        teen::dispatch(args, base);
    }
    cout << "Bye!\n";
    return EXIT_SUCCESS;
}
