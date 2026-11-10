
#include "SportEquipment.h"

#include <istream>
#include <ostream>
#include <iomanip>
#include <tuple>

SportEquipment::SportEquipment(
    int inventoryNumber,
    const std::string& name,
    const std::string& condition,
    int quantity,
    const Money& replacementValue
)
    : inventoryNumber_(inventoryNumber),
      name_(name),
      condition_(condition),
      quantity_(quantity),
      replacementValue_(replacementValue) {
}

int SportEquipment::getInventoryNumber() const noexcept {
    return inventoryNumber_;
}

const std::string& SportEquipment::getName() const noexcept {
    return name_;
}

const std::string& SportEquipment::getCondition() const noexcept {
    return condition_;
}

int SportEquipment::getQuantity() const noexcept {
    return quantity_;
}

const Money& SportEquipment::getReplacementValue() const noexcept {
    return replacementValue_;
}

bool operator==(const SportEquipment& lhs,
                const SportEquipment& rhs) {
    return lhs.inventoryNumber_ == rhs.inventoryNumber_;
}

bool operator<(const SportEquipment& lhs,
               const SportEquipment& rhs) {
    return std::tie(lhs.inventoryNumber_, lhs.name_, lhs.condition_)
         < std::tie(rhs.inventoryNumber_, rhs.name_, rhs.condition_);
}

bool operator!=(const SportEquipment& lhs,
                const SportEquipment& rhs) {
    return !(lhs == rhs);
}

bool operator>(const SportEquipment& lhs,
               const SportEquipment& rhs) {
    return rhs < lhs;
}

bool operator<=(const SportEquipment& lhs,
                const SportEquipment& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const SportEquipment& lhs,
                const SportEquipment& rhs) {
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os,
                         const SportEquipment& equipment) {
    os << equipment.inventoryNumber_ << ' '
       << std::quoted(equipment.name_) << ' '
       << std::quoted(equipment.condition_) << ' '
       << equipment.quantity_ << ' '
       << equipment.replacementValue_;

    return os;
}

std::istream& operator>>(std::istream& is,
                         SportEquipment& equipment) {
    int inventoryNumber;
    std::string name;
    std::string condition;
    int quantity;
    Money replacementValue;

    if (is >> inventoryNumber
           >> std::quoted(name)
           >> std::quoted(condition)
           >> quantity
           >> replacementValue) {

        if (inventoryNumber <= 0 || quantity < 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        equipment.inventoryNumber_ = inventoryNumber;
        equipment.name_ = name;
        equipment.condition_ = condition;
        equipment.quantity_ = quantity;
        equipment.replacementValue_ = replacementValue;
    }

    return is;
}
