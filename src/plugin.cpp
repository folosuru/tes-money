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
#include <llapi/MC/CommandOrigin.hpp>
#include <llapi/MC/CommandOutput.hpp>


#include "version.h"
#include "./header/api.hpp"

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
        ) {}  // The callback function
    );
}
