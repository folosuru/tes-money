#ifndef TES_SRC_MONEY_EVENT_HPP_
#define TES_SRC_MONEY_EVENT_HPP_
#ifndef DEBUG_WITHOUT_LLAPI
#include <llapi/EventAPI.h>

namespace tes {
namespace money {
void init();

void onServerStop(const Event::ServerStoppedEvent& event);

bool onPlayerJoin(const Event::PlayerJoinEvent& event);
}
}
#endif
#endif //TES_SRC_MONEY_EVENT_HPP_
