#ifndef TES_TEST_COUNTRY_TEST_DOMINION_HPP_
#define TES_TEST_COUNTRY_TEST_DOMINION_HPP_



void dominionRange_test();
void PosToIndex_test();
void serve_test();
void dominionArea_test();

inline void dominion_test() {
    cpptf::change_section("dominion");
    dominionRange_test();
    PosToIndex_test();
    serve_test();
    dominionArea_test();
}

#endif //TES_TEST_COUNTRY_TEST_DOMINION_HPP_
