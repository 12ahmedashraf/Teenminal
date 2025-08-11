#ifndef journal_h
#define journal_h

#include "teenminal.h"

namespace teen
{
    void journal_add(const fs::path &base, const string &text, const string &date = "");
    void journal_read(const fs::path &base, const string &date);
}
#endif
