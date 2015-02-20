
#pragma once

#include <string>

/// @todo Fix comments in this file

namespace vg
{
    class FileManager;

	/**
		<description>
	*/
	class Asset
	{
		friend class AssetManager;
	public:
		/**
			<description>
			@param path <description>
            @param fileManager <description>
			@return <description>
		*/
		Asset(const std::string& path);

		virtual ~Asset() = default;

		/**
			<description>
			@return <description>
		*/
        virtual bool load(FileManager& fileManager) = 0;
		
		/**
			<description>
			@return <description>
		*/
		virtual bool unload() = 0;
		
		/**
			<description>
			@return <description>
		*/
		bool isLoaded() const;
	protected:
		const std::string mPath; ///< description
		bool mIsLoaded = false;  ///< description
	private:
		size_t mUseCount = 1;    ///< description
	};
}
