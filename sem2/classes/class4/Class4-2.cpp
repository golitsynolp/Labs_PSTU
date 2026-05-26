#include "Class4-2.h"

LONG::LONG() : PAIR(0, 0) {}

LONG::LONG(int high, int low) : PAIR(high, low) {
    if (low >= BASE || low < 0) {
        second = low % BASE;
        first += low / BASE;
        if (second < 0) {
            second += BASE;
            first--;
        }
    }
}

LONG::LONG(const LONG& other) : PAIR(other) {}

// Сложение с переносом
LONG LONG::operator+(const LONG& other) const {
    int lowSum = second + other.second;
    int carry = lowSum / BASE;
    int newLow = lowSum % BASE;
    int newHigh = first + other.first + carry;
    return LONG(newHigh, newLow);
}

// Вычитание с заёмом
LONG LONG::operator-(const LONG& other) const {
    int newLow = second - other.second;
    int borrow = 0;
    if (newLow < 0) {
        newLow += BASE;
        borrow = 1;
    }
    int newHigh = first - other.first - borrow;
    return LONG(newHigh, newLow);
}

LONG LONG::operator*(const LONG& other) const {
    long long a = static_cast<long long>(first) * BASE + second;
    long long b = static_cast<long long>(other.first) * BASE + other.second;
    long long product = a * b;

    int newLow  = static_cast<int>(product % BASE);
    int newHigh = static_cast<int>(product / BASE);
    return LONG(newHigh, newLow);
}