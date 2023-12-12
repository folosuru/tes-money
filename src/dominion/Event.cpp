#include "Event.hpp"
#include <DataManager.hpp>
#include <country/dominion/DominionManager.hpp>
#include <country/dominion/Dominion.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <country/dominion/land/Land.hpp>

namespace tes {
namespace country {
void commandInit() {

    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    const DynamicCommandInstance *money_normal;
    const DynamicCommandInstance *money_edit;
    money_edit = DynamicCommand::setup(
        "money_edit",  // The command
        "edit money",  // The description
        {
            {"enum_3", {"show"}},
            {"serve", {"serve"}},
            {"serve_stat", {"start, end"}},
            {"", {}},
        },  // The enumeration
        {
            Param("mode", ParamType::Enum, false, "serve"),
            Param("mode", ParamType::Enum, false, "enum_3"),
            Param("position", ParamType::Enum, false, "enum_4"),
            Param("value", ParamType::Int, false),
            Param("to", ParamType::String, false)
        },  // The parameters
        {
            // overloads{ (type == Enum ? enumOptions : name) ...}
            {"enum_2", "enum_4"},  // serve [start | end]
        },  // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {
            auto action = results["mode"].get<std::string>();
            switch (do_hash(action.c_str())) {
                case do_hash("serve"): {
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
                default:
                    break;
            }
        },  // The callback function
        CommandPermissionLevel::Any);  // The permission level

}

bool onBreak(const Event::PlayerDestroyBlockEvent& event) {
    std::shared_ptr<PlayerIdentifyProvider> identify_prov = DataManager::get()->player_identify;
    PlayerIdentify identify = identify_prov->getIdentifyByPlayer(event.mPlayer);
    std::shared_ptr<DominionManager> dominion_mng = DataManager::get()->DominionMng;
    auto block_pos = const_cast<BlockInstance&>(event.mBlockInstance).getPosition();

    geometry::Point2D block = {block_pos.x, block_pos.z};
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
