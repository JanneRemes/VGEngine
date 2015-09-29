#if defined (OS_WINDOWS)
#pragma once
#include "engine\assets\fileManager.h"
#include<fstream>
using namespace vg;
using namespace vg::core;
FileManager::FileManager()
{

}

bool FileManager::readAsset(const std::string& path, std::string& outData)
{ 
	readFile(FileManager::DataPath::File,"./assets/" + path, outData);
	return true;
}

bool FileManager::readAsset(const std::string& path, std::vector<unsigned char>& outData)
{

	std::ifstream ifstream(path.c_str());
	if (!ifstream.eof() && !ifstream.fail())
	{
		ifstream.seekg(0, std::ios_base::end);
		std::streampos fileSize = ifstream.tellg();
		outData.resize(fileSize);
		std::vector<char> tempData;
		ifstream.seekg(0, std::ios_base::beg);
		ifstream.read(&tempData[0], fileSize);
		for (int i = 0; i < tempData.size(); i++)
			outData.push_back(tempData[i]);
	}
	ifstream.close();
	return true;
}

bool FileManager::readAsset(const std::string& path, sound::SoundEffectData* soundOutDat)
{
	return true;
}

bool FileManager::readFile(DataPath dataPath, const std::string& path, std::string& outData)
{
	std::ifstream ifs(path);
	outData = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	/*outData = std::string();
	std::ifstream ifstream(path.c_str());
	ifstream.seekg(0, std::ios::end);
	outData.reserve(ifstream.tellg());
	ifstream.seekg(0, std::ios::beg);

	outData.assign((std::istreambuf_iterator<char>(ifstream)),
		std::istreambuf_iterator<char>());
	ifstream.close();*/
	return true;
}

bool FileManager::writeFile(DataPath dataPath, const std::string& path, const std::string& inData) const
{
	std::ofstream myfile;
	myfile.open(path);
	myfile << inData.c_str();
	myfile.close();
	return true;
}




#endif