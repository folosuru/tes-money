#pragma once
#ifndef PLUGIN_MONEY_HPP
#define PLUGIN_MONEY_HPP
#include <utility>
#include <stdexcept>
#include <string>
#include <types/MoneyTypes.hpp>
#include <currency/Currency.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class TES_DLL Money {
public:
    const Types::money_value_t value;

    const Types::currency currency;

    /**
     * @throws std::invalid_argument valueが0以下の時
     */
    Money(Types::money_value_t value_, Types::currency currency_);

    Money(const Money& m) = default;

    /**
     * 額面の表示用のテキストを返す。
     * @return example: "150 JPY", "0 USD"
     */
    [[nodiscard]]
    std::string getText() const noexcept;

    [[nodiscard]]
    inline bool isCompatible(const Money& money) const noexcept;

    bool operator==(const Money& compare) const noexcept;

    bool operator<(const Money& compare) const;

    bool operator>(const Money& compare) const;

    bool operator<=(const Money& compare) const;

    bool operator>=(const Money& compare) const;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;

    Money operator+(const Money& money) const;

    Money operator-(const Money& money) const;

    Money operator*(std::int64_t count) const;
    Money& operator=(const Money& money);

    Money();
};
}
#endif  // PLUGIN_MONEY_HPP
