#include "Event.hpp"
#include <DataManager.hpp>
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
    std::shared_ptr<Citizen> citizen = data->CitizenRefer->get(event.mPlayer->getRealName());
    if (!citizen) {
        return true;
    }
    citizen->getCountry()->economy->runTrigger(trigger.value(), citizen->name);
    return true;
}
}
}