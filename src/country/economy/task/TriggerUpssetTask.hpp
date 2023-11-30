#pragma once
#ifndef TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERUPSSETTASK_HPP_
#define TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERUPSSETTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <country/CountryManager.hpp>
#include <types/MoneyTypes.hpp>
#include <utility>

namespace tes::task {

class TriggerUpsertTask : public AsyncTask::AsyncTaskBase {
public:
    TriggerUpsertTask(std::string_view trigger, Types::money_value_t add_value, CountryManager::country_id id)
        : trigger(trigger), add_value(add_value), country_id(id) {}

    void onRun() override {
        SQLite::Database db = getCountryDB();
        SQLite::Statement query1(db,
                                 "insert INTO country_money_trigger (trigger, add_value, country) VALUES (?1, ?2, ?3)"
                                 "on conflict(country,trigger) DO UPDATE SET add_value = ?2");
        query1.bind(1, std::string(trigger));
        query1.bind(2, add_value);
        query1.bind(3, country_id);
        query1.exec();
    }

    void onComplete() override {}

private:
    std::string_view trigger;

    Types::money_value_t add_value;

    CountryManager::country_id country_id;
};
}  // tes
#endif //TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERUPSSETTASK_HPP_
