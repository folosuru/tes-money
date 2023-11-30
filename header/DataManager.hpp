/**
 * Use this to get data
 */
#ifndef TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
#include <memory>
#include <country/CountryManager.hpp>
#include <country/citizen/CitizenRefer.hpp>
#include <currency/CurrencyManager.hpp>
#include <money/player/PlayerManager.hpp>
#include <util/player_identify/PlayerIdentifyProvider.hpp>
#include <misc/PermissionManager.hpp>
#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>

namespace tes {
class PermissionManager;
class CitizenRefer;
class CountryManager;
class CurrencyManager;
class MoneyAddTriggerManager;
class PlayerManager;
class PlayerIdentifyProvider;
class DataManager : public std::enable_shared_from_this<DataManager> {
public:
    static std::shared_ptr<DataManager> get();

    const std::shared_ptr<PlayerIdentifyProvider> player_identify;

    const std::shared_ptr<MoneyAddTriggerManager> MoneyAddTriggerMng;

    const std::shared_ptr<CurrencyManager> CurrencyMng;

    const std::shared_ptr<PlayerManager> PlayerMoneyMng;

    const std::shared_ptr<CountryManager> CountryManager;

    const std::shared_ptr<PermissionManager> PermissionManager;

    const std::shared_ptr<CitizenRefer> CitizenRefer;

private:
    DataManager();

    static inline std::shared_ptr<DataManager> instance;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_DATAMANAGER_HPP_
