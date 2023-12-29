#ifndef LAND_TEST_HPP
#define LAND_TEST_HPP
#include <cpptf/Cpptf.hpp>

namespace land_test_ns {
void save_and_load();

void serve();
}


inline void land_test() {
    using namespace land_test_ns;
    cpptf::change_section("Land");
    serve();
}

#endif //LAND_TEST_HPP
