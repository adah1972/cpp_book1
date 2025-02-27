#ifndef FINALLY_H
#define FINALLY_H

#include <exception>    // std::uncaught_exceptions
#include <type_traits>  // std::decay
#include <utility>      // std::exchange/forward/move

template <typename T>
class final_action {
public:
    explicit final_action(T action) : action_(std::move(action)) {}

    final_action(final_action&& other) noexcept
        : action_(std::move(other.action_)),
          is_active_(std::exchange(other.is_active_, false))
    {
    }

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;
    final_action& operator=(final_action&&) = delete;

    ~final_action()
    {
        if (is_active_) {
            action_();
        }
    }

    void dismiss() noexcept
    {
        is_active_ = false;
    }

private:
    T action_;
    bool is_active_{true};
};

template <typename T>
auto finally(T&& action)
{
    return final_action<std::decay_t<T>>(std::forward<T>(action));
}

#if __cpp_lib_uncaught_exceptions >= 201411L

// Similar to final_action but with the key difference that the
// contained action will not be invoked during exception propagation.
// Requires C++17 or later.
template <typename T>
class on_return {
public:
    explicit on_return(T action)
        : action_(std::move(action)),
          uncaught_exceptions_on_entry_(std::uncaught_exceptions())
    {
    }

    on_return(const on_return&) = delete;
    on_return(on_return&&) = delete;
    on_return& operator=(const on_return&) = delete;
    on_return& operator=(on_return&&) = delete;

    ~on_return()
    {
        if (std::uncaught_exceptions() == uncaught_exceptions_on_entry_) {
            action_();
        }
    }

private:
    T action_;
    int uncaught_exceptions_on_entry_;
};

#endif

#endif // FINALLY_H
