#pragma once
#ifndef TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#define TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include "Money.hpp"
#include <types/MoneyTypes.hpp>
#include <util/dll_declspec.hpp>
#include <currency/CurrencyManager.hpp>

namespace tes {
class Money;
class TES_DLL MoneyAccount {
public:
    virtual std::string getName() = 0;

    [[nodiscard]]
    virtual bool has(const Money& money) const noexcept = 0;

    /**
     * money_の分お金を減らす
     * @param money_
     * @throw
     */
    virtual void remove(const Money& money_) = 0;

    /**
     * money_の額を加える。
     * @param money_
     */
    virtual void add(const Money& money_) noexcept = 0;

    virtual void set(const Money& money_) noexcept = 0;

    /**
     * toに送金する。内部でtoのreceive関数が呼ばれるハズ
     * @param to
     * @param money_
     */
    virtual void send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) = 0;

    /**
     * fromからの送金を受け取る。
     * @param from
     * @param money_
     */
    virtual void receive(const MoneyAccount *from, const Money& money_) = 0;

    /**
     * curで指定された通貨のMoneyを返す
     * @param cur
     * @return Money
     */
    virtual Money get(const Types::currency& cur) const noexcept = 0;
};

}
#endif  // TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
