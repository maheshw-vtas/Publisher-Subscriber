#ifndef _FILEDATAPUBLISHER_H_
#define _FILEDATAPUBLISHER_H_

#include <map>
#include <string>

#include "Publisher.h"

class FileDataPublisher : public Publisher {
public:
	FileDataPublisher();
	~FileDataPublisher();

	void calculateAllComponentPrices(const std::string& dirPath);
	void updateComponentPrice(const std::string& componentName);
	void notify();

private:
	/*
	* Component Name -> Component file Path
	*		map => {
	*				"abc" -> "/test/componentfiles/abc",
	*				"efg" -> "/test/componentfiles/efg",
	*				"asdf" -> "/test/componentfiles/asdf"
	*				}
	*/
	std::map<std::string, std::string> m_componentNameFileMap;

	int getComponentPrice(const std::string& componentName, int& price);	
	int getComponentsinDir(const std::string& dirPath);
};

#endif //_FILEDATAPUBLISHER_H_
