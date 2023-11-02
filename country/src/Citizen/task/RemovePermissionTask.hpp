#pragma once
#ifndef TES_COUNTRY_SRC_CITIZEN_TASK_REMOVEPERMISSIONTASK_HPP_
#define TES_COUNTRY_SRC_CITIZEN_TASK_REMOVEPERMISSIONTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <permission/Perimission.hpp>
#include <types/GeneralTypes.hpp>
#include <string>
#include <utility>
namespace tes {
class RemovePermissionTask : public AsyncTask::AsyncTaskBase {
public:
    RemovePermissionTask(std::string name_, Permission permission)
        : name(std::move(name_)), permission_name(permission) {}

    void onRun() override {
        SQLite::Database db(country_db_file,
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query1(db,
                                 "DELETE FROM citizen_permission where name = ? and permission = ?");
        query1.bind(1, name);
        query1.bind(2, permission_name);
        query1.exec();
    }

    void onComplete() override {}

private:
    Types::player_name name;
    std::string permission_name;
};


}
#endif //TES_COUNTRY_SRC_CITIZEN_TASK_REMOVEPERMISSIONTASK_HPP_
