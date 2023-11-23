#pragma once
#ifndef TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
#define TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
#ifndef DEBUG_WITHOUT_LLAPI
#include <optional>
#include <unordered_map>
#include <string>
#include <types/MoneyTypes.hpp>
#include <llapi/DynamicCommandAPI.h>
#include <llapi/mc/CommandOrigin.hpp>
#include <llapi/mc/CommandOutput.hpp>

namespace tes {
class CommandParser {
public:
    CommandParser(CommandOrigin const& origin,
                  CommandOutput& output,
                  std::unordered_map<std::string, DynamicCommand::Result>& results);

    const std::string origin_language;

    std::optional<Types::player_money> getOriginMoney();

    std::optional<Types::currency> getCurrency();

    std::optional<Types::money_value_t> getValue();

    std::optional<Types::player_money> getTargetMoney();

private:
    CommandOrigin const& origin;

    CommandOutput& output;

    std::unordered_map<std::string, DynamicCommand::Result>& results;
};
}
#endif  // DEBUG_WITHOUT_LLAPI
#endif  // TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
