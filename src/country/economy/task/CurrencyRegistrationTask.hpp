#ifndef TES_SRC_COUNTRY_ECONOMY_TASK_CURRENCYREGISTRATIONTASK_HPP_
#define TES_SRC_COUNTRY_ECONOMY_TASK_CURRENCYREGISTRATIONTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <country/CountryManager.hpp>
#include <types/MoneyTypes.hpp>
#include <utility>

namespace tes::task {

class CurrencyRegistrationTask : public AsyncTask::AsyncTaskBase {
public:
    CurrencyRegistrationTask(std::string currency, CountryManager::country_id id)
        : currency(currency), country_id(id) {}

    void onRun() override {
        SQLite::Database db = getCountryDB();
        SQLite::Statement query1(db,"update country SET currency = ? where id = ?;");
        query1.bind(1, currency);
        query1.bind(2, country_id);
        query1.exec();
    }

    void onComplete() override {}

private:
    std::string currency;

    CountryManager::country_id country_id;
};
}
#endif //TES_SRC_COUNTRY_ECONOMY_TASK_CURRENCYREGISTRATIONTASK_HPP_
