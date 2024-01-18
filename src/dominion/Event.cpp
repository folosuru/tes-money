#include "Event.hpp"
#include <DataManager.hpp>
#include <country/dominion/DominionManager.hpp>
#include <country/dominion/Dominion.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <country/dominion/land/Land.hpp>

#include "Command/CommandAction.hpp"

namespace tes {
namespace dominion {
void commandInit() {
    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    DynamicCommand::setup(
        "land",
        // The command
        "edit land",
        // The description
        {
            {"enum_3", {"show"}},
            {"serve", {"serve"}},
            {"serve_stat", {"start, end"}},
            {"info", {"info"}},
            {"here", {"here"}}
        },
        // The enumeration
        {
            Param("mode", ParamType::Enum, false, "serve"),
            Param("mode", ParamType::Enum, false, "info"),
            Param("mode", ParamType::Enum, false, "here"),
            Param("position", ParamType::Enum, false, "serve_stat"),
        },
        // The parameters
        {
            // overloads{ (type == Enum ? enumOptions : name) ...}
            {"serve", "serve_stat"}, // serve [start | end]
            {"info"},  // info
            {"here"},  // here
        },
        // The overloads
        [](
        DynamicCommand const& command,
        CommandOrigin const& origin,
        CommandOutput& output,
        std::unordered_map<std::string, DynamicCommand::Result>& results
    ) {
            auto action = results["mode"].get<std::string>();
            switch (do_hash(action.c_str())) {
                case do_hash("serve"): {
                    command::Serve(command,origin,output,results);
                    break;
                }
                case do_hash("info"): {
                    command::info(command,origin,output,results);
                    break;
                }
                case do_hash("here"): {
                    command::here(command,origin,output,results);
                    break;
                }
                default:
                    break;
            }
        },
        // The callback function
        CommandPermissionLevel::Any); // The permission level
}

bool onBreak(const PlayerIdentify& identify,
             const std::shared_ptr<DominionManager>& dominion_mng,
             const geometry::Point2D block) {
    if (auto dominion = dominion_mng->get(DominionManager::pos_to_index(block));
        dominion) {
        if (auto land = dominion.value()->land->getLand(block); land) {
            if (land.value().get().land.canUse(identify)) {
                return true;
            } else {
                return false;
            }
        }
    }
    return true;
}
}
}
