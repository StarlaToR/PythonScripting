#pragma once
#include <IResource.h>
#include <Maths.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Log.h>
#include <glad/glad.h>

struct Vertex
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 TextureUV;
};

namespace Resources
{
	class Model : public IResource
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indexes;


	public:

		std::vector<Vertex> getVertexBuffer() { return vertices; }
		std::vector<uint32_t> getIndexBuffer() { return indexes; }

		void loadResource();
		void unloadResource();
		void printResource();

		~Model() 
		{

		}
	};
}