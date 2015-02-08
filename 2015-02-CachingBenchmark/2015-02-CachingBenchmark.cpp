// 2015-02-CachingBenchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "LazyCachingCurve.h"
#include "PrecompCurve.h"
#include "SimpleCurve.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <utility>		/* make_pair */
#include <map>
#include <vector>
#include <chrono>		/* time */

void sequentialTest(const std::map<long, double> alphas, size_t nbRun)
{
	size_t nbVals = 50 * 366;
	size_t start = alphas.begin()->first;

	std::vector<double> simpleDf(nbVals);
	std::vector<double> precompDf(nbVals);
	std::vector<double> lazyCacheDf(nbVals);

	//  Start Timers
	auto wall0s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		SimpleCurve sc(alphas);
		for (size_t idx = 0; idx < nbVals; ++idx)
		{
			simpleDf[idx] = sc.df(start + idx);
		}
	}
	auto wall0e = std::chrono::high_resolution_clock::now();


	auto wall1s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		PrecompCurve pc(alphas);
		for (size_t idx = 0; idx < nbVals; ++idx)
		{
			precompDf[idx] = pc.df(start + idx);
		}
	}
	auto wall1e = std::chrono::high_resolution_clock::now();

	auto wall2s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		LazyCachingCurve lc(alphas);
		for (size_t idx = 0; idx < nbVals; ++idx)
		{
			lazyCacheDf[idx] = lc.df(start + idx);
		}
	}
	auto wall2e = std::chrono::high_resolution_clock::now();

	for (size_t idx = 0; idx < nbVals; ++idx)
	{
		if (std::abs(lazyCacheDf[idx] - simpleDf[idx]) > 1.0e-8)
			throw std::runtime_error("error");
		if (std::abs(precompDf[idx] - simpleDf[idx]) > 1.0e-8)
			throw std::runtime_error("error");
	}

	std::cout << nbVals << " sequential values 10 times" << std::endl;
	std::cout << "Simple Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall0e - wall0s).count() << std::endl;
	std::cout << "Precomp Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall1e - wall1s).count() << std::endl;
	std::cout << "Lazy Cache Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall2e - wall2s).count() << std::endl;

}


void randomValuesTest(const std::map<long, double> alphas, const std::vector<int> randDates, size_t nbRun)
{
	std::vector<double> simpleDf(randDates.size());
	std::vector<double> precompDf(randDates.size());
	std::vector<double> lazyCacheDf(randDates.size());

	//  Start Timers
	auto wall0s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		SimpleCurve sc(alphas);
		for (size_t idx = 0; idx < randDates.size(); ++idx)
		{
			simpleDf[idx] = sc.df(randDates[idx]);
		}
	}
	auto wall0e = std::chrono::high_resolution_clock::now();


	auto wall1s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		PrecompCurve pc(alphas);
		for (size_t idx = 0; idx < randDates.size(); ++idx)
		{
			precompDf[idx] = pc.df(randDates[idx]);
		}
	}
	auto wall1e = std::chrono::high_resolution_clock::now();

	auto wall2s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		LazyCachingCurve lc(alphas);
		for (size_t idx = 0; idx < randDates.size(); ++idx)
		{
			lazyCacheDf[idx] = lc.df(randDates[idx]);
		}
	}
	auto wall2e = std::chrono::high_resolution_clock::now();

	for (size_t idx = 0; idx < randDates.size(); ++idx)
	{
		if (std::abs(lazyCacheDf[idx] - simpleDf[idx]) > 1.0e-8)
			throw std::runtime_error("error");
		if (std::abs(precompDf[idx] - simpleDf[idx]) > 1.0e-8)
			throw std::runtime_error("error");
	}

	std::cout << "30 000 random values " << nbRun << " times" << std::endl;
	std::cout << "Simple Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall0e - wall0s).count() << std::endl;
	std::cout << "Precomp Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall1e - wall1s).count() << std::endl;
	std::cout << "Lazy cache Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall2e - wall2s).count() << std::endl;

}

void randomRepeatedValuesTest(const std::map<long, double> alphas, const std::vector<int> randDatesInput, size_t nbRun)
{
	size_t nbRepeat = 400;
	size_t nbValues = 100;
	std::vector<int> randDates = randDatesInput;
	randDates.resize(nbValues);
	//  Start Timers
	auto wall0s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		SimpleCurve sc(alphas);
		for (size_t rep = 0; rep < nbRepeat; ++rep)
		{
			for (size_t idx = 0; idx < randDates.size(); ++idx)
			{
				double df = sc.df(randDates[idx]);
			}
		}
	}
	auto wall0e = std::chrono::high_resolution_clock::now();


	auto wall1s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		PrecompCurve pc(alphas);
		for (size_t rep = 0; rep < nbRepeat; ++rep)
		{
			for (size_t idx = 0; idx < randDates.size(); ++idx)
			{
				double df = pc.df(randDates[idx]);
			}
		}
	}
	auto wall1e = std::chrono::high_resolution_clock::now();

	auto wall2s = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < nbRun; ++i)
	{
		LazyCachingCurve lc(alphas);
		for (size_t rep = 0; rep < nbRepeat; ++rep)
		{
			for (size_t idx = 0; idx < randDates.size(); ++idx)
			{
				double df = lc.df(randDates[idx]);
			}
		}
	}
	auto wall2e = std::chrono::high_resolution_clock::now();

	std::cout << "Repeat " << nbRepeat  << " times the same " << nbValues << " random values (do this " << nbRun << " times)" << std::endl;
	std::cout << "Simple Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall0e - wall0s).count() << std::endl;
	std::cout << "Precomp Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall1e - wall1s).count() << std::endl;
	std::cout << "Lazy Time = " << std::chrono::duration_cast<std::chrono::duration<double>>(wall2e - wall2s).count() << std::endl;

}


int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> randDates;
	size_t startDate = 35000;
	size_t maxDate = 35000 + 50 * 365;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 30000; i++){
		int b = rand() % (maxDate - startDate) + startDate;
		randDates.push_back(b);
	}

	std::map<long, double> alphas;
	alphas.insert(std::make_pair(startDate, 0.04));
	alphas.insert(std::make_pair(startDate + 1 * 365, 0.045));
	alphas.insert(std::make_pair(startDate + 2 * 365, 0.035));
	alphas.insert(std::make_pair(startDate + 5 * 365, 0.030));
	alphas.insert(std::make_pair(startDate + 7 * 365, 0.027));
	alphas.insert(std::make_pair(startDate + 10 * 365, 0.025));
	
#ifdef _DEBUG
	size_t nbRun = 1;
#else
	size_t nbRun = 10;
#endif
	sequentialTest(alphas, nbRun);
	randomValuesTest(alphas, randDates, nbRun);
	randomRepeatedValuesTest(alphas, randDates, nbRun);

	system("pause");
}

