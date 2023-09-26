#pragma once
#ifndef TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
#define TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
#include <optional>
#include <unordered_map>
#include <string>
#include <llapi/DynamicCommandAPI.h>
#include <Util/types.hpp>
#include <llapi/mc/CommandOrigin.hpp>
#include <llapi/mc/CommandOutput.hpp>
namespace tes {
class CommandParser {
public:
    CommandParser(CommandOrigin const& origin,
                  CommandOutput& output,
                  std::unordered_map<std::string, DynamicCommand::Result>& results);

    std::optional<Types::player_money> getOriginMoney();

    std::optional<Types::currency> getCurrency();

    std::optional<Types::money_value> getValue();

    std::optional<Types::player_money> getTargetMoney();

private:
    CommandOrigin const& origin;

    CommandOutput& output;

    std::unordered_map<std::string, DynamicCommand::Result>& results;
};
}

#endif  // TES_MONEY_SRC_COMMAND_COMMANDPARSER_HPP_
