#pragma once

class fraction {
private:
	double first;
	double second;
	
public:
	void Init(double f, double s);
	
	void Read();
	
	void Show() const;
	
	double root() const;
};