
#pragma once

#include <string>

/// @todo Fix comments in this file

namespace vg
{
	/**
		<description>
	*/
	class Asset
	{
		friend class AssetManager;
	public:
		/**
			<description>
			@param <param name> <description>
			@return <description>
		*/
		Asset(const std::string& path);

		virtual ~Asset() = default;

		/**
			<description>
			@return <description>
		*/
		virtual bool load() = 0;
		
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
		size_t mUseCount = 1;    ///< description
		bool mIsLoaded = false;  ///< description
	};
}
