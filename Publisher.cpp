#include <list>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>

#include "Subscriber.h"
#include "Publisher.h"

using namespace std;

Publisher::Publisher()
{
}

Publisher::~Publisher()
{
}

void Publisher::addSubscriber(Subscriber* pSub)
{
	m_subscribers.push_back(pSub);
}

void Publisher::removeSubscriber(Subscriber* pSub)
{
	m_subscribers.remove(pSub);
}

void Publisher::notifySubscribers()
{
	std::cout << "Publisher notifying all subscribers\n";
	std::vector<std::thread> tvec;
	for (list<Subscriber*>::iterator it = m_subscribers.begin(); it != m_subscribers.end(); it++)
	{
		std::thread th = std::thread(&Subscriber::update, (*it), std::ref(m_componentPrice));
		tvec.push_back(std::move(th));	
	}
	
	for (auto& th : tvec)
	{
		th.join();
	}
}

void Publisher::updateComponentInfo(const std::string& componentName, int price)
{
	m_componentPrice[componentName] = price;
}

void Publisher::clearComponentinfo()
{
	m_componentPrice.clear();
}
