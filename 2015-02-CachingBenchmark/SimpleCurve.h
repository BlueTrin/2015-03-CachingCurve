#pragma once

#include "ICurve.h"

#include <map>

class SimpleCurve : public ICurve
{
public:
	SimpleCurve();
	SimpleCurve(const std::map<long, double> alphas);
	double df(long date) const;

private:
	std::map<long, double> m_alphas;
};
