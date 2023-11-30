#include <misc/money_add_trigger/MoneyAddTriggerCategory.hpp>
#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>

tes::MoneyAddTriggerCategory::MoneyAddTriggerCategory(std::string name_, std::vector<MoneyAddTriggerKey> child_)
    : name(std::move(name_)), Child(std::move(child_)) {}
