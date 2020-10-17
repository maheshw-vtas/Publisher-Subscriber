#include <iostream>
#include <cstdlib>
#include <memory>

#include "Publisher.h"
#include "FileDataPublisher.h"
#include "BarChart.h"
#include "LineChart.h"
#include "PieChart.h"

using namespace std;

void usage()
{
	cout << "====================================================\n"
			"                 Component Prices\n"
			"====================================================\n"
			"u)pdate/load single component info\n"
			"r)eload/load all components\n"
			"q)uit\n"
			"====================================================\n"
			"Enter your choice: ";
}

/*
* Test program to get user inputs and use those inputs to depict Publisher-Subscriber behaviour.
* It's minimal code to get user choices and act accordingly. It doesnt handle all possible user interactions.
* Intention of this interactive code is to just get user inputs, in order to showcase Publisher-Subscriber design.
*/
int main()
{
	try {
		// Instantiate a file data source
		shared_ptr<Publisher> pPub(new FileDataPublisher());

		//Instantiate and add subscribers/listeners that are interested in getting notified about changes in file data source
		shared_ptr<BarChart> pBarChart(new BarChart());
		pPub->addSubscriber(pBarChart.get());
		shared_ptr<PieChart> pPieChart(new PieChart());
		pPub->addSubscriber(pPieChart.get());
		shared_ptr<LineChart> pLineChart(new LineChart());

		// Get user inputs.
		// User interactions such as update or reload of file data source, trigger push notifications to registerd subscribers.
		usage();
		char choice;
		string dirPath;
		string componentName;
		static int addLinechart = 1;

		cin >> choice;
		while (1)
		{			
			switch (choice)
			{
			case 'u':
				// Alternately add/remove LineChart subscriber just to depict addSubscriber()/removeSubscriber() functionality
				if (addLinechart)
				{
					pPub->addSubscriber(pLineChart.get());
					addLinechart = 0;
				}
				else {
					pPub->removeSubscriber(pLineChart.get());
					addLinechart = 1;
				}

				// Get component name as input
				cout << "\nEnter component name to update: ";
				cin >> componentName;
				pPub->updateComponentPrice(componentName);
				usage();
				break;

			case 'r':
				// Get directory path having all components as input				
				cout << "\nEnter parent directory path of component files: ";
				cin >> dirPath;
				pPub->calculateAllComponentPrices(dirPath);
				usage();
				break;

			case 'q':
				cout << "\nExiting..." << endl;
				exit(0);
			default:
				usage();
				break;
			}
			cin >> choice;
		}
	}
	catch (exception& ex) {
		cout << "\nException occurred: " << ex.what() << endl;
	}

	exit(0);
}
