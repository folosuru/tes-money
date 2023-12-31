#include "CommandParser.hpp"

#ifndef DEBUG_WITHOUT_LLAPI
#include <money/player/PlayerManager.hpp>
#include <string>
#include <DataManager.hpp>

namespace tes {
CommandParser::CommandParser(const CommandOrigin& origin,
                             CommandOutput& output,
                             std::unordered_map<string, DynamicCommand::Result>& results) :
    origin(origin), output(output), results(results),
    origin_language(origin.getPlayer()->getLanguageCode()) {}

std::optional<Types::player_money> CommandParser::getOriginMoney() {
    auto mng = tes::DataManager::get()->PlayerMoneyMng;
    PlayerIdentify name = DataManager::get()->player_identify->getIdentifyByPlayer(origin);
    if (!mng->exists(name)) {
        output.error(
            Arrai18n::trl(origin_language,
                          "money.player_not_found", {name->name}));
        return std::nullopt;
    }
    return mng->getPlayer(name);
}

std::optional<Types::currency> CommandParser::getCurrency() {
    auto mng = tes::DataManager::get()->CurrencyMng;
    if (!results.contains("currency")) {
        return std::nullopt;
    }
    auto cur_name = results["currency"].get<std::string>();
    if (!mng->exists(cur_name)) {
        output.error(Arrai18n::trl(origin_language, "currency.not_found", {cur_name}));
        return std::nullopt;
    }
    return mng->getCurrency(cur_name);
}

std::optional<Types::money_value_t> CommandParser::getValue() {
    if (!results.contains("value")) {
        return std::nullopt;
    }
    int value = results["value"].get<int>();
    if (value < 0) {
        output.error(Arrai18n::trl(
            origin_language, "money.money.cannot_under_0", {}));
        return std::nullopt;
    }
    return value;
}

std::optional<Types::player_money> CommandParser::getTargetMoney() {
    auto mng = tes::DataManager::get()->PlayerMoneyMng;;
    if (!results.contains("to")) {
        return std::nullopt;
    }
    auto name = DataManager::get()->player_identify->getIdentify(results["to"].get<std::string>());
    if (!mng->exists(name)) {
        output.error(
            Arrai18n::trl(origin_language,
                          "money.player_not_found", {name->name}));
        return std::nullopt;
    }
    return mng->getPlayer(name);
}
}
#endif  // DEBUG_WITHOUT_LLAPI
