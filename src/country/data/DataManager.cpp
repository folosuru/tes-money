#include <DataManager.hpp>

namespace tes {

DataManager::DataManager() :
    CountryManager(CountryManager::build()),
    PermissionManager(std::make_shared<tes::PermissionManager>()),
    CitizenRefer(std::make_shared<tes::CitizenRefer>(CountryManager,
                                                     PermissionManager)),
    MoneyAddTriggerMng(std::make_shared<MoneyAddTriggerManager>()) {

}

std::shared_ptr<DataManager> DataManager::get() {
    if (instance == nullptr) {
        instance = std::shared_ptr<DataManager>(new DataManager());
    }
    return instance;
}
}