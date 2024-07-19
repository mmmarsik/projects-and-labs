from collections.abc import Callable, Hashable, Iterable
from collections import OrderedDict
from functools import wraps
from dataclasses import dataclass

"""
       Функция создает декоратор, позволяющий кэшировать результаты выполнения обернутой функции по принципу LRU-кэша.
       Размер LRU кэша ограничен количеством max_items. При попытке сохранить новый результат в кэш, в том случае, когда
       размер кэша уже равен max_size, происходит удаление одного из старых элементов, сохраненных в кэше.
       Удаляется тот элемент, к которому обращались давнее всего.
       Также у обернутой функции должен появиться атрибут stats, в котором лежит объект с атрибутами cache_hits и
       cache_misses, подсчитывающие количество успешных и неуспешных использований кэша.
       :param max_items: максимальный размер кэша.
       :return: декоратор, добавляющий LRU-кэширование для обернутой функции.
       """


@dataclass
class Stats:
    cache_hits: int = 0
    cache_misses: int = 0


def lru_cache(max_items: int) -> Callable:
    def decorator(f):
        cache = OrderedDict()
        f.stats = Stats()

        @wraps(f)
        def inner(*args, **kwargs):
            key = str(args) + str(kwargs.items())
            if key in cache:
                cache.move_to_end(key)
                f.stats.cache_hits += 1
            else:
                if len(cache) >= max_items:
                    cache.popitem(last=False)

                f.stats.cache_misses += 1
                cache[key] = f(*args, **kwargs)

            return cache[key]
        return inner
    return decorator
