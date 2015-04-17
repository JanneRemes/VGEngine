
#include "engine/graphics/batch.h"
#include "engine/graphics/graphicsDevice.h"

using namespace vg;
using namespace std;
using Ite = vector<RenderComponent*>::iterator;

Batch::Batch(Texture* texture)
    :mTexture(texture), mBuffersOutOfDate(false)
{
}

Batch::~Batch()
{

}

void Batch::add(RenderComponent* drwawable)
{
    mDrawables.push_back(drwawable);
    mBuffersOutOfDate = true;
}

void Batch::draw(Shader& shader)
{
    if (mBuffersOutOfDate)
    {
        /*
        vector<uint> indices;
        for (Ite i = mDrawables.begin(); i != mDrawables.end(); i++)
        {
            /// @todo relative indices
            indices.push_back(*(*i)->getIndices());
        }
        mIndexBuffer.setData(indices);
    
        vector<float> vertices;
        for (Ite i = mDrawables.begin(); i != mDrawables.end(); i++)
        {
            vertices.push_back((*i)->getIndices());
        }
        mVertexBuffer.setData(vertices);

        mBuffersOutOfDate = false;
        */
    }
    shader.useProgram();
    mTexture->bind();
    shader.unUseProgram();

    GraphicsDevice::draw(&shader, &mVertexBuffer, &mIndexBuffer);

    shader.useProgram();
    mTexture->unbind();
    shader.unUseProgram();
}
