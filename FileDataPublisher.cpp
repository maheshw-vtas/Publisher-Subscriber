#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <sys/types.h>
#include <dirent.h>

#include "FileDataPublisher.h"
#include "Utils.h"

using namespace std;

FileDataPublisher::FileDataPublisher()
{
}

FileDataPublisher::~FileDataPublisher()
{
}

void FileDataPublisher::notify()
{
	return notifySubscribers();
}

/*
* For specified component, read it's associated data file line-by-line, parse the and retrieve costs and calculate it's price 
*/
int FileDataPublisher::getComponentPrice(const std::string& componentName, int& price)
{

	//Open the component file
	std::ifstream componentFile(m_componentNameFileMap.at(componentName).c_str(), std::ios::in);
	if (!componentFile.is_open())
	{
		std::cout << "File could not be opened: " << m_componentNameFileMap.at(componentName) << "\n";
		return 1;
	}

	//Read file and calculate price
	string line;
	Tokenizer tokenizer;
	while (getline(componentFile, line))
	{
		std::istringstream istr(line);
		std::string key;
		int val = 0;
		tokenizer.getKeyVal(istr, key, val);
#if DEBUG
		std::cout << "Line[" << line << "] Key[" << key << "] Value[" << val << "]\n";
#endif
		price += val;
	}

#if DEBUG
	std::cout << componentName << ": total price = " << price << std::endl;
#endif
	return 0;
}

/*
* Read all component files in specified directory, calculate their prices and notifies registered subscribers 
*/
void FileDataPublisher::calculateAllComponentPrices(const std::string& dirPath)
{
	// Clear existing component information and their prices
	m_componentNameFileMap.clear();
	clearComponentinfo();

	// Get all component names  and associated files containing component price info
	if (0 != getComponentsinDir(dirPath))
	{
		std::cout << "Failed to get components in dir [" << dirPath << "]\n";
		return;
	}

	// Get prices of all components
	std::map<std::string, std::string>::const_iterator itr = m_componentNameFileMap.begin();
	for (; itr != m_componentNameFileMap.end(); itr++)
	{
		int componentPrice = 0;
		if (0 != getComponentPrice(itr->first, componentPrice))
		{
			std::cout << "Failed to get price of component [" << itr->first << "]\n";
			continue;
		}
		updateComponentInfo(itr->first, componentPrice);		
	}

	// Notify registerd subscribers
	notify();
}

/*
* Update price of existing component
* Reads components's associated file, calculates its price and notifies registered subscribers
*/
void FileDataPublisher::updateComponentPrice(const std::string& componentName)
{
	//Check if component exists in map
	if (m_componentNameFileMap.count(componentName) <= 0)
	{
		std::cout << "\nComponent [" << componentName << "] does not exist. If it's newly added component then please reload all components.\n";
		return;
	}

	//Get price of specified component from it's associated data file
	int componentPrice = 0;
	if (0 != getComponentPrice(componentName, componentPrice))
	{
		std::cout << "Failed to get price of component [" << componentName << "]\n";
		return;
	}
	updateComponentInfo(componentName, componentPrice);

	// Notify registerd subscribers
	notify();
}

/*
* This method accepts directory path as input and updates component name -> component file path map
* @in dirPath : Parent directory path containing all files. These files contain information about various factors which can be used
*				to calculate price of that component.
*
* @return : 0 if successful; otherwise non-zero value
*/
int FileDataPublisher::getComponentsinDir(const std::string& dirPath)
{
	int retval = 0;
	const static std::string pathsep = "/";
	//Open directory
	DIR* dirp = NULL;
	if ((dirp = opendir(dirPath.c_str())) == NULL)
	{
		std::cout << "Could not open directory [" << dirPath << "]\n";
		return 1;
	}

	// Read directory
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL)
	{
#if DEBUG
		std::cout << "d_name: " << dp->d_name << "\n";
#endif
		if ((dp->d_type != DT_REG) || (0 == strcmp(".", dp->d_name)) || (0 == strcmp("..", dp->d_name)))
		{
			continue;
		}
		
		m_componentNameFileMap[dp->d_name] = dirPath + pathsep + dp->d_name;
	}
	closedir(dirp);

	//Check whether any component file was found
	if (m_componentNameFileMap.size() <= 0)
	{
		std::cout << "Could not find any readable component file in [" << dirPath << "]\n";
		retval = 1;
	}
	return retval;
}
