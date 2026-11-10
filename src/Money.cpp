
#include "Money.h"

#include <istream>
#include <ostream>
#include <iomanip>
#include <limits>

Money::Money(long long hryvnias, int kopecks) {
    cents_ = hryvnias * 100 + kopecks;
}

long long Money::getCents() const noexcept {
    return cents_;
}

Money& Money::operator+=(const Money& other) {
    cents_ += other.cents_;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    cents_ -= other.cents_;
    return *this;
}

Money& Money::operator*=(int multiplier) {
    cents_ *= multiplier;
    return *this;
}

Money Money::operator-() const {
    Money result;
    result.cents_ = -cents_;
    return result;
}

Money operator+(Money lhs, const Money& rhs) {
    lhs += rhs;
    return lhs;
}

Money operator-(Money lhs, const Money& rhs) {
    lhs -= rhs;
    return lhs;
}

Money operator*(Money money, int multiplier) {
    money *= multiplier;
    return money;
}

Money operator*(int multiplier, Money money) {
    money *= multiplier;
    return money;
}

bool operator==(const Money& lhs, const Money& rhs) {
    return lhs.cents_ == rhs.cents_;
}

bool operator<(const Money& lhs, const Money& rhs) {
    return lhs.cents_ < rhs.cents_;
}

bool operator!=(const Money& lhs, const Money& rhs) {
    return !(lhs == rhs);
}

bool operator>(const Money& lhs, const Money& rhs) {
    return rhs < lhs;
}

bool operator<=(const Money& lhs, const Money& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Money& lhs, const Money& rhs) {
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    const auto oldFlags = os.flags();
    const auto oldPrecision = os.precision();
    const auto oldFill = os.fill();

    const long long absoluteCents =
        money.cents_ < 0 ? -money.cents_ : money.cents_;

    if (money.cents_ < 0) {
        os << '-';
    }

    os << absoluteCents / 100
       << '.'
       << std::setw(2) << std::setfill('0')
       << absoluteCents % 100;

    os.flags(oldFlags);
    os.precision(oldPrecision);
    os.fill(oldFill);

    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    long long hryvnias;
    char separator;
    int kopecks;

    if (is >> hryvnias >> separator >> kopecks) {
        if (separator != '.' || kopecks < 0 || kopecks > 99) {
            is.setstate(std::ios::failbit);
            return is;
        }

        money.cents_ = hryvnias * 100 + kopecks;
    }

    return is;
}
