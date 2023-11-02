/**
 * Use this to get data
 */
#ifndef TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
#include <memory>
#include "manager/CountryManager.hpp"
#include "manager/CitizenRefer.hpp"
#include "permission/PermissionManager.hpp"
namespace tes {
class DataManager : public std::enable_shared_from_this<DataManager>{
public:
    static std::shared_ptr<DataManager> get();

    const std::shared_ptr<PermissionManager> PermissionManager;

    const std::shared_ptr<CitizenRefer> CitizenRefer;

    const std::shared_ptr<CountryManager> CountryManager;

private:
    DataManager();
    static inline std::shared_ptr<DataManager> manager;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
