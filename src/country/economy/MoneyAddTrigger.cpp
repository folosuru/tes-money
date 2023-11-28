#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>
#include <Nlohmann/json.hpp>
#include <fstream>

namespace tes {
std::optional<MoneyAddTriggerKey> MoneyAddTriggerManager::getTriggerOnBreak(int id, int data) {
    if (auto id_map = trigger_on_break.find(id); id_map != trigger_on_break.end()) {
        if (auto result = id_map->second.find(data); result != id_map->second.end()) {
            return result->second;
        }
    }
    return std::nullopt;
}

void MoneyAddTriggerManager::load(std::ifstream file = std::ifstream(trigger_define_file)) {
    nlohmann::json data = nlohmann::json::parse(file);
    /*
     * {
     *  "SurfaceBlockBreak" : {
     *      "DirtBreak" : [
     *          [2,0],
     *          [3,0]
     *      ],
     *   }
     *  }
     */
    for (const auto& category : data.items()) {  // foreach category
        std::vector<MoneyAddTriggerKey> triggers;  // contain triggers in category
        for (const auto& trigger : category.value().items()) { // foreach block
            MoneyAddTriggerKey key_ptr = std::make_shared<std::string>(trigger.key());
            triggers.push_back(key_ptr);
            for (const auto& block : trigger.value()) {  // foreach block id
                trigger_on_break[block.at(0).get<int>()][ block.at(1).get<int>()] = key_ptr;
            }
        }
        all_trigger.push_back(std::make_shared<MoneyAddTriggerCategory>(category.key(), triggers));
    }
}

const std::vector<std::shared_ptr<MoneyAddTriggerCategory>>& MoneyAddTriggerManager::getAllWithCategory() {
    return all_trigger;
}

MoneyAddTriggerKey MoneyAddTriggerManager::getKey(const std::string& name) const {
    return trigger_by_name.at(name);
}

}