#include "LazyCachingCurve.h"


LazyCachingCurve::LazyCachingCurve()
{
}

LazyCachingCurve::LazyCachingCurve(const std::map<long, double> alphas)
: m_alphas(alphas)
{
	if (m_alphas.empty())
	{
		throw std::runtime_error("invalid alphas");
	}
	m_start = m_alphas.begin()->first;
	m_cachedDfs[m_start] = 1.0;
}

double LazyCachingCurve::df(long date) const
{
	std::map<long, double>::const_iterator lbCacheDf = m_cachedDfs.lower_bound(date);
	if (lbCacheDf != m_cachedDfs.end() && lbCacheDf->first == date)
		return lbCacheDf->second;
	std::map<long, double>::const_iterator lastDf = std::prev(lbCacheDf);
	std::map<long, double>::const_iterator nextAlpha = m_alphas.upper_bound(lastDf->first);
	std::map<long, double>::const_iterator currAlpha = std::prev(nextAlpha);
	double currDf = lastDf->second;
	long currDate = lastDf->first;
	while (true)
	{
		if (nextAlpha == m_alphas.end() || date <= nextAlpha->first)
		{
			double dateDf = currDf * std::exp(-currAlpha->second * (date - currDate) / 365.0);
			m_cachedDfs[date] = dateDf;
			return dateDf;
		}
		else
		{
			currDf = currDf * std::exp(-currAlpha->second * (nextAlpha->first - currDate) / 365.0);
			currDate = nextAlpha->first;
			m_cachedDfs[currDate] = currDf;
			currAlpha = nextAlpha;
			nextAlpha++;
		}
	}
}