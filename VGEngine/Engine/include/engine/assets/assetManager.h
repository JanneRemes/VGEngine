
#pragma once

#include <string>
#include <vector>
#include <map>
#include "engine/assets/asset.h"
#include "engine/assets/fileManager.h"

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
            Constructor
            @param fileManager Filemanager class used for loading assets
        */
        AssetManager(FileManager& fileManager);

		/**
			Retrieves an asset, returning a point to it, or null if it doesn't exist.
			@param path Path to the asset
			@return Point to the asset
		*/
		template<class T>
		T* get(const std::string& path)
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
			Loads an asset from given path
			@param path The path for the asset we are trying to load
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
			Loads multiple assets from the path
			@param paths paths for the files we are trying to load
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
			Unloads an asset from the path
			@param path path for the files we are trying to unload
		*/
		void unload(const std::string& path);

		/**
			Unloads multiple assets from the path
			@param paths paths for the files we are trying to unload
		*/
		void unloadAll(const std::vector<std::string>& paths);

		/**
			Unloads every asset
		*/
		void unloadAll();

		/**
			Loads all the assets that are not yet loaded
		*/
		void commit();
	private:
		/**
			Finds and returns an asset from the given hash
			@param hash Hashcode that is given for every asset
			@return Asset
		*/
		Asset* find(size_t hash);

		/**
		Finds and returns an asset from the given hash
		@param hash Hashcode that is given for every asset
		@return Asset
		*/
		Asset const* find(size_t hash) const;

		std::hash<std::string> mHasher;		///< Hash from a string
		std::map<size_t, Asset*> mAssets;	///< Map that constains the asset and "id" for the said asset
        FileManager& mFileManager;			///< The manager that manages files
	};
}
