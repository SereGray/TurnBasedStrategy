#include "resourse.h"

Resourse::Resourse():count_(0),cost_conventional_units(1)
{
}

Resourse::Resourse(unsigned count, unsigned cost):count_(count), cost_conventional_units(cost)
{
}

Resourse& Resourse::operator=(const Resourse& in)
{
	return *this;
}

Resourse& Resourse::operator+(const Resourse& in)
{
	return *this;
}

Resourse& Resourse::operator+(const int in)
{
	return *this;
}

Resourse& Resourse::operator+=(const Resourse& in)
{
	return *this;
}

Resourse& Resourse::operator-(const Resourse& in)
{
	return *this;
}

Resourse& Resourse::operator-(const int in)
{
	return *this;
}

Resourse& Resourse::operator-=(const Resourse& in)
{
	return *this;
}

Resourse& Resourse::operator--(int in)
{
	return *this;
}

Resourse& Resourse::operator++(int in)
{
	return *this;
}
