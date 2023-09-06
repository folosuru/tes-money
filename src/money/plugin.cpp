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
#include <llapi/MC/CommandOrigin.hpp>
#include <llapi/MC/CommandOutput.hpp>
#include <Nlohmann/json.hpp>

#include "Util/mc_Util.hpp"
#include "version.h"
#include "./header/api.hpp"


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
        tes::getPlayerManager()->newPlayer(event.mPlayer->getRealName());
        return true;
        });

    Event::ServerStoppedEvent::subscribe([](const Event::ServerStoppedEvent& event) {
        return true;
        });


    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    const DynamicCommandInstance* money_normal;
    const DynamicCommandInstance* money_edit;
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

                player_money target_money;
                if (!tes::getPlayerManager()->exists(results["to"].getRaw<std::string>())) {
                    output.error("could not find target player...");
                    return;
                }
                target_money = tes::getPlayerManager()->getPlayer(results["to"].getRaw<std::string>());
                currency input_currency;
                if (!results["currency"].isSet) {
                    input_currency = tes::getCurrencyManager()
                        ->getCurrency(results["currency"].getRaw<std::string>());
                }

                switch (do_hash(action.c_str())) {
                    case do_hash("show"): {
                        output.success(target_money->get(input_currency)->getText());
                        break;
                    }

                    case do_hash("set"): {
                        target_money->set(tes::Money(results["value"].getRaw<int>(), input_currency));
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

                player_money origin_money;
                if (!tes::getPlayerManager()->exists(origin.getPlayer()->getRealName())) {
                    return;
                }
                origin_money = tes::getPlayerManager()->getPlayer(origin.getPlayer()->getRealName());
                currency input_currency;
                if (!results["currency"].isSet) {
                    input_currency = tes::getCurrencyManager()
                        ->getCurrency(results["currency"].getRaw<std::string>());
                }

                switch (do_hash(action.c_str())) {
                    case do_hash("list"): {
                        for (const auto& item : origin_money->getAll()) {
                            output.success(item.second->getText());
                        }
                        break;
                    }

                    case do_hash("show"): {
                        output.success(origin_money->get(input_currency)->getText());
                        break;
                    }

                    case do_hash("send"): {
                        std::string to_name = results["to"].getRaw<std::string>();

                        if (!tes::getPlayerManager()->exists(to_name)) {
                            break;
                        }
                        tes::Types::player_money to = tes::getPlayerManager()->getPlayer(to_name);
                        tes::Money request_money = tes::Money(results["value"].getRaw<int>(), input_currency);
                        if (!origin_money->has(request_money)) {
                            break;
                        }
                        origin_money->send(to, request_money);
                        sendTextToPlayer(Global<Level>->getPlayer(to_name), "");
                        break;
                    }
                    default:break;
                }
            },  // The callback function
            CommandPermissionLevel::Any);  // The permission level
    }
    tes::initCurrencyManager(tes::CurrencyCommandUpdater(money_normal,money_edit));

}
