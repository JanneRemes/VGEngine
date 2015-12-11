
#pragma once

#include <vector>
#include <stdint.h>
#include "engine/assets/asset.h"
#include "../external/glm/vec2.hpp"

namespace vg
{
	namespace graphics
	{
		class Texture : public core::Asset
		{
		public:

			inline bool operator<(Texture &tex)
			{
				if (pixels.size() < tex.pixels.size())
				{
					return true;
				}
				return false;
			}
			/**
				Constructor
				@param path Filepath for the texture, must be .png
				*/
			Texture(const std::string& path);

			~Texture() = default;

			/**
				<description>
				@param fileManager <description>
				@return <description>
				*/
			bool load(core::FileManager *fileManager);

			/**
				Deletes the loaded texture
				@return <description>
				*/
			bool unload();

			/**
				Binds the loaded texture
				@return Returns whether the texture is loaded or not
				*/
			void bind() const;

			/**
				Unbinds the loaded texture
				*/
			void unbind() const;

			/**
				Enables smoothing for the texture
				*/
			void setSmoothing(bool enable) const;

			/**
				@return Returns texture id
				*/
			uint32_t getId() const;

			/**
				@return Returns texture width
				*/
			uint32_t getWidth() const;

			/**
				@return Returns texture height
				*/
			uint32_t getHeight() const;

			/**
				@return Returns vector containing the pixel data of a texture
				*/
			std::vector<unsigned char> getDataVector() const;

			/**
			Repeating textures can be used for tiled backgrounds
			@param value enable or disable texture repeating
			*/
			void setRepeat(bool value);

		private:

			void init();
			uint32_t mWidth = 0;				///< Texture width
			uint32_t mHeight = 0;				///< Texture height
			uint32_t mId = 0;					///< Texture id
			std::vector<unsigned char>pixels;	///< Texture pixel data vector
			glm::vec2 textureRegion[4];			///< Texture Region(Coordinates for the texture in its texture atlas)
		};
	}
}