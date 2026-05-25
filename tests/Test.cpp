#include "Parser.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace mdmodel;

TEST_CASE("heading parsing")
{
    const std::string markdown =
        "# Layout\n"
        "  - Indicators\n"
        "    - BatteryIndicator\n"
        "    - BluetoothIndicator\n"
        "# BatteryIndicator\n"
        "  - Type: StatedImage\n"
        "  - Width: 24\n"
        "  - Height: 24.5\n"
        "  - Visible: true\n";

    auto doc = Parser().Parse(markdown);

    auto it = doc->Find("/Layout");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Layout node");
    CHECK_MESSAGE(it->second->Name() == "Layout", "Expected node name 'Layout', got '" << it->second->Name() << "'");

    it = doc->Find("/BatteryIndicator");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find BatteryIndicator node");
    CHECK_MESSAGE(it->second->Name() == "BatteryIndicator", "Expected node name 'BatteryIndicator', got '" << it->second->Name() << "'");

    it = doc->Find("/Layout/Indicators");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Indicators node");
    CHECK_MESSAGE(it->second->Name() == "Indicators", "Expected node name 'Indicators', got '" << it->second->Name() << "'");

    it = doc->Find("/Layout/Indicators/BatteryIndicator");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find BatteryIndicator node");
    CHECK_MESSAGE(it->second->Name() == "BatteryIndicator", "Expected node name 'BatteryIndicator', got '" << it->second->Name() << "'");

    it = doc->Find("/Layout/Indicators/BluetoothIndicator");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find BluetoothIndicator node");
    CHECK_MESSAGE(it->second->Name() == "BluetoothIndicator", "Expected node name 'BluetoothIndicator', got '" << it->second->Name() << "'");
    
    it = doc->Find("/BatteryIndicator/Type");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Type node");
    CHECK_MESSAGE(it->second->Name() == "Type", "Expected node name 'Type', got '" << it->second->Name() << "'");
    CHECK_MESSAGE(it->second->StringValue().value_or("") == "StatedImage", "Expected node value 'StatedImage', got '" << it->second->StringValue().value_or("") << "'");

    it = doc->Find("/BatteryIndicator/Width");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Width node");
    CHECK_MESSAGE(it->second->Name() == "Width", "Expected node name 'Width', got '" << it->second->Name() << "'");
    CHECK_MESSAGE(it->second->IntValue().value_or(0) == 24, "Expected node value 24, got '" << it->second->IntValue().value_or(0) << "'");

    it = doc->Find("/BatteryIndicator/Height");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Height node");
    CHECK_MESSAGE(it->second->Name() == "Height", "Expected node name 'Height', got '" << it->second->Name() << "'");
    CHECK_MESSAGE(it->second->DoubleValue().value_or(0.0) == 24.5, "Expected node value 24.5, got '" << it->second->DoubleValue().value_or(0.0) << "'");

    it = doc->Find("/BatteryIndicator/Visible");
    REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Visible node");
    CHECK_MESSAGE(it->second->Name() == "Visible", "Expected node name 'Visible', got '" << it->second->Name() << "'");
    CHECK_MESSAGE(it->second->BoolValue().value_or(false) == true, "Expected node value true, got '" << it->second->BoolValue().value_or(false) << "'");
}


// TEST_CASE("heading and list parsing")
// {
//     const std::string markdown =
//         "# Layout\n"
//         "  - Indicators\n"
//         "# BatteryIndicator\n";

//     auto doc = Parser().Parse(markdown);

//     auto it = doc->Find("/Layout");
//     REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Layout node");
//     CHECK_MESSAGE(it->second->Name() == "Layout", "Expected node name 'Layout', got '" << it->second->Name() << "'");

//     it = doc->Find("/Layout/Indicators");
//     REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Indicators node");
//     CHECK_MESSAGE(it->second->Name() == "Indicators", "Expected node name 'Indicators', got '" << it->second->Name() << "'");

//     it = doc->Find("/BatteryIndicator");
//     REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find BatteryIndicator node");
//     CHECK_MESSAGE(it->second->Name() == "BatteryIndicator", "Expected node name 'BatteryIndicator', got '" << it->second->Name() << "'");
// }

// TEST_CASE("property parsing")
// {
//     const std::string markdown =
//         "# Layout\n"
//         // "  - Indicators\n"
//         // "    - BatteryIndicator\n"
//         // "    - BluetoothIndicator\n"
//         // "    - PlayingSong\n"
//         // "    - NoteImage\n"
//         // "  - Separator\n"
//         "# BatteryIndicator\n"
//        // "  - Type: StatedImage\n";
//        ;

//     auto doc = Parser().Parse(markdown);

//     auto it = doc->Find("/Layout");
//     REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Layout node");
//     CHECK_MESSAGE(it->second->Name() == "Layout", "Expected node name 'Layout', got '" << it->second->Name() << "'");

//     it = doc->Find("Layout/Indicators");
//     REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Indicators node");
//     CHECK_MESSAGE(it->second->Name() == "Indicators", "Expected node name 'Indicators', got '" << it->second->Name() << "'");

//     // it = doc->Find("Layout/Separator");
//     // REQUIRE_MESSAGE(it != doc->ChildrenEnd(), "Failed to find Separator node");
//     // CHECK_MESSAGE(it->second->Name() == "Separator", "Expected node name 'Separator', got '" << it->second->Name() << "'");

//     // const std::vector<std::string> indicator_names = {
//     //     "BatteryIndicator", "BluetoothIndicator", "PlayingSong", "NoteImage"
//     // };

//     // auto indicators_it = indicator_names.begin();
//     // it = doc->Find("Layout/Indicators");
//     // for (auto child_it = it->second->ChildrenBegin(); 
//     //      child_it != it->second->ChildrenEnd() && 
//     //      indicators_it != indicator_names.end(); 
//     //      ++child_it, ++indicators_it)
//     // {
//     //     CHECK(child_it->second->Name() == *indicators_it);
//     // }
// }