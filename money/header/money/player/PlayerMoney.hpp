#pragma once
#ifndef PLUGIN_PLAYERMONEY_HPP
#define PLUGIN_PLAYERMONEY_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include <CppArrai18n/Arrai18n.hpp>
#include <util/OptionalMessage.hpp>
#include "../money/Money.hpp"
#include "Util/MoneyTypes.hpp"
#include "Util/dll_declspec.hpp"
#include "../currency/CurrencyManager.hpp"
#include "../money/MoneyAccount.hpp"

namespace tes {
class Money;
using Arrai18n::trl_text;
class TES_MONEY_DLL PlayerMoney : public MoneyAccount {
public:
    bool edited = false;

    PlayerMoney();

    PlayerMoney(const nlohmann::json& json, const std::shared_ptr<CurrencyManager>& currency_manager);

    std::string getName() override;


    bool has(const Money& money) const noexcept final;

    void remove(const Money& money_) final;

    void add(const Money& money_) noexcept final;

    void set(const Money& money_) noexcept final;

    util::OptionalMessage<trl_text, trl_text> try_send(const std::shared_ptr<MoneyAccount>& to, const Money& money_);

    void send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) final;

    void receive(const MoneyAccount* from, const Money& money_) final;

    [[nodiscard]]
    Money get(const Types::currency& cur) const noexcept final;

    [[nodiscard]]
    const std::unordered_map<Types::currency, std::shared_ptr<Money>>& getAll() const noexcept;

private:
    std::unordered_map<Types::currency , std::shared_ptr<Money>> money;
    std::string name;
};

}
#endif  // PLUGIN_PLAYERMONEY_HPP
