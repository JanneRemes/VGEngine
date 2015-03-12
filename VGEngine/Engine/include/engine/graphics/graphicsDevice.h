
#pragma once


namespace vg
{
	class Shader;
	class VertexBuffer;
	class IndexBuffer;
	
	class GraphicsDevice
	{
	public:
		void draw(Shader& shader, VertexBuffer& vertices);
		void draw(Shader& shader, VertexBuffer& vertices, IndexBuffer& indices);
	private:
	};
}
