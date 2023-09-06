#pragma once
#ifndef PLUGIN_MONEY_HPP
#define PLUGIN_MONEY_HPP
#include <utility>
#include <stdexcept>
#include <string>
#include "../Util/types.hpp"
#include "./Currency.hpp"
#include "../Util/dll_declspec.hpp"
namespace tes {
class TES_MONEY_DLL Money {
public:
    const Types::money_value value;
    const Types::currency currency;

    Money(Types::money_value value_, Types::currency currency_);

    Money(const Money& m) = default;

    std::string getText() const;

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
