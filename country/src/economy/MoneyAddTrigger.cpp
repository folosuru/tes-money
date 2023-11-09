#include <economy/MoneyAddTriggerManager.hpp>
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
    for (const auto& category : data.items()) {
        std::vector<std::string> triggers;
        for (const auto& trigger : category.value().items()) {
            triggers.push_back(trigger.key());
            for (const auto& block : trigger.value()) {
                trigger_on_break.insert({block.get<std::pair<int, int>>(), trigger.key()});
            }
        }
        all_trigger.push_back(std::make_shared<MoneyAddTriggerCategory>(category.key(),triggers));
    }
}

const std::vector<std::shared_ptr<MoneyAddTriggerCategory>>& MoneyAddTriggerManager::getAllWithCategory() {
    return all_trigger;
}
}