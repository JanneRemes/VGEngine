
#pragma once

#include "engine/assets/asset.h"
#include <GLES2/gl2.h>
namespace vg
{
	class Texture : public Asset
	{
	public:
		/**
			<description>
			@param fileManager <description>
		*/
		Texture(const std::string& path);

		~Texture();

		/**
			<description>
			@param fileManager <description>
			@return <description>
		*/
		bool load(FileManager& fileManager);

		/**
			<description>
			@return <description>
		*/
		bool unload();

		/**
			<description>
			@return <description>
		*/
		void bind() const;

		/**
			<description>
			@return <description>
		*/
		void unbind() const;

		/**
			<description>
			@return <description>
		*/
		void setSmoothing(bool enable) const;

		/**
			<description>
			@return <description>
		*/
		uint32_t getId() const;

		/**
			<description>
			@return <description>
		*/
		uint32_t getWidth() const;

		/**
			<description>
			@return <description>
		*/
		uint32_t getHeight() const;
	private:
		void init();

		uint32_t mWidth = 0;
		uint32_t mHeight = 0;
		uint32_t mId = 0; ///< description
	};

}