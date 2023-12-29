#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cpptf/Cpptf.hpp>
#include <util/geometry/geometry.hpp>

int main() {
    cpptf::Section& area_test = cpptf::Section::create("Area2d");
    cpptf::TestPattern duplicate_test(area_test, "duplicate test");
    duplicate_test.isSame(tes::geometry::Area2D{{-10,-10},{10,10}}, [] {
        return tes::geometry::Area2D{{100,-100}, {-10,10}}.getDuplicateArea({{-100,100},{10,-10}});
    });
    duplicate_test.isSame(tes::geometry::Area2D{{1,1},{0,0}}, [] {
        return tes::geometry::Area2D{{100,100}, {0,0}}.getDuplicateArea({{1,1},{0,0}});
    });
    cpptf::complete();
    return 0;
}