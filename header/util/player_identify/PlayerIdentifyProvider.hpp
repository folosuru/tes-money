#ifndef TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP
#define TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP
#include "PlayerIdentify.hpp"
#include <unordered_map>
#include <string_view>
#include <llapi/mc/Player.hpp>
namespace tes {
class PlayerIdentifyProvider {
public:
    static std::shared_ptr<PlayerIdentifyProvider> get();

#ifndef DEBUG_WITHOUT_LLAPI
    template<class T>
    PlayerIdentify getIdentifyByPlayer(T&);
    template<class T>
    PlayerIdentify getIdentifyByPlayer(T*);
#endif

    PlayerIdentify getIdentify(const std::string&);

private:
    PlayerIdentifyProvider() = default;
    static std::shared_ptr<PlayerIdentifyProvider> instance;
    std::unordered_map<std::string_view, PlayerIdentify> identify;
};
}
#endif  // TES_UTIL_PLAYERIDENTIFYPROVIDER_HPP