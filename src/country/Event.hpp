#pragma once
#ifndef TES_SRC_COUNTRY_EVENT_HPP_
#define TES_SRC_COUNTRY_EVENT_HPP_
#include <llapi/EventAPI.h>
namespace tes {
namespace country {
/**
 * Add Money if trigger set
 * @return
 */
bool onBreak(const Event::PlayerDestroyBlockEvent&);
}
}

#endif //TES_SRC_COUNTRY_EVENT_HPP_