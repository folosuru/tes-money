#include "../header/Money.hpp"
#include <format>

namespace tes {

    Money::Money(int value_, Types::currency currency_) : value(value_), currency(std::move(currency_)) {
        if (value_ < 0) {
            throw std::invalid_argument("money cannot be under 0");
        }
    }

    bool Money::isSameCurrency(const Money &money) const {
        return (this->currency == currency);
    }

    bool Money::operator<(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value < compare.value);
    }

    bool Money::operator>(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value < compare.value);
    }

    bool Money::operator<=(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value <= compare.value);
    }

    bool Money::operator>=(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value <= compare.value);
    }

    Money Money::operator+(const Money &money) const {
        if (!isSameCurrency(money)) throw std::invalid_argument("different currency");
        return Money(value + money.value, currency);
    }

    Money Money::operator-(const Money &money) const {
        if (!isSameCurrency(money)) throw std::invalid_argument("different currency");
        return Money(value - money.value, currency);
    }

    std::string Money::getText() const {
        return std::format("{0} {1}", value, currency->currency_name);
    }
}
