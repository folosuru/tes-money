/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */
#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>
#include <llapi/I18nAPI.h>

#include <string>
#include <fstream>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/CommandOrigin.hpp>
#include <llapi/mc/CommandOutput.hpp>
#include <Nlohmann/json.hpp>

#include <Util/mc_Util.hpp>
#include "version.h"
#include <player/PlayerManager.hpp>
#include <currency/CurrencyManager.hpp>
#include "command/CommandParser.hpp"
 // We recommend using the global logger.
extern Logger logger;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    using tes::Types::player_money;
    using tes::Types::currency;

    // Your code here
    Logger logger(PLUGIN_NAME);
    logger.info("Hello, world!!");
    // Translation::load("plugins/tes/lang/");
    Event::PlayerJoinEvent::subscribe([](const Event::PlayerJoinEvent& event) {
        sendTextToPlayer(event.mPlayer, "hoge")
        if (event.mPlayer != nullptr) {
            event.mPlayer->sendText("hoge");
        }
        tes::PlayerManager::get()->newPlayer(event.mPlayer->getRealName());
        return true;
    });

    Event::ServerStoppedEvent::subscribe([](const Event::ServerStoppedEvent& event) {
        return true;
    });

    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    const DynamicCommandInstance *money_normal;
    const DynamicCommandInstance *money_edit;
    {
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
                Param("currency", ParamType::SoftEnum, false, "currency name"),
                Param("value", ParamType::Int, false),
                Param("to", ParamType::String, false)
            },  // The parameters
            {
                // overloads{ (type == Enum ? enumOptions : name) ...}
                {"enum_2", "to", "value", "currency name"},  // money_edit [String: to] [Int: value] <currency>
                {"enum_3", "to", "currency name"},  // money show [to] <currency>
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
                            output.success(target.value()->get(currency.value())->getText());
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
                            output.success(origin_money.value()->get(currency.value())->getText());
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
                            if (!from.value()->has(request_money)) {
                                break;
                            }
                            from.value()->send(to.value(), request_money);
                            sendTextToPlayer(Global<Level>->getPlayer(to_name), "");
                        }
                        break;
                    }
                    default:break;
                }
            },  // The callback function
            CommandPermissionLevel::Any);  // The permission level
    }
    tes::CurrencyManager::get()->setCommandUpdater(new tes::CurrencyCommandUpdater(money_normal, money_edit));
}
