#include <misc/PermissionManager.hpp>

namespace tes {
Permission PermissionManager::getSv(const std::string& name) {
    if (!keys.contains(name)) {
        std::shared_ptr<std::string> new_key = std::make_shared<std::string>(name);
        key_original.push_back(new_key);
        keys.insert({name, std::string_view{new_key->begin(), new_key->end()}});
    }
    return keys.at(name);
}
}
