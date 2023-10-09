#pragma once
#ifndef TES_UTIL_OPTIONAL_MESSAGE_HPP_
#define TES_UTIL_OPTIONAL_MESSAGE_HPP_
#include <string>
#include <stdexcept>
#include <utility>
namespace tes::util {
template<class T, class U> class OptionalMessage {
public:
    explicit OptionalMessage(T value_) : succeed_value(value_), flag(true) {};
    explicit OptionalMessage(U message_): fail_value(std::move(message_)), flag(false){}
    explicit operator bool() const noexcept {
        return flag;
    }
    [[nodiscard]]
    T get_succeed() const {
        if (!flag) {
            throw std::runtime_error("");
        }
        return succeed_value;
    }
    [[nodiscard]] U get_fail() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return fail_value;
    }
private:
    bool flag;
    T succeed_value;
    U fail_value;
};
template<class T> class OptionalMessage<T,T> {
public:
    explicit OptionalMessage(T value_, bool flag_) : flag(flag_) {
        if (flag_) {
            succeed_value = value_;
        } else {
            fail_value = value_;
        }
    };

    explicit operator bool() const noexcept {
        return flag;
    }
    [[nodiscard]]
    T get_succeed() const {
        if (!flag) {
            throw std::runtime_error("");
        }
        return succeed_value;
    }
    [[nodiscard]] T get_fail() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return fail_value;
    }
private:
    bool flag;
    T succeed_value;
    T fail_value;
};



}
#endif