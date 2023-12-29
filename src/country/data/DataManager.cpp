#include <DataManager.hpp>
#include <country/dominion/DominionManager.hpp>
#include <country/dominion/land/LandManager.hpp>

namespace tes {

DataManager::DataManager() :
    player_identify(PlayerIdentifyProvider::get()),
    MoneyAddTriggerMng(std::make_shared<MoneyAddTriggerManager>()),
    CurrencyMng(CurrencyManager::load()),
    PlayerMoneyMng(PlayerManager::load(CurrencyMng, player_identify)),
    CountryManager(CountryManager::build(MoneyAddTriggerMng, CurrencyMng)),
    PermissionManager(std::make_shared<tes::PermissionManager>()),
    CitizenRefer(CitizenRefer::load(CountryManager,
                                    PermissionManager,
                                    player_identify)),
    DominionMng(DominionManager::load(CountryManager)),
    LandMng(LandManager::load(*DominionMng, player_identify)){
    MoneyAddTriggerMng->load();
}

std::shared_ptr<DataManager> DataManager::get() {
    if (instance == nullptr) {
        instance = std::shared_ptr<DataManager>(new DataManager());
    }
    return instance;
}
}
