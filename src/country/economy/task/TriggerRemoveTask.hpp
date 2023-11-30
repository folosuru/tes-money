#pragma once
#ifndef TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERREMOVETASK_HPP_
#define TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERREMOVETASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <country/CountryManager.hpp>
#include <utility>

namespace tes::task {

class TriggerRemoveTask : public AsyncTask::AsyncTaskBase {
public:
    TriggerRemoveTask(std::string_view trigger, CountryManager::country_id id)
        : trigger(trigger), country_id(id) {}

    void onRun() override {
        SQLite::Database db = getCountryDB();
        SQLite::Statement query1(db,
                                 "delete FROM country_money_trigger WHERE country = ? and trigger = ?;");
        query1.bind(1, country_id);
        query1.bind(2, std::string(trigger));
        query1.exec();
    }

    void onComplete() override {}

private:
    std::string_view trigger;

    CountryManager::country_id country_id;
};
}  // tes
#endif //TES_SRC_COUNTRY_ECONOMY_TASK_TRIGGERREMOVETASK_HPP_
