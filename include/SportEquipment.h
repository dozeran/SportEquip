
#ifndef SPORT_EQUIPMENT_H
#define SPORT_EQUIPMENT_H

#include "Money.h"

#include <iosfwd>
#include <string>

class SportEquipment {
public:
    SportEquipment() = default;

    SportEquipment(
        int inventoryNumber,
        const std::string& name,
        const std::string& condition,
        int quantity,
        const Money& replacementValue
    );

    int getInventoryNumber() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getCondition() const noexcept;
    int getQuantity() const noexcept;
    const Money& getReplacementValue() const noexcept;

    friend bool operator==(const SportEquipment& lhs,
                           const SportEquipment& rhs);

    friend bool operator<(const SportEquipment& lhs,
                          const SportEquipment& rhs);

    friend std::ostream& operator<<(std::ostream& os,
                                    const SportEquipment& equipment);

    friend std::istream& operator>>(std::istream& is,
                                    SportEquipment& equipment);

private:
    int inventoryNumber_ = 0;
    std::string name_;
    std::string condition_;
    int quantity_ = 0;
    Money replacementValue_;
};

bool operator!=(const SportEquipment& lhs, const SportEquipment& rhs);
bool operator>(const SportEquipment& lhs, const SportEquipment& rhs);
bool operator<=(const SportEquipment& lhs, const SportEquipment& rhs);
bool operator>=(const SportEquipment& lhs, const SportEquipment& rhs);

#endif
