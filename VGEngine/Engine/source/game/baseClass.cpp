#include "engine\game\baseClass.h"
#include "engine\utility\logger.h"
#include <utility>
using namespace vg;
std::map<std::string, int> BaseClass::memLeaks;
BaseClass::BaseClass(std::string name){ 
	className = name; 
	int value = getValue(name);
	if (value == -1)
	memLeaks.insert(std::make_pair(name, 1)); 
	else
	{
		std::map<std::string, int>::iterator it = memLeaks.find(className);

		if (it != memLeaks.end())
			it->second = ++value;
	}
	Log("memory", "Current count for %s is %d.", name.c_str(), getValue(name));
}
BaseClass::~BaseClass(){ 
	int value = getValue(className);
	if (value != -1)
	{
		value--;
		
		std::map<std::string, int>::iterator it = memLeaks.find(className);

		if (it != memLeaks.end())
			it->second = value;
		Log("memory", "removing object: %s with value %d.", className.c_str(), value);
	}
	Log("memory", "Removed: %s", className.c_str()); 
}
int BaseClass::getValue(std::string name)
{
	std::map<std::string, int>::iterator it;
	it = memLeaks.find(name);
	if (it != memLeaks.end())
	{
		return (*it).second;
	}
	else
	{
		return -1;
	}
}