#pragma once
#ifndef PLUGIN_PLAYERMONEY_HPP
#define PLUGIN_PLAYERMONEY_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <Nlohmann/json.hpp>
#include <CppArrai18n/Arrai18n_def.hpp>
#include <util/OptionalMessage.hpp>
#include <money/Money.hpp>
#include <types/MoneyTypes.hpp>
#include <util/dll_declspec.hpp>
#include <currency/CurrencyManager.hpp>
#include <money/MoneyAccount.hpp>
#include <util/player_identify/PlayerIdentify.hpp>
#include <util/player_identify/PlayerIdentifyProvider.hpp.>

namespace tes {
class Money;
using Arrai18n::trl_text;
class TES_DLL PlayerMoney : public MoneyAccount {
public:
    bool edited = false;

    explicit PlayerMoney(PlayerIdentify);

    static std::shared_ptr<PlayerMoney> init(const nlohmann::json& json,
                                             const std::shared_ptr<CurrencyManager>& currency_manager,
                                             const std::shared_ptr<PlayerIdentifyProvider>&);

    std::string getName() override;

    const PlayerIdentify identify;

    nlohmann::json get_json();

    [[nodiscard]]
    bool has(const Money& money) const noexcept final;

    void remove(const Money& money_) final;

    void add(const Money& money_) noexcept final;

    void set(const Money& money_) noexcept final;

    util::OptionalMessage<trl_text, trl_text> try_send(const std::shared_ptr<MoneyAccount>& to, const Money& money_);

    void send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) final;

    void receive(const MoneyAccount *from, const Money& money_) final;

    [[nodiscard]]
    Money get(const Types::currency& cur) const noexcept final;

    [[nodiscard]]
    const std::unordered_map<Types::currency, std::shared_ptr<Money>>& getAll() const noexcept;

private:
    std::unordered_map<Types::currency, std::shared_ptr<Money>> money;
};

}
#endif  // PLUGIN_PLAYERMONEY_HPP
