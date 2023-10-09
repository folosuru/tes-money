#include <money/Money.hpp>
#include <format>
namespace tes {

    Money::Money(Types::money_value value_, Types::currency currency_) : value(value_), currency(std::move(currency_)) {
        if (value_ < 0) {
            throw std::invalid_argument("money cannot be under 0");
        }
    }

    bool Money::isSameCurrency(const Money &money) const noexcept {
        return (this->currency == money.currency);
    }


    bool Money::operator==(const Money &compare) const {
        return (isSameCurrency(compare) && value == compare.value);
    }
    bool Money::operator<(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value < compare.value);
    }

    bool Money::operator>(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value > compare.value);
    }

    bool Money::operator<=(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value <= compare.value);
    }

    bool Money::operator>=(const Money &compare) const {
        if (!isSameCurrency(compare)) throw std::invalid_argument("different currency");
        return (value >= compare.value);
    }

    Money Money::operator+(const Money &money) const {
        if (!isSameCurrency(money)) throw std::invalid_argument("different currency");
        return Money(value + money.value, currency);
    }

    Money Money::operator-(const Money &money) const {
        if (!isSameCurrency(money)) throw std::invalid_argument("different currency");
        return Money(value - money.value, currency);
    }

    std::string Money::getText() const noexcept {
        return std::format("{0} {1}", value, currency->currency_name);
    }
}
