#include "mdmodel/Parser.h"
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

    auto node = doc->Find("/Layout");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Layout node");
    CHECK_MESSAGE(node->Name() == "Layout", "Expected node name 'Layout', got '" << node->Name() << "'");

    node = doc->Find("/BatteryIndicator");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find BatteryIndicator node");
    CHECK_MESSAGE(node->Name() == "BatteryIndicator", "Expected node name 'BatteryIndicator', got '" << node->Name() << "'");

    node = doc->Find("/Layout/Indicators");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Indicators node");
    CHECK_MESSAGE(node->Name() == "Indicators", "Expected node name 'Indicators', got '" << node->Name() << "'");

    node = doc->Find("/Layout/Indicators/BatteryIndicator");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find BatteryIndicator node");
    CHECK_MESSAGE(node->Name() == "BatteryIndicator", "Expected node name 'BatteryIndicator', got '" << node->Name() << "'");

    node = doc->Find("/Layout/Indicators/BluetoothIndicator");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find BluetoothIndicator node");
    CHECK_MESSAGE(node->Name() == "BluetoothIndicator", "Expected node name 'BluetoothIndicator', got '" << node->Name() << "'");
    
    node = doc->Find("/BatteryIndicator/Type");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Type node");
    CHECK_MESSAGE(node->Name() == "Type", "Expected node name 'Type', got '" << node->Name() << "'");
    CHECK_MESSAGE(node->StringValue().value_or("") == "StatedImage", "Expected node value 'StatedImage', got '" << node->StringValue().value_or("") << "'");

    node = doc->Find("/BatteryIndicator/Width");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Width node");
    CHECK_MESSAGE(node->Name() == "Width", "Expected node name 'Width', got '" << node->Name() << "'");
    CHECK_MESSAGE(node->IntValue().value_or(0) == 24, "Expected node value 24, got '" << node->IntValue().value_or(0) << "'");

    node = doc->Find("/BatteryIndicator/Height");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Height node");
    CHECK_MESSAGE(node->Name() == "Height", "Expected node name 'Height', got '" << node->Name() << "'");
    CHECK_MESSAGE(node->DoubleValue().value_or(0.0) == 24.5, "Expected node value 24.5, got '" << node->DoubleValue().value_or(0.0) << "'");

    node = doc->Find("/BatteryIndicator/Visible");
    REQUIRE_MESSAGE(node != nullptr, "Failed to find Visible node");
    CHECK_MESSAGE(node->Name() == "Visible", "Expected node name 'Visible', got '" << node->Name() << "'");
    CHECK_MESSAGE(node->BoolValue().value_or(false) == true, "Expected node value true, got '" << node->BoolValue().value_or(false) << "'");
}

TEST_CASE("for each")
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

    doc->ForEach([](Node& node)
    {
        std::cout << node.Name() << std::endl;
    });
}