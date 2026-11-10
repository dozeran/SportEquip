
#ifndef LIBRARY_H
#define LIBRARY_H

#include "SportEquipment.h"

#include <iosfwd>
#include <vector>
#include <string>

class Library {
public:
    void add(const SportEquipment& equipment);

    std::size_t size() const noexcept;

    const SportEquipment& at(std::size_t index) const;

    void sort();

    void write(std::ostream& os) const;
    void read(std::istream& is);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    const std::vector<SportEquipment>& getItems() const noexcept;

private:
    std::vector<SportEquipment> items_;
};

#endif
