
#pragma once

#include "engine\android_native_app_glue.h"
#include <android/asset_manager.h>
#include <string>

/// @todo Fix comments in this file

/**
	<description>
*/
class FileManager
{
public:
	/**
		<description>
	*/
	enum DataPath
	{
		Internal,
		External
	};

	/**
		<description>
		@param path <description>
		@return <description>
	*/
	FileManager(android_app* app);

	~FileManager() = default;

	/**
		<description>
		@param path <description>
		@return <description>
	*/
	bool readAsset(const std::string& path, std::string& outData);
	
	/**
		<description>
		@param path <description>
		@return <description>
	*/
	bool readFile(DataPath dataPath, const std::string& path, std::string& outData);
	
	/**
		<description>
		@param path <description>
		@return <description>
	*/
	bool writeFile(DataPath dataPath, const std::string& path, const std::string& inData) const;
private:
	/**
		<description>
		@param path <description>
		@return <description>
	*/
	std::string getDataPath(DataPath dataPath) const;

	AAssetManager* mAssetManager = nullptr; ///< description
	std::string mInternalDataPath;          ///< description
	std::string mExternalDataPath;          ///< description
};
