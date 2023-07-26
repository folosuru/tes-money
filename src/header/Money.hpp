#pragma once
#ifndef PLUGIN_MONEY_HPP
#define PLUGIN_MONEY_HPP
#include <utility>
#include <stdexcept>
#include "../Util/types.hpp"
#include "api.hpp"
namespace tes {
class DLL Money {
public:
    const int value;
    const Types::currency currency;

    Money(int value_, Types::currency currency_);

    Money(const Money& m) = default;

    [[nodiscard]]
    inline bool isSameCurrency(const Money& money) const;

    bool operator<(const Money &compare) const;
    bool operator>(const Money &compare) const;
    bool operator<=(const Money &compare) const;
    bool operator>=(const Money &compare) const;
    Money operator+(const Money &money) const;
    Money operator-(const Money &money) const;

    Money() = delete;
};
}
#endif  // PLUGIN_MONEY_HPP
