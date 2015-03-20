//
//#include "engine/graphics/sprite.h"
//
//using namespace vg;
//using namespace std;
//
//Sprite::Sprite(const Texture& texture)
//    :mTexture(texture)
//{
//
//}
//
//Sprite::~Sprite()
//{
//
//}
//
//void Sprite::draw(Shader& shader)
//{
//    VertexBuffer vertexBuffer(getVertices());
//    GraphicsDevice::draw(shader, vertexBuffer);
//}
//
//Texture* Sprite::getTexture()
//{
//    return &mTexture;
//}
//
//vector<float> Sprite::getVertices()
//{
//    float result[] = 
//    {
//        // Position Vec2
//        // Color Vec4
//        // TexCoord Vec2
//        //left up
//        -1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        //left down
//        -1.0f, -1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        0.0f, 0.0f,
//
//        //right down
//        1.0f, -1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 0.0f,
//
//        //right up
//        1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f
//
//    };
//    return vector<float>(result, result + sizeof(result) / sizeof(float));
//}
//
