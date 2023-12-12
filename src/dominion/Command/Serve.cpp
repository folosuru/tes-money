#include "Serve.hpp"
#include <unordered_map>
#include <util/geometry/Geometry.hpp>
#include <misc/player_identify/PlayerIdentifyProvider.hpp>

namespace tes {
namespace dominion {
namespace command {


namespace {
void serveConfirmForm(Player* pl, std::shared_ptr<ServeLandOrder>);
}

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
    geometry::Point2D current_pos = geometry::Point2D(origin.getPlayer().getPosition());
    auto landMng = DataManager::get()->LandMng;

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
                auto order = LandMng->prepareServe(origin_identify, geometry::Area2D(*history.second,current_pos);
                if (std::holds_alternative<ServeLandOrder::ErrorCode>) {
                    //...
                    output.error();
                    return;
                }
                output.getPlayer()
            } else {
                output.error(/* please use start before use! */);
            }
        }
        default:
            break;
        }
}

void serveConfirmForm(Player* pl, std::shared_ptr<ServeLandOrder> order) {
    Form::ModalForm form(Arrai18n::trl(pl->getLanguageCode(),
                                "dominion.form.serve.title"), // title
                        Arrai18n::trl(pl->getLanguageCode(),
                                "dominion.form.serve.description",
                                {order->getPrice().getText(),
                                    order->area->getWidth(),
                                     order->area->getHeight()}),
                  Arrai18n::trl(pl->getLanguageCode(), "yes"),
                  Arrai18n::trl(pl->getLanguageCode(), "no"));
}

}
}
}
