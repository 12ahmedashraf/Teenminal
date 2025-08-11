#ifndef exam_h
#define exam_h

#include "teenminal.h"

namespace teen
{
    void exam_add(const fs::path &base, const string &name, const string &date);
    void exam_list(const fs::path &base);
    void nearest_exam(const fs::path &base);
}
#endif