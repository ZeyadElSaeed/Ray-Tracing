#pragma once
#include "rtweekend.h"
class Interval
{
private:
	double m_Min;
	double m_Max;
public:
	Interval() :
		m_Min(+infinity), m_Max(-infinity)
	{ 
		// Empty Interval 
	}

	Interval(double min, double max)
		:m_Min(min), m_Max(max)
	{
	}

	bool contains(double x) const {
		return m_Min <= x && x <= m_Max;
	}

	bool surrounds(double x) const {
		return m_Min < x && x < m_Max;
	}

	inline double getMin() const { return m_Min; }
	inline double getMax() const { return m_Max; }

	static const Interval empty, universe;
};
static const Interval empty		(+infinity, -infinity);
static const Interval universe	(-infinity, +infinity);
