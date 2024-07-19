#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int> &v) {
    std::vector<int> v_ans(v.size());
    priority_queue<int> pr_Q;
    for (size_t i = 0; i < v.size(); ++i) {
        pr_Q.push(v[i]);
    }

    size_t pos = 1;
    while (!pr_Q.empty()) {
        v_ans[v.size() - pos ] = pr_Q.top();
        pr_Q.pop();
        ++pos;
    }
    return v_ans;
}
