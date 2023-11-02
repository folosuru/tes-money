#pragma once
#ifndef TES_COUNTRY_COUNTRY_HEADER_CITIZEN_PERIMISSION_HPP_
#define TES_COUNTRY_COUNTRY_HEADER_CITIZEN_PERIMISSION_HPP_
#include <string>
namespace tes {
typedef std::string_view Permission;

namespace country_permission {
constexpr inline std::string currency = "currency";
}
}

#endif  // TES_COUNTRY_COUNTRY_HEADER_CITIZEN_PERIMISSION_HPP_
