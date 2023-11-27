#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include <unordered_map>
#include <string>
#include "MoneyAddTriggerCategory.hpp"
namespace tes {
using MoneyAddTriggerKey = std::shared_ptr<std::string>;
class MoneyAddTriggerManager {
public:

    [[nodiscard]]
    std::optional<MoneyAddTriggerKey> getTriggerOnBreak(int id, int data);

    void load();

    const std::vector<std::shared_ptr<MoneyAddTriggerCategory>>& getAllWithCategory();

    [[nodiscard]]
    MoneyAddTriggerKey getKey(const std::string&) const;

private:
    std::vector<std::shared_ptr<MoneyAddTriggerCategory>> all_trigger;
    std::unordered_map<std::string, MoneyAddTriggerKey> trigger_by_name;
    std::unordered_map<int,std::unordered_map<int, MoneyAddTriggerKey>> trigger_on_break;
    static const inline std::string trigger_define_file = "plugin/tes/country/MoneyTrigger.json";
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
