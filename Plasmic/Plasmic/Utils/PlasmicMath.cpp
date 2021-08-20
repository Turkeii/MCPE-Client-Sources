#include "PlasmicMath.h"
#include <DirectXMath.h>



float DegreeToRadiant(float degree) {
	return (float)(degree * PI / 180);
}




//Vec2

float Vec2::Distance(const Vec2& other) {
	Vec2 one;
	Vec2 two;
	if (x > other.x) {
		one.x = other.x;
		two.x = x;
	} else {
		one.x = x;
		two.x = other.x;
	}
	if (y > other.y) {
		one.y = other.y;
		two.y = y;
	} else {
		one.y = y;
		two.y = other.y;
	}

	two.x -= one.x;
	two.y -= one.y;

	return sqrtf((two.x * two.x) + (two.y * two.y));
}
bool operator == (Vec2 v1, Vec2 v2) {
	return v1.x == v2.x && v1.y == v2.y;
}
bool operator != (Vec2 v1, Vec2 v2) {
	return v1.x != v2.x || v1.y != v2.y;
}
void operator += (Vec2& v1, float number) {
	v1.x += number;
	v1.y += number;
}
void operator += (Vec2& v1, Vec2 v2) {
	v1.x += v2.x;
	v1.y += v2.y;
}
void operator -= (Vec2& v1, float number) {
	v1.x -= number;
	v1.y -= number;
}
void operator -= (Vec2& v1, Vec2 v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
}
void operator *= (Vec2& v1, float number) {
	v1.x *= number;
	v1.y *= number;
}
void operator /= (Vec2& v1, float number) {
	v1.x /= number;
	v1.y /= number;
}
Vec2 operator + (Vec2 v1, float number) {
	v1.x += number;
	v1.y += number;
	return v1;
}
Vec2 operator + (Vec2 v1, Vec2 v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}
Vec2 operator - (Vec2 v1, float number) {
	v1.x -= number;
	v1.y -= number;
	return v1;
}
Vec2 operator - (Vec2 v1, Vec2 v2) {
	v1.x = v2.x;
	v1.y = v2.y;
	return v1;
}
Vec2 operator * (Vec2 v1, float number) {
	v1.x *= number;
	v1.y *= number;
	return v1;
}
Vec2 operator / (Vec2 v1, float number) {
	v1.x /= number;
	v1.y /= number;
	return v1;
}



//BlockPos
bool operator == (BlockPos b1, BlockPos b2) {
	return b1.x == b2.x && b1.y == b2.y && b1.z == b2.z;
}
bool operator != (BlockPos b1, BlockPos b2) {
	return b1.x != b2.x || b1.y != b2.y || b1.z != b2.z;
}
void operator += (BlockPos& v1, int number) {
	v1.x += number;
	v1.y += number;
	v1.z += number;
}
void operator += (BlockPos& v1, BlockPos v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}
void operator -= (BlockPos& v1, int number) {
	v1.x -= number;
	v1.y -= number;
	v1.z -= number;
}
void operator -= (BlockPos& v1, BlockPos v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}
void operator *= (BlockPos& v1, int number) {
	v1.x *= number;
	v1.y *= number;
	v1.z *= number;
}
void operator /= (BlockPos& v1, int number) {
	v1.x /= number;
	v1.y /= number;
	v1.z /= number;
}


//Vec3
bool operator == (Vec3 v1, Vec3 v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
bool operator != (Vec3 v1, Vec3 v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}
void operator += (Vec3& v1, float number) {
	v1.x += number;
	v1.y += number;
	v1.z += number;
}
void operator += (Vec3& v1, Vec3 v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}
void operator -= (Vec3& v1, float number) {
	v1.x -= number;
	v1.y -= number;
	v1.z -= number;
}
void operator -= (Vec3& v1, Vec3 v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}
void operator *= (Vec3& v1, float number) {
	v1.x *= number;
	v1.y *= number;
	v1.z *= number;
}
void operator /= (Vec3& v1, float number) {
	v1.x /= number;
	v1.y /= number;
	v1.z /= number;
}

float Vec3::Distance(const Vec3& other) {
	Vec3 one;
	Vec3 two;
	if (x > other.x) {
		one.x = other.x;
		two.x = x;
	} else {
		one.x = x;
		two.x = other.x;
	}
	if (y > other.y) {
		one.y = other.y;
		two.y = y;
	} else {
		one.y = y;
		two.y = other.y;
	}
	if (z > other.z) {
		one.z = other.z;
		two.z = z;
	} else {
		one.z = z;
		two.z = other.z;
	}

	two.x -= one.x;
	two.y -= one.y;
	two.z -= one.z;

	return sqrtf(powf(sqrtf((two.x * two.x) + (two.y * two.y)), 2.f) + (two.z * two.z));
}


//Rect

bool Rect::isInside(float PointX, float PointY) {
	if (PointX < x)
		return false;
	if (PointY < y)
		return false;
	if (PointX > z)
		return false;
	if (PointY > w)
		return false;
	return true;
}
bool Rect::isInside(Vec2 Point) {
	if (Point.x < x)
		return false;
	if (Point.y < y)
		return false;
	if (Point.x > z)
		return false;
	if (Point.y > w)
		return false;
	return true;
}


bool operator == (Rect r1, Rect r2) {
	return r1.x == r2.x && r1.y == r2.y && r1.z == r2.z && r1.w == r2.w;
}
bool operator != (Rect r1, Rect r2) {
	return r1.x != r2.x || r1.y != r2.y || r1.z != r2.z || r1.w != r2.w;
}
void operator += (Rect& r1, float number) {
	r1.x += number;
	r1.y += number;
	r1.z += number;
	r1.w += number;
}
void operator += (Rect& r1, Rect r2) {
	r1.x += r2.x;
	r1.y += r2.y;
	r1.z += r2.z;
	r1.w += r2.w;
}
void operator -= (Rect& r1, float number) {
	r1.x -= number;
	r1.y -= number;
	r1.z -= number;
	r1.w -= number;
}
void operator -= (Rect& r1, Rect r2) {
	r1.x -= r2.x;
	r1.y -= r2.y;
	r1.z -= r2.z;
	r1.w -= r2.w;
}
void operator *= (Rect& r1, float number) {
	r1.x *= number;
	r1.y *= number;
	r1.z *= number;
	r1.w *= number;
}
void operator /= (Rect& r1, float number) {
	r1.x /= number;
	r1.y /= number;
	r1.z /= number;
	r1.w /= number;
}