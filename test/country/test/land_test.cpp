#include "land_test.hpp"

#include <country/dominion/Dominion.hpp>
#include <country/dominion/land/LandManager.hpp>
#include <cpptf/Cpptf.hpp>
namespace land_test_ns {
void save_and_load() {
}

void serve() {
    cpptf::isSame("not_dominion", tes::ServeLandOrder::ErrorCode::ContainNotCountryDominion, []() {
        auto dominion = std::make_shared<tes::DominionManager>();
        auto land_mng = tes::LandManager(*dominion);
        return std::get<1>(land_mng.prepareServe(tes::PlayerIdentify(), tes::geometry::Area2D{1,5,-1,-5}));
    }());
    auto dominion = std::make_shared<tes::DominionManager>();
    auto country  = std::make_shared<tes::Country>("JP", 1);
    tes::geometry::Area2D serve_area{15,20,45,60};
    tes::PlayerIdentify player_foo = tes::PlayerIdentify(new tes::PlayerIdentifyClass("foo"));
    tes::Types::Land_id_t first_serve_land_id;
    {
        auto land_mng = std::make_shared<tes::LandManager>(*dominion);
        {
            tes::DominionIndex index{0,0};
            dominion->serve(country, index);
            auto i = land_mng->prepareServe(player_foo, serve_area);
            first_serve_land_id = land_mng->serve(std::get<0>(i));
            auto dominion_land = dominion->get(index).value()->land;
            cpptf::isTrue("access from dominion_land #1 ", [=]() -> bool{
                auto& land = dominion_land->getLand({25,31}).value().get();
                return land.id == first_serve_land_id;
            }());
            cpptf::isTrue("access from dominion_land #2", [=]() -> bool{
                auto& land = dominion_land->getLand(serve_area.getEndPos()).value().get();
                return land.id == first_serve_land_id;
            }());
            cpptf::isTrue("access from dominion_land #3", [=]() -> bool{
                auto& land = dominion_land->getLand(serve_area.getStartPos()).value().get();
                return land.id == first_serve_land_id;
            }());

            cpptf::isTrue("access from LandManager #1", [=]() -> bool{
                auto land = land_mng->getLandByPos(serve_area.getStartPos());
                return std::get<tes::Types::land_area_ref>(land).get().land.id == first_serve_land_id;
            }());
            cpptf::isTrue("access unknown in land_mng", [=]() -> bool{
                auto land = dominion_land->getLand(80,80);
                return land == std::nullopt;
            });
        }
        cpptf::isSame("already served land",tes::ServeLandOrder::ErrorCode::ServedLand,
            [land_mng, player_foo] {
                tes::geometry::Area2D serve_area{16, 27, 32, 40};
                auto i = land_mng->prepareServe(player_foo, serve_area);
                return std::get<tes::ServeLandOrder::ErrorCode>(i);
        });
        cpptf::isSame("not served dominion",tes::ServeLandOrder::ErrorCode::ContainNotCountryDominion,
                      [land_mng, player_foo] {
            tes::geometry::Area2D serve_area{10, 10, -30, -40};
            auto i = land_mng->prepareServe(player_foo, serve_area);
            return std::get<tes::ServeLandOrder::ErrorCode>(i);
        });
        {
            dominion->serve(country, {-1,0});
            dominion->serve(country, {0,-1});
            dominion->serve(country, {-1,-1});
            tes::geometry::Area2D serve_area_mluti{-15,-30,12,19};
            auto i = land_mng->prepareServe(player_foo, serve_area_mluti);
            auto serve_land_id = land_mng->serve(std::get<0>(i));
            cpptf::isTrue("Land in mluti dominion #1", [=]() -> bool{
                auto& land = std::get<0>(land_mng->getLandByPos(serve_area_mluti.getStartPos())).get();
                return land.id == serve_land_id;
            });
            cpptf::isTrue("Land in mluti dominion #2", [=]() -> bool{
                auto& land = std::get<0>(land_mng->getLandByPos(serve_area_mluti.getEndPos())).get();
                return land.id == serve_land_id;
            });
            cpptf::isTrue("Land in mluti dominion #3", [=]() -> bool{
                auto& land = std::get<0>(land_mng->getLandByPos({-5,-5})).get();
                return land.id == serve_land_id;
            });
            cpptf::isTrue("Land in mluti dominion #4", [=]() -> bool{
                auto& land = std::get<0>(land_mng->getLandByPos({5,-5})).get();
                return land.id == serve_land_id;
            });
            cpptf::isTrue("Land in mluti dominion #5", [=]() -> bool{
                auto& land = std::get<0>(land_mng->getLandByPos({-5,5})).get();
                return land.id == serve_land_id;
            });
        }
    }
    {
        auto country_mng = std::make_shared<tes::CountryManager>();
        country_mng->addCountry(std::make_shared<tes::Country>("JP", 1));
        auto new_dominion = tes::DominionManager::load(country_mng);
        auto land_mng = std::make_shared<tes::LandManager>(*new_dominion);
        land_mng->loadFromDB(std::make_shared<tes::PlayerIdentifyProvider>());
        cpptf::isTrue("Load from DB #1", [=]() -> bool{
            auto land = land_mng->getLandByPos(serve_area.getStartPos());
            return std::get<tes::Types::land_area_ref>(land).get().land.id == first_serve_land_id;
        }());
    }
}
}
