#include<iostream>

#include "Class2.cpp"

Country make_country() {
	std::string cap;
	int pop;
	double sq;
	
	std::cout<<"Введите столицу: ";
	std::cin>>cap;
	
	std::cout<<"Введите численность: ";
	std::cin>>pop;
	
	std::cout<<"Введите площадь: ";
	std::cin>>sq;
	
	Country t(cap, pop, sq);
	return t;
}

int main() {
	//конструктор без параметров
	Country t1;
	t1.show();
	
	//коструктор с параметрами
	Country t2("Computer", 1,15000);
	t2.show();
	
	//конструктор копирования
	Country t3=t2;
	t3.set_capital("Telephon");
	t3.set_population(2);
	t3.set_square(5000.0);

	t3.show();

	t1 = make_country();
	t1.show();

	return 0;
}