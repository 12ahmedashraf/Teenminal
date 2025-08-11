#include "snake.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>

static struct termios orig_term;

void reset_term()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}

void set_conio_terminal_mode()
{
    struct termios new_term;
    tcgetattr(STDIN_FILENO, &orig_term);
    memcpy(&new_term, &orig_term, sizeof(new_term));
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    atexit(reset_term);
}

int kbhit()
{
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

int getch() { return getchar(); }
#endif

namespace teen
{
    using namespace std;
    void draw(const vector<string> &screen)
    {
        for (auto &r : screen)
            cout << r << "\n";
    }

    void play_snake()
    {
        srand((unsigned)time(nullptr));

        int w = 30, h = 12;
        deque<pair<int, int>> snake;
        snake.push_back({w / 2, h / 2});
        pair<int, int> food = {5, 5};
        int dir = 0;

#ifndef _WIN32
        set_conio_terminal_mode();
#endif

        bool alive = true;
        while (alive)
        {
            // Draw screen
            vector<string> scr(h, string(w, ' '));
            for (int x = 0; x < w; ++x)
            {
                scr[0][x] = '-';
                scr[h - 1][x] = '-';
            }
            for (int y = 0; y < h; ++y)
            {
                scr[y][0] = '|';
                scr[y][w - 1] = '|';
            }

            scr[food.second][food.first] = 'O';
            for (size_t i = 0; i < snake.size(); ++i)
            {
                auto p = snake[i];
                scr[p.second][p.first] = (i == 0 ? '@' : '#');
            }
            cout << "\033[2J\033[H";
            cout << cyan << "=== SNAKE GAME ===" << reset << "\n";
            draw(scr);
            this_thread::sleep_for(chrono::milliseconds(150));

            int ch = -1;
#ifdef _WIN32
            if (_kbhit())
                ch = _getch();
#else
            if (kbhit())
                ch = getch();
#endif

            if (ch != -1)
            {
                if (ch == 27)
                {
#ifndef _WIN32
                    if (kbhit())
                        getch();
                    if (kbhit())
                    {
                        int c2 = getch();
                        if (c2 == 'A')
                            dir = 3;
                        else if (c2 == 'B')
                            dir = 1;
                        else if (c2 == 'C')
                            dir = 0;
                        else if (c2 == 'D')
                            dir = 2;
                    }
#else
                    if (_kbhit())
                    {
                        int c2 = _getch();
                        if (c2 == 72)
                            dir = 3;
                        else if (c2 == 80)
                            dir = 1;
                        else if (c2 == 77)
                            dir = 0;
                        else if (c2 == 75)
                            dir = 2;
                    }
#endif
                }
                else if (ch == 'q' || ch == 'Q')
                {
                    alive = false;
                    break;
                }
            }

            auto head = snake.front();
            pair<int, int> nh = head;
            if (dir == 0)
                nh.first++;
            else if (dir == 1)
                nh.second++;
            else if (dir == 2)
                nh.first--;
            else if (dir == 3)
                nh.second--;
            if (nh.first <= 0 || nh.first >= w - 1 || nh.second <= 0 || nh.second >= h - 1)
            {
                alive = false;
                break;
            }
            for (auto &s : snake)
                if (s == nh)
                {
                    alive = false;
                    break;
                }
            if (!alive)
                break;
            snake.push_front(nh);
            if (nh == food)
            {
                food.first = rand() % (w - 2) + 1;
                food.second = rand() % (h - 2) + 1;
            }
            else
            {
                snake.pop_back();
            }
        }

        cout << red << "Game over! Press Enter to return..." << reset << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

