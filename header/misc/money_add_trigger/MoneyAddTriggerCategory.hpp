#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
#include <utility>
#include <vector>
#include <string>
#include <memory>

namespace tes {
using MoneyAddTriggerKey = std::shared_ptr<std::string>;
struct MoneyAddTriggerCategory {
    const std::string name;

    const std::vector<MoneyAddTriggerKey> Child;

    MoneyAddTriggerCategory(std::string name_,
                            std::vector<MoneyAddTriggerKey> child_);
};
}

#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
