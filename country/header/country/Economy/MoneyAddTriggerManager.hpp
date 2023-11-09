#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include <string_view>
#include "MoneyAddTriggerCategory.hpp"
namespace tes {
class MoneyAddTriggerManager {
public:
    std::optional<std::string_view> getTriggerOnBreak(int id, int data);

    void load();

    const std::vector<std::shared_ptr<MoneyAddTriggerCategory>>& getAllWithCategory();

private:
    std::vector<std::shared_ptr<MoneyAddTriggerCategory>> all_trigger;
    std::map<std::pair<int,int>, std::string> trigger_on_break;
    static const inline std::string trigger_define_file = "plugin/tes/country/MoneyTrigger.json";
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
