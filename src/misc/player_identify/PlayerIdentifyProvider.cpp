#include <util/player_identify/PlayerIdentifyProvider.hpp>

namespace tes {
std::shared_ptr<PlayerIdentifyProvider> PlayerIdentifyProvider::get() {
    if (!PlayerIdentifyProvider::instance) {
        PlayerIdentifyProvider::instance = std::shared_ptr<PlayerIdentifyProvider>(new PlayerIdentifyProvider());
    }
    return PlayerIdentifyProvider::instance;
}

PlayerIdentify PlayerIdentifyProvider::getIdentify(const std::string& name) {
    auto iter = this->identify.find(name);
    if (iter != this->identify.end()) {
        return (*iter).second;
    }
    PlayerIdentify new_identify{new PlayerIdentifyClass(name)};
    this->identify.insert({{new_identify->name.begin(), new_identify->name.end()}, new_identify});
    return new_identify;
}
#ifndef DEBUG_WITHOUT_LLAPI
template<class T>
PlayerIdentify PlayerIdentifyProvider::getIdentifyByPlayer(T& pl) {
    return getIdentify(pl.getRealName());
}
template<class T>
PlayerIdentify PlayerIdentifyProvider::getIdentifyByPlayer(T* pl) {
    return getIdentify(pl->getRealName());
}
#endif
}
