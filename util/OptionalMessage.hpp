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
template<class U> class OptionalMessage<void,U> {
public:
    OptionalMessage() : flag(true) {};
    explicit OptionalMessage(U value) : fail_value(std::move(value)), flag(false) {}

    explicit operator bool() const noexcept {
        return flag;
    }
    [[nodiscard]]
    U get_fail() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return fail_value;
    }
private:
    bool flag;
    U fail_value;
};
}
#endif