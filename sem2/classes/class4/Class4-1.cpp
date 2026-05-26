#include "Class4-1.h"

PAIR::PAIR(void) : first(0), second(0) {}
PAIR::~PAIR(void) {}
PAIR::PAIR(int F, int S) : first(F), second(S) {}
PAIR::PAIR(const PAIR& other) : first(other.first), second(other.second) {}

void PAIR::Set_first(int F) { first = F; }
void PAIR::Set_second(int S) { second = S; }

PAIR& PAIR::operator=(const PAIR& c) {
    if (&c == this) return *this;
    first = c.first;
    second = c.second;
    return *this;
}

// Покомпонентное сложение: (a,b)+(c,d) = (a+c, b+d)
PAIR PAIR::operator+(const PAIR& other) const {
    return PAIR(first + other.first, second + other.second);
}

std::istream& operator>>(std::istream& in, PAIR& c) {
    std::cout << std::endl << "first: ";
    in >> c.first;
    std::cout << "second: ";
    in >> c.second;
    return in;
}

std::ostream& operator<<(std::ostream& out, const PAIR& c) {
    out << "first : " << c.first << std::endl;
    out << "second : " << c.second << std::endl;
    return out;
}