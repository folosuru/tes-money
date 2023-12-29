#ifndef DEBUG_WITHOUT_LLAPI
#ifndef TES_SRC_DOMINION_EVENT_HPP_
#define TES_SRC_DOMINION_EVENT_HPP_
#include <llapi/EventAPI.h>
namespace tes {
namespace dominion {
void init();

/**
 * cancel if in land
 * @return
 */
bool onBreak(const Event::PlayerDestroyBlockEvent&);

void commandInit();

}
}

#endif //TES_SRC_DOMINION_EVENT_HPP_
#endif
