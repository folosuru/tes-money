#include "PlayerIdentify.hpp"
#include <unordered_map>
#include <string_view>
namespace tes {
class PlayerIdentifyProvider {
public:
    static std::shared_ptr<PlayerIdentifyProvider> get();

    PlayerIdentify getIdentify(const std::string&);

private:
    PlayerIdentifyProvider() = default;
    static std::shared_ptr<PlayerIdentifyProvider> instance;
    std::unordered_map<std::string_view, PlayerIdentify> identify;
};
}