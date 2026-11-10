
#ifndef MONEY_H
#define MONEY_H

#include <iosfwd>

class Money {
public:
    Money() = default;
    Money(long long hryvnias, int kopecks = 0);

    long long getCents() const noexcept;

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(int multiplier);

    Money operator-() const;

    friend Money operator+(Money lhs, const Money& rhs);
    friend Money operator-(Money lhs, const Money& rhs);
    friend Money operator*(Money money, int multiplier);
    friend Money operator*(int multiplier, Money money);

    friend bool operator==(const Money& lhs, const Money& rhs);
    friend bool operator<(const Money& lhs, const Money& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Money& money);
    friend std::istream& operator>>(std::istream& is, Money& money);

private:
    long long cents_ = 0;
};

bool operator!=(const Money& lhs, const Money& rhs);
bool operator>(const Money& lhs, const Money& rhs);
bool operator<=(const Money& lhs, const Money& rhs);
bool operator>=(const Money& lhs, const Money& rhs);

#endif
