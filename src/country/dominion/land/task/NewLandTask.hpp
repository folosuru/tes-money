#ifndef TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
#define TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
#include <ranges>
#include <SQLiteCpp/SQLiteCpp.h>
#include <AsyncTask/AsyncTaskBase.hpp>
#include <country/dominion/land/ServeLandOrder.hpp>

#include "country/dominion/land/LandArea.hpp"
#include <util/geometry/geometry.hpp>
#include <util/Resources.hpp>
#include <utility>
namespace tes {
class NewLandTask : public AsyncTask::AsyncTaskBase {
public:
    explicit NewLandTask(std::shared_ptr<ServeLandOrder> order, std::int64_t id) : id(id), order(std::move(order)) {}

    void onRun() override {
        SQLite::Database db(getDominionDB());
        {
            SQLite::Statement owner_query(db, "INSERT INTO land_owner (owner, id) VALUES (?,?);");
            owner_query.bind(1, order->owner->name);
            owner_query.bind(2, id);
            owner_query.exec();
        }
        for (const auto& val : order->separate_area | std::views::values) {
            SQLite::Statement area_query(db, "insert into land_area (x1, x2, z1, z2, id) values (?,?,?,?,?);");
            area_query.bind(1, val.min_x);
            area_query.bind(2, val.max_x);
            area_query.bind(3, val.min_z);
            area_query.bind(4, val.max_z);
            area_query.bind(5, id);
            area_query.exec();
        }
    }

    void onComplete() override {}

private:
    std::int64_t id;
    std::shared_ptr<ServeLandOrder> order;
};

}
#endif //TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
