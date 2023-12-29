#ifndef TES_SRC_DOMINION_EVENT_HPP_
#define TES_SRC_DOMINION_EVENT_HPP_
#include <country/dominion/DominionManager.hpp>
#include <util/player_identify/PlayerIdentify.hpp>

namespace tes::dominion {
void init();

/**
 * \brief ブロック壊したときに出すやつ
 * \return 破壊する場所が自分のじゃない土地だった場合にfalse
 */
bool onBreak(const PlayerIdentify&, const std::shared_ptr<DominionManager>&, geometry::Point2D);

void commandInit();
}

#ifndef DEBUG_WITHOUT_LLAPI
#include <llapi/EventAPI.h>

namespace tes::dominion {
/**
 * cancel if in land
 * @return
 */
inline bool onBreak(const Event::PlayerDestroyBlockEvent& event) {
    auto block_pos = const_cast<BlockInstance&>(event.mBlockInstance).getPosition();
    return onBreak(DataManager::get()->player_identify->getIdentifyByPlayer(event.mPlayer),
                   DataManager::get()->DominionMng,
                   {block_pos.x, block_pos.z});
}
}
#endif

#endif //TES_SRC_DOMINION_EVENT_HPP_
