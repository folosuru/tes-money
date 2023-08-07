#include "../header/PlayerMoney.hpp"
#include <format>
#include <memory>

namespace tes {

    bool PlayerMoney::has(const tes::Money &money_) const{
        if (money.find(money_.currency) != money.end()) {
            return (*money.at(money_.currency) >= money_);
        } else {
            return false;
        }
    }

    void PlayerMoney::remove(const Money &money_) {
        edited = true;
        /* 0以下ならMoneyのコンストラクタが怒ってくれる！あんしん！ */
        money[money_.currency] = std::make_shared<Money>(*get(money_.currency) - money_);
    }

    void PlayerMoney::add(const Money &money_) {
        edited = true;
        money[money_.currency] = std::make_shared<Money>(*get(money_.currency) + money_);
    }

    void PlayerMoney::send(const std::shared_ptr<PlayerMoney> &to, const Money &money_) {
        to->add(money_);
        this->remove(money_);
    }

    std::shared_ptr<Money> PlayerMoney::get(const Types::currency &cur) {
        if (!money.contains(cur)) {
            money[cur] = std::make_shared<Money>(0, cur);
        }
        return money[cur];
    }

    const std::unordered_map<Types::currency, std::shared_ptr<Money>>& PlayerMoney::getAll() const {
        return money;
    }

    void PlayerMoney::set(const Money& money_) {
        edited = true;
        money[money_.currency] = std::make_shared<Money>(money_);
    }

    PlayerMoney::PlayerMoney() {
        edited = true;
    }
}
