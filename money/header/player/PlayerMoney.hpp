#pragma once
#ifndef PLUGIN_PLAYERMONEY_HPP
#define PLUGIN_PLAYERMONEY_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include "../money/Money.hpp"
#include "Util/types.hpp"
#include "Util/dll_declspec.hpp"
#include "../currency/CurrencyManager.hpp"
#include "../money/MoneyAccount.hpp"

namespace tes {
class Money;
class TES_MONEY_DLL PlayerMoney : public MoneyAccount {
public:
    bool edited = false;

    PlayerMoney();

    PlayerMoney(const nlohmann::json& json, const std::shared_ptr<CurrencyManager>& currency_manager);

    nlohmann::json get_json();

    bool has(const Money& money) const final;

    void remove(const Money& money_) final;

    void add(const Money& money_) final;

    void set(const Money& money_) final;

    void send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) final;

    void receive(const MoneyAccount* from, const Money& money_) final;

    std::shared_ptr<Money> get(const Types::currency& cur) final;

    const std::unordered_map<Types::currency, std::shared_ptr<Money>>& getAll() const final;

private:
    std::unordered_map<Types::currency , std::shared_ptr<Money>> money;
};

}
#endif  // PLUGIN_PLAYERMONEY_HPP
