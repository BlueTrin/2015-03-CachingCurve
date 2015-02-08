#pragma once

class ICurve
{
public:
	~ICurve() {}
	virtual double df(long date) const = 0;
};