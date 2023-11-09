#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
#include <utility>
#include <vector>
#include <string>
namespace tes {
struct MoneyAddTriggerCategory {
    const std::string name;
    const std::vector<std::string> Child;
    MoneyAddTriggerCategory(std::string name_,
                            std::vector<std::string> child_)
      : name(std::move(name_)), Child(std::move(child_)) {}
};
}

#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERCATEGORY_HPP_
