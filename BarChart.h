#ifndef _BARCHART_H_
#define _BARCHART_H_

#include <iostream>
#include <iterator>
#include <algorithm>
#include "Subscriber.h"


class BarChart :public Subscriber {
public:
	BarChart()
	{
#if DEBUG
		std::cout << "BarChart default constructor\n";
#endif
	}

	~BarChart()
	{
#if DEBUG
		std::cout << "BarChart destructor\n";
#endif
	}

	virtual void update(const std::map<std::string, int>& datamap) {
		std::cout << "=====================================\n";
		std::cout << "             Bar Chart              \n";
		std::cout << "=====================================\n";
		for (std::map<std::string, int>::const_iterator itr = datamap.begin(); itr != datamap.end(); itr++)
		{
			std::cout << itr->first << ": " << itr->second << "\n";
		}
		std::cout << "--------------------------------------------------\n";
	}
};

#endif // _BARCHART_H_
