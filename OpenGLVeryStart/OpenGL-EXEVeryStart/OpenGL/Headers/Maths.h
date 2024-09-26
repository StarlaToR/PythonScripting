#pragma once
#include <cmath>
#include <stdio.h>
#include <vector>


#define M_PI 3.14159265

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec2                       /////////////////////////////////////////////////////

class Vec2
{
public:
    float x;
    float y;


    Vec2(const float a, const float b)
    {
        x = a;
        y = b;
    }

    Vec2()
    {
        x = 0;
        y = 0;
    }
};


///////////////////////////////////                       Vec2                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3(const float a, const float b, const float c)
    {
        x = a;
        y = b;
        z = c;
    }

    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    float GetMagnitude() const;
    void Normalize();
    Vec3 GetNormalizedVector();
    bool IsInTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2);
    Vec3 GetBarycentricCoords(const Vec3& p0, const Vec3& p1, const Vec3& p2);

    void GetNewZForZBuffer();

    bool operator==(const Vec3& a) const;
    void operator+=(const Vec3& a);
    void operator-=(const Vec3& a);
};


///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat3                       /////////////////////////////////////////////////////

class Mat3
{
public:
    float tab[3][3];

    Mat3()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tab[i][j] = 0.f;
            }
        }
    }

    Mat3(const float a[3][3]);

    Mat3(
        const float a, const float b, const float c, 
        const float d, const float e, const float f,
        const float g, const float h, const float i
    );

    void PrintMatrix();
    Mat3 GetTransposeMat3();
    Mat3 GetAdjugateMat3();
    Mat3 GetInvertibleMat3();

    void operator*=(const Mat3& a);
    void operator*=(const float a);
    void operator=(const Mat3& a);
};

///////////////////////////////////                       Mat3                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////

class Mat4
{
public:
    float tab[4][4];

    Mat4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tab[i][j] = 0.f;
            }
        }
    }

    Mat4(const float a[4][4]);

    Mat4(
        const float a, const float b, const float c, const float d,
        const float e, const float f, const float g, const float h,
        const float i, const float j, const float k, const float l,
        const float m, const float n, const float o, const float p
    );


    void Translate(const Vec3& translation);
    void Rotate(const Vec3& rotation);
    void Scale(const Vec3& scale);

    void PrintMatrix();
    Mat4 GetTransposeMat4();
    Mat4 GetAdjugateMat4();
    Mat4 GetInvertibleMat4();

    void operator*=(const Mat4& a);
    void operator*=(const float a);
    void operator=(const Mat4& a);
};

///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4(const Vec3& vec3, float _w = 1.0f)
    {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
        w = _w;
    }

    Vec4(const float a, const float b, const float c, const float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }

    Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 1;
    }

    void Homogenize();
    Vec4 GetHomogenizedVec();
    float GetMagnitude();
    void Normalize();
    bool IsInTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2);
    Vec4 GetBarycentricCoords(const Vec4& p0, const Vec4& p1, const Vec4& p2);
    void GetNewZForZBuffer();

    friend Vec4 operator+(const Vec4& a, const Vec4& b);
    friend Vec4 operator-(const Vec4& a, const Vec4& b);

    friend Vec4 operator*(const Vec4& a, const float b);

    void operator*=(const float tab[4][4]);


};


///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////                Operator                /////////////////////////////////////////////////////


Mat4 operator*(const Mat4& a, const Mat4& b);
Mat4 operator*(const Mat4& a, const float b);

Mat3 operator*(const Mat3& a, const Mat3& b);
Mat3 operator*(const Mat3& a, const float b);

Vec4 operator+(const Vec4& a, const Vec4& b);
Vec4 operator*(const Vec4& a, const float b);
Vec4 operator*(const Vec4& b, const Mat4& a);
Vec4 operator*(const Mat4& a, const Vec4& b);


Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, const float b);
Vec3 operator*(const float b, const Vec3& a);
Vec3 operator*(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);

/////////////////////////////////////////////                Operator                /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////           Inline functions            /////////////////////////////////////////////////////


inline Vec3 GetNormalVector(const Vec3& p0, const Vec3& p1, const Vec3& p2)
{
    Vec3 normal = (p1 - p0) * (p2 - p0);
    return normal;
}

inline Vec4 GetMaximumXandY(const std::vector<Vec3>& vertices)
{
    float x = -1, y = -1;
    for (int i = 0; i < (int)vertices.size(); i++)
    {
        if (vertices[i].x >= x)
            x = vertices[i].x;
        if (vertices[i].y >= y)
            y = vertices[i].y;
    }
    return { x,y,0,1 };
}


inline Vec4 GetMinimumXandY(const std::vector<Vec3>& vertices)
{
    float x = 9999, y = 9999;
    for (int i = 0; i < (int)vertices.size(); i++)
    {
        if (vertices[i].x <= x)
            x = vertices[i].x;
        if (vertices[i].y <= y)
            y = vertices[i].y;
    }
    return { x,y,0,1 };
}

inline Vec3 getSphericalCoords(const float r, const float theta, const float phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

inline Mat4 GetIdentityMat4()
{
    Mat4 matrix = Mat4();
    matrix.tab[0][0] = 1;
    matrix.tab[1][1] = 1;
    matrix.tab[2][2] = 1;
    matrix.tab[3][3] = 1;
    return matrix;
}

inline Mat4 CreateTranslationMatrix(const Vec3& translation)
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][3] = translation.x;
    matrix.tab[1][3] = translation.y;
    matrix.tab[2][3] = translation.z;
    return matrix;
}

inline Mat4 CreateScaleMatrix(const Vec3& scale)
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = scale.x;
    matrix.tab[1][1] = scale.y;
    matrix.tab[2][2] = scale.z;
    return matrix;
}

inline Mat4 CreateXRotationMatrix(const float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[1][1] = cos(angle);
    matrix.tab[1][2] = -sin(angle);
    matrix.tab[2][1] = sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

inline Mat4 CreateYRotationMatrix(const float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][2] = sin(angle);
    matrix.tab[2][0] = -sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

inline Mat4 CreateZRotationMatrix(const float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][1] = -sin(angle);
    matrix.tab[1][0] = sin(angle);
    matrix.tab[1][1] = cos(angle);
    return matrix;
}



inline Mat4 CreateTransformMatrix(const Vec3& position, const Vec3& rotation, const Vec3& scale)
{
    Mat4 translation = CreateTranslationMatrix(position);
    Mat4 rotateX = CreateXRotationMatrix(rotation.x);
    Mat4 rotateY = CreateYRotationMatrix(rotation.y);
    Mat4 rotateZ = CreateZRotationMatrix(rotation.z);
    Mat4 scaling = CreateScaleMatrix(scale);

    Mat4 transform = translation * rotateY * rotateX * rotateZ * scaling;

    return transform;
}

inline Vec3 GetCrossProduct(const Vec3& a, const Vec3& b)
{
    return a * b;
}

inline float GetDotProduct(const Vec3& a, const Vec3& b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float DegToRad(float a)
{
    return a * M_PI / 180;
}

inline float RadToDeg(float a)
{
    return a * 180 / M_PI;
}

inline float GetAngleBetweenVectors(Vec3 vector1, Vec3 vector2)
{
    float angle = acos(GetDotProduct(vector1, vector2)) / (vector1.GetMagnitude() * vector2.GetMagnitude());
    if (vector1.x < 0)
        angle *= -1;
    return angle;
}

/////////////////////////////////////////////           Inline functions            /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float GetDeterminantMat2(const float a, const float b, const float c, const float d);
float GetDeterminantMat3(const Vec3& a, const Vec3& b, const Vec3& c);
float GetDeterminantMat3(const float tab[3][3]);
float GetDeterminantMat4(const Mat4& a);

float GetMaximumDifference(const float a, const float b, const float c);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////           GJK Algorythm            /////////////////////////////////////////////////////

class Shape
{
private:
    
public:
    Vec3 rotation;
    Vec3 position;
    Vec3 scale;
    std::vector<Vec3> vertices;
    float radius;

    Shape()
    {
        rotation = Vec3();
        position = Vec3();
        scale = Vec3(1,1,1);
        radius = 1;
    }

    Shape(const Vec3& rot, const Vec3& pos, const Vec3& sca, float rad)
    {
        rotation = rot;
        position = pos;
        scale = sca;
        radius = rad;
    }

    Vec3 GetFarthestPoint(const Vec3& direction);
};

class Sphere : public Shape
{
private:

public:
    Sphere()
    {
        rotation = Vec3();
        scale = Vec3();
        position = Vec3(1,1,1);
        radius = 1;
    }

    Sphere(const Vec3& rot, const Vec3& pos, const Vec3& sca, float rad)
    {
        rotation = rot;
        scale = sca;
        position = pos;
        radius = rad;
    }

    Vec3 GetFarthestPoint(const Vec3& direction);
};

class GJK2D
{
private:

public:
    bool GJK2d(Shape& s1, Shape& s2);
    Vec3 GJKsupport(Shape& s1, Shape& s2, Vec3& direction);
    bool handleSimplex2D(std::vector<Vec3> simplex, Vec3& direction);
    bool lineCase(std::vector<Vec3> simplex, Vec3& direction);
    bool triangleCase(std::vector<Vec3> simplex, Vec3& direction);
};

class GJK3D
{
public:
    bool intersect(Shape& shape1, Shape& shape2);
    Vec3 support(Shape& shape1, Shape& shape2, const Vec3& v);

private:
    Vec3 v;
    Vec3 b, c, d;
    unsigned int n; //simplex size

    const int MAX_ITERATIONS = 30;

    bool Update(const Vec3& a);

    Vec3 tripleProduct(const Vec3& ab, const Vec3& c);

    bool checkOneFaceAC(const Vec3& abc, const Vec3& ac, const Vec3& ao);
    bool checkOneFaceAB(const Vec3& abc, const Vec3& ab, const Vec3& ao);
    bool checkTwoFaces(Vec3& abc, Vec3& acd, Vec3& ac, Vec3& ab, Vec3& ad, const Vec3& ao);

};
/////////////////////////////////////////////           GJK Algorythm            ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////