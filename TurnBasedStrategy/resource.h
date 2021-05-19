#ifndef RESOURSE
#define RESOURSE

class Resource {
	
public:
	unsigned count_;
	unsigned cost_conventional_units; // cost in hundredths e.g cost_conventional_units=1 equal 0.01, 100 equal1
	Resource()=delete;
	bool operator==(const Resource&) const;
	Resource(unsigned count, unsigned cost);
	Resource& operator= (const Resource& );
	const Resource operator+ (const Resource& );
	Resource& operator+ (const int );
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

#endif // !RESOURSE
