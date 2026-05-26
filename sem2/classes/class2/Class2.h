#pragma once

#include<iostream>
#include<string>

class Country {
private:
	std::string capital;
	int population;
	double square;
public:
	Country();
	Country(std::string cap, int pop, double sq);
	Country(const Country& country);
	
	~Country();
	
	std::string get_capital() const;
	void set_capital(std::string cap);
	
	int get_population() const;
	void set_population(int pop);
	
	double get_square() const;
	void set_square(double sq);
	
	void show();
};