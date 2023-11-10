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
#include <DataManager.hpp>
#include <Nlohmann/json.hpp>
#include "version.h"


 // We recommend using the global logger.
extern Logger logger;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    // TODO: moneyのlangファイルもロードするようにする

    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent& event){
        // event.mBlockInstance;
        return true;
    });
}
