#ifdef OS_0
#include "engine/assets/fileManager.h"
#include "engine\utility\logger.h"
#include "engine/sound/Sound.h"
#include <vector>

using namespace vg::core;

std::string mInternalDataPath;          ///< For reading and writing internal assets
std::string mExternalDataPath;          ///< For reading and writing external assets


FileManager::FileManager(android_app* app)
	: mAssetManager(app->activity->assetManager)
	, mInternalDataPath(std::string(app->activity->internalDataPath) + "/")
	, mExternalDataPath(std::string(app->activity->externalDataPath) + "/")
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

bool FileManager::readAsset(const std::string& path, std::vector<unsigned char>& outData)
{
	AAsset* asset = AAssetManager_open(mAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);
	const size_t length = AAsset_getLength(asset);
	outData.resize(length, 0);

	AAsset_read(asset, &outData[0], outData.size());
	AAsset_close(asset);
	return true;
}

bool FileManager::readAsset(const std::string& path, sound::SoundEffectData* soundOutDat)
{
	AAsset* asset = AAssetManager_open(mAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);

	off_t fileSize = AAsset_getLength(asset);
	off_t start, length;
	soundOutDat->fd = AAsset_openFileDescriptor(asset, &soundOutDat->start, &soundOutDat->length);
	AAsset_close(asset);
}

bool FileManager::readFile(DataPath dataPath, const std::string& path, std::string& outData)
{
	const std::string absolutePath = getDataPath(dataPath) + path;
	FILE* file = fopen(absolutePath.c_str(), "r");

	Log("vgengine", "open? %s", ferror(file) == 0 ? "true" : "false");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		const size_t length = ftell(file);
		fseek(file, 0, SEEK_SET);

		std::vector<char> buffer(length);
		fread(&buffer[0], sizeof(char), buffer.size(), file);

		Log("vgengine", "read? %s", ferror(file) == 0 ? "true" : "false");

		fclose(file);

		Log("vgengine", "close? %s", ferror(file) == 0 ? "true" : "false");

		outData.assign(buffer.begin(), buffer.end());
	}

	return ferror(file) == 0;
}

bool FileManager::writeFile(DataPath dataPath, const std::string& path, const std::string& inData) const
{
	const std::string absolutePath = getDataPath(dataPath) + path;

	FILE* file = fopen(absolutePath.c_str(), "w");

	Log("vgengine", "open? %s", ferror(file) == 0 ? "true" : "false");

	if (file)
	{
		fwrite(inData.data(), sizeof(char), inData.size(), file);

		Log("vgengine", "write? %s", ferror(file) == 0 ? "true" : "false");

		fclose(file);

		Log("vgengine", "close? %s", ferror(file) == 0 ? "true" : "false");
	}

	return ferror(file) == 0;
}

std::string FileManager::getDataPath(DataPath dataPath) const
{
	if (dataPath == DataPath::Internal)
	{
		return mInternalDataPath;
	}
	else
	{
		return mExternalDataPath;
	}
}
#endif