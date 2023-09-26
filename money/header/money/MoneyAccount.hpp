#pragma once
#ifndef TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#define TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include "Money.hpp"
#include "Util/types.hpp"
#include "Util/dll_declspec.hpp"
#include "../currency/CurrencyManager.hpp"

namespace tes {
class Money;
class TES_MONEY_DLL MoneyAccount {
public:
    virtual bool has(const Money& money) const = 0;

    virtual void remove(const Money& money_) = 0;

    virtual void add(const Money& money_) = 0;

    virtual void set(const Money& money_) = 0;

    virtual void send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) = 0;

    virtual void receive(const MoneyAccount* from, const Money& money_) = 0;

    virtual std::shared_ptr<Money> get(const Types::currency& cur) = 0;

    virtual const std::unordered_map<Types::currency, std::shared_ptr<Money>>& getAll() const = 0;
};

}
#endif  // TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
