class EnhancedList(list):
    """
    Улучшенный list.
    Данный класс является наследником класса list и добавляет к нему несколько новых атрибутов.

    - first -- позволяет получать и задавать значение первого элемента списка.
    - last -- позволяет получать и задавать значение последнего элемента списка.
    - size -- позволяет получать и задавать длину списка:
        - если новая длина больше старой, то дополнить список значениями None;
        - если новая длина меньше старой, то удалять значения из конца списка.
    """

    @property
    def first(self):
        return self[0]

    @first.setter
    def first(self, val):
        self[0] = val

    @property
    def last(self):
        return self[-1]

    @last.setter
    def last(self, val):
        self[-1] = val

    @property
    def size(self):
        return len(self)

    @size.setter
    def size(self, Size):
        while Size > len(self):
            self.append(None)
        while Size < len(self):
            while len(self) > Size:
                self.pop(-1)
