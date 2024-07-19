#include <string>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

vector<string> split(string s, char delimiter) {
    size_t len = 1;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == delimiter) {
            ++len;
        }
    }
    vector<string> str_arr(len);
    string elem = "";
    size_t index = 0;
    for (size_t i = 0; i < s.size(); ++i) {

        if (s[i] != delimiter) {
            elem.push_back(s[i]);
            if (len - index == 1 && i == s.size() - 1) {
                str_arr[index] = elem;
                elem = "";
            }
        } else {
            str_arr[index] = elem;
            elem = "";
            ++index;
        }
    }

    return str_arr;

}

string join(const vector<string> &str_arr_, char delimiter) {
    string j_str = "";
    for (size_t i = 0; i < str_arr_.size(); ++i) {
        if (i != str_arr_.size() - 1) {
            j_str += str_arr_[i];
            j_str += string(1, delimiter);
        } else {
            j_str += str_arr_[i];
        }
    }
    return j_str;
}


string normalize(string_view path) {

    string a = "";
    a += path;
    vector<string> path_v = split(a, '/');
    for (size_t i = 0; i < path_v.size(); ++i) {


        if (isalpha(path_v[i][0]) && i + 1 < path_v.size() && path_v[i + 1].size() >= 2 && (path_v[i + 1] == "..")) {
            path_v.erase(path_v.begin() + i, path_v.begin() + i + 2);
            --i;
        }

        if ( i + 1 < path_v.size() && !path_v[i + 1].empty() && isalpha(path_v[i][0]) && path_v[i + 1][0] == '.') {
            path_v.erase(path_v.begin() + i + 1);
            --i;
        }

        if (path_v[0] == "" && path_v[i] == "..") {
            path_v.erase(path_v.begin() + i);
            --i;
        }

        if (i != 0 && path_v[i] == "" ) {
            path_v.erase(path_v.begin() + i);
            --i;
        }

        if ( path_v.size() > 1 && path_v[i] == ".") {
            path_v.erase(path_v.begin() + i);
        }

    }
    if (path_v.size() == 1 && path_v[0] == "") {
        return "/";
    } else return join(path_v, '/');
}