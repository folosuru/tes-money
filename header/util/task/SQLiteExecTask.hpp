#ifndef TES_HEADER_UTIL_TASK_SQLITEEXECTASK_HPP_
#define TES_HEADER_UTIL_TASK_SQLITEEXECTASK_HPP_
#include <AsyncTask/AsyncTaskBase.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <string>
#include <utility>
#include <functional>
#include <tuple>

namespace tes {

template<class... Args>
class SQLiteExecTask : public AsyncTask::AsyncTaskBase {
public:
    explicit SQLiteExecTask(std::function<SQLite::Database()> db, std::string statement, Args... args_) :
    db_func(std::move(db)), statement(std::move(statement)), args({args_...}) {}

    void onRun() override {
        SQLite::Database db = db_func();
        SQLite::Statement query(db, statement);
        bind_all(query);
        query.exec();
    }

    void onComplete() override {}

private:
    std::function<SQLite::Database()> db_func;
    std::string statement;
    std::tuple<Args...> args;

    template <size_t N = 0> void bind_all(SQLite::Statement& query) {
        if constexpr(N < std::tuple_size<std::tuple<Args...>>::value) {
            query.bind(N + 1, std::get<N>(args));
            bind_all<N + 1>(query);
        }
    }
};
}  // tes
#endif //TES_HEADER_UTIL_TASK_SQLITEEXECTASK_HPP_
