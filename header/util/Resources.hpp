#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

namespace tes {
namespace resource {
inline const std::string resource_directory{"plugins/tes/resource/"};
inline const std::string country_data_directory{"plugins/tes/country/"};
}

const inline std::string country_db_file = resource::country_data_directory + "country.sqlite";

void init_Database();

/**
 * delete all data in DB.
 * Do not use without debug...
 */
void reset_Database();

SQLite::Database getCountryDB();

}
#endif  // TES_COUNTRY_HEADER_COUNTRY_UTIL_RESOURCES_HPP_
