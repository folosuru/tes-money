#ifndef TES_HEADER_PLAYER_PLAYER
#define TES_HEADER_PLAYER_PLAYER
#include <memory>
#include <string>

namespace tes {
class PlayerIdentifyClass;
using PlayerIdentify = std::shared_ptr<PlayerIdentifyClass>;

class PlayerIdentifyClass {
public:
    const std::string name;

private:
    PlayerIdentifyClass(const PlayerIdentifyClass&) = delete;

    PlayerIdentifyClass& operator=(const PlayerIdentifyClass&) = delete;

    PlayerIdentifyClass() = delete;

    explicit PlayerIdentifyClass(std::string name_) : name(name_) {};

    friend class PlayerIdentifyProvider;
};
}

#endif // TES_HEADER_PLAYER_PLAYER
