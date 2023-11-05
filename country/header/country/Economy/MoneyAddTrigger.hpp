#ifndef TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGER_HPP_
#include <optional>
#include <map>
#include <string_view>
namespace tes {
class MoneyAddTriggerManager {
public:
    std::optional<std::string_view> getTriggerOnBreak(int id, int data);

    void load();

private:
    std::map<std::pair<int,int>, std::string> trigger_on_break;
    static constexpr inline std::string trigger_define_file = "plugin/tes/country/MoneyTrigger.json";
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_ECONOMY_MONEYADDTRIGGER_HPP_
