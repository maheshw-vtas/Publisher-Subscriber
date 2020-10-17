#ifndef _LINECHART_H_
#define _LINECHART_H_

#include <iostream>
#include <iterator>
#include <algorithm>
#include "Subscriber.h"


class LineChart :public Subscriber {
public:
	LineChart()
	{
#if DEBUG
		std::cout << "LineChart default constructor\n";
#endif
	}

	~LineChart()
	{
#if DEBUG
		std::cout << "LineChart destructor\n";
#endif
	}

	virtual void update(const std::map<std::string, int>& datamap) {
		std::cout << "=====================================\n";
		std::cout << "             Line Chart              \n";
		std::cout << "=====================================\n";
		for (std::map<std::string, int>::const_iterator itr = datamap.begin(); itr != datamap.end(); itr++)
		{
			std::cout << itr->first << ": " << itr->second << "\n";
		}
		std::cout << "--------------------------------------------------\n";
	}
};

#endif //_LINECHART_H_
