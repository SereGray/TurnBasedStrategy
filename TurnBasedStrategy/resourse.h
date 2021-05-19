#ifndef RESOURSE
#define RESOURSE

class Resourse {
	
public:
	unsigned count_;
	unsigned cost_conventional_units; // cost in hundredths e.g cost_conventional_units=1 equal 0.01, 100 equal1
	Resourse();
	Resourse(unsigned count, unsigned cost);
	Resourse& operator= (const Resourse& in);
	Resourse& operator+ (const Resourse& in);
	Resourse& operator+ (const int in);
	Resourse& operator+= (const Resourse& in);
	Resourse& operator- (const Resourse& in);
	Resourse& operator- (const int in);
	Resourse& operator-= (const Resourse& in);
	Resourse& operator-- (int in);
	Resourse& operator++ (int in);
	~Resourse() = default;
};

#endif // !RESOURSE
