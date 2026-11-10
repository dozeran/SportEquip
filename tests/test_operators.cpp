
#include "Money.h"
#include "SportEquipment.h"
#include "Library.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <vector>

TEST(MoneyTest, AdditionIsCommutative) {
    Money a(100, 50);
    Money b(20, 25);

    EXPECT_EQ(a + b, b + a);
}

TEST(MoneyTest, AdditionMatchesCompoundAssignment) {
    Money a(100, 0);
    Money b(50, 0);

    Money result = a;
    result += b;

    EXPECT_EQ(a + b, result);
}

TEST(MoneyTest, MultiplicationWorksFromBothSides) {
    Money money(10, 50);

    EXPECT_EQ(money * 3, Money(31, 50));
    EXPECT_EQ(3 * money, Money(31, 50));
}

TEST(MoneyTest, ComparisonOperatorsWork) {
    Money a(10, 0);
    Money b(20, 0);

    EXPECT_EQ(a, a);
    EXPECT_NE(a, b);
    EXPECT_LT(a, b);
    EXPECT_GT(b, a);
    EXPECT_LE(a, b);
    EXPECT_GE(b, a);
}

TEST(MoneyTest, StreamOutput) {
    Money money(123, 45);

    std::ostringstream output;
    output << money;

    EXPECT_EQ(output.str(), "123.45");
}

TEST(MoneyTest, StreamInput) {
    Money money;

    std::istringstream input("123.45");
    input >> money;

    EXPECT_FALSE(input.fail());
    EXPECT_EQ(money, Money(123, 45));
}

TEST(MoneyTest, InvalidInputDoesNotChangeObject) {
    Money money(50, 25);

    std::istringstream input("100.150");
    input >> money;

    EXPECT_TRUE(input.fail());
    EXPECT_EQ(money, Money(50, 25));
}

TEST(SportEquipmentTest, EqualityUsesInventoryNumber) {
    SportEquipment a(
        101, "Football", "Good", 10, Money(500, 0)
    );

    SportEquipment b(
        101, "Basketball", "Used", 5, Money(700, 0)
    );

    EXPECT_EQ(a, b);
}

TEST(SportEquipmentTest, SortingWorks) {
    std::vector<SportEquipment> items = {
        {103, "Basketball", "Good", 10, Money(500, 0)},
        {101, "Football", "Good", 20, Money(600, 0)},
        {102, "Volleyball", "Used", 15, Money(400, 0)}
    };

    std::sort(items.begin(), items.end());

    EXPECT_EQ(items[0].getInventoryNumber(), 101);
    EXPECT_EQ(items[1].getInventoryNumber(), 102);
    EXPECT_EQ(items[2].getInventoryNumber(), 103);
}

TEST(SportEquipmentTest, StreamOutput) {
    SportEquipment equipment(
        101, "Football", "Good", 10, Money(500, 0)
    );

    std::ostringstream output;
    output << equipment;

    EXPECT_EQ(
        output.str(),
        "101 \"Football\" \"Good\" 10 500.00"
    );
}

TEST(SportEquipmentTest, StreamInput) {
    SportEquipment equipment;

    std::istringstream input(
        "101 \"Football\" \"Good\" 10 500.00"
    );

    input >> equipment;

    EXPECT_FALSE(input.fail());
    EXPECT_EQ(equipment.getInventoryNumber(), 101);
    EXPECT_EQ(equipment.getName(), "Football");
    EXPECT_EQ(equipment.getQuantity(), 10);
    EXPECT_EQ(equipment.getReplacementValue(), Money(500, 0));
}

TEST(LibraryTest, SaveAndLoadCatalog) {
    Library original;

    original.add({
        101, "Football", "Good", 10, Money(500, 0)
    });

    original.add({
        102, "Volleyball", "Used", 5, Money(400, 0)
    });

    std::stringstream stream;

    original.write(stream);

    Library restored;
    restored.read(stream);

    ASSERT_EQ(original.size(), restored.size());

    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original.at(i), restored.at(i));
    }
}
