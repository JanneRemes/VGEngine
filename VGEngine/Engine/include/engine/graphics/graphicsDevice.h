
#pragma once


namespace vg
{
	class Shader;
	class VertexBuffer;
	class IndexBuffer;
	
	class GraphicsDevice
	{
	public:
		static void draw(Shader& shader, VertexBuffer& vertices);
		static void draw(Shader& shader, VertexBuffer& vertices, IndexBuffer& indices);
	private:
	};
}
