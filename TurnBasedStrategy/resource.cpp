#include "resource.h"

bool Resource::operator==(const Resource& other) const{
	if(this->count_==other.count_ && \
			this->cost_conventional_units==other.cost_conventional_units)return true;
	return false;
}
Resource::Resource(int count, int cost):count_(count), cost_conventional_units(cost)
{
	if(cost_conventional_units==0) ++cost_conventional_units;
}

Resource& Resource::operator=(const Resource& in)
{
	if(in == *this) return *this;
	count_ = (int) ((double)((long)in.count_ * in.cost_conventional_units))/(double)cost_conventional_units;
	return *this;
}

const Resource Resource::operator+(const Resource& in)
{
	Resource res = *this;
	res.count_ = count_ + (int) ((double)((long)in.count_ * in.cost_conventional_units))/(double)cost_conventional_units;
	return res;
}

Resource& Resource::operator+(const int in)
{
	count_+= in;
	return *this;
}

Resource& Resource::operator+=(const Resource& in)
{
	*this = *this + in;
	return *this;
}

Resource Resource::operator-(const Resource& in)
{
	Resource res = *this;
	res.count_ = count_ - (int) ((double)((long)in.count_ * in.cost_conventional_units))/(double)cost_conventional_units;
	return res;
}

Resource& Resource::operator-(const int in)
{
	count_-=in;
	return *this;
}

Resource& Resource::operator-=(const Resource& in)
{
	*this = *this - in;
	return *this;
}

Resource& Resource::operator--()
{
	--count_;
	return *this;
}

Resource& Resource::operator++()
{
	++count_;
	return *this;
}
Resource Resource::operator--(int in)
{
	Resource res = *this;
	--*this;
	return res;
}

Resource Resource::operator++(int in)
{
	Resource res = *this;
	++*this;
	return res;
}
