#include<Enemy.h>


void Platformer::Enemy::Update(const Mat4& projviewMatrix, unsigned int shaderProgram)
{
	Vec3 offset=Vec3(5,8,0);

	float x = sin(glfwGetTime()) * movementRadius ; 
	float z = cos(glfwGetTime()) * movementRadius ;

	transform->SetPosition(Vec3(x, 0, z) + offset);
	

}