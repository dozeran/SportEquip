
#include "Library.h"

#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <utility>

void Library::add(const SportEquipment& equipment) {
    items_.push_back(equipment);
}

std::size_t Library::size() const noexcept {
    return items_.size();
}

const SportEquipment& Library::at(std::size_t index) const {
    return items_.at(index);
}

void Library::sort() {
    std::sort(items_.begin(), items_.end());
}

void Library::write(std::ostream& os) const {
    os << items_.size() << '\n';

    for (const auto& equipment : items_) {
        os << equipment << '\n';
    }
}

void Library::read(std::istream& is) {
    std::size_t count;

    if (!(is >> count)) {
        return;
    }

    std::vector<SportEquipment> loadedItems;
    loadedItems.reserve(count);

    for (std::size_t i = 0; i < count; ++i) {
        SportEquipment equipment;

        if (!(is >> equipment)) {
            return;
        }

        loadedItems.push_back(equipment);
    }

    items_ = std::move(loadedItems);
}

bool Library::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file) {
        return false;
    }

    write(file);
    return file.good();
}

bool Library::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        return false;
    }

    read(file);
    return file.good() || file.eof();
}

const std::vector<SportEquipment>& Library::getItems() const noexcept {
    return items_;
}
