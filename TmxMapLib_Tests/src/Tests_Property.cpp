#include "TmxMapLib/Property.h"
#include "catch.hpp"

using namespace TmxMapLib;

//  ===============================================================================
TEST_CASE("Property", "[property]")
{
    Property property("Text", "Hello.", PropertyType::String);
    REQUIRE(property.getName() == "Text");
    REQUIRE(property.getValue() == "Hello.");
    REQUIRE_THROWS(property.getBoolValue() == false);
    REQUIRE_THROWS(property.getDoubleValue() == 0);
    REQUIRE_THROWS(property.getFloatValue() == 0);
    REQUIRE_THROWS(property.getIntValue() == 0);
    bool textBool = false;
    property.queryBoolValue(textBool, true);
    REQUIRE(textBool == true);
    double textDouble = 0;
    property.queryDoubleValue(textDouble, 25.5);
    REQUIRE(textDouble == 25.5);
    float textFloat = 0;
    property.queryFloatValue(textFloat, 2.5f);
    REQUIRE(textFloat == 2.5f);
    int textInt = 0;
    property.queryIntValue(textInt, 50);
    REQUIRE(textInt == 50);

    property = Property("Enabled", "true", PropertyType::Bool);
    REQUIRE(property.getName() == "Enabled");
    REQUIRE(property.getValue() == "true");
    REQUIRE(property.getBoolValue() == true);
    bool enabled = false;
    property.queryBoolValue(enabled);
    REQUIRE(enabled == true);
    enabled = false;
    property.queryBoolValue(enabled, false);
    REQUIRE(enabled == true);
    REQUIRE_THROWS(property.getDoubleValue() == 0);
    REQUIRE_THROWS(property.getFloatValue() == 0);
    REQUIRE_THROWS(property.getIntValue() == 0);

    property = Property("Chance", "23.45", PropertyType::Float);
    REQUIRE(property.getName() == "Chance");
    REQUIRE(property.getValue() == "23.45");
    REQUIRE(property.getIntValue() == 23);
    REQUIRE(property.getDoubleValue() == 23.45);
    REQUIRE(property.getFloatValue() == 23.45f);
    double chanceDouble;
    property.queryDoubleValue(chanceDouble);
    REQUIRE(chanceDouble == 23.45);
    chanceDouble = 0;
    property.queryDoubleValue(chanceDouble, 0);
    REQUIRE(chanceDouble == 23.45);
    float chance;
    property.queryFloatValue(chance);
    REQUIRE(chance == 23.45f);
    chance = 0;
    property.queryFloatValue(chance, 0);
    REQUIRE(chance == 23.45f);
    REQUIRE_THROWS(property.getBoolValue() == false);

    property = Property("Health", "521", PropertyType::Int);
    REQUIRE(property.getName() == "Health");
    REQUIRE(property.getValue() == "521");
    REQUIRE(property.getIntValue() == 521);
    REQUIRE(property.getDoubleValue() == 521);
    REQUIRE(property.getFloatValue() == 521);
    int health = 0;
    property.queryIntValue(health);
    REQUIRE(health == 521);
    health = 0;
    property.queryIntValue(health, 0);
    REQUIRE(health == 521);
    REQUIRE_THROWS(property.getBoolValue() == false);
}