#pragma once
#ifndef PLUGIN_PLAYERMONEY_HPP
#define PLUGIN_PLAYERMONEY_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include "./Money.hpp"
#include "../Util/types.hpp"
#include "../Util/dll_declspec.hpp"

namespace tes {
class Money;
class DLL PlayerMoney {
public:
    bool edited;

    PlayerMoney();

    bool has(const Money& money) const;

    void remove(const Money& money_);

    void add(const Money& money_);

    void set(const Money& money_);

    void send(const std::shared_ptr<PlayerMoney>& to, const Money& money_);

    std::shared_ptr<Money> get(const Types::currency& cur);

    const std::unordered_map<Types::currency, std::shared_ptr<Money>>& getAll() const;

private:
    std::unordered_map<Types::currency , std::shared_ptr<Money>> money;
};

}
#endif  // PLUGIN_PLAYERMONEY_HPP
