#pragma once
#ifndef TES_COUNTRY_SRC_CITIZEN_TASK_PERMISSIONADDTASK_HPP_
#define TES_COUNTRY_SRC_CITIZEN_TASK_PERMISSIONADDTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <country/citizen/permission/Perimission.hpp>
#include <string>
#include <utility>
#include <types/GeneralTypes.hpp>
namespace tes {

class AddPermissionTask : public AsyncTask::AsyncTaskBase {
public:
    AddPermissionTask(std::string name_, Permission permission)
        : name(std::move(name_)), permission_name(permission) {}

    void onRun() override {
        SQLite::Database db(country_db_file,
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query1(db,
                                 "INSERT INTO citizen_permission (name,permission) VALUES (?,?)"
                                 "ON CONFLICT(name,permission) DO NOTHING");
        query1.bind(1, name);
        query1.bind(2, permission_name);
        query1.exec();
    }

    void onComplete() override {}

private:
    Types::player_name name;
    std::string permission_name;
};
}  // tes
#endif  // TES_COUNTRY_SRC_CITIZEN_TASK_PERMISSIONADDTASK_HPP_
