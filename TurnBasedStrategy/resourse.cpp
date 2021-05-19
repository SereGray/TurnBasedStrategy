#include "resourse.h"

bool Resourse::operator==(const Resourse& other) const{
	if(this->count_==other.count_ && \
			this->cost_conventional_units==other.cost_conventional_units)return true;
	return false;
}
Resourse::Resourse(unsigned count, unsigned cost):count_(count), cost_conventional_units(cost)
{
}

Resourse& Resourse::operator=(const Resourse& in)
{
	if(in == *this) return *this;
	count_ = (unsigned) ((double)(in.count_ * in.cost_conventional_units))/(double)cost_conventional_units;
	return *this;
}

const Resourse Resourse::operator+(const Resourse& in)
{
	Resourse res = in;
	res.count_ = res.count_ + (unsigned) ((double)(in.count_ * in.cost_conventional_units))/(double)cost_conventional_units;
	return res;
}

Resourse& Resourse::operator+(const int in)
{
	return *this;
}

Resourse& Resourse::operator+=(const Resourse& in)
{
	*this = *this + in;
	return *this;
}

Resourse Resourse::operator-(const Resourse& in)
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

Resourse& Resourse::operator--()
{
	return *this;
}

Resourse& Resourse::operator++()
{
	return *this;
}
Resourse Resourse::operator--(int in)
{
	return *this;
}

Resourse Resourse::operator++(int in)
{
	return *this;
}
