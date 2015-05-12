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
		Factory(AssetManager *assetManager,FileManager *fileManager);
		~Factory();
		template <typename T>
		T *createRenderComponent(std::string filename)
		{
			T *texComp = new T();
			
            graphics::Texture *texture;
            if ((mAssetManager->get<vg::graphics::Texture>(filename)) == nullptr)
            {
                mAssetManager->load<vg::graphics::Texture>(filename);
                texture = mAssetManager->get<vg::graphics::Texture>(filename);
                texture->load(mFileManager);
            }
            else
                texture = mAssetManager->get<vg::graphics::Texture>(filename);

			
			texComp->setTexture(texture);
			return texComp;
		}

        TextComponent* create(std::string fontPath, uint fontSize = 12u);

	private:
		AssetManager *mAssetManager;
		FileManager *mFileManager;
	};

}