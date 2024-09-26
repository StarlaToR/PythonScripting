#pragma once
#include<Mesh.h>
#include<Transform.h>

using namespace Physics;

namespace Platformer
{

	class GameObject
	{
	private:
		LowRenderer::Mesh* mesh;
	
	public:
		Transform* transform;
		Shape* collider;
		LowRenderer::Mesh* hitbox;

		float* rotation;
		float* position;
		float* scale;

		GameObject()
		{
			mesh = nullptr;
			transform = new Transform();
			position = new float[3]{ 0,0,0 };
			rotation = new float[3]{ 0,0,0 };
			scale = new float[3]{ 1,1,1 };
			collider = new Sphere();
		}

		GameObject(LowRenderer::Mesh* m, const Vec3& pos, const Vec3& sca, const Vec3& rot, Shape* coll);
		GameObject(LowRenderer::Mesh* m, const Vec3& pos, const Vec3& sca, const Vec3& rot);

		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId);
		void DrawHitbox(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId);
		void SetMesh(LowRenderer::Mesh* m);
		void SetHitbox(LowRenderer::Mesh* m);
	};
}