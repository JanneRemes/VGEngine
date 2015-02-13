
#pragma once

#include "engine\android_native_app_glue.h"
#include <android/asset_manager.h>
#include <string>

class FileManager
{
public:
	FileManager(android_app* application);
	~FileManager() = default;

	bool readAsset(const std::string& path, std::string& outData);
	bool readFile(const std::string& path, std::string& outData);
	bool writeFile(const std::string& path, const std::string& inData) const;
private:
	AAssetManager* mAssetManager = nullptr;
};
