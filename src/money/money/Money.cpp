#include <money/Money.hpp>
#include <format>

namespace tes {

namespace {
Types::currency getVaildCurrency(Types::currency v1, Types::currency v2) {
    if (v1 == nullptr) {
        return v2;
    }
    if (v2 == nullptr) {
        return v1;
    }
    return v1;
}

}

Money::Money(Types::money_value_t value_, Types::currency currency_) : value(value_), currency(std::move(currency_)) {
    if (value_ < 0) {
        throw std::invalid_argument("money cannot be under 0");
    }
}

bool Money::isCompatible(const Money& money) const noexcept {
    return (this->currency == money.currency);
}

bool Money::operator==(const Money& compare) const noexcept {
    return (isCompatible(compare) && value == compare.value);
}

bool Money::operator<(const Money& compare) const {
    if (!isCompatible(compare)) throw std::invalid_argument("different currency");
    return (value < compare.value);
}

bool Money::operator>(const Money& compare) const {
    if (!isCompatible(compare)) throw std::invalid_argument("different currency");
    return (value > compare.value);
}

bool Money::operator<=(const Money& compare) const {
    if (!isCompatible(compare)) throw std::invalid_argument("different currency");
    return (value <= compare.value);
}

bool Money::operator>=(const Money& compare) const {
    if (!isCompatible(compare)) throw std::invalid_argument("different currency");
    return (value >= compare.value);
}

Money::operator bool() const noexcept {
    return currency != nullptr;
}

bool Money::operator!() const noexcept {
    return !(operator bool());
}

Money Money::operator+(const Money& money) const {
    if (!isCompatible(money)) throw std::invalid_argument("different currency");
    return Money(value + money.value, getVaildCurrency(currency, money.currency));
}

Money Money::operator-(const Money& money) const {
    if (!isCompatible(money)) throw std::invalid_argument("different currency");
    return Money(value - money.value, getVaildCurrency(currency, money.currency));
}

Money Money::operator*(std::int64_t count) const {
    if (count < 0) throw std::runtime_error("mlutiple cannot be under 0");
    return Money(value * count, currency);
}

Money::Money() : value(0), currency(nullptr) {
}

std::string Money::getText() const noexcept {
    if (!currency) {
        return "0";
    }
    return std::format("{0} {1}", value, currency->currency_name);
}
}
