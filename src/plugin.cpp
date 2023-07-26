/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/LoggerAPI.h>

#include "version.h"
#include <string>
#include <vector>

#include <llapi/MC/ItemStack.hpp>
#include <llapi/MC/Level.hpp>
#include <llapi/MC/Player.hpp>
#include <llapi/mc/Types.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/Container.hpp>
#include <llapi/I18nAPI.h>

#include <llapi/MC/CommandOrigin.hpp>
#include <llapi/MC/CommandOutput.hpp>

#include <llapi/EventAPI.h>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>
#include "./header/api.hpp"

// We recommend using the global logger.
extern Logger logger;
std::string latest_player_xuid;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    // Your code here
    Logger logger(PLUGIN_NAME);
    logger.info("Hello, world!");

    Translation::load("plugins/tes/lang/");

    Event::PlayerJoinEvent::subscribe([](const Event::PlayerJoinEvent& event) {
        return true;
    });

    Event::ServerStoppedEvent::subscribe([](const Event::ServerStoppedEvent& event){
        return true;
    });

    DynamicCommand::setup(
        "hub", // The command
        "return to hub.", // The description
        {}, // The enumeration
        {}, // The parameters
        {{},}, // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {

        }// The callback function
    );
}
