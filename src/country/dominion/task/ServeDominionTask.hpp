#ifndef TES_SRC_COUNTRY_DOMINION_TASK_SERVEDOMINIONTASK_HPP_
#define TES_SRC_COUNTRY_DOMINION_TASK_SERVEDOMINIONTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>

namespace tes {

class ServeDominionTask : public AsyncTask::AsyncTaskBase {
public:
    explicit ServeDominionTask(int x, int z, int country, int id) : x(x), z(z), country(country), id(id) {}

    void onRun() override {
        SQLite::Database db(getDominionDB());
        SQLite::Statement query1(db, "insert into dominion (x, z, country, id) values (?,?,?,?);");
        query1.bind(1, x);
        query1.bind(2, z);
        query1.bind(3, country);
        query1.bind(4, id);
        query1.exec();
    }

    void onComplete() override {}

private:
    int x, z, country, id;
};
}
#endif //TES_SRC_COUNTRY_DOMINION_TASK_SERVEDOMINIONTASK_HPP_
