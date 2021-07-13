#ifndef RESOURSE
#define RESOURSE

class Resource {
public:
	int count_;
	int cost_conventional_units; // cost in hundredths e.g cost_conventional_units=1 equal 0.01, 100 equal1
	Resource()=delete;
	bool operator==(const Resource&) const;
	Resource(int count, int cost);
	Resource& operator= (const Resource& );
	Resource& operator= (const int);
	const Resource operator+ (const Resource& );
	Resource& operator+ (const int );
	Resource& operator*( const int);
	Resource& operator+= (const Resource& );
	Resource operator- (const Resource& );
	Resource& operator- (const int );
	Resource& operator-= (const Resource& );
	Resource& operator-- ();
	Resource operator--(int );
	Resource& operator++();
	Resource operator++(int );
	~Resource() = default;
};


// Gold class
class Gold : public Resource {
public:
	Gold(int);
};

// Eat class
class Food : public Resource {
public:
	Food(int);
};

//
class BaseCost {
public:
	virtual ~BaseCost();
	virtual Resource& Buy();
	virtual Resource& Sell();
};

template<typename TypeResource>
class UnitCost : public BaseCost {
public:
	TypeResource buy_, consumption_, sell_; //in 0.01
public:
	UnitCost(int buy, int consumption, int sell) : buy_(buy), consumption_(consumption), sell_(sell) {};
	Resource& Buy() override {
		return buy_;
	}
	Resource& Consumption() {
		return consumption_;
	}
	Resource& Sell() override
	{
		return sell_;
	}
};

#endif // !RESOURSE
