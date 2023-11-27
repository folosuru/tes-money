#ifndef TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP
#define TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP
#include "PlayerIdentify.hpp"
#include <unordered_map>
#include <string_view>
#ifndef DEBUG_WITHOUT_LLAPI
#include <llapi/mc/Player.hpp>
#include <llapi/mc/CommandOrigin.hpp>
#endif
namespace tes {
class PlayerIdentifyProvider {
public:
    PlayerIdentifyProvider() = default;

    static std::shared_ptr<PlayerIdentifyProvider> get();

#ifndef DEBUG_WITHOUT_LLAPI
    template<class T>
    PlayerIdentify getIdentifyByPlayer(T& pl) {
        return getIdentify(pl.getName());
    }

    template<class T>
    PlayerIdentify getIdentifyByPlayer(T* pl) {
        return getIdentify(pl->getRealName());
    }
#endif

    PlayerIdentify getIdentify(const std::string&);

private:
    static inline std::shared_ptr<PlayerIdentifyProvider> instance;
    std::unordered_map<std::string_view, PlayerIdentify> identify;
};
}
#endif  // TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP