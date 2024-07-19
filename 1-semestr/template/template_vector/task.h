#include <iostream>
template<typename T>
class Array {
public:
    Array(std::ostream &ostream)
            : Ostream_(ostream), size_(0), capacity_(2), data_(new T[capacity_]) {
        Ostream_ << "Constructed. " << *this << std::endl;
    }


    Array(const Array &array)
            : Ostream_(array.Ostream_), size_(array.size_), capacity_(array.capacity_), data_(new T[capacity_]) {
        CopyData(array.data_, data_);
        Ostream_ << "Constructed from another Array. " << *this << std::endl;
    }


    Array(size_t size, std::ostream &ostream = std::cout, T defaultValue = 0)
            : Ostream_(ostream), size_(size), capacity_(size * 2), data_(new T[capacity_]) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = defaultValue;
        }

        Ostream_ << "Constructed with default. " << *this << std::endl;
    }

    ~Array() {
        Ostream_ << "Destructed " << size_ << std::endl;
        delete[] data_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            capacity_ = newCapacity;
            T *const newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
    }

    void Resize(size_t newSize) {

        if (capacity_ < newSize) {
            capacity_ = newSize;
            T *const newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
        size_ = newSize;
    }

    void PushBack(T value) {
        if (size_ == capacity_) {
            capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
            T *const newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }

        data_[size_] = value;
        ++size_;
    }

    void PopBack() {
        --size_;
    }

    const T &operator[](const size_t i) const {
        return const_cast<Array *>(this)->operator[](i);
    }

    T &operator[](const size_t i) {
        return data_[i];
    }

    explicit operator bool() const {
        if (this->size_ > 0) {
            return true;
        }
        return false;
    }

    bool operator<(const Array &it) const {
        if (size_ < it.size_) {
            for (size_t i = 0; i < size_; ++i) {
                if (data_[i] < it.data_[i]) return true;
                else if (data_[i] > it.data_[i]) return false;
            }
            return true;
        } else {
            for (size_t i = 0; i < it.size_; ++i) {
                if (data_[i] < it.data_[i]) return true;
                else if (data_[i] > it.data_[i]) return false;
            }
            return false;
        }
    }


    bool operator>(const Array &it) const {
        return it < *this;
    }

    bool operator!=(const Array &it) const {
        return !(*this == it);
    }

    bool operator==(const Array &it) const {
        return !(it < *this || *this < it);
    }

    bool operator<=(const Array &it) const {
        return (*this < it || *this == it);
    }

    bool operator>=(const Array &it) const {
        return (it < *this || *this == it);
    }
    template<typename T1>
    friend std::ostream& operator<< (std::ostream &ostream, const Array<T1>&);
    Array<T> &operator<<(const T &value) {
        PushBack(value);
        return *this;
    }

    Array<T> &operator<<(const Array<T> &it) {
        for (size_t i = 0; i < it.size_; ++i) {
            PushBack(it.data_[i]);
        }
        return *this;
    }


    void CopyData(T *source, T *destination) {
        for (size_t i = 0; i < size_; ++i) {
            destination[i] = source[i];
        }
    }

    void Clear(void){
        size_ = 0;
    }


    bool Insert(size_t pos, const T &value) {
        if (pos > size_){
            return false;
        }

        if (capacity_ == size_) {
            capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
            T *const newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
        for (size_t i = size_; i < pos ; --i) {
            data_[i] = data_[i - 1];
        }
        ++size_;
        data_[pos] = value;
        return true;
        }

    bool Erase(size_t pos) {
        if (size_ > 0 && pos < size_) {
            for (size_t i = pos; i < size_ - 1; ++i) {
                data_[i] = data_[i + 1];
            }
        --size_;
        return true;
        }
        else{
            return false;
        }
    }

private:
    std::ostream &Ostream_;
    size_t size_, capacity_;
    T *data_;

};

template<typename T1>
std::ostream &operator<< (std::ostream &ostream, const Array<T1> &array) {
    if (array.size_ > 0) {
        ostream << "Result Array's capacity is " << array.capacity_ << " and size is " << array.size_
                << ", elements are: ";
        for (size_t i = 0; i < array.size_ - (size_t) (1); ++i) {
            ostream << array[i] << ", ";
        }
        ostream << array[array.size_ - (size_t) (1)];
    } else {
        ostream << "Result Array's capacity is " << array.capacity_ << " and size is 0";
    }
    return ostream;

}
