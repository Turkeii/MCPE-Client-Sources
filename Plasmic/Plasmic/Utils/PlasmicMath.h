#pragma once

#define PI 3.14159265359

extern float DegreeToRadiant(float degree);

struct Vec2 {
	float x, y;

	Vec2() { x = y = 0.f; }
	Vec2(float nx, float ny) 
	:x(nx), y(ny){}

	float Distance(const Vec2& other);
};
bool operator == (Vec2 v1, Vec2 v2);
bool operator != (Vec2 v1, Vec2 v2);
void operator += (Vec2& v1, float number);
void operator += (Vec2& v1, Vec2 v2);
void operator -= (Vec2& v1, float number);
void operator -= (Vec2& v1, Vec2 v2);
void operator *= (Vec2& v1, float number);
void operator /= (Vec2& v1, float number);
Vec2 operator + (Vec2 v1, float number);
Vec2 operator + (Vec2 v1, Vec2 v2);
Vec2 operator - (Vec2 v1, float number);
Vec2 operator - (Vec2 v1, Vec2 v2);
Vec2 operator * (Vec2 v1, float number);
Vec2 operator / (Vec2 v1, float number);


struct BlockPos {
	int x, y, z;

	BlockPos() { x = y = z = 0; }
	BlockPos(int nx, int ny, int nz)
		:x(nx), y(ny), z(nz) {}

};
bool operator == (BlockPos b1, BlockPos b2);
bool operator != (BlockPos b1, BlockPos b2);
void operator += (BlockPos& v1, int number);
void operator += (BlockPos& v1, BlockPos v2);
void operator -= (BlockPos& v1, int number);
void operator -= (BlockPos& v1, BlockPos v2);
void operator *= (BlockPos& v1, int number);
void operator /= (BlockPos& v1, int number);


struct Vec3 {
	float x, y, z;

	Vec3() { x = y = z = 0.f; }
	Vec3(float nx, float ny, float nz)
		:x(nx), y(ny), z(nz) {}

	float Distance(const Vec3& other);

};
bool operator == (Vec3 v1, Vec3 v2);
bool operator != (Vec3 v1, Vec3 v2);
void operator += (Vec3& v1, float number);
void operator += (Vec3& v1, Vec3 v2);
void operator -= (Vec3& v1, float number);
void operator -= (Vec3& v1, Vec3 v2);
void operator *= (Vec3& v1, float number);
void operator /= (Vec3& v1, float number);


struct Rect {
	float x, y, z, w;

	Rect() { x = y = z = w = 0.f; }
	Rect(float nx, float ny, float nz, float nw)
		:x(nx), y(ny), z(nz), w(nw) {}

	bool isInside(float PointX, float PointY);
	bool isInside(Vec2 Point);
};
bool operator == (Rect r1, Rect r2);
bool operator != (Rect r1, Rect r2);
void operator += (Rect& r1, float number);
void operator += (Rect& r1, Rect r2);
void operator -= (Rect& r1, float number);
void operator -= (Rect& r1, Rect r2);
void operator *= (Rect& r1, float number);
void operator /= (Rect& r1, float number);