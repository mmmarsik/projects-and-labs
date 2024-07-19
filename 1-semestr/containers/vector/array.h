#include <bits/stdc++.h>


class Array {
public:
    Array(std::ostream &ostream)
            : Ostream_(ostream), size_(0), capacity_(2), data_(new int[capacity_]) {
        Ostream_ << "Constructed. " << *this << std::endl;
    }

    Array(const Array &array)
            : Ostream_(array.Ostream_), size_(array.size_), capacity_(array.capacity_), data_(new int[capacity_]) {
        CopyData(array.data_, data_);
        Ostream_ << "Constructed from another Array. " << *this << std::endl;
    }

    Array(size_t size, std::ostream &ostream = std::cout, int defaultValue = 0)
            : Ostream_(ostream), size_(size), capacity_(size * 2), data_(new int[capacity_]) {
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
            int *const newData = new int[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
    }

    void Resize(size_t newSize) {

        if (capacity_ < newSize) {
            capacity_ = newSize;
            int *const newData = new int[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
        size_ = newSize;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
            int *const newData = new int[capacity_];
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

    const int &operator[](const size_t i) const {
        return const_cast<Array *>(this)->operator[](i);
    }

    int &operator[](const size_t i) {
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

Array &operator<<(const int value) {
    PushBack(value);
    return *this;
}

Array &operator<<(const Array &it) {
    for (size_t i = 0; i < it.size_ ; ++i) {
        PushBack(it.data_[i]);
    }
    return *this;
}

friend std::ostream &operator<<(std::ostream &ostream, const Array &array);


void CopyData(int *source, int *destination) {
    for (size_t i = 0; i < size_; ++i) {
        destination[i] = source[i];
    }
}


private:
std::ostream &Ostream_;
size_t size_, capacity_;
int *data_;
// ...
};

std::ostream &operator<<(std::ostream &ostream, const Array &array) {
    if (array.size_ > 0) {
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.size_
                << ", elements are: ";
        for (size_t i = 0; i < array.Size() - (size_t) (1); ++i) {
            ostream << array[i] << ", ";
        }
        ostream << array[array.Size() - (size_t) (1)];
    } else {
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is 0";
    }
    return ostream;

}

