#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include <unordered_map>
#include <string_view>
#include "MoneyAddTriggerCategory.hpp"
namespace tes {
using MoneyAddTriggerKey = std::string_view;
class MoneyAddTriggerManager {
public:

    [[nodiscard]]
    std::optional<std::string_view> getTriggerOnBreak(int id, int data);

    void load();

    const std::vector<std::shared_ptr<MoneyAddTriggerCategory>>& getAllWithCategory();

    std::optional<MoneyAddTriggerKey> getKey(const std::string&);

    MoneyAddTriggerKey getOrGenKey(const std::string&);

private:
    std::vector<std::shared_ptr<MoneyAddTriggerCategory>> all_trigger;
    std::map<std::pair<int,int>, std::string_view> trigger_on_break;
    std::unordered_map<std::string_view, std::shared_ptr<std::string>> all_key;
    static const inline std::string trigger_define_file = "plugin/tes/country/MoneyTrigger.json";
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGERMANAGER_HPP_
