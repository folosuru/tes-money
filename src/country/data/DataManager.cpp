#include <DataManager.hpp>

namespace tes {

DataManager::DataManager() :
    player_identify(PlayerIdentifyProvider::get()),
    MoneyAddTriggerMng(std::make_shared<MoneyAddTriggerManager>()),
    CurrencyMng(CurrencyManager::load()),
    CountryManager(CountryManager::build(MoneyAddTriggerMng, CurrencyMng)),
    PermissionManager(std::make_shared<tes::PermissionManager>()),
    CitizenRefer(CitizenRefer::load(CountryManager,
                                    PermissionManager,
                                    player_identify))
     {}

std::shared_ptr<DataManager> DataManager::get() {
    if (instance == nullptr) {
        instance = std::shared_ptr<DataManager>(new DataManager());
    }
    return instance;
}
}