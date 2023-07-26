//
// Created by folosuru on 2023/07/19.
//

#include "../header/PlayerMoney.hpp"
#include "../header/Money.hpp"

namespace tes {

    bool PlayerMoney::has(const tes::Money &money_) {
        if (money.find(money_.currency) != money.end()) {
            return (*money[money_.currency] > money_);
        } else {
            return false;
        }
    }

    void PlayerMoney::remove(const Money &money_) {
        // 0以下ならMoneyのコンストラクタが怒ってくれる！あんしん！
        Money new_money = *get(money_.currency) - money_;
        money[money_.currency] = std::shared_ptr<Money>(&new_money);
    }

    void PlayerMoney::add(const Money &money_) {
        money[money_.currency] = std::make_shared<Money>(*get(money_.currency) + money_);
    }

    void PlayerMoney::send(const std::shared_ptr<PlayerMoney> &to, const Money &money_) {
        to->add(money_);
        this->remove(money_);
    }

    std::shared_ptr<Money> PlayerMoney::get(const Types::currency &cur) {
        if (money.find(cur) == money.end()) {
            money[cur] = std::make_shared<Money>(Money(0, cur));
        }
        return money[cur];
    }
}
