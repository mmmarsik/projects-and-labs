#include <cstddef>
#include <algorithm>


struct State {
    int ref_count;
    std::size_t size, capacity;
    char *str;
};

class CowString {
public:

    CowString()
            : str_state(new State{.ref_count = 1, .size = 0, .capacity = 2, .str = new char[2]}) {}

    CowString(const CowString &cs)
            : str_state(cs.str_state) {
        ++str_state->ref_count;
    }

    CowString(CowString &&cs)
            : str_state(cs.str_state) {
        cs.str_state->size = 0;
        cs.str_state->capacity = 0;
        cs.str_state->ref_count = 1;
        cs.str_state->str = nullptr;
    }


    ~CowString() {
        --str_state->ref_count;
        if (str_state->str != nullptr && str_state->ref_count <= 0) {
            delete[] str_state->str;
            delete str_state;
        }
    }

    CowString &operator=(const CowString &cs) {
        if (this != &cs) {
            --str_state->ref_count;
            if (str_state->ref_count <= 0) {
                delete[] str_state->str;
                delete str_state;
            }
            str_state = cs.str_state;
            ++str_state->ref_count;
        }
        return *this;
    }

    CowString &operator=(CowString &&cs) {
        std::swap(str_state, cs.str_state);
        cs.str_state = nullptr;
        return *this;
    }

    const char &At(std::size_t index) const {
        return str_state->str[index];
    }

    char &operator[](std::size_t index) {

        if (str_state->str != nullptr && index < str_state->size && str_state->ref_count > 1) {
            State *newState = new State;
            newState->capacity = str_state->capacity;
            newState->size = str_state->size;
            newState->ref_count = 1;
            char *const newStr = new char[newState->capacity];
            std::copy(str_state->str, str_state->str + newState->size, newStr);
            newState->str = newStr;
            --str_state->ref_count;
            str_state = newState;
        }
        return str_state->str[index];
    }

    const char &Back() const {
        return str_state->str[str_state->size - 1];
    }

    void PushBack(char c) {
        if (str_state->ref_count == 1 && str_state->capacity > str_state->size) {
            str_state->str[str_state->size] = c;
            ++str_state->size;
        } else {
            State *newState = new State;
            newState->capacity = str_state->capacity > 0 ? str_state->capacity * 2 : 1;
            newState->size = str_state->size + 1;
            newState->ref_count = 1;
            char *const newStr = new char[newState->capacity];
            std::copy(str_state->str, str_state->str + newState->size - 1, newStr);
            newStr[newState->size - 1] = c;
            newState->str = newStr;
            --str_state->ref_count;
            if (str_state->ref_count == 0) {
                delete[] str_state->str;
                delete str_state;
            }
            str_state = newState;
        }
    }

    std::size_t Size() const {
        return str_state->size;
    }

    std::size_t Capacity() const {
        return str_state->capacity;
    }

    void Reserve(std::size_t capacity_) {
        State *new_str_state = new State;
        new_str_state->capacity = capacity_;
        new_str_state->size = str_state->size;
        new_str_state->ref_count = 1;
        char *const newStr = new char[new_str_state->capacity];
        std::copy(str_state->str, str_state->str + new_str_state->size, newStr);
        new_str_state->str = newStr;
        --str_state->ref_count;
        if (str_state->ref_count == 0) {
            delete[] str_state->str;
            delete str_state;
        }
        str_state = new_str_state;
    }

    void Resize(std::size_t newSize) {
        State *new_str_state = new State;
        new_str_state->size = newSize;
        if (str_state->capacity < newSize) {
            new_str_state->capacity = newSize;
        }
        char *const newStr = new char[new_str_state->capacity];
        new_str_state->ref_count = 1;
        std::copy(str_state->str, str_state->str + str_state->size, newStr);
        new_str_state->str = newStr;
        --str_state->ref_count;
        if (str_state->ref_count == 0) {
            delete[] str_state->str;
            delete str_state;
        }
        str_state = new_str_state;
    }

private:
    State *str_state;
};
