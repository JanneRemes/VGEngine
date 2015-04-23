#pragma once
#include "engine/assets/fileManager.h"
#include "engine/assets/asset.h"

namespace vg
{
	/**
	<description>
	*/
	struct SoundEffectData
	{
		off_t start;
		off_t length;
		int fd;
	};

	/**
	<class description>
	*/
	class Sound :
		public Asset
	{
	public:

		/**
		<description>
		@param path
		*/
		Sound(const std::string& path);
		~Sound();

		/**
		Loads sound from file
		@return <description>
		*/
		bool load(FileManager& fileManager);

		/**
		@return <description>
		*/
		bool unload();
		SoundEffectData data;	///< <description>
	private:
	};

}