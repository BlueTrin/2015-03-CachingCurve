#include "PrecompCurve.h"

#include <algorithm>

const long PrecompCurve::s_cacheSize = 50 * 366;

PrecompCurve::PrecompCurve()
: m_cachedDfs(s_cacheSize)
{
}

PrecompCurve::PrecompCurve(const std::map<long, double> alphas)
: m_alphas(alphas)
, m_cachedDfs(s_cacheSize)
{
	if (m_alphas.empty()) {
		throw std::runtime_error("no alphas");
	}
	m_cachedDfs[0] = 1.;
	std::map<long, double>::const_iterator alphaIt = m_alphas.begin();
	m_start = alphaIt->first;
	
	for (size_t idx = 1; idx < s_cacheSize; )
	{
		std::map<long, double>::const_iterator alphNextIt = std::next(alphaIt);
		size_t nextCacheSlot;
		if (alphNextIt == m_alphas.end()) 
		{
			nextCacheSlot = s_cacheSize - 1;
		}
		else 
		{
			nextCacheSlot = std::min(s_cacheSize-1, alphNextIt->first - m_start);
		}
		double factor = std::exp(-alphaIt->second / 365.0);
		for (; idx <= nextCacheSlot; ++idx)
		{
			m_cachedDfs[idx] = m_cachedDfs[idx - 1] * factor;
		}
		alphaIt++;
	}
}

double PrecompCurve::df(long date) const
{
	if (date < m_start || (date - m_start) >= s_cacheSize)
	{
		throw std::runtime_error("invalid date");
	}
	return m_cachedDfs[date - m_start];
}