#include <Transform.h>

using namespace Physics;

Mat4 Transform::GetModelMatrix()
{
	return CreateTransformMatrix(position, rotation, scale);
}

void Transform::SetPosition(const Vec3& pos)
{
	position = pos;
}

void Transform::SetScale(const Vec3& sca)
{
	scale = sca;
}

void Transform::SetRotation(const Vec3& rot)
{
	rotation = rot;
}

Vec3 Transform::GetPosition()
{
	return position;
}

Vec3 Transform::GetScale()
{
	return scale;
}

Vec3 Transform::GetRotation()
{
	return rotation;
}