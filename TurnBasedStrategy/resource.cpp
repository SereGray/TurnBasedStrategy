#include "resource.h"

bool Resource::operator==(const Resource& other) const {
	if (std::abs(this->count_ - other.count_) < 0.01 && \
		this->cost_conventional_units_ == other.cost_conventional_units_)return true;
	if (std::abs(this->count_ * cost_conventional_units_ - other.count_ * other.cost_conventional_units_) < 0.01) return true;
	return false;
}
Resource::Resource(int count, int cost) :count_((float)count), cost_conventional_units_(cost)
{
	if (cost_conventional_units_ == 0) ++cost_conventional_units_; // conventional units must be > 0
}

Resource& Resource::operator=(const Resource& in)
{
	if (in == *this) return *this;
	count_ = in.count_ * in.cost_conventional_units_ / cost_conventional_units_;
	return *this;
}

Resource& Resource::operator=(const int in){
	count_ = (float)in;
	return *this;
}

const Resource Resource::operator+(const Resource& in)
{
	Resource res = *this;
	res.count_ = count_ + in.count_ * in.cost_conventional_units_/cost_conventional_units_;
	return res;
}

Resource& Resource::operator+(const int in)
{
	count_+= in;
	return *this;
}

Resource& Resource::operator*(const int in){
	count_ *= in;
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
	res.count_ = count_ - in.count_ * in.cost_conventional_units_/ cost_conventional_units_;
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
	count_ -= 1.0;
	return *this;
}

Resource& Resource::operator++()
{
	count_ += 1.0;
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

int Resource::Count()
{
	return std::round(count_);
}



// Gold
Gold::Gold(int count) : Resource(count, 10000)
{
}

// Food
Food::Food(int count) : Resource(count, 100)
{
}

// BaseCost

BaseCost::~BaseCost() {};

Resource& BaseCost::Buy()
{
	Resource res(0, 1);
	return res;
};

Resource& BaseCost::Sell()
{
	Resource res(0, 1);
	return res;
}
