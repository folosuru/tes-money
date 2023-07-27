/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */
#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>
#include <string>
#include <fstream>
#include <llapi/MC/CommandOrigin.hpp>
#include <llapi/MC/CommandOutput.hpp>
#include <Nlohmann/json.hpp>

#include "Util/mc_Util.hpp"
#include "version.h"
#include "./header/api.hpp"
#include "./header/PlayerManager.hpp"
#include "./header/PlayerMoney.hpp"
#include "./header/CurrencyManager.hpp"
#include "./Util/types.hpp"

// We recommend using the global logger.
extern Logger logger;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    // Your code here
    Logger logger(PLUGIN_NAME);
    logger.info("Hello, world!");

    Translation::load("plugins/tes/lang/");

    std::shared_ptr<tes::PlayerManager> player_mng;
    std::shared_ptr<tes::CurrencyManager> currency_mng;

    for (const auto& entry : std::filesystem::directory_iterator("plugins/tes/money/player")) {
        if (!std::filesystem::is_regular_file(entry)) continue;

        nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
        std::string player_name = entry.path().stem().string();

        std::shared_ptr<tes::PlayerMoney> player_money;

        for (const auto& item : j["money"].items()) {
            tes::Types::money_value value = item.value().get<int>();
            tes::Types::currency currency = currency_mng->getCurrency(item.key());
            player_money->add(tes::Money(value, currency));
        }
        player_mng->addPlayer(player_name, player_money);
    }

    Event::PlayerJoinEvent::subscribe([](const Event::PlayerJoinEvent& event) {
        return true;
    });

    Event::ServerStoppedEvent::subscribe([](const Event::ServerStoppedEvent& event){
        return true;
    });

    DynamicCommand::setup(
        "hub",  // The command
        "return to hub.",  // The description
        {},  // The enumeration
        {},  // The parameters
        {{}, },  // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {}  /*The callback function*/);
}
