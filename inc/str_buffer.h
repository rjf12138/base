#ifndef __STR_UTIL_H__
#define __STR_UTIL_H__

#include "basic_head.h"

namespace my_util {

class StrBuffer {
public:
    StrBuffer(const string str);
    ~StrBuffer(void);

    vector<string> split_str(const string& p_separator);
    string remove_str_from_buffer(const string& p_str2);
private:
    string str_buffer_;
};

}

#endif