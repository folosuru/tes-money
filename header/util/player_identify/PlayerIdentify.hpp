#ifndef TES_HEADER_PLAYER_PLAYER
#define TES_HEADER_PLAYER_PLAYER
#include <memory>
#include <string>
#include <utility>

namespace tes {
class PlayerIdentifyClass;
using PlayerIdentify = std::shared_ptr<PlayerIdentifyClass>;

class PlayerIdentifyClass {
public:
    const std::string name;

    PlayerIdentifyClass(const PlayerIdentifyClass&) = delete;

    PlayerIdentifyClass& operator=(const PlayerIdentifyClass&) = delete;

    PlayerIdentifyClass() = delete;

private:
    explicit PlayerIdentifyClass(std::string name_) : name(std::move(name_)) {};

    friend class PlayerIdentifyProvider;
};
}

#endif // TES_HEADER_PLAYER_PLAYER
