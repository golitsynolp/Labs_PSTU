#pragma once

#include<iostream>

#include "Class1.h"

void fraction::Init(double f, double s) {
		first = f;
		second = s;
}

void fraction::Read() {
		std::cout<<"Введите A: ";
		std::cin>>first;
		
		std::cout<<std::endl<<"Введите B: ";
		std::cin>>second;
		
		std::cout<<std::endl<<std::endl;
}

void fraction::Show() const {
		std::cout<<"A: "<<first<<std::endl<<"B: "<<second<<std::endl<<std::endl;
}

double fraction::root() const {
		if (first == 0) {
			throw "А не должно быть равно 0";
		} else {
			return -second/first;
		}
}