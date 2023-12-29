#include <country/dominion/DominionManager.hpp>
#include <country/dominion/Dominion.hpp>
#include <iostream>
#include <cpptf/Cpptf.hpp>


void dominionRange_test() {
    {
        auto country = std::make_shared<tes::Country>("country",1);
        auto mng = std::make_shared<tes::DominionManager>();
        mng->serve(country,{1,1});
        cpptf::isSame("range_iter", 1, [&mng]() {
            int count = 0;
            for (const auto& i : mng->getRange({1,1},{1,1})) {
               count++;
            }
            return count;
        }());
        cpptf::isSame("range_iter", 4, [&mng]() {
            int count = 0;
            for (const auto& i : mng->getRange({-1,-1},{0,0})) {
               count++;
            }
            return count;
        }());
    }

}
void PosToIndex_test() {
    cpptf::isSame("convert index #1", 0, tes::convertIndex(0));
    cpptf::isSame("convert index #2", 0, tes::convertIndex(10));
    cpptf::isSame("convert index #3", 0, tes::convertIndex(99));
    cpptf::isSame("convert index #4", 1, tes::convertIndex(100));
    cpptf::isSame("convert index #5", -1, tes::convertIndex(-1));
    cpptf::isSame("convert index #6", -1, tes::convertIndex(-10));
    cpptf::isSame("convert index #7", -2, tes::convertIndex(-100));
}
void serve_test() {
    cpptf::isTrue("serve", []() {
        auto dominion = std::make_shared<tes::DominionManager>();
        tes::DominionIndex index{1,1};
        dominion->serve(std::make_shared<tes::Country>("JP", 1), index);
        return dominion->get(index).has_value();
    }());
}
void dominionArea_test() {
    cpptf::Section& section = cpptf::Section::create("dominion area");
    {
        cpptf::TestPattern conv_test(section, "convert index to pos");
        auto test_func = [&conv_test](int value) {
            conv_test.isSame(tes::convertIndex(tes::convertIndexToPosMin(tes::convertIndex(value))), tes::convertIndex(value));
            conv_test.isSame(tes::convertIndex(tes::convertIndexToPosMax(tes::convertIndex(value))), tes::convertIndex(value));
        };
        test_func(0);
        test_func(1);

        test_func(-1);
        test_func(-99);
        test_func(-100);
        test_func(-101);
        test_func(99);
        test_func(100);
        test_func(-199);
        test_func(-200);
        test_func(101);
        test_func(199);
        test_func(200);
    }
}


