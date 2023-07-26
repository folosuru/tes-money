#pragma once
#ifndef PLUGIN_PLAYERMONEY_HPP
#define PLUGIN_PLAYERMONEY_HPP

#include <unordered_map>
#include <memory>
#include "Money.hpp"
#include "../Util/types.hpp"
namespace tes {

class DLL PlayerMoney {
public:

    inline bool has(const Money& money);

    inline void remove(const Money& money_);

    inline void add(const Money& money_);

    inline void send(const std::shared_ptr<PlayerMoney>& to, const Money& money_);

private:
    std::unordered_map<Types::currency , std::shared_ptr<Money>> money;

    inline std::shared_ptr<Money> get(const Types::currency& cur);
};

}
#endif  // PLUGIN_PLAYERMONEY_HPP
