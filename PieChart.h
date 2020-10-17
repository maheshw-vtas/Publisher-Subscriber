#ifndef _PIECHART_H_
#define _PIECHART_H_

#include <iostream>
#include <iterator>
#include <algorithm>
#include "Subscriber.h"


class PieChart :public Subscriber {
public:
	PieChart()
	{
#if DEBUG
		std::cout << "PieChart default constructor\n";
#endif
	}

	~PieChart()
	{
#if DEBUG
		std::cout << "PieChart destructor\n";
#endif
	}

	virtual void update(const std::map<std::string, int>& datamap) {
		std::cout << "=====================================\n";
		std::cout << "             Pie Chart              \n";
		std::cout << "=====================================\n";
		for (std::map<std::string, int>::const_iterator itr = datamap.begin(); itr != datamap.end(); itr++)
		{
			std::cout << itr->first << ": " << itr->second << "\n";
		}
		std::cout << "--------------------------------------------------\n";
	}
};

#endif //_PIECHART_H_
