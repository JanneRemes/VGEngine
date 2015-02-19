
#pragma once

#include <string>
#include <vector>
#include <map>
#include "engine\assets\asset.h"

/// @todo Fix comments in this file

namespace vg
{
	/**
		Manages the lifetime of asset files and optimizes their (un)loading.
	*/
	class AssetManager
	{
	public:
		/**
			Retrieves an asset, returning a point to it, or null if it doesn't exist.
			@param path Path to the asset
			@return Point to the asset
		*/
		template<class T>
		const T* get(const std::string& path) const
		{
			const size_t hash = mHasher(path);

			Asset* asset = find(hash);

			if (asset)
			{
				return static_cast<T*>(asset);
			}
			
			return nullptr;
		}
		
		/**
			<description>
			@param path <description>
			@return <description>
		*/
		template<class T>
		void load(const std::string& path)
		{
			const size_t hash = mHasher(path);

			Asset* asset = find(hash);

			if (asset)
			{
				if (asset->mUseCount < static_cast<size_t>(-1))
				{
					asset->mUseCount++;
				}
			}
			else
			{
				mAssets[hash] = new T(path);
			}
		}
		
		/**
			<description>
			@param paths <description>
			@return <description>
		*/
		template<class T>
		void loadAll(const std::vector<std::string>& paths)
		{
			for (auto& e : paths)
			{
				load<T>(e);
			}
		}
		
		/**
			<description>
			@param path <description>
			@return <description>
		*/
		void unload(const std::string& path);

		/**
			<description>
			@param paths <description>
			@return <description>
		*/
		void unloadAll(const std::vector<std::string>& paths);

		/**
			<description>
		*/
		void unloadAll();

		/**
			<description>
		*/
		void commit();
	private:
		/**
			<description>
			@param hash <description>
			@return <description>
		*/
		Asset* find(size_t hash);

		/**
			<description>
			@param hash <description>
			@return <description>
		*/
		Asset const* find(size_t hash) const;

		std::hash<std::string> mHasher;   ///< description
		std::map<size_t, Asset*> mAssets; ///< description
	};
}
