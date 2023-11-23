#include <money/player/PlayerMoney.hpp>
#include <format>
#include <memory>

namespace tes {
using Arrai18n::trl_text;

PlayerMoney::PlayerMoney(tes::PlayerIdentify name) : identify(name) {}

std::shared_ptr<PlayerMoney> PlayerMoney::init(const nlohmann::json& json,
                                               const std::shared_ptr<CurrencyManager>& currency_manager,
                                               const std::shared_ptr<PlayerIdentifyProvider>& identify) {
    auto result = std::make_shared<PlayerMoney>(identify->getIdentify(json["name"].get<std::string>()));
    for (const auto& item : json["money"].items()) {
        tes::Types::money_value_t value = item.value().get<tes::Types::money_value_t>();
        tes::Types::currency currency = currency_manager->getCurrency(item.key());
        result->add(tes::Money(value, currency));
    }
    return result;
}

bool PlayerMoney::has(const tes::Money& money_) const noexcept {
    if (money.find(money_.currency) != money.end()) {
        return (*money.at(money_.currency) >= money_);
    } else {
        return false;
    }
}

void PlayerMoney::remove(const Money& money_) {
    edited = true;
    /* 0以下ならMoneyのコンストラクタが怒ってくれる！あんしん！ */
    money[money_.currency] = std::make_shared<Money>(get(money_.currency) - money_);
}

void PlayerMoney::add(const Money& money_) noexcept {
    edited = true;
    money[money_.currency] = std::make_shared<Money>(get(money_.currency) + money_);
}

void PlayerMoney::send(const std::shared_ptr<MoneyAccount>& to, const Money& money_) {
    this->remove(money_);
    to->receive(this, money_);
}

Money PlayerMoney::get(const Types::currency& cur) const noexcept {
    if (!money.contains(cur)) {
        return Money(0, cur);
    }
    return *money.at(cur);
}

const std::unordered_map<Types::currency, std::shared_ptr<Money>>& PlayerMoney::getAll() const noexcept {
    return money;
}

void PlayerMoney::set(const Money& money_) noexcept {
    edited = true;
    money[money_.currency] = std::make_shared<Money>(money_);
}

nlohmann::json PlayerMoney::get_json() {
    nlohmann::json result;
    for (const auto& item : money) {
        result["money"][item.first->currency_name] = item.second->value;
    }
    return result;
}

void PlayerMoney::receive(const MoneyAccount *from, const Money& money_) {
    this->add(money_);
}

util::OptionalMessage<trl_text, trl_text> PlayerMoney::try_send(const std::shared_ptr<MoneyAccount>& to,
                                                                const Money& money_) {
    if (!this->has(money_)) {
        return util::OptionalMessage<trl_text, trl_text>(
            {"money.send.not_enough",
             {}
            }, false);
    }
    this->send(to, money_);
    return util::OptionalMessage<trl_text, trl_text>(
        {"money.send.success",
         {money_.getText(), to->getName()}
        }, true);
}

std::string PlayerMoney::getName() {
    return identify->name;
}
}
