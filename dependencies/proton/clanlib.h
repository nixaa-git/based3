#pragma once

struct CL_Vec2f
{
    float x;
    float y;

    CL_Vec2f() {}
    CL_Vec2f(float xx, float yy) : x(xx), y(yy) {}
};

struct CL_Vec2i
{
    int x;
    int y;

    CL_Vec2i() {}
    CL_Vec2i(int xx, int yy) : x(xx), y(yy) {}
};

struct CL_Vec3f
{
    float x;
    float y;
    float z;

    CL_Vec3f() {}
    CL_Vec3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
};

struct CL_Vec4f
{
    float x;
    float y;
    float z;
    float a;

    CL_Vec4f() {}
    CL_Vec4f(float xx, float yy, float zz, float aa) : x(xx), y(yy), z(zz), a(aa) {}
};

struct CL_Rectf
{
    float x;
    float y;
    float z;
    float a;

    CL_Rectf() {}
    CL_Rectf(float xx, float yy, float zz, float aa) : x(xx), y(yy), z(zz), a(aa) {}
};