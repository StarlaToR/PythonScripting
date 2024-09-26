#include<GameObject.h>
using namespace Platformer;


GameObject::GameObject(LowRenderer::Mesh* m, const Vec3& pos, const Vec3& sca, const Vec3& rot, Shape* coll)
{
	transform = new Transform();
	transform->SetPosition(pos);
	transform->SetScale(sca);
	transform->SetRotation(rot);
	position = new float[3]{ pos.x, pos.y, pos.z };
	rotation = new float[3]{ rot.x, rot.y, rot.z };
	scale = new float[3]{ sca.x, sca.y, sca.z };
	mesh = m;
	collider = coll;
	collider->position += pos;
}

GameObject::GameObject(LowRenderer::Mesh* m, const Vec3& pos, const Vec3& sca, const Vec3& rot)
{
	transform = new Transform();
	transform->SetPosition(pos);
	transform->SetScale(sca);
	transform->SetRotation(rot);
	position = new float[3]{ pos.x, pos.y, pos.z };
	rotation = new float[3]{ rot.x, rot.y, rot.z };
	scale = new float[3]{ sca.x, sca.y, sca.z };
	mesh = m;
	collider = new Shape(rot, pos, sca, 1.f);
	collider->vertices.push_back(Vec3(1, 1, 1));
	collider->vertices.push_back(Vec3(-1, 1, 1));
	collider->vertices.push_back(Vec3(-1, 1, -1));
	collider->vertices.push_back(Vec3(1, 1, -1));
	collider->vertices.push_back(Vec3(1, -1, 1));
	collider->vertices.push_back(Vec3(-1, -1, 1));
	collider->vertices.push_back(Vec3(-1, -1, -1));
	collider->vertices.push_back(Vec3(1, -1, -1));
}

void GameObject::Update(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId)
{
	mesh->SetModelMatrix(transform->GetModelMatrix());
	mesh->Update(projviewMatrix, shaderProgram, sampler, textId);
	collider->position = transform->GetPosition();
	collider->rotation = transform->GetRotation();
	collider->scale = transform->GetScale() * 1.1f;
}

void GameObject::DrawHitbox(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId)
{
	hitbox->SetModelMatrix(CreateTransformMatrix(collider->position, collider->rotation, collider->scale));
	hitbox->Update(projviewMatrix, shaderProgram, sampler, textId);
}

void GameObject::SetMesh(LowRenderer::Mesh* m)
{
	mesh = m;
}

void GameObject::SetHitbox(LowRenderer::Mesh* m)
{
	hitbox = m;
}
