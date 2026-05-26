#pragma once
#include "Class4-1.h"

class LONG : public PAIR {
public:
    static const int BASE = 10;

    LONG();
    LONG(int high, int low);
    LONG(const LONG&);

    // Переопределение сложения
    LONG operator+(const LONG&) const;

    // Операция вычитания
    LONG operator-(const LONG&) const;

    // Операция умножения
    LONG operator*(const LONG&) const;
};