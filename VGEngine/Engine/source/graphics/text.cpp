#define STB_TRUETYPE_IMPLEMENTATION
#include "engine\graphics\text.h"
#include <vector>
#include "engine\utility\logger.h"
using namespace vg;


text::text(std::string& fontPath, FileManager *manager)
{
	std::vector<unsigned char> charData;
	manager->readAsset(fontPath, charData);

	for (int i = 0; i < 50; i++)
		Log("text", "index %d is %c", i, charData[i]);
	const unsigned char* data = (const unsigned char*)&charData[0];
	stbtt_BakeFontBitmap(data, 0, 32.0, mBitmap, 512, 512, 32, 96, mData);
	glGenTextures(1, &ftex);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, mBitmap);
	// can free temp_bitmap at this point
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void text::print(float x,float y,char* text)
{
	std::vector<float> data= std::vector<float>();
	std::vector<uint32_t> index = std::vector<uint32_t>();
	glBindTexture(GL_TEXTURE_2D, ftex);
	//glBegin(GL_QUADS);
	while (*text) {
		if (*text >= 32 && *text < 128) {

			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(mData, 512, 512, *text - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
			
			//vertex x0 y0
			data.push_back(q.x0);
			data.push_back(q.y0);
			data.push_back(0.0f);//Z
			//UV
			data.push_back(q.s0);
			data.push_back(q.t1);

			//vertex x1 y0
			data.push_back(q.x1);
			data.push_back(q.y0);
			data.push_back(0.0f);//Z
			//UV
			data.push_back(q.s1);
			data.push_back(q.t1);

			//vertex x1 y1
			data.push_back(q.x1);
			data.push_back(q.y1);
			data.push_back(0.0f);//Z
			//UV
			data.push_back(q.s1);
			data.push_back(q.t0);

			//vertex x0 y1
			data.push_back(q.x0);
			data.push_back(q.y1);
			data.push_back(0.0f);//Z
			//UV
			data.push_back(q.s0);
			data.push_back(q.t0);

			for (int i = 0; i < 4; i++)
			{
				index.push_back(i==3?2:i);
			}
			index.push_back(3);
			index.push_back(0);
			/*
			glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y0);
			glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y0);
			glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y1);
			glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y1);
			*/
		}
		++text;
	}
	//glEnd();
}
