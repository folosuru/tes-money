#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>

namespace tes {
class PlayerMoney;
class Currency;
}

namespace tes::Types {
// typedef std::string currency;
typedef std::shared_ptr<Currency> currency;
typedef std::shared_ptr<PlayerMoney> player_money;
typedef std::string player_name;
typedef const std::string& player_name_view;
typedef std::vector<std::string> player_list;
typedef std::pair<int, int> posXZ;
typedef int country;
typedef unsigned long long money_value;
}
