
#pragma once

#include "engine\android_native_app_glue.h"
#include <android/asset_manager.h>
#include <string>

/// @todo Fix comments in this file

namespace vg
{
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
			@param outData <description>
            @return <description>
        */
        bool readAsset(const std::string& path, std::string& outData);

		/**
            <description>
			@param path <description>
			@param outData <description>
            @return <description>
        */
		bool readAsset(const std::string& path, std::vector<unsigned char>& outData);

        /**
            <description>
			@param dataPath <description>
			@param path <description>
			@param outData <description>
            @return <description>
        */
        bool readFile(DataPath dataPath, const std::string& path, std::string& outData);

        /**
            <description>
			@param dataPath <description>
			@param path <description>
			@param inData <description>
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
}
