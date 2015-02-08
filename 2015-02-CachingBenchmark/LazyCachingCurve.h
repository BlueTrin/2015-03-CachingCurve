#pragma once
#include "ICurve.h"

#include <map>

class LazyCachingCurve : public ICurve
{
public:
	LazyCachingCurve();
	LazyCachingCurve(const std::map<long, double> alphas);
	double df(long date) const;

private:
	static const long s_cacheSize;
	std::map<long, double> m_alphas;
	mutable std::map<long, double> m_cachedDfs;
	long m_start;
};

