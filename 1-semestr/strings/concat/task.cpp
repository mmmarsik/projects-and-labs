#include "task.h"
#include <stdio.h>

using namespace std;

char *concat(const char *lhs, const char *rhs) {

    size_t s1 = 0, s2 = 0;
    while ((lhs[s1])) {
        ++s1;
    }
    while ((rhs[s2])) {
        ++s2;
    }
    char *c_ans = new char[s1 + s2 + 1];
    for (size_t i = 0; i < s1; ++i) {
        c_ans[i] = lhs[i];
    }
    for (size_t i = s1; i < s1 + s2; ++i) {
        c_ans[i] = rhs[i - s1];
    }
    c_ans[s1+s2] = '\0';
    return c_ans;
}