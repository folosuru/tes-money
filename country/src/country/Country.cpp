#include <country/Country.hpp>
#include <memory>
namespace tes {
Country::Country(std::string name_,
                 CountryManager::country_id id_)
    : name(std::move(name_)),
      citizen(std::make_shared<CitizenManager>()),
      id(id_){
}
}