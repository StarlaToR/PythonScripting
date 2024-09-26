#pragma once
#include<GameObject.h>
#include<Maths.h>
#include<Mesh.h>

namespace Platformer
{
	class Enemy : public GameObject
	{
	public :
		using GameObject::GameObject;
		
		float movementRadius=10;
		float detectionRadius=20;
		
		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram);


	private:

	};
}