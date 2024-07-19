#pragma once
#include <cmath>
#include <iostream>


class Range {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = int64_t;
    using reference         = int64_t&;

    Range(value_type n)
            : start_(0)
            , end_(n)
            , step_(1) {}

    Range(value_type start, value_type end)
            : start_(start)
            , end_(end)
            , step_(1) {}

    Range(value_type start, value_type end, value_type step)
            : start_(start)
            , end_(end)
            , step_(step) {}

    class iterator {
    public:

        iterator(value_type end, value_type step ,value_type cur)
                : end_(end)
                , step_(step)
                , cur_(cur) {}

        value_type operator->(){
            return cur_;
        }

        value_type operator*(){
            return cur_;
        }

        iterator operator++(){
            cur_ += step_;
            if (step_ < 0) {
                if (cur_ < end_) {
                    cur_ = end_;
                }
            } else {
                if (cur_ > end_) {
                    cur_ = end_;
                }
            }
            return *this;
        }

        iterator operator--(){
            cur_ -= step_;
            return *this;
        }

        iterator operator++(int){
            value_type old_cur_ = cur_;
            cur_ += step_;
            if (step_ < 0) {
                if (cur_ < end_) {
                    cur_ = end_;
                }
            } else {
                if (cur_ > end_) {
                    cur_ = end_;
                }
            }
            return iterator(end_, step_, old_cur_);
        }

        bool operator==(const iterator& other){
            return cur_ == other.cur_;
        }

        bool operator!=(const iterator& other){
            return cur_ != other.cur_;
        }

    private:
        value_type end_;
        value_type step_;
        value_type cur_;
    };

public:

    value_type Size() const {
        return (std::abs(end_ - start_) + std::abs(step_) - 1) / std::abs(step_);
    }

    iterator begin() const{
        return iterator(end_,step_,start_);
    }

    iterator end() const{
        return iterator(end_,step_,end_);
    }
private:
    value_type start_;
    value_type end_;
    value_type step_;
};