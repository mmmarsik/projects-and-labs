#pragma once

namespace ranges {

// Определяет тип данных, на которые ссылается итератор
template <typename Iterator>
using IteratorValueType = typename std::iterator_traits<Iterator>::value_type;

// Определяет тип возвращаемого функцией значения F(Args...) -> Result
template <typename F, typename... Args>
using FunctionResultType = std::invoke_result_t<F, Args...>;

// Your code here

}  // namespace ranges
