#pragma once

#include <iostream>

class PAIR {
public:
    PAIR(void);
    virtual ~PAIR(void);
    PAIR(int, int);
    PAIR(const PAIR&);

    // Селекторы
    int Get_first() const { return first; }
    int Get_second() const { return second; }

    // Модификаторы
    void Set_first(int);
    void Set_second(int);

    // Операция присваивания
    PAIR& operator=(const PAIR&);

    // Операция сложения пар (покомпонентно)
    PAIR operator+(const PAIR&) const;

    // Глобальные операторы ввода-вывода
    friend std::istream& operator>>(std::istream&, PAIR&);
    friend std::ostream& operator<<(std::ostream&, const PAIR&);

protected:
    int first;
    int second;
};