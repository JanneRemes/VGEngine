
#pragma once

#include "engine/graphics/graphicsContext.h"
#include "engine/graphics/shader.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/spriteBatch.h"

#include <string>
#include <vector>

namespace vg
{
    class Graphics
    {
    public:
        Graphics();
        ~Graphics();

        void initialize(android_app* app, const Shader& shader = Shader());
        void unInitialize();
        bool isInitialized();
        void swapBuffers();
        int getScreenWidth();
        int getScreenHeight();
        void switchShader(std::string vertexPath, std::string fragmentPath);
        //void draw();
        //void append(SpriteBatch* spriteBatch);

    private:
        FileManager* mFileManager;
        GraphicsContext mContext;
        Shader mShader;
        bool mInitialized;
        //std::vector<SpriteBatch*> mBatches;

    };
}