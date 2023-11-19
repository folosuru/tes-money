#include "Event.hpp"
#include <DataManager.hpp>
#include <util/player_identify/PlayerIdentifyProvider.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/Block.hpp>

namespace tes{
namespace country {
bool onBreak(const Event::PlayerDestroyBlockEvent& event) {
    Block* block = const_cast<BlockInstance&>(event.mBlockInstance).getBlock();
    std::shared_ptr<DataManager> data = DataManager::get();
    auto trigger = data->MoneyAddTriggerMng->getTriggerOnBreak(block->getId(),block->getTileData());
    if (!trigger) {
        return true;
    }
    PlayerIdentify player = PlayerIdentifyProvider::get()->getIdentifyByPlayer(event.mPlayer);
    std::shared_ptr<Citizen> citizen = data->CitizenRefer->get(player);
    std::shared_ptr<PlayerMoney> money = data->PlayerMoneyMng->getPlayer(player);
    if ((!citizen) || (!money)) {
        return true;
    }
    citizen->getCountry()->economy->runTrigger(trigger.value(), money);
    return true;
}
}
}