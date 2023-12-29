#include "Serve.hpp"
#include <unordered_map>
#include <util/geometry/Geometry.hpp>
#include <util/player_identify/PlayerIdentifyProvider.hpp>
#include <memory>
#include <llapi/DynamicCommandAPI.h>
#include <llapi/FormUI.h>
#include <DataManager.hpp>
#include <country/dominion/land/LandManager.hpp>
#include <util/minecraft/message.hpp>

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
    auto IdentifyProvider = DataManager::get()->player_identify;
    auto origin_identify = IdentifyProvider->getIdentify(origin.getName());
    geometry::Point2D current_pos = geometry::Point2D{origin.getPlayer()->getPosition()};
    auto landMng = DataManager::get()->LandMng;

    auto land = DataManager::get()->LandMng->getLandByPos(current_pos);
    if (std::holds_alternative<Types::land_area_ref>(land)) {
        output.error(Arrai18n::trl(origin.getPlayer()->getLanguageCode(),
                     LandManager::getStatusText(LandManager::LandFoundStatus::already_served)));
        return;
    }
    auto land_status = std::get<LandManager::LandFoundStatus>(land);
    if (land_status != LandManager::LandFoundStatus::not_served) {  // 戻り値がLandFoundStatus
        output.error(Arrai18n::trl(origin.getPlayer()->getLanguageCode(),
                     LandManager::getStatusText(land_status)));
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
                auto order = landMng->prepareServe(origin_identify, geometry::Area2D(history->second,current_pos));
                if (std::holds_alternative<ServeLandOrder::ErrorCode>(order)) {
                    output.error(Arrai18n::trl(origin.getPlayer()->getLanguageCode(),
                                               ServeLandOrder::errorCodeToText(std::get<ServeLandOrder::ErrorCode>(order))));
                    return;
                }
                serveConfirmForm(origin.getPlayer(), std::get<std::shared_ptr<ServeLandOrder>>(order));
            } else {
                output.error(Arrai18n::trl(origin.getPlayer()->getLanguageCode(), "dominion.command.serve.before_use_start"));
            }
        }
        default:
            break;
        }
}

void serveConfirmForm(Player* pl, const std::shared_ptr<ServeLandOrder>& order, const std::shared_ptr<LandManager>& land_mng) {
    Form::ModalForm form(Arrai18n::trl(pl->getLanguageCode(),
                                "land.form.serve.title"), // title
                        Arrai18n::trl(pl->getLanguageCode(),
                                "land.form.serve.description",
                                order->Price.getText(),
                                order->area.getWidth(),
                                order->area.getHeight()),
                  Arrai18n::trl(pl->getLanguageCode(), "yes"),
                  Arrai18n::trl(pl->getLanguageCode(), "no"));
    form.sendTo(pl, [order, land_mng](Player* player, bool cond) {
        if (auto status = order->canServe(); status != ServeLandOrder::ErrorCode::None) {
            // send error description
            return;
        } else {
            auto id = land_mng->serve(order);
            util::sendTrlText(player, {"land.serve.complete", {std::to_string(id)}});
        }
    });
}

}
}
}
