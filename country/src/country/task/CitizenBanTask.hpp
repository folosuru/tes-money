#pragma once
#ifndef TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENBANTASK_HPP_
#define TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENBANTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <utility>
namespace tes {

class CitizenBanTask : public AsyncTask::AsyncTaskBase {
public:
    explicit CitizenBanTask(std::string name)  : target_name(std::move(name)) {}

    void onRun() override {
        SQLite::Database db(country_db_file,
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query1(db,
                                 "delete FROM citizen WHERE name = ?;");
        query1.bind(1, target_name);
        query1.exec();
        SQLite::Statement query2(db,
                                 "delete from citizen_permission where name = ?;");
        query2.bind(1, target_name);
        query2.exec();
    }

    void onComplete() override {}

private:
    std::string target_name;
};
}  // tes
#endif  // TES_COUNTRY_SRC_COUNTRY_TASK_CITIZENBANTASK_HPP_
