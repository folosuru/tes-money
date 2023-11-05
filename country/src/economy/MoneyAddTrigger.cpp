#include <economy/MoneyAddTrigger.hpp>
#include <Nlohmann/json.hpp>
#include <fstream>
namespace tes {
std::optional<std::string_view> MoneyAddTriggerManager::getTriggerOnBreak(int id, int data) {
    if (trigger_on_break.contains({id,data})){
        return trigger_on_break.at({id,data});
    }
    return std::nullopt;
}
void MoneyAddTriggerManager::load() {
    nlohmann::json data = nlohmann::json::parse(std::ifstream(trigger_define_file));
    for (const auto& trigger : data.items()) {
        for (const auto& i : trigger.value()) {
            trigger_on_break.insert({i.get<std::pair<int,int>>(), trigger.key()});
        }
    }
}
}