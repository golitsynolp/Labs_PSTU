#include "Money.h"

Money::Money(void) : rub(0), kop(0) {}

Money::~Money(void) {}

Money::Money(long rubles, int kopeks) : rub(rubles), kop(kopeks) {
    if (kop < 0 || kop > 99) {
        rub += kop / 100;
        kop %= 100;
        if (kop < 0) {
            kop += 100;
            rub--;
        }
    }
}

Money::Money(const Money& other) : rub(other.rub), kop(other.kop) {}

void Money::Set_kop(int k) {
    kop = k;
    if (kop < 0 || kop > 99) {
        rub += kop / 100;
        kop %= 100;
        if (kop < 0) {
            kop += 100;
            rub--;
        }
    }
}

Money& Money::operator=(const Money& other) {
    if (this == &other) return *this;
    rub = other.rub;
    kop = other.kop;
    return *this;
}

Money Money::operator+(const Money& other) const {
    long total_kop = (rub * 100 + kop) + (other.rub * 100 + other.kop);
    long new_rub = total_kop / 100;
    int  new_kop = total_kop % 100;
    return Money(new_rub, new_kop);
}

Money Money::operator-(const Money& other) const {
    long total_kop = (rub * 100 + kop) - (other.rub * 100 + other.kop);
    long new_rub = total_kop / 100;
    int  new_kop = total_kop % 100;
    // корректировка отрицательных копеек
    if (new_kop < 0) {
        new_kop += 100;
        new_rub--;
    }
    return Money(new_rub, new_kop);
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
    out << m.rub << ",";
    if (m.kop < 10) out << "0";   // ведущий ноль для копеек
    out << m.kop;
    return out;
}

std::istream& operator>>(std::istream& in, Money& m) {
    std::cout << "rub: ";
    in >> m.rub;
    std::cout << "kop (0..99): ";
    in >> m.kop;
    // нормализация
    if (m.kop < 0 || m.kop > 99) {
        m.rub += m.kop / 100;
        m.kop %= 100;
        if (m.kop < 0) {
            m.kop += 100;
            m.rub--;
        }
    }
    return in;
}