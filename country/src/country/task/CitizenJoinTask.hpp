#pragma once
#ifndef TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENJOINTASK_HPP_
#define TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENJOINTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <manager/CountryManager.hpp>
#include <utility>
namespace tes {

class CitizenJoinTask : public AsyncTask::AsyncTaskBase {
public:
    CitizenJoinTask(std::string name, CountryManager::country_id id)
        : target_name(std::move(name)), country_id(id) {}

    void onRun() override {
        SQLite::Database db(country_db_file,
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        db.exec("CREATE TABLE IF NOT EXISTS citizen (name string, country int);");
        SQLite::Statement query1(db,
                                 "insert into citizen(name, country)  VALUES (?,?)");
        query1.bind(1, target_name);
        query1.bind(2, country_id);
        query1.exec();
    }

    void onComplete() override {}

private:
    std::string target_name;
    CountryManager::country_id country_id;
};
}  // tes
#endif  // TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENJOINTASK_HPP_
