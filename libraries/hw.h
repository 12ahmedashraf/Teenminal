#ifndef hw_h
#define hw_h

#include "teenminal.h"

namespace teen
{
    void hw_add(const fs::path &base, const string &description, const string &deadline);
    void hw_list(const fs::path &base);
    void nearest_hw(const fs::path &base);
}
#endif