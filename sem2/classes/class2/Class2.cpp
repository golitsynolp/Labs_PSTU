#pragma once

#include<iostream>
#include<string>

#include "Class2.h"

// Конструкторы
Country::Country() : capital(""), population(0), square(0) {
	std::cout<<"Конструктор без параметров для: "<<this<<std::endl;
};

Country::Country(std::string cap, int pop, double sq) : capital(cap), population(pop), square(sq) {
	std::cout<<"Конструктор с параметрами для: "<<this<<std::endl;
};

Country::Country(const Country& country) : capital(country.capital), population(country.population), square(country.square) {
	std::cout<<"Конструктор копирования для: "<<this<<std::endl;
};

// Деструктор
Country::~Country() {
	std::cout<<"Деструктор для: "<<this<<std::endl;
}

// Геттеры
std::string Country::get_capital() const {
	return capital;
}

int Country::get_population() const {
	return population;
}

double Country::get_square() const {
	return square;
}

// Сеттеры
void Country::set_capital(std::string cap) {
	capital = cap;
}

void Country::set_population(int pop) {
	population = pop;
}

void Country::set_square(double sq) {
	square = sq;
}

void Country::show() {
	std::cout<<"capital: "<<capital<<std::endl;
	std::cout<<"population: "<<population<<std::endl;
	std::cout<<"square: "<<square<<std::endl;
}