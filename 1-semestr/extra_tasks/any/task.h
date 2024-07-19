#include <memory>
#include <typeinfo>
#include <stdexcept>

class Any {
private:
    struct Base {
        virtual ~Base() = default;
        virtual std::unique_ptr<Base> Copy() const = 0;
        virtual const std::type_info& GetType() const = 0;
    };

    template <typename T>
    struct Derived : public Base {
        T value;

        Derived(const T& val) : value(val) {}

        std::unique_ptr<Base> Copy() const override {
            return std::make_unique<Derived<T>>(value);
        }

        const std::type_info& GetType() const override {
            return typeid(T);
        }
    };

    std::unique_ptr<Base> owner;

public:
    template <typename T>
    Any(const T& val) : owner(std::make_unique<Derived<T>>(val)) {}

    Any() = default;

    Any(const Any& other) {
        if (other.owner) {
            owner = other.owner->Copy();
        }
    }

    Any(Any&& other)  {
        owner = std::move(other.owner);
    }

    Any& operator=(const Any& other) {
        if (this != &other) {
            owner = nullptr;
            if (other.owner) {
                owner = other.owner->Copy();
            }
        }
        return *this;
    }

    Any& operator=(Any&& other) {
        if (this != &other) {
            owner = std::move(other.owner);
        }
        return *this;
    }

    template <typename T>
    T& Value() {
        if (!owner || owner->GetType() != typeid(T)) {
            throw std::bad_cast();
        }
        return dynamic_cast<Derived<T>*>(owner.get())->value;
    }

    bool Empty() const {
        return !owner;
    }

    void Reset() {
        owner.reset();
    }

    void Swap(Any& other) {
        owner.swap(other.owner);
    }

};
