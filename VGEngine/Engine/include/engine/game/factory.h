#pragma once

#include "engine/assets/assetManager.h"
#include "engine/graphics/texture.h"
#include "engine/assets/fileManager.h"
#include "engine/game/textComponent.h"

#include <string>

namespace vg
{
	
	class Factory
	{
	public:
		Factory(core::AssetManager *assetManager, core::FileManager *fileManager);
		~Factory();
		template <typename T>
		T *createRenderComponent(std::string filename)
		{
			T *texComp = new T();
            if ((mAssetManager->get<vg::graphics::Texture>(filename)) == nullptr)
                mAssetManager->load<vg::graphics::Texture>(filename);
			graphics::Texture* texture = mAssetManager->get<vg::graphics::Texture>(filename);
			
			texComp->setTexture(texture);
			return texComp;
		}

        TextComponent* create(std::string fontPath, uint fontSize = 12u);

	private:
		core::AssetManager *mAssetManager;
		core::FileManager *mFileManager;
	};

}