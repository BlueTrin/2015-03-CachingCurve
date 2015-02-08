#pragma once

#include "ICurve.h"

#include <vector>
#include <map>

class PrecompCurve : public ICurve
{
public:
	PrecompCurve();
	PrecompCurve(const std::map<long, double> alphas);
	double df(long date) const;

private:
	static const long s_cacheSize;
	std::map<long, double> m_alphas;
	std::vector<double> m_cachedDfs;
	long m_start;
};

