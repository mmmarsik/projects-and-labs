#include "task.h"

void ReverseList(std::list<int> &l) {
    std::list<int>::iterator beg_it = l.begin();
    std::list<int>::iterator back_it = l.end();
    --back_it;
    while (beg_it != back_it) {
        std::swap(*beg_it, *back_it);
        ++beg_it; --back_it;
    }
}
