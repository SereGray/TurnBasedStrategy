#ifndef RESOURSE
#define RESOURSE

class Resourse {
	
public:
	unsigned count_;
	unsigned cost_conventional_units; // cost in hundredths e.g cost_conventional_units=1 equal 0.01, 100 equal1
	Resourse()=delete;
	bool operator==(const Resourse&) const;
	Resourse(unsigned count, unsigned cost);
	Resourse& operator= (const Resourse& );
	const Resourse operator+ (const Resourse& );
	Resourse& operator+ (const int );
	Resourse& operator+= (const Resourse& );
	Resourse operator- (const Resourse& );
	Resourse& operator- (const int );
	Resourse& operator-= (const Resourse& );
	Resourse& operator-- ();
	Resourse operator--(int );
	Resourse& operator++();
	Resourse operator++(int );
	~Resourse() = default;
};

#endif // !RESOURSE
