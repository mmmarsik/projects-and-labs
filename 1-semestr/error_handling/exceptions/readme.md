# Программируемый калькулятор

В данной задаче требуется реализовать калькулятор, который умеет выполнять инструкции (statements) двух видов:
- Вычисление введенного выражения (expression)
- Присваивание значения введенного выражения какому-то имени

### Принцип работы калькулятора
Инструкция подается на вход либо в виде строки либо в виде специальной структуры.
Калькулятор исполняет одну инструкцию за раз.

Как выглядят инструкции (очень условная вольная нотация, не отражающая приоритет операций):
```
<statement> := <expression> | <assignment>
<assignment> := <name> = <expression>
<expression> := <atomic expression> | <function application> | <expression> <binary operation> <expression>
<function application> := <expression> <atomic expression>
<atomic expression> := <literal> | <name> | <lambda> | ( <expression> )
<literal> := десятичное число с опициональной дробной частью
<name> := строка из латинских букв и цифр, начинается с буквы
<lambda> := \ <argument list> -> <expression>
<argument list> := <name> <optional argument list>
<optional argument list> := <name> <optional argument list> | пустая строка
<binary operation> := + | - | * | /
```

Приоритет операций:
- Скобки
- Лямбда
- *, /
- +, -
- Применение функции к аргументу

Как можно заметить, операция применения функции к аргументу в рассматриваемом калькуляторе записывается без скобок, например
```
> f = \ x y -> x + y
> f 5 6
< 11
```

Подразумевается, что функции в данной задаче каррированные, т.е. могут быть применены только к одному аргументу
за один раз. В таком случае функция с несколькими аргументами превращается в функцию от одного аргумента, которая возвращает
другую функцию, имеющую на один аргумент меньше. См. https://ru.wikipedia.org/wiki/Каррирование.

При выполнении инструкций в калькуляторе кроме входящей строки также используется контекст, сохраняющийся по мере
выполнения инструкций. Контекст представляет собой словарь, в котором различным именам ставится в соответствие какой-то
объект (функция, константа). Когда калькулятор начинает свою работу, в его контексте присутствуют функции
`+`, `-`, `*`, `/`, `sin`, `cos`. При этом функции `+`, `-`, `*`, `/` должны использовать как бинарные операторы
в инфиксной форме (т.е. такая запись `a + b`, а не `+ a b`). По мере выполнения инструкций присваивания в контексте будут появляться новые значения,
либо будут изменяться старые.

В рассматриваемом калькуляторе функции являются объектами первого порядка, что означает, что их можно присваивать, передавать в качестве аргументов
и использовать в качестве возвращаемого значения в других функциях и выражениях. См. https://ru.wikipedia.org/wiki/Функции_первого_класса

Примеры инструкций и ожидаемые результаты их выполнения можно посмотреть в проверяющем коде в файле `main.cpp`.

### Обработка ошибок
В процессе обработки входных данных или вычисления значений выражений могут возникать различные ошибки, связанные, как
правило, с некорректным вводом данных на вход калькулятора. В данном задании нужно уметь обрабатывать ошибки следующих типов:
- Ошибки разбора данных (парсинга)
  - Ошибка токенизации. Не получилось выделить токены из исходной строки. Про токены см. `task.h`
  - Несоответствие открывающих и закрывающих скобок
  - Пустой результат парсинга. Отсутствует выражения, которое можно вычислить. Скорее всего на вход была подана пустая строки или пустые скобки
  - Попытка задать лямбду без аргументов
  - Попытка указать в качестве имени аргумента строку, которая не может быть именем
- Ссылка на имя, которое не определено (отсутствует в контексте калькулятора)
- Неправильное применение функции к аргументу. Возможно, что объект, который пытаются использовать как функцию, таковой не является.
Либо функция ожидает в качестве аргумента число, а получает другую функцию.

Все ошибки должны приводить к выбрасыванию исключений, при этом под каждый из перечисленных выше видов ошибок должен быть 
заведен отдельный тип исключения. Типы исключений должны соединяться в иерархию с помощью наследования так, как показано
в списке выше. Также нужно ввести единый базовый класс для исключений, с помощью которого можно будет отлавливать все 
исключения калькулятора. И еще исключения калькулятора должны быть унаследованы от класса `std::exception` и отдавать
текстовое описание ошибки с помощью функции `what()`.