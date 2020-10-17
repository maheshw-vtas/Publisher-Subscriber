#ifndef _SUBSCRIBER_H_
#define _SUBSCRIBER_H_

#include <map>
#include <string>

class Subscriber {
public:
	Subscriber() {};
	virtual ~Subscriber() {};
	virtual void update(const std::map<std::string, int>& datamap) = 0;

private:
	Subscriber(const Subscriber&);
	Subscriber& operator=(const Subscriber&);
};

#endif //_SUBSCRIBER_H_
