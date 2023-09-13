//
// Created by folosuru on 2023/09/13.
//

#include "CommandParser.hpp"
#include <player/PlayerManager.hpp>
#include <string>
namespace tes {
CommandParser::CommandParser(const CommandOrigin& origin,
                             CommandOutput& output,
                             std::unordered_map<string, DynamicCommand::Result>& results) :
                             origin(origin), output(output), results(results) {}

std::optional<Types::player_money> CommandParser::getOriginMoney() {
    auto mng = PlayerManager::get();
    std::string name = origin.getPlayer()->getRealName();
    if (!mng->exists(name)){
        output.error("target is not exist");
        return std::nullopt;
    }
    return mng->getPlayer(name);
}

std::optional<Types::currency> CommandParser::getCurrency() {
    auto mng = tes::CurrencyManager::get();
    if (!results.contains("currency")){
        return std::nullopt;
    }
    auto cur_name = results["currency"].get<std::string>();
    if (!mng->exists(cur_name)){
        output.error("currency is not exist:");
        return std::nullopt;
    }
    return mng->getCurrency(cur_name);
}

std::optional<Types::money_value> CommandParser::getValue() {
    if (!results.contains("value")){
        return std::nullopt;
    }
    int value = results["value"].get<int>();
    if (value < 0) {
        output.error("value cannot under 0");
        return std::nullopt;
    }
    return value;
}

std::optional<Types::player_money> CommandParser::getTargetMoney() {
    auto mng = tes::PlayerManager::get();
    if (!results.contains("to")){
        return std::nullopt;
    }
    auto name = results["to"].get<std::string>();
    if (!mng->exists(name)){
        output.error("player dose not exist:");
        return std::nullopt;
    }
    return mng->getPlayer(name);
}
}
