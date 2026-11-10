
#include "Library.h"

#include <algorithm>
#include <iostream>

int main() {
    Library library;

    library.add(SportEquipment(
        103, "Basketball", "Good", 12, Money(850, 50)
    ));

    library.add(SportEquipment(
        101, "Football", "Excellent", 20, Money(1200, 0)
    ));

    library.add(SportEquipment(
        105, "Tennis racket", "Used", 8, Money(2300, 99)
    ));

    library.add(SportEquipment(
        102, "Volleyball", "Good", 15, Money(950, 75)
    ));

    library.add(SportEquipment(
        104, "Dumbbell", "Excellent", 30, Money(600, 0)
    ));

    std::cout << "Initial inventory:\n";
    for (const auto& item : library.getItems()) {
        std::cout << item << '\n';
    }

    library.sort();

    std::cout << "\nSorted inventory:\n";
    for (const auto& item : library.getItems()) {
        std::cout << item << '\n';
    }

    if (!library.saveToFile("catalog.txt")) {
        std::cerr << "Could not save catalog\n";
        return 1;
    }

    Library restoredLibrary;

    if (!restoredLibrary.loadFromFile("catalog.txt")) {
        std::cerr << "Could not load catalog\n";
        return 1;
    }

    const bool restored =
        library.size() == restoredLibrary.size() &&
        std::equal(
            library.getItems().begin(),
            library.getItems().end(),
            restoredLibrary.getItems().begin()
        );

    std::cout << "\nCatalog restored: "
              << (restored ? "success" : "failure")
              << '\n';

    return restored ? 0 : 1;
}
