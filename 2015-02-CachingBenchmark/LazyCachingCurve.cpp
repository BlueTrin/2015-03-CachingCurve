#include "LazyCachingCurve.h"

#include "SimpleCurve.h"

LazyCachingCurve::LazyCachingCurve()
{
}

LazyCachingCurve::LazyCachingCurve(const std::map<long, double> alphas)
: m_curveImpl(new SimpleCurve(alphas))
{
}

double LazyCachingCurve::df(long date) const
{
	std::map<long, double>::const_iterator lbCacheDf = m_cachedDfs.lower_bound(date);
	if (lbCacheDf->first != date)
	{
		double df = m_curveImpl->df(date);
		m_cachedDfs[date] = df;
		return df;
	}
	else
	{
		return lbCacheDf->second;
	}
}