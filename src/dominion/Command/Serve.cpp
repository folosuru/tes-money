#include "Serve.hpp"
#include <unordered_map>
#include <util/geometry/Geometry.hpp>
#include <misc/player_identify/PlayerIdentifyProvider.hpp>

namespace tes {
namespace dominion {
namespace command {

using ParamType = DynamicCommand::ParameterType;
using Param = DynamicCommand::ParameterData;

std::unordered_map<PlayerIdentify, geometry::Point2D> point_history;

void Serve(DynamicCommand const& command,
    CommandOrigin const& origin,
    CommandOutput& output,
    std::unordered_map<std::string, DynamicCommand::Result>& results) {
    auto action = results["serve_stat"].get<std::string>();

    auto IdentifyProvider = /**/;
    auto origin_identify = IdentifyProvider->getIdentify(origin.getName());
    auto pos = origin.getPlayer().getPosition();
    geometry::Point2D current_pos = {pos.x, pos.z};

    if (auto land = DataManager::get()->LandMng->getLand(current_pos);
        std::holds_alternative<LandManager::LandFoundStatus>) {  // 戻り値がLandFoundStatus
        switch (std::get<LandManager::LandFoundStatus>(land)) {
            case (LandManager::LandFoundStatus::not_dominion): {
                output.error(/**/);
                break;
            }
            case (LandManager::LandFoundStatus::already_served): {
                output.error(/**/);
                break;
            }
            default: break;
        }
        return;
    }
    switch (do_hash(action.c_str())) {
        case do_hash("start"): {
            point_history[origin_identify] = current_pos;
            break;
        }
        case (do_hash("end")): {
            if (auto history = point_history.find(origin_identify);
                history != point_history.end()) {
                    
            } else {
                output.error(/* please use start before use! */);
            }
        }
        default:
            break;
}
}


}
}
}
