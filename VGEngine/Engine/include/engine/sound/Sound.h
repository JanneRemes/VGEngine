#pragma once
#include "engine/assets/fileManager.h"
#include "engine/assets/asset.h"

namespace vg
{
	struct SoundEffectData
	{
		off_t start;
		off_t length;
		int fd;
	};
	class Sound :
		public Asset
	{
	public:
		Sound(const std::string& path);
		~Sound();
		bool load(FileManager& fileManager);
		bool unload();
		SoundEffectData data;
	private:
	};

}