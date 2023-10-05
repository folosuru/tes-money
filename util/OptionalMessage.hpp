#include <string>
#include <stdexcept>
template<typename T> class OptionalMessage {
public:
    OptionalMessage(T value_) : value(value_), flag(true) {};
    OptionalMessage(std::string message_): message(message_), flag(false){}
    explicit operator bool() const noexcept {
        return flag;
    }
    T getValue() const {
        if (!flag) {
            throw std::runtime_error("");
        }
        return value;
    }
    std::string getMessage() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return message;
    }
private:
    bool flag;
    T value;
    std::string message;
};
template<> class OptionalMessage<std::string> {
public:
    OptionalMessage(std::string object_, bool isValue)
     : object(object_), flag(isValue) {}

    explicit operator bool() const noexcept {
        return flag;
    }
    std::string getValue() const {
        if (!flag) {
            throw std::runtime_error("");
        }
        return object;
    }
    std::string getMessage() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return object;
    }
private:
    bool flag;
    std::string object;
};
template<> class OptionalMessage<void> {
public:
    OptionalMessage() : flag(true) {};
    OptionalMessage(std::string message_) : message(message_), flag(false) {}

    explicit operator bool() const noexcept {
        return flag;
    }
    std::string getMessage() const {
        if (flag) {
            throw std::runtime_error("");
        }
        return message;
    }
private:
    bool flag;
    std::string message;
};
