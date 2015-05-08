
#pragma once

#include "engine/game/component.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/utility/Vector2.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/shader.h"

#include <vector>
#include <string>
#include "GLES2/gl2.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vg
{
    class TextComponent : public Component
    {
    public:
        TextComponent(std::string& fontPath, FileManager *manager);
        ~TextComponent();
        
        void draw(graphics::Shader* shader);
        void setText(std::string text);
        void setFontSize(uint fontSize);
        void setPosition(Vector2<int> position);

    private:
        /**
        Default vertices
        */
        const std::vector<float> defaultVertices =
        {
            // Position Vec2
            // Color Vec4
            // TexCoord Vec2

            //left up
            0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f,

            //left down
            0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f,

            //right down
            1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f,

            //right up
            1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f
        };

        /**
        Default indices
        */
        const std::vector<uint> defaultIndices =
        {
            0u, 1u, 2u,
            0u, 2u, 3u
        };

        GLuint mTexture;				        ///< <Font texture ID>
        graphics::VertexBuffer* mVertexBuffer;	///< <Vertex buffer for drawing>
        graphics::IndexBuffer* mIndexBuffer;	///< <Index buffer for drawing>

        std::vector<FT_Byte> mCharData;	        ///< <Vector where fontfile is saved>
        Vector2<int> mPosition;			        ///< <Text position>
        std::string mText;				        ///< <String to render>

        FT_UInt mGlyph_index;			        ///< <Glyph index for each char>
        FT_Library mLibrary;			        ///< <Freetype library>
        FT_Face mFace;					        ///< <Face that includes the loaded font>
        FT_GlyphSlot mGlyph;			        ///< <Slot where each glyph is saved>
        FT_UInt mFontSize;				        ///< <Fontsize for text>
    };
}
