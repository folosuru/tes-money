#pragma once
#ifndef DEBUG_WITHOUT_LLAPI
#ifndef TES_SRC_COUNTRY_EVENT_HPP_
#define TES_SRC_COUNTRY_EVENT_HPP_
#include <llapi/EventAPI.h>

namespace tes {
namespace country {
void init();

/**
 * Add Money if trigger set
 * @return
 */
bool onBreak(const Event::PlayerDestroyBlockEvent&);

namespace command {
void init_command();
}
}
}
#endif //TES_SRC_COUNTRY_EVENT_HPP_
#endif
