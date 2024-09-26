#include<Maths.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////

float Vec3::GetMagnitude() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec3::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
}

Vec3 Vec3::GetNormalizedVector()
{
    return (Vec3(x / GetMagnitude(),
        y / GetMagnitude(),
        z / GetMagnitude()));
}


float edgeFunction(const Vec3& a, const Vec3& b, const Vec3& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float edgeFunction(const Vec4& a, const Vec4& b, const Vec4& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

Vec3 Vec3::GetBarycentricCoords(const Vec3& p0, const Vec3& p1, const Vec3& p2)
{
    Vec3 barycentricCoords;

    float area = edgeFunction(p0, p1, p2);
    float w0 = edgeFunction(p1, p2, *this);
    float w1 = edgeFunction(p2, p0, *this);
    float w2 = edgeFunction(p0, p1, *this);

    if (w0 <= 0 and w1 <= 0 and w2 <= 0)
    {
        barycentricCoords.x = w0 / area;
        barycentricCoords.y = w1 / area;
        barycentricCoords.z = w2 / area;
    }
    return barycentricCoords;
}

bool Vec3::operator==(const Vec3& a) const
{
    if (this->x == a.x && this->y == a.y && this->z == a.z)
        return true;

    return false;
}

void Vec3::operator+=(const Vec3& a)
{
    this->x += a.x;
    this->y += a.y;
    this->z += a.z;
}

void Vec3::operator-=(const Vec3& a)
{
    this->x -= a.x;
    this->y -= a.y;
    this->z -= a.z;
}

Vec3 operator+(const Vec3& a, const Vec3& b)
{
    Vec3 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
    return c;
}

Vec3 operator*(const Vec3& a, const float b)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Vec3 operator*(const float b, const Vec3& a)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Vec3 operator*(const Vec3& a, const Vec3& b)
{
    Vec3 d(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
    return d;
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
    Vec3 d(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    );
    return d;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////

void Vec4::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

Vec4 Vec4::GetHomogenizedVec()
{
    Vec4 vec = Vec4();
    if (w != 0)
    {
        vec.x = this->x / w;
        vec.y = this->y / w;
        vec.z = this->z / w;
    }

    return vec;
}

float Vec4::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec4::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
    //  w /= GetMagnitude();
}

bool Vec4::IsInTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{
    float e01 = (this->x - p0.x) * (p1.y - p0.y) - (this->y - p0.y) * (p1.x - p0.x);
    float e12 = (this->x - p1.x) * (p2.y - p1.y) - (this->y - p1.y) * (p2.x - p1.x);
    float e20 = (this->x - p2.x) * (p0.y - p2.y) - (this->y - p2.y) * (p0.x - p2.x);

    if (e01 <= 0 && e12 <= 0 && e20 <= 0)
        return true;
    else
        return false;
}

void Vec4::GetNewZForZBuffer()
{
    this->z = 2 * (this->z - 10) / (100 - 10) - 1;
}

Vec4 Vec4::GetBarycentricCoords(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{
    Vec4 barycentricCoords;

    float area = edgeFunction(p0, p1, p2);
    float w0 = edgeFunction(p1, p2, *this);
    float w1 = edgeFunction(p2, p0, *this);
    float w2 = edgeFunction(p0, p1, *this);

    if (w0 <= 0 and w1 <= 0 and w2 <= 0)
    {
        barycentricCoords.x = w0 / area;
        barycentricCoords.y = w1 / area;
        barycentricCoords.z = w2 / area;
    }
    return barycentricCoords;
}

Vec4 operator+(const Vec4& a, const Vec4& b)
{
    Vec4 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
    return c;
}

Vec4 operator-(const Vec4& a, const Vec4& b)
{
    Vec4 c(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
    return c;
}

Vec4 operator*(const Vec4& a, const float b)
{
    Vec4 c(
        a.x * b,
        a.y * b,
        a.z * b,
        a.w * b
    );
    return c;
}

void Vec4::operator*=(const float tab[4][4])
{
    float x1 = this->x;
    float y1 = this->y;
    float z1 = this->z;
    float w1 = this->w;

    this->x = tab[0][0] * x1 + tab[0][1] * y1 + tab[0][2] * z1 + tab[0][3] * w1;
    this->y = tab[1][0] * x1 + tab[1][1] * y1 + tab[1][2] * z1 + tab[1][3] * w1;
    this->z = tab[2][0] * x1 + tab[2][1] * y1 + tab[2][2] * z1 + tab[2][3] * w1;
    this->w = tab[3][0] * x1 + tab[3][1] * y1 + tab[3][2] * z1 + tab[3][3] * w1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat3                       /////////////////////////////////////////////////////

Mat3::Mat3(const float a[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tab[i][j] = a[i][j];
        }
    }
}

Mat3::Mat3(const float a, const float b, const float c,
           const float d, const float e, const float f,
           const float g, const float h, const float i)
{
    tab[0][0] = a;
    tab[0][1] = b;
    tab[0][2] = c;
    tab[1][0] = d;
    tab[1][1] = e;
    tab[1][2] = f;
    tab[2][0] = g;
    tab[2][1] = h;
    tab[2][2] = i;
}

void Mat3::PrintMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        printf("{ ");
        for (int j = 0; j < 2; j++)
            printf("%f, ", this->tab[i][j]);
        printf("%f }\n", this->tab[i][2]);
    }
    printf("\n\n");
}

Mat3 Mat3::GetTransposeMat3()
{
    Mat3 matrix = Mat3();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix.tab[i][j] = this->tab[j][i];
        }
    }
    return matrix;
}

Mat3 Mat3::GetAdjugateMat3()
{
    Mat3 matrix = Mat3();   

    matrix.tab[0][0] = GetDeterminantMat2(this->tab[1][1], this->tab[1][2], this->tab[2][1], this->tab[2][2]);
    matrix.tab[0][1] = GetDeterminantMat2(this->tab[1][0], this->tab[1][2], this->tab[2][0], this->tab[2][2]);
    matrix.tab[0][2] = GetDeterminantMat2(this->tab[1][0], this->tab[1][1], this->tab[2][0], this->tab[2][1]);

    matrix.tab[1][0] = GetDeterminantMat2(this->tab[0][1], this->tab[0][2], this->tab[2][1], this->tab[2][2]);
    matrix.tab[1][1] = GetDeterminantMat2(this->tab[0][0], this->tab[0][2], this->tab[2][0], this->tab[2][2]);
    matrix.tab[1][2] = GetDeterminantMat2(this->tab[0][0], this->tab[0][1], this->tab[2][0], this->tab[2][1]);

    matrix.tab[2][0] = GetDeterminantMat2(this->tab[0][1], this->tab[0][2], this->tab[1][1], this->tab[1][2]);
    matrix.tab[2][1] = GetDeterminantMat2(this->tab[0][0], this->tab[0][2], this->tab[1][0], this->tab[1][2]);
    matrix.tab[2][2] = GetDeterminantMat2(this->tab[0][0], this->tab[0][1], this->tab[1][0], this->tab[1][1]);

    return matrix;
}

Mat3 Mat3::GetInvertibleMat3()
{
    return (this->GetAdjugateMat3().GetTransposeMat3() * (1 / GetDeterminantMat3(this->tab)));
}

void Mat3::operator=(const Mat3& a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->tab[i][j] = a.tab[i][j];
        }
    }
}


void Mat3::operator*=(const Mat3& a)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.tab[i][j] += this->tab[i][k] * a.tab[k][j];
            }
        }
    }

    *this = c;
}

//Working
void Mat3::operator*=(const float a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->tab[i][j] *= a;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////

void Mat4::Translate(const Vec3& translation)
{
    /*
    printf("BEFORE:\n");
    PrintMatrix();\
    */

    this->tab[0][3] += translation.x;
    this->tab[1][3] += translation.y;
    this->tab[2][3] += translation.z;
    /*
    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n\n\n");
    */
}

void Mat4::Rotate(const Vec3& rotation)
{
    /*
    printf("BEFORE:\n");
    PrintMatrix();\
    */

    if (rotation.y != 0)
       *this *= CreateYRotationMatrix(rotation.y);
    if (rotation.x != 0)
       *this *= CreateXRotationMatrix(rotation.x);
    if (rotation.z != 0)
       *this *= CreateZRotationMatrix(rotation.z);

    /*
    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n\n\n");
    */
}

void Mat4::Scale(const Vec3& scale)
{
    /*
    printf("BEFORE:\n");
    PrintMatrix();\
    */

    *this *= CreateScaleMatrix(scale);

    /*
    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n\n\n");
    */
}

Mat4::Mat4(const float a[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tab[i][j] = a[i][j];
        }
    }
}

Mat4::Mat4(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, const float k, const float l, const float m, const float n, const float o, const float p)
{
    tab[0][0] = a;
    tab[0][1] = b;
    tab[0][2] = c;
    tab[0][3] = d;
    tab[1][0] = e;
    tab[1][1] = f;
    tab[1][2] = g;
    tab[1][3] = h;
    tab[2][0] = i;
    tab[2][1] = j;
    tab[2][2] = k;
    tab[2][3] = l;
    tab[3][0] = m;
    tab[3][1] = n;
    tab[3][2] = o;
    tab[3][3] = p;
}

void Mat4::PrintMatrix()
{
    for (int i = 0; i < 4; i++)
    {
        printf("{ ");
        for (int j = 0; j < 3; j++)
            printf("%f, ", this->tab[i][j]);
        printf("%f }\n", this->tab[i][3]);
    }
    printf("\n\n");
}

Mat4 Mat4::GetTransposeMat4()
{
    Mat4 matrix = Mat4();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix.tab[i][j] = this->tab[j][i];
        }
    }
    return matrix;
}

Mat4 Mat4::GetAdjugateMat4()
{
    Mat4 matrix = Mat4();

    matrix.tab[0][0] = GetDeterminantMat3({ this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[0][1] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[0][2] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[0][3] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[1][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[1][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[1][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[1][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[2][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[2][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[2][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[2][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[3][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] });
    matrix.tab[3][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] });
    matrix.tab[3][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] });
    matrix.tab[3][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] });

    return matrix;
}


Mat4 Mat4::GetInvertibleMat4()
{
    return (this->GetAdjugateMat4().GetTransposeMat4() * (1 / GetDeterminantMat4(*this)));
}


float GetDeterminantMat2(const float a, const float b, const float c, const float d)
{
    return (a * d - b * c);
}

float GetDeterminantMat3(const Vec3& a, const Vec3& b, const Vec3& c)
{
    return (
        a.x * GetDeterminantMat2(b.y, b.z, c.y, c.z)
        - a.y * GetDeterminantMat2(b.x, b.z, c.x, c.z)
        + a.z * GetDeterminantMat2(b.x, b.y, c.x, c.y)
        );
}

float GetDeterminantMat3(const float tab[3][3])
{
    return (
        tab[0][0] * GetDeterminantMat2(tab[1][1], tab[1][2], tab[2][1], tab[2][2])
        - tab[0][1] * GetDeterminantMat2(tab[1][0], tab[1][2], tab[2][0], tab[2][2])
        + tab[0][2] * GetDeterminantMat2(tab[1][0], tab[1][1], tab[2][0], tab[2][1])
        );
}

float GetDeterminantMat4(const Mat4& a)
{
    return(
        a.tab[0][0] * GetDeterminantMat3({ a.tab[1][1], a.tab[1][2], a.tab[1][3] }, { a.tab[2][1], a.tab[2][2], a.tab[2][3] }, { a.tab[3][1], a.tab[3][2], a.tab[3][3] })
        - a.tab[0][1] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][2], a.tab[1][3] }, { a.tab[2][0], a.tab[2][2], a.tab[2][3] }, { a.tab[3][0], a.tab[3][2], a.tab[3][3] })
        + a.tab[0][2] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][1], a.tab[1][3] }, { a.tab[2][0], a.tab[2][1], a.tab[2][3] }, { a.tab[3][0], a.tab[3][1], a.tab[3][3] })
        - a.tab[0][3] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][1], a.tab[1][2] }, { a.tab[2][0], a.tab[2][1], a.tab[2][2] }, { a.tab[3][0], a.tab[3][1], a.tab[3][2] })
        );
}




void Mat4::operator=(const Mat4& a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] = a.tab[i][j];
        }
    }
}


void Mat4::operator*=(const Mat4& a)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += this->tab[i][k] * a.tab[k][j];
            }
        }
    }

    *this = c;
}

//Working
void Mat4::operator*=(const float a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] *= a;
        }
    }
}

///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4 operator*(const Mat4& a, const Mat4& b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
            }
        }
    }

    return c;
}


Mat4 operator*(const Mat4& a, const float b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.tab[i][j] = a.tab[i][j] * b;
        }
    }

    return c;
}

Mat3 operator*(const Mat3& a, const Mat3& b)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
            }
        }
    }

    return c;
}

Mat3 operator*(const Mat3& a, const float b)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c.tab[i][j] = a.tab[i][j] * b;
        }
    }

    return c;
}


Vec4 operator*(const Mat4& a, const Vec4& b)
{
    Vec4 c = Vec4();

    c.x = a.tab[0][0] * b.x + a.tab[0][1] * b.y + a.tab[0][2] * b.z + a.tab[0][3] * b.w;
    c.y = a.tab[1][0] * b.x + a.tab[1][1] * b.y + a.tab[1][2] * b.z + a.tab[1][3] * b.w;
    c.z = a.tab[2][0] * b.x + a.tab[2][1] * b.y + a.tab[2][2] * b.z + a.tab[2][3] * b.w;
    c.w = a.tab[3][0] * b.x + a.tab[3][1] * b.y + a.tab[3][2] * b.z + a.tab[3][3] * b.w;

    return c;
}

Vec4 operator*(const Vec4& b, const Mat4& a)
{
    Vec4 c = Vec4();

    c.x = a.tab[0][0] * b.x + a.tab[0][1] * b.y + a.tab[0][2] * b.z + a.tab[0][3] * b.w;
    c.y = a.tab[1][0] * b.x + a.tab[1][1] * b.y + a.tab[1][2] * b.z + a.tab[1][3] * b.w;
    c.z = a.tab[2][0] * b.x + a.tab[2][1] * b.y + a.tab[2][2] * b.z + a.tab[2][3] * b.w;
    c.w = a.tab[3][0] * b.x + a.tab[3][1] * b.y + a.tab[3][2] * b.z + a.tab[3][3] * b.w;

    return c;
}

float GetMaximumDifference(const float a, const float b, const float c)
{
    float maxDiff = 0;
    float tab[6] = { a - b, a - c, b - a, b - c, c - a, c - b };
    for (int i = 0; i < 6; i++)
    {
        if (tab[i] > maxDiff)
            maxDiff = tab[i];
    }
    return maxDiff;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////           GJK Algorythm            /////////////////////////////////////////////////////

Vec3 Shape::GetFarthestPoint(const Vec3& direction)
{
    Vec3 maxPoint;
    float maxDistance = -1000;
    for (Vec3 vertex : vertices)
    {
        float distance = GetDotProduct(vertex, direction);
        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxPoint = vertex;
        }
    }
    Vec4 vec = maxPoint * CreateTransformMatrix(position, rotation, scale);
    maxPoint = Vec3(vec.x, vec.y, vec.z);
    return maxPoint;
}

Vec3 Sphere::GetFarthestPoint(const Vec3& direction)
{
    Vec3 dir = direction;
    Vec3 maxPoint = position + dir.GetNormalizedVector() * radius;
    return maxPoint;
}

bool GJK2D::GJK2d(Shape& s1, Shape& s2)
{
    Vec3 direction = (s2.position - s1.position).GetNormalizedVector();
    std::vector<Vec3> simplex;
    simplex.push_back(GJKsupport(s1, s2, direction));
    direction = Vec3() - simplex[0];
    while (true)
    {
        Vec3 a = GJKsupport(s1, s2, direction);

        if (GetDotProduct(a, direction) < 0)
            return false;
        simplex.push_back(a);
        if (handleSimplex2D(simplex, direction))
            return true;
    }
}

Vec3 GJK2D::GJKsupport(Shape& s1, Shape& s2, Vec3& direction)
{
    return (s1.GetFarthestPoint(direction) - s2.GetFarthestPoint(-1 * direction));
}

bool GJK2D::handleSimplex2D(std::vector<Vec3> simplex, Vec3& direction)
{
    if (simplex.size() == 2)
        return lineCase(simplex, direction);
    return triangleCase(simplex, direction);
}

bool GJK2D::lineCase(std::vector<Vec3> simplex, Vec3& direction)
{
    Vec3 b = simplex[0];
    Vec3 a = simplex[1];
    Vec3 o = Vec3();
    Vec3 ab = b - a;
    Vec3 ao = o - a;
    direction = GetCrossProduct(GetCrossProduct(ab, ao), ab);
    return false;
}

bool GJK2D::triangleCase(std::vector<Vec3> simplex, Vec3& direction)
{
    Vec3 c = simplex[0];
    Vec3 b = simplex[1];
    Vec3 a = simplex[2];
    Vec3 o = Vec3();
    Vec3 ab = b - a;
    Vec3 ac = c - a;
    Vec3 ao = o - a;
    Vec3 abPerp = GetCrossProduct(GetCrossProduct(ac, ab), ab);
    Vec3 acPerp = GetCrossProduct(GetCrossProduct(ab, ac), ac);

    if (GetDotProduct(abPerp, ao) > 0)
    {
        simplex.clear();
        simplex.push_back(a);
        simplex.push_back(b);
        direction = abPerp;
        return false;
    }
    else if (GetDotProduct(acPerp, ao) > 0)
    {
        simplex.clear();
        simplex.push_back(a);
        simplex.push_back(c);
        direction = acPerp;
        return false;
    }
    return true;
}

bool GJK3D::intersect(Shape& shape1, Shape& shape2)
{
    v = Vec3(1, 0, 0);//initial vector
    n = 0;//set simplex size 0

    c = support(shape1, shape2, v);

    if (GetDotProduct(c, v) < 0) {
        return false;
    }
    v = -1 * c;
    b = support(shape1, shape2, v);

    if (GetDotProduct(b, v) < 0) {
        return false;
    }
    v = tripleProduct(c - b, -1 * b);
    n = 2;

    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        Vec3 a = support(shape1, shape2, v);
        if (GetDotProduct(a, v) < 0) {
            // no intersection
            return false;
        }

        if (Update(a)) {
            return true;
        }
    }
    return true;
}

Vec3 GJK3D::support(Shape& shape1, Shape& shape2, const Vec3& v)
{
    Vec3 p1 = shape1.GetFarthestPoint(v);
    Vec3 p2 = shape2.GetFarthestPoint(-1 * v);//negate v
    Vec3 p3 = p1 - p2;
    return p3;
}

bool GJK3D::Update(const Vec3& a)
{
    if (n == 2) {
        //handling triangle
        Vec3 ao = -1 * a;
        Vec3 ab = b - a;
        Vec3 ac = c - a;

        Vec3 abc = GetCrossProduct(ab, ac);//normal of triangle abc

        // plane test on edge ab
        Vec3 abp = GetCrossProduct(ab, abc);//direction vector pointing inside triangle abc from ab
        if (GetDotProduct(abp, ao) > 0) {
            //origin lies outside the triangle abc, near the edge ab
            c = b;
            b = a;
            v = tripleProduct(ab, ao);
            return false;
        }

        //plane test on edge ac

        //direction vector pointing inside triangle abc from ac
        //note that different than abp, the result of acp is abc cross ac, while abp is ab cross abc.
        //The order does matter. Based on the right-handed rule, we want the vector pointing inside the triangle.
        Vec3 acp = GetCrossProduct(abc, ac);
        if (GetDotProduct(acp, ao) > 0) {
            //origin lies outside the triangle abc, near the edge ac
            b = a;
            v = tripleProduct(ac, ao);
            return false;
        }

        // Now the origin is within the triangle abc, either above or below it.
        if (GetDotProduct(abc, ao) > 0) {
            //origin is above the triangle
            d = c;
            c = b;
            b = a;
            v = abc;
        }
        else {
            //origin is below the triangle
            d = b;
            b = a;
            v = -1 * abc;
        }

        n = 3;

        return false;

    }

    if (n == 3) {
        Vec3 ao = -1 * a;
        Vec3 ab = b - a;
        Vec3 ac = c - a;
        Vec3 ad = d - a;

        Vec3 abc = GetCrossProduct(ab, ac);
        Vec3 acd = GetCrossProduct(ac, ad);
        Vec3 adb = GetCrossProduct(ad, ab);

        Vec3 tmp;

        const int over_abc = 0x1;
        const int over_acd = 0x2;
        const int over_adb = 0x4;

        int plane_tests =
            (GetDotProduct(abc, ao) > 0 ? over_abc : 0) |
            (GetDotProduct(acd, ao) > 0 ? over_acd : 0) |
            (GetDotProduct(adb, ao) > 0 ? over_adb : 0);

        switch (plane_tests) {
        case 0:
        {
            //inside the tetrahedron
            return true;
        }
        case over_abc:
        {
            if (!checkOneFaceAC(abc, ac, ao)) {
                //in the region of AC
                return false;
            }
            if (!checkOneFaceAB(abc, ab, ao)) {
                //in the region of AB
                return false;
            }

            //otherwise, in the region of ABC
            d = c;
            c = b;
            b = a;
            v = abc;
            n = 3;
            return false;
        }
        case over_acd:
        {
            //rotate acd to abc, and perform the same procedure
            b = c;
            c = d;

            ab = ac;
            ac = ad;

            abc = acd;

            if (!checkOneFaceAC(abc, ac, ao)) {
                //in the region of AC (actually is ad)
                return false;
            }
            if (!checkOneFaceAB(abc, ab, ao)) {
                //in the region of AB (actually is ac)
                return false;
            }

            //otherwise, in the region of "ABC" (which is actually acd)
            d = c;
            c = b;
            b = a;
            v = abc;
            n = 3;
            return false;

        }
        case over_adb:
        {
            //rotate adb to abc, and perform the same procedure
            c = b;
            b = d;

            ac = ab;
            ab = ad;

            abc = adb;
            if (!checkOneFaceAC(abc, ac, ao)) {
                //in the region of "AC" (actually is AB)
                return false;
            }
            if (!checkOneFaceAB(abc, ab, ao)) {
                //in the region of AB (actually is AD)
                return false;
            }

            //otherwise, in the region of "ABC" (which is actually acd)
            d = c;
            c = b;
            b = a;
            v = abc;
            n = 3;
            return false;
        }
        case over_abc | over_acd:
        {
            if (!checkTwoFaces(abc, acd, ac, ab, ad, ao)) {
                if (!checkOneFaceAC(abc, ac, ao)) {
                    //in the region of "AC" (actually is AB)
                    return false;
                }
                if (!checkOneFaceAB(abc, ab, ao)) {
                    //in the region of AB (actually is AD)
                    return false;
                }
                //otherwise, in the region of "ABC" (which is actually acd)
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
            else {
                if (!checkOneFaceAB(abc, ab, ao)) {
                    return false;
                }
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
        }
        case over_acd | over_adb:
        {
            //rotate ACD, ADB into ABC, ACD
            tmp = b;
            b = c;
            c = d;
            d = tmp;

            tmp = ab;
            ab = ac;
            ac = ad;
            ad = tmp;

            abc = acd;
            acd = adb;
            if (!checkTwoFaces(abc, acd, ac, ab, ad, ao)) {
                if (!checkOneFaceAC(abc, ac, ao)) {
                    //in the region of "AC" (actually is AB)
                    return false;
                }
                if (!checkOneFaceAB(abc, ab, ao)) {
                    //in the region of AB (actually is AD)
                    return false;
                }
                //otherwise, in the region of "ABC" (which is actually acd)
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
            else {
                if (!checkOneFaceAB(abc, ab, ao)) {
                    return false;
                }
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
        }
        case over_adb | over_abc:
        {
            //rotate ADB, ABC into ABC, ACD
            tmp = c;
            c = b;
            b = d;
            d = tmp;

            tmp = ac;
            ac = ab;
            ab = ad;
            ad = tmp;

            acd = abc;
            abc = adb;

            if (!checkTwoFaces(abc, acd, ac, ab, ad, ao)) {
                if (!checkOneFaceAC(abc, ac, ao)) {
                    //in the region of "AC" (actually is AB)
                    return false;
                }
                if (!checkOneFaceAB(abc, ab, ao)) {
                    //in the region of AB (actually is AD)
                    return false;
                }
                //otherwise, in the region of "ABC" (which is actually acd)
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
            else {
                if (!checkOneFaceAB(abc, ab, ao)) {
                    return false;
                }
                d = c;
                c = b;
                b = a;
                v = abc;
                n = 3;
                return false;
            }
        }
        default:
            return true;
        }
    }
    return true;
}

Vec3 GJK3D::tripleProduct(const Vec3& ab, const Vec3& c)
{
    return GetCrossProduct(GetCrossProduct(ab, c), ab);
}

bool GJK3D::checkOneFaceAC(const Vec3& abc, const Vec3& ac, const Vec3& ao)
{
    if (GetDotProduct(GetCrossProduct(abc, ac), ao) > 0) {
        //origin is in the region of edge ac
        b = -1 * ao;//b=a
        v = tripleProduct(ac, ao);
        n = 2;

        return false;
    }
    return true;
}
bool GJK3D::checkOneFaceAB(const Vec3& abc, const Vec3& ab, const Vec3& ao)
{
    if (GetDotProduct(GetCrossProduct(ab, abc), ao) > 0) {
        //origin in the region of edge ab
        c = b;
        b = -1 * ao;//b=a
        v = tripleProduct(ab, ao);
        n = 2;

        return false;
    }
    return true;
}

bool GJK3D::checkTwoFaces(Vec3& abc, Vec3& acd, Vec3& ac, Vec3& ab, Vec3& ad, const Vec3& ao)
{
    if (GetDotProduct(GetCrossProduct(abc, ac), ao) > 0) {
        b = c;
        c = d;
        ab = ac;
        ac = ad;

        abc = acd;
        return false;
    }
    return true;
}
/////////////////////////////////////////////           GJK Algorythm            ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////