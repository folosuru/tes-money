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
#include <CppArrai18n/Arrai18n.hpp>
#include "version.h"
#include "command/CommandParser.hpp"
// We recommend using the global logger.
extern Logger logger;
/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    // Your code here
    Logger logger(PLUGIN_NAME);
    logger.info("Hello, world!!");
}