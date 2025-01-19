#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "rawMaterials.hh"
#include <iostream>
#include <string>

TEST_CASE("1: RawMaterial getReduction with negative input") {
    CHECK_THROWS_WITH_AS(RawMaterial::getReduction(-1), "Impossible argument négatif 🤬", const char*);
}

TEST_CASE("2: RawMaterial getReduction with 0 to 9 raw materials") {
    CHECK(RawMaterial::getReduction(0) == 0.0f);
    CHECK(RawMaterial::getReduction(9) == 0.0f);
}

TEST_CASE("3: RawMaterial getReduction with 10 to 49 raw materials") {
    CHECK(RawMaterial::getReduction(10) == 0.1f);
    CHECK(RawMaterial::getReduction(49) == 0.1f);
}

TEST_CASE("4: RawMaterial getReduction with 50 or more raw materials") {
    CHECK(RawMaterial::getReduction(50) == 0.2f);
    CHECK(RawMaterial::getReduction(100) == 0.2f);
}

