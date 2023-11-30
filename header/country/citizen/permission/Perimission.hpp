#pragma once
#ifndef TES_HEADER_COUNTRY_CITIZEN_PERIMISSION_HPP_
#define TES_HEADER_COUNTRY_CITIZEN_PERIMISSION_HPP_
#include <string>
namespace tes {
typedef std::string_view Permission;

namespace country_permission {
const inline std::string currency = "currency";
const inline std::string any = "any";
}
}

#endif  // TES_HEADER_COUNTRY_CITIZEN_PERIMISSION_HPP_
