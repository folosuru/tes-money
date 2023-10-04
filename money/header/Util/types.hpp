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
typedef const std::string& player_name_view;
typedef std::int64_t money_value;

}
