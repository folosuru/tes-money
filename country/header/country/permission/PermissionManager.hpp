#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_PERMISSION_PERMISSIONMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_PERMISSION_PERMISSIONMANAGER_HPP_
#include <string>
#include <unordered_map>
#include "Perimission.hpp"
namespace tes {
class PermissionManager {
public:
    PermissionManager() = default;
    Permission getSv(const std::string& name);
private:
    std::unordered_map<std::string, Permission> keys;
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_PERMISSION_PERMISSIONMANAGER_HPP_
