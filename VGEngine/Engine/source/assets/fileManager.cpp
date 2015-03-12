
#include "engine/assets/fileManager.h"
#include <vector>
#include "engine/sound/Sound.h"
using namespace vg;

/// @todo Use the dedicated logger instead
#include <android/log.h>
#define Log(tag, message, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

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

bool FileManager::readAsset(const std::string& path, SoundEffectData* soundOutDat)
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

	Log("fm", "open? %s", ferror(file) == 0 ? "true" : "false");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		const size_t length = ftell(file);
		fseek(file, 0, SEEK_SET);

		std::vector<char> buffer(length);
		fread(&buffer[0], sizeof(char), buffer.size(), file);

		Log("fm", "read? %s", ferror(file) == 0 ? "true" : "false");

		fclose(file);

		Log("fm", "close? %s", ferror(file) == 0 ? "true" : "false");

		outData.assign(buffer.begin(), buffer.end());
	}

	return ferror(file) == 0;
}

bool FileManager::writeFile(DataPath dataPath, const std::string& path, const std::string& inData) const
{
	const std::string absolutePath = getDataPath(dataPath) + path;

	FILE* file = fopen(absolutePath.c_str(), "w");

	Log("fm", "open? %s", ferror(file) == 0 ? "true" : "false");

	if (file)
	{
		fwrite(inData.data(), sizeof(char), inData.size(), file);

		Log("fm", "write? %s", ferror(file) == 0 ? "true" : "false");

		fclose(file);

		Log("fm", "close? %s", ferror(file) == 0 ? "true" : "false");
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
