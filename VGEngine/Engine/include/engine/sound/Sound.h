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

	/**
	Storing filedata for sound
	*/
	class Sound :
		public Asset
	{
	public:
		Sound(const std::string& path);
		~Sound();

		/**
		Loads sound from file
		@return true if succesful
		*/
		bool load(FileManager *fileManager);
		bool unload();
		SoundEffectData data;	///< Used to store sound data
	private:
	};

}