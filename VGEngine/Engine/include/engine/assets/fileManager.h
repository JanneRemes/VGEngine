
#pragma once

#include "engine\android_native_app_glue.h"
#include <android/asset_manager.h>
#include <string>

class FileManager
{
public:
	enum DataPath
	{
		Internal,
		External
	};

	FileManager(android_app* app);
	~FileManager() = default;

	bool readAsset(const std::string& path, std::string& outData);
	bool readFile(DataPath dataPath, const std::string& path, std::string& outData);
	bool writeFile(DataPath dataPath, const std::string& path, const std::string& inData) const;
private:
	std::string getDataPath(DataPath dataPath) const;

	AAssetManager* mAssetManager = nullptr;
	std::string mInternalDataPath;
	std::string mExternalDataPath;
};
