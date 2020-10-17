#ifndef _PUBLISHER_H_
#define _PUBLISHER_H_

#include <list>
#include <map>
#include <string>
#include "Subscriber.h"

class Publisher
{
public:
	Publisher();
	virtual ~Publisher();
	
	void addSubscriber(Subscriber* pSub);	
	void removeSubscriber(Subscriber* pSub);

	virtual void calculateAllComponentPrices(const std::string& dirPath) = 0;
	virtual void updateComponentPrice(const std::string& componentName) = 0;
	virtual void notify() = 0;

protected:
	void notifySubscribers();
	void updateComponentInfo(const std::string& componentName, int price);
	void clearComponentinfo();

private:
	Publisher(const Publisher&);
	Publisher& operator=(const Publisher&);

	std::list<Subscriber*> m_subscribers;
	std::map<std::string, int> m_componentPrice;
};

#endif //_PUBLISHER_H_
