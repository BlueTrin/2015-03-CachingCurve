#pragma once
#include "ICurve.h"

#include <memory>
#include <map>

class LazyCachingCurve : public ICurve
{
public:
	LazyCachingCurve();
	LazyCachingCurve(const std::map<long, double> alphas);
	double df(long date) const;

private:
	std::shared_ptr<ICurve> m_curveImpl;
	mutable std::map<long, double> m_cachedDfs;
};

