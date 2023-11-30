#ifndef TES_SRC_COUNTRY_COUNTRYMANAGER_TASK_COUNTRYCREATETASK_HPP_
#define TES_SRC_COUNTRY_COUNTRYMANAGER_TASK_COUNTRYCREATETASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <utility>

namespace tes {

class CountryCreateTask : public AsyncTask::AsyncTaskBase {
public:
    explicit CountryCreateTask(std::string name, int id) : name(std::move(name)), id(id) {}

    void onRun() override {
        SQLite::Database db(getCountryDB());
        SQLite::Statement query(db,
                                "insert into country (id, name) values (?,?);");
        query.bind(1, id);
        query.bind(2, name);
        query.exec();
    }

    void onComplete() override {}

private:
    std::string name;

    int id;
};
}  // tes
#endif //TES_SRC_COUNTRY_COUNTRYMANAGER_TASK_COUNTRYCREATETASK_HPP_
