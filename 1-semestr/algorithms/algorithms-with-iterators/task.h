#include <cstdlib>
#include <iterator>
#include <iostream>
#include <stdio.h>
#include <cstdint>

/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    while (firstIn != lastIn) {
        *firstOut = op(*firstIn);
        ++firstOut;
        ++firstIn;
    }
}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {

    auto it_c = first;
    while (first != last){
        if (p(*first)){
            std::swap(*first, *it_c);
            ++it_c;
        }
        ++first;
    }
}

/*
* Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
*/
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    while (first1 < last1 && first2 < last2) {
        if (*first1 < *first2) {
            *firstOut = *first1;
            ++firstOut;
            ++first1;
        } else {
            *firstOut = *first2;
            ++firstOut;
            ++first2;
        }
    }
    if (first1 < last1) {
        while (first1 < last1) {
            *firstOut = *first1;
            ++firstOut;
            ++first1;
        }
    }
    if (first2 < last2) {
        while (first2 < last2) {
            *firstOut = *first2;
            ++firstOut;
            ++first2;
        }
    }
}


/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */

class FibonacciRange {
public:

    class Iterator {
        friend class FibonacciRange;

    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        Iterator(uint64_t _prev_1, uint64_t _prev_2)
        : prev_1(_prev_1)
        , prev_2(_prev_2) {}

        value_type operator*() const {
            // разыменование итератора -- доступ к значению
            return prev_1 + prev_2;
        }

        Iterator &operator++() {
            // prefix increment
            value_type v_copy = prev_1;
            prev_1 = prev_2;
            prev_2 = prev_2 + v_copy;
            return *this;
        }

        Iterator operator++(int) {
            // postfix increment
            value_type v_copy = prev_1;
            prev_1 = prev_2;
            prev_2 = prev_2 + v_copy;
            return Iterator(v_copy, prev_2 - v_copy);
        }

        bool operator==(const Iterator &rhs) const {
            return prev_1 + prev_2 == rhs.prev_1 + rhs.prev_2;
        }
        bool operator!=(const Iterator &rhs) const {
            return prev_1 + prev_2 != rhs.prev_1 + rhs.prev_2;
        }

        bool operator<(const Iterator &rhs) const {
            return prev_1 + prev_2 < rhs.prev_1 + rhs.prev_2;
        }
    private:
        uint64_t prev_1;
        uint64_t prev_2;
    };

    FibonacciRange(size_t amount)
    : amount_(amount) {
    }

    Iterator begin() const {
        return Iterator(0,1);
    }

    Iterator end() const {
        Iterator b_it = Iterator(0,1);
        for (size_t i = 0; i < amount_; ++i) {
            ++b_it;
        }
        return b_it;
    }

    size_t size() const {
        return amount_;
    }
private:
    size_t amount_;
};
