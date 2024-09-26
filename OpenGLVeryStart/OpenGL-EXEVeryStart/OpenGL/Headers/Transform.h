#pragma once
#include <Maths.h>

namespace Physics
{
    class Transform
    {
    private:
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
    public:
        Mat4 GetModelMatrix();

        void SetPosition(const Vec3& pos);
        void SetScale(const Vec3& sca);
        void SetRotation(const Vec3& rot);

        Vec3 GetPosition();
        Vec3 GetScale();
        Vec3 GetRotation();
    };
}