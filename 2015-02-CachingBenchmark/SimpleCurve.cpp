#include "SimpleCurve.h"

SimpleCurve::SimpleCurve()
{
}

SimpleCurve::SimpleCurve(const std::map<long, double> alphas)
: m_alphas(alphas)
{
}

double SimpleCurve::df(long date) const
{
	if (m_alphas.empty()) {
		throw std::runtime_error("no alphas");
	}

	double df = 1.;
	for (
		std::map<long, double>::const_iterator alphaIt = m_alphas.begin();
		alphaIt != m_alphas.end(); alphaIt++)
	{
		std::map<long, double>::const_iterator alphaNextIt = std::next(alphaIt);
		if (alphaNextIt == m_alphas.end() || date <= alphaNextIt->first)
		{
			df *= std::exp(-alphaIt->second * (date - alphaIt->first) / 365.0);
			return df;
		}
		else
		{
			df *= std::exp(-alphaIt->second * (alphaNextIt->first - alphaIt->first) / 365.0);
		}
	}
	throw std::runtime_error("should not be reached");
}