#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_
#include <string>
namespace tes {
    const inline std::string country_db_file = "country.sqlite";

    void init_Database();
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_