#include <DataManager.hpp>

namespace tes {

DataManager::DataManager() :
    MoneyAddTriggerMng(std::make_shared<MoneyAddTriggerManager>()),
    CurrencyMng(CurrencyManager::get()),
    CountryManager(CountryManager::build(MoneyAddTriggerMng, CurrencyMng)),
    PermissionManager(std::make_shared<tes::PermissionManager>()),
    CitizenRefer(std::make_shared<tes::CitizenRefer>(CountryManager,
                                                     PermissionManager))
     {

}

std::shared_ptr<DataManager> DataManager::get() {
    if (instance == nullptr) {
        instance = std::shared_ptr<DataManager>(new DataManager());
    }
    return instance;
}
}