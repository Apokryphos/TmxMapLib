#include <TmxMapLib/Map.h>
#include <iostream>

using namespace TmxMapLib;

//  ===============================================================================
int main()
{
    Map map("map01.tmx");

    const TmxMapLib::PropertySet& propertySet = map.getPropertySet();

    //  Get a property value and specify a default value in case it doesn't
    //  exist or can't be converted to the requested type.
    int difficulty = map.getPropertySet().getIntValue("Difficulty", 0);
    std::cout << "Difficulty: " << difficulty << std::endl;

    //  Or get the property itself and use its methods.
    if (propertySet.hasProperty("AllowSave")) {
        const TmxMapLib::Property* saveProp;
        saveProp = map.getPropertySet().getProperty("AllowSave");

        bool allowSave = false;

        //  QueryValue will only change the input argument if the
        //  conversion is successful.
        saveProp->queryBoolValue(allowSave);

        //  Or specify a default value to use if conversion fails.
        //  saveProp->QueryBoolValue(allowSave, false);

        std::cout << "Allow Save: " << std::boolalpha << allowSave << std::endl;
    }

    //  Properties also have GetValue methods that either return the
    //  specified default...
    float lootChance = propertySet.getProperty("LootChance")->getFloatValue(0.25f);

    //  ...or throw an exception if the property value can't be converted.
    //  float lootChance = propertySet.GetProperty("LootChance")->GetFloatValue();

    std::cout << "Loot Chance: " << lootChance << std::endl;

    return 0;
}