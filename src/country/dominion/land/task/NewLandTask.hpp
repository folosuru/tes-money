#ifndef TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
#define TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
#include <SQLiteCpp/SQLiteCpp.h>
#include <AsyncTask/AsyncTaskBase.hpp>
#include "country/dominion/land/LandArea.hpp"
#include <util/geometry/geometry.hpp>
#include <util/Resources.hpp>
namespace tes {
class NewLandTask : public AsyncTask::AsyncTaskBase {
public:
    explicit NewLandTask(const std::shared_ptr<LandArea>& land) : id(land->id), area(land->area) {}

    void onRun() override {
        SQLite::Database db(getDominionDB());
        SQLite::Statement query(db, "insert into land_area (x1, x2, z1, z2, id) values (?,?,?,?,?);");
        query.bind(1,area.min_x);
        query.bind(2,area.max_x);
        query.bind(3,area.min_z);
        query.bind(4,area.max_z);
        query.bind(5, id);
        query.exec();
    }

    void onComplete() override {}

private:
    int id;
    geometry::Area2D area;
};

}
#endif //TES_SRC_COUNTRY_DOMINION_LAND_TASK_NEWLANDTASK_HPP_
