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

#endif // !RESOURSE
