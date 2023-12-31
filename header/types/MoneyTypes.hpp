#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cstdint>

namespace tes {
class PlayerMoney;
class Currency;
}

namespace tes::Types {
// typedef std::string currency;
typedef std::shared_ptr<Currency> currency;
typedef std::shared_ptr<PlayerMoney> player_money;
typedef std::int64_t money_value_t;

}
