#pragma once

#include <iostream>

class Money {
public:
    Money(void);
    Money(long rubles, int kopeks);
    Money(const Money& other);
    ~Money(void);

    // селекторы
    long Get_rub() const { return rub; }
    int  Get_kop() const { return kop; }

    // модификаторы
    void Set_rub(long r) { rub = r; }
    void Set_kop(int k);

    // операция присваивания
    Money& operator=(const Money& other);

    // арифметические операции
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    // дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);

private:
    long rub;
    int  kop;
};