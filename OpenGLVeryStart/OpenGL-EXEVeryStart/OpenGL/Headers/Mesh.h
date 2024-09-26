#pragma once
#include <Model.h>
#include <Math.h>
#include <Texture.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
	private:
		unsigned int VBO, VAO, EBO;
		Model* model;
		Texture* texture;
		Mat4 modelMatrix;
		bool isInit = false;
	public:

		Mesh(Model* mod, Texture* text);
		~Mesh();

		void Init(GLuint& sampler, int& textId);
		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId);
		void SetModelMatrix(const Mat4& modelMat);
		std::vector<Vec3> GetVertices();
	};
}