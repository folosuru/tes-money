#include <memory>
#include <util/player_identify/PlayerIdentifyProvider.hpp>

namespace tes {
std::shared_ptr<PlayerIdentifyProvider> PlayerIdentifyProvider::get() {
    if (!instance) {
        instance = std::make_shared<PlayerIdentifyProvider>();
    }
    return instance;
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
}
