#include <type_traits>
#include <typeinfo>
#include <stdexcept>
#include <utility>

class Any
{
public:
    Any() : storage_(nullptr) {}

    Any(const Any &other)
        : storage_(other.storage_ ? other.storage_->get_copy() : nullptr) {}

    Any(Any &&other)
        : storage_(other.storage_)
    {
        other.storage_ = nullptr;
    }

    Any &operator=(const Any &other)
    {
        if (this == &other)
            return *this;
        delete storage_;
        storage_ = other.storage_ ? other.storage_->get_copy() : nullptr;
        return *this;
    }

    Any &operator=(Any &&other)
    {
        if (this == &other)
            return *this;
        delete storage_;
        storage_ = other.storage_;
        other.storage_ = nullptr;
        return *this;
    }

    template <typename U,
              typename D = std::decay_t<U>,
              std::enable_if_t<!std::is_same_v<D, Any>, int> = 0>
    Any(U &&value) : storage_(new Derived<D>(std::forward<U>(value))) {}

    template <typename U,
              typename D = std::decay_t<U>,
              std::enable_if_t<!std::is_same_v<D, Any>, int> = 0>
    Any &operator=(U &&value)
    {
        delete storage_;
        storage_ = new Derived<D>(std::forward<U>(value));
        return *this;
    }

    bool Empty() const
    {
        return storage_ == nullptr;
    }

    template <typename T>
    T Value() const
    {
        if (Empty())
            throw std::runtime_error("Any is empty");

        using D = std::decay_t<T>;
        if (typeid(D) != storage_->get_type())
        {
            throw std::bad_cast();
        }

        return static_cast<Derived<D> *>(storage_)->value_;
    }

    void Reset()
    {
        delete storage_;
        storage_ = nullptr;
    }

    void Swap(Any &other)
    {
        std::swap(storage_, other.storage_);
    }

    ~Any()
    {
        delete storage_;
        storage_ = nullptr;
    }

private:
    struct Base
    {
        virtual ~Base() = default;
        virtual Base *get_copy() const = 0;
        virtual const std::type_info &get_type() const = 0;
    };

    template <typename T>
    struct Derived : Base
    {
        template <class V>
        Derived(V &&value) : value_(std::forward<V>(value)) {}

        Base *get_copy() const override { return new Derived<T>(value_); }
        const std::type_info &get_type() const override { return typeid(T); }

        T value_;
    };

    Base *storage_;
};
