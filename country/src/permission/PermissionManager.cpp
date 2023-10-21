#include <permission/PermissionManager.hpp>

namespace tes {
Permission PermissionManager::getSv(const std::string& name) {
    if (!keys.contains(name)) {
        keys.insert({name,std::string_view{name.begin(), name.end()}});
    }
    return keys.at(name);
}

}