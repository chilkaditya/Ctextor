#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../include/cursor.hpp" // Or include header if available

TEST_CASE("Cursor basic movement", "[cursor]") {
    Cursor c;
    c.setX(5);
    c.setY(10);
    REQUIRE(c.getX() == 5);
    REQUIRE(c.getY() == 10);
}