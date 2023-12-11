#include <country/dominion/DominionManager.hpp>
#include <country/dominion/Dominion.hpp>
#include <iostream>
void dominionRange_test() {
    auto country = std::make_shared<tes::Country>("country",1);
    tes::DominionManager mng{};
    mng.serve(country,{1,1});
    mng.serve(country,{-1,1});
    mng.serve(country,{1,-1});
    mng.serve(country,{-1,-1});
    for (const auto& i : mng.getRange({-1,-1},{1,1})) {
        std::cout <<  i.value()->country.lock()->getName() << std::endl;
    }
}
