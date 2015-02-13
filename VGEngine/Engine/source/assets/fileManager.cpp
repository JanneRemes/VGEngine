
#include "engine\assets\fileManager.h"
#include <vector>

FileManager::FileManager(android_app* application)
	: mAssetManager(application->activity->assetManager)
{
}

bool FileManager::readAsset(const std::string& path, std::string& outData)
{
	AAsset* asset = AAssetManager_open(mAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);
	const size_t length = AAsset_getLength(asset);
	std::vector<char> buffer(length, 0);

	AAsset_read(asset, &buffer[0], buffer.size());
	AAsset_close(asset);
	outData.assign(buffer.begin(), buffer.end());
	return true;
}

bool FileManager::readFile(const std::string& path, std::string& outData)
{
	FILE* file = fopen(path.c_str(), "r");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		const size_t length = ftell(file);

		std::vector<char> buffer(length);
		fread(&buffer[0], sizeof(char), buffer.size(), file);
		fclose(file);

		outData.assign(buffer.begin(), buffer.end());
	}

	return ferror(file) == 0;
}

bool FileManager::writeFile(const std::string& path, const std::string& inData) const
{
	FILE* file = fopen(path.c_str(), "w");

	if (file)
	{
		fwrite(inData.data(), sizeof(char), inData.size(), file);
		fclose(file);
	}

	return ferror(file) == 0;
}
