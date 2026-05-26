#include<iostream>

#include "Class1.h"

fraction make_fraction(double A, double B) {
	fraction t;
	t.Init(A, B);
	return t;
}

int main() {
	fraction A;
	fraction B;
	
	A.Init(3.0, 2);
	B.Read();
	
	A.Show();
	B.Show();
	
	try {
		std::cout<<A.root()<<std::endl;
		}
		catch(const char* error_message) {
			std::cout<<error_message<<std::endl;
		}
		
		try {
		std::cout<<B.root()<<std::endl;
		}
		catch(const char* error_message) {
			std::cout<<error_message<<std::endl;
		}
}
