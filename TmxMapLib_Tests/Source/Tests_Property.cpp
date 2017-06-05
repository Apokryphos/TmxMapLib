#include "TmxMapLib/Property.h"
#include "catch.hpp"

using namespace TmxMapLib;

//  ===========================================================================
TEST_CASE("Property", "[property]")
{
    Property property("Text", "Hello.", PropertyType::String);
    REQUIRE(property.GetName() == "Text");
    REQUIRE(property.GetValue() == "Hello.");
    REQUIRE_THROWS(property.GetBoolValue() == false);
    REQUIRE_THROWS(property.GetDoubleValue() == 0);
    REQUIRE_THROWS(property.GetFloatValue() == 0);
    REQUIRE_THROWS(property.GetIntValue() == 0);
    bool textBool = false;
    property.QueryBoolValue(textBool, true);
    REQUIRE(textBool == true);
    double textDouble = 0;
    property.QueryDoubleValue(textDouble, 25.5);
    REQUIRE(textDouble == 25.5);
    float textFloat = 0;
    property.QueryFloatValue(textFloat, 2.5f);
    REQUIRE(textFloat == 2.5f);
    int textInt = 0;
    property.QueryIntValue(textInt, 50);
    REQUIRE(textInt == 50);

    property = Property("Enabled", "true", PropertyType::Bool);
    REQUIRE(property.GetName() == "Enabled");
    REQUIRE(property.GetValue() == "true");
    REQUIRE(property.GetBoolValue() == true);
    bool enabled = false;
    property.QueryBoolValue(enabled);
    REQUIRE(enabled == true);
    enabled = false;
    property.QueryBoolValue(enabled, false);
    REQUIRE(enabled == true);
    REQUIRE_THROWS(property.GetDoubleValue() == 0);
    REQUIRE_THROWS(property.GetFloatValue() == 0);
    REQUIRE_THROWS(property.GetIntValue() == 0);

    property = Property("Chance", "23.45", PropertyType::Float);
    REQUIRE(property.GetName() == "Chance");
    REQUIRE(property.GetValue() == "23.45");
    REQUIRE(property.GetIntValue() == 23);
    REQUIRE(property.GetDoubleValue() == 23.45);
    REQUIRE(property.GetFloatValue() == 23.45f);
    double chanceDouble;
    property.QueryDoubleValue(chanceDouble);
    REQUIRE(chanceDouble == 23.45);
    chanceDouble = 0;
    property.QueryDoubleValue(chanceDouble, 0);
    REQUIRE(chanceDouble == 23.45);
    float chance;
    property.QueryFloatValue(chance);
    REQUIRE(chance == 23.45f);
    chance = 0;
    property.QueryFloatValue(chance, 0);
    REQUIRE(chance == 23.45f);
    REQUIRE_THROWS(property.GetBoolValue() == false);

    property = Property("Health", "521", PropertyType::Int);
    REQUIRE(property.GetName() == "Health");
    REQUIRE(property.GetValue() == "521");
    REQUIRE(property.GetIntValue() == 521);
    REQUIRE(property.GetDoubleValue() == 521);
    REQUIRE(property.GetFloatValue() == 521);
    int health = 0;
    property.QueryIntValue(health);
    REQUIRE(health == 521);
    health = 0;
    property.QueryIntValue(health, 0);
    REQUIRE(health == 521);
    REQUIRE_THROWS(property.GetBoolValue() == false);
}