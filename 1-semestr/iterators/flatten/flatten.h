#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
template <typename T>
class FlattenedVector {
public:
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(size_t _n_pos, FlattenedVector<T>& _it)
                : n_pos(_n_pos)
                , it(_it) {}

        iterator& operator++() {
            ++n_pos;
            return *this;
        }

        iterator operator++(int) {
            iterator old(n_pos, it);
            ++n_pos;
            return old;
        }

        iterator operator--(int) {
            iterator old(n_pos, it);
            --n_pos;
            return old;
        }

        iterator& operator--() {
            --n_pos;
            return *this;
        }

        iterator operator+(const size_t n) const {
            return iterator(n_pos + n, it);
        }

        iterator& operator+=(const size_t n) {
            n_pos += n;
            return *this;
        }

        iterator operator-(const size_t n) const {
            return iterator(n_pos - n, it);
        }

        size_t operator-(const iterator& o_it) const {
            return n_pos - o_it.n_pos;
        }

        iterator& operator-=(const size_t n) {
            n_pos -= n;
            return *this;
        }

        friend iterator operator+(const size_t n, const iterator& o_it) {
            return iterator(o_it.n_pos + n, o_it.it);
        }

        size_t bin_search() const {
            ssize_t l = -1, r = it.pref_summs.size() - 1;
            while (r - l > 1) {
                size_t m = std::abs(r + l) / 2;
                if (it.pref_summs[m] > n_pos) {
                    r = m;
                } else {
                    l = m;
                }
            }
            return r;
        }

        reference operator*() const {
            size_t x = bin_search();
            if (x == 0){
                return it.vv[x][n_pos];
            }
            return it.vv[x][n_pos - it.pref_summs[x-1]];
        }

        reference operator[](const size_t n) const {
            return *(*this + n);
        }

        bool operator==(const iterator& o_it) const {
            return (n_pos == o_it.n_pos);
        }

        bool operator!=(const iterator& o_it) const {
            return (n_pos != o_it.n_pos);
        }

        bool operator<(const iterator& o_it) const {
            return (n_pos < o_it.n_pos);
        }

        bool operator>(const iterator& o_it) const {
            return (n_pos > o_it.n_pos);
        }

        bool operator<=(const iterator& o_it) const {
            return (n_pos <= o_it.n_pos);
        }

        bool operator>=(const iterator& o_it) const {
            return (n_pos >= o_it.n_pos);
        }

        void operator=(const iterator& o_it) {
            n_pos = o_it.n_pos;
            it = o_it.it;
        }

    private:
        size_t n_pos;
        FlattenedVector<T>& it;
    };

public:
    FlattenedVector(std::vector<std::vector<T>>& v)
            : vv(v)
    {
        if (!(vv.empty())){


            pref_summs.resize(vv.size());

            size_t sum = 0;
            for (size_t i = 0; i < vv.size(); ++i) {
                sum += vv[i].size();
                pref_summs[i] = sum;}
        }
    }




        std::vector<T> operator[](size_t n) const {
return vv[n];
}

iterator begin() {
    return iterator(0, (*this));
}

iterator end() {
    if (!(vv.empty())){
        return iterator(pref_summs.back(), (*this));}
    else {
        return iterator(0, *this);
    }
}

void operator=(const FlattenedVector<T>& o_fl) {
    vv = o_fl.vv;
    pref_summs = o_fl.pref_summs;
}

public:
std::vector<std::vector<T>>& vv;
std::vector<size_t> pref_summs;
};
