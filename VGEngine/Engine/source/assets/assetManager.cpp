
#include "engine/assets/assetManager.h"
#include "engine/assets/asset.h"

using namespace vg;

AssetManager::AssetManager(FileManager *fileManager)
    :mFileManager(fileManager)
{

}

void AssetManager::unload(const std::string& path)
{
	const size_t hash = mHasher(path);

	Asset* asset = find(hash);

	if (asset)
	{
		if (asset->mUseCount > 0)
		{
			asset->mUseCount--;
		}
	}
}

void AssetManager::unloadAll(const std::vector<std::string>& paths)
{
	for (auto& e : paths)
	{
		unload(e);
	}
}

void AssetManager::unloadAll()
{
	for (auto& e : mAssets)
	{
		e.second->mUseCount = 0;
	}
}

void AssetManager::commit()
{
	auto it = mAssets.begin();
	while (it != mAssets.end())
	{
		Asset* asset = it->second;

		if (asset->mUseCount > 0 &&
			asset->mIsLoaded == false)
		{
			asset->mIsLoaded = asset->load(mFileManager);
		}
		else if (asset->mUseCount == 0 &&
			asset->mIsLoaded == true)
		{
			asset->mIsLoaded = !asset->unload();
		}

		if (asset->mIsLoaded)
		{
			it++;
		}
		else
		{
			delete asset;
			mAssets.erase(it++);
		}
	}
}

Asset* AssetManager::find(size_t hash)
{
	auto it = mAssets.find(hash);

	if (it != mAssets.end())
	{
		return it->second;
	}

	return nullptr;
}

Asset const* AssetManager::find(size_t hash) const
{
	auto it = mAssets.find(hash);

	if (it != mAssets.end())
	{
		return it->second;
	}

	return nullptr;
}
