#ifndef DEBUG_WITHOUT_LLAPI
/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */
#include <llapi/EventAPI.h>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>
#include <string>
#include <fstream>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/CommandOrigin.hpp>
#include <llapi/mc/CommandOutput.hpp>
#include <CppArrai18n/Arrai18n_def.hpp>
#include <util/minecraft/message.hpp>
#include "Event.hpp"
#include <money/player/PlayerManager.hpp>
#include <DataManager.hpp>
#include "command/CommandParser.hpp"

namespace tes {
namespace money {
void init_command() {
    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    const DynamicCommandInstance *money_normal;
    const DynamicCommandInstance *money_edit;
    money_edit = DynamicCommand::setup(
        "money_edit",  // The command
        "edit money",  // The description
        {
            {"enum_2", {"set"}},
            {"enum_3", {"show"}},
            {"currency name", {}},
        },  // The enumeration
        {
            Param("mode", ParamType::Enum, false, "enum_2"),
            Param("mode", ParamType::Enum, false, "enum_3"),
            Param("mode", ParamType::Enum, false, "enum_4"),
            Param("currency", ParamType::SoftEnum, false, "currency name"),
            Param("value", ParamType::Int, false),
            Param("to", ParamType::String, false)
        },  // The parameters
        {
            // overloads{ (type == Enum ? enumOptions : name) ...}
            {"enum_2", "to", "value", "currency name"},  // money_edit [String: to] [Int: value] <currency>
            {"enum_3", "to", "currency name"},  // money show [to] <currency>
            {"enum_4"}  // money help
        },  // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {
            auto action = results["mode"].get<std::string>();
            tes::CommandParser parser(origin, output, results);
            switch (do_hash(action.c_str())) {
                case do_hash("show"): {
                    auto target = parser.getTargetMoney();
                    auto currency = parser.getCurrency();
                    if (target && currency) {
                        output.success(target.value()->get(currency.value()).getText());
                    }
                    break;
                }

                case do_hash("set"): {
                    auto target = parser.getTargetMoney();
                    auto value = parser.getValue();
                    auto currency = parser.getCurrency();
                    if (target && value && currency) {
                        target.value()->set(tes::Money(value.value(), currency.value()));
                    }
                    break;
                }
                default:break;
            }
        },  // The callback function
        CommandPermissionLevel::Console);  // The permission level

    money_normal = DynamicCommand::setup(
        "money",  // The command
        "Example description",  // The description
        {
            {"enum_2", {"list"}},
            {"enum_3", {"show"}},
            {"enum_4", {"send"}},
            {"enum_5", {"help"}},
            {"currency name", {}},
        },  // The enumeration
        {
            Param("mode", ParamType::Enum, false, "enum_2"),
            Param("mode", ParamType::Enum, false, "enum_3"),
            Param("mode", ParamType::Enum, false, "enum_4"),
            Param("currency", ParamType::SoftEnum, false, "currency name"),
            Param("value", ParamType::Int, false),
            Param("to", ParamType::String, false)
        },  // The parameters
        {
            // overloads{ (type == Enum ? enumOptions : name) ...}
            {"enum_2"},  // money <list>
            {"enum_3", "currency name"},  // money show <currency>
            {"enum_4", "to", "value", "currency name"}  // money send <player> [value] <currency>
        },  // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {
            auto action = results["mode"].get<std::string>();
            tes::CommandParser parser(origin, output, results);
            switch (do_hash(action.c_str())) {
                case do_hash("list"): {
                    auto money = parser.getOriginMoney();
                    if (money) {
                        for (const auto& item : money.value()->getAll()) {
                            output.success(item.second->getText());
                        }
                    }
                    break;
                }

                case do_hash("show"): {
                    auto currency = parser.getCurrency();
                    auto origin_money = parser.getOriginMoney();
                    if (currency && origin_money) {
                        output.success(origin_money.value()->get(currency.value()).getText());
                    }
                    break;
                }

                case do_hash("send"): {
                    std::string to_name = results["to"].getRaw<std::string>();
                    auto currency = parser.getCurrency();
                    auto from = parser.getOriginMoney();
                    auto to = parser.getTargetMoney();
                    auto value = parser.getValue();
                    if (currency && from && to && value) {
                        tes::Money request_money = tes::Money(value.value(), currency.value());
                        auto result = from.value()->try_send(to.value(), request_money);
                        if (result) {
                            output.success(Arrai18n::trl(parser.origin_language,
                                                         result.get_succeed()));
                            tes::util::sendText(Global<Level>->getPlayer(to_name), "");
                        } else {
                            output.error(Arrai18n::trl(parser.origin_language,
                                                       result.get_fail()));
                        }
                    }
                    break;
                }
                case do_hash("help"): {
                    output.addMessage(tes::util::trl(origin, {"money.command.help",{}}));
                    break;
                }
                default:break;
            }
        },  // The callback function
        CommandPermissionLevel::Any);  // The permission level
    tes::DataManager::get()->CurrencyMng->setCommandUpdater(new tes::CurrencyCommandUpdater(money_normal, money_edit));
}

void init() {
    using tes::Types::player_money;
    using tes::Types::currency;
    init_command();
    Arrai18n::load(tes::resource::resource_directory + "lang/money/ja-JP.txt");
}

bool onPlayerJoin(const Event::PlayerJoinEvent& event) {
    tes::util::sendText(event.mPlayer, "hoge");
    auto player = DataManager::get()->player_identify->getIdentify(event.mPlayer->getRealName());
    if (tes::DataManager::get()->PlayerMoneyMng->exists(player)) return true;
    tes::DataManager::get()->PlayerMoneyMng->newPlayer(player);
    return true;
}

}
}
#endif
