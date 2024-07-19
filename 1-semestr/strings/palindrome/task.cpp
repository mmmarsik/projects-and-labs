#include "task.h"

bool isalpha( char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
        return true;
    }
    return false;
}

bool is_palindrome(const std::string &s) {
    long long cnt = 0;
    if (s.size() <= 1) {
        return true;
    }
    size_t l = 0, r = s.size() - 1;
    bool flag = true;
    if (isalpha(s[l]) == true || isalpha(s[r]) == true) {
        ++cnt;
    }
    while (r > l && flag == true) {
        while (isalpha(s[l]) == false) {
            if (r < l) {
                break;
            }
            ++l;
        }
        while (isalpha(s[r]) == false) {

            if (r < l) {
                break;
            }
            --r;
        }

        if (isalpha(s[l]) == true || isalpha(s[r]) == true) {
            ++cnt;
        }

        if (s[l] == s[r] || s[l] + 32 == s[r] || s[l] == s[r] + 32) {
            ++l;
            --r;
            ++cnt;
        } else {
            flag = false;
        }
    }

    if (flag == true && cnt > 0) {
        return true;
    }
    else if (cnt > 0 && flag == false){
        return false;
    } else if (cnt == 0 && flag == false){
        return true;
    }
    return false;
}
