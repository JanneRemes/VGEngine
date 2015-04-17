#pragma once
#include <string>
#include <map>
#include <iostream>
namespace vg{

	class BaseClass
	{
	public:
		static std::map<std::string, int> memLeaks;
		std::string className;
		BaseClass(std::string name);
		~BaseClass();
		static int getValue(std::string name);
	};

}