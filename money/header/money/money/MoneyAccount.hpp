#pragma once
#ifndef TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#define TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include "Money.hpp"
#include "Util/MoneyTypes.hpp"
#include "Util/dll_declspec.hpp"
#include "../currency/CurrencyManager.hpp"

namespace tes {
class Money;
class TES_MONEY_DLL MoneyAccount {
public:
    enum class MoneySendStatus {
        success,
        not_enough
    };

    virtual std::string getName() = 0;
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
    virtual void receive(const MoneyAccount* from,
                         const Money& money_,
                         std::function<void(MoneySendStatus)> callback) = 0;

    /**
     * curで指定された通貨のMoneyを返す
     * @param cur
     * @return Money
     */
    virtual Money get(const Types::currency& cur) const noexcept = 0;
};

}
#endif  // TES_COUNTRY_MONEY_HEADER_MONEY_MONEYACCOUNT_HPP_
