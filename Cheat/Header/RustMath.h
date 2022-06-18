#pragma once

inline void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

class Vector3
{
public:
	float x, y, z;

	Vector3() {
		x = y = z = 0.f;
	}

	Vector3(float fx, float fy, float fz) {
		x = fx;
		y = fy;
		z = fz;
	}

	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	static Vector3 One() {
		return Vector3(1.0f, 1.0f, 1.0f);
	}

	static Vector3 Up() {
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	static Vector3 Down() {
		return Vector3(0.0f, -1.0f, 0.0f);
	}

	static Vector3 Left() {
		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	static Vector3 Right() {
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	static Vector3 Forward() {
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	static Vector3 Back() {
		return Vector3(0.0f, 0.0f, -1.0f);
	}
	static float Clamp01(float value)
	{
		if (value < 0.f)
			return 0.f;
		else if (value > 1.f)
			return 1.f;
		else
			return value;
	}

	static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		t = Clamp01(t);
		return Vector3(
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t,
			a.z + (b.z - a.z) * t
		);
	}

	Vector3 operator+(const Vector3& input) const {
		return Vector3{ x + input.x, y + input.y, z + input.z };
	}

	Vector3 operator+(const float& input) const {
		return Vector3{ x + input, y + input, z + input };
	}

	Vector3 operator-(const Vector3& input) const {
		return Vector3{ x - input.x, y - input.y, z - input.z };
	}

	Vector3 operator/(float input) const {
		return Vector3{ x / input, y / input, z / input };
	}

	Vector3 operator*(float input) const {
		return Vector3{ x * input, y * input, z * input };
	}

	Vector3 operator*(Vector3 input) const {
		return Vector3{ x * input.x, y * input.y, z * input.z };
	}

	Vector3 operator/(Vector3 input) const {
		return Vector3{ x / input.x, y / input.y, z / input.z };
	}

	bool operator>(float input) const
	{
		if (x > input) return true;
		if (y > input) return true;
		if (z > input) return true;
		return false;
	}

	bool operator<(float input) const
	{
		if (x < input) return true;
		if (y < input) return true;
		if (z < input) return true;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}

	float operator[](int i) const {
		return ((float*)this)[i];
	}

	Vector3& operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator/=(float input) {
		x /= input;
		y /= input;
		z /= input;
		return *this;
	}

	Vector3& operator*=(float input) {
		x *= input;
		y *= input;
		z *= input;
		return *this;
	}

	bool operator==(const Vector3& input) const {
		return x == input.x && y == input.y && z == input.z;
	}
	bool operator!=(const Vector3& input) const {
		if (x != input.x || y != input.y || z != input.z)
			return true;

		return false;
	}

	void make_absolute() {
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	float UnityMagnitude()
	{
		return (float)sqrt((double)(this->x * this->x + this->y * this->y + this->z * this->z));
	}

	float magnitude2d()
	{
		return sqrt(x * x + z * z);
		//return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float magnitude()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float length_sqr() const {
		return (x * x) + (y * y) + (z * z);
	}

	float length() const {
		return std::sqrt(length_sqr());
	}

	float length_2d() const {
		return std::sqrt((x * x) + (y * y));
	}

	void UnityNormalize()
	{
		Vector3 tis(x, y, z);
		float num = Vector3(x, y, z).magnitude();
		if (num > 1E-05f)
		{
			tis /= num;
		}
		else
		{
			tis = Vector3().Zero();
		}
		x = tis.x;
		y = tis.y;
		z = tis.z;
	}

	Vector3 normalized() const {
		return { x / length(), y / length(), z / length() };
	}

	Vector3 midPoint(Vector3 v2) {
		return Vector3((x + v2.x) / 2, (y + v2.y) / 2, (z + v2.z) / 2);
	}

	float dot_product(float input) const {
		return (x * input) + (y * input) + (z * input);
	}

	float dot_product(Vector3 input) const {
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	float distance(Vector3 input) const {
		return (*this - input).length();
	}

	float distance_2d(Vector3 input) const {
		return (*this - input).length_2d();
	}

	void clamp() {
		std::clamp(x, -89.f, 89.f);
		std::clamp(y, -180.f, 180.f);

		z = 0.f;
	}

	bool empty() const {
		return x == 0.f && y == 0.f && z == 0.f;
	}

	inline float UnityDot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	inline float Dot(const Vector3& Vec2) {
		return this->x * Vec2.x + this->y * Vec2.y + this->z * Vec2.z;
	}

	inline Vector3 Cross(const Vector3& Vec2) {
		return Vector3(this->y * Vec2.z - this->z * Vec2.y, this->z * Vec2.x - this->x * Vec2.z, this->x * Vec2.y - this->y * Vec2.x);
	}

	inline float Distance(const Vector3& Dst) {
		return sqrtf(pow((this->x - Dst.x), 2) + pow((this->y - Dst.y), 2) + pow((this->z - Dst.z), 2));
	}
};

class Quaternion {
public:
	float x, y, z, w;

	Quaternion() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	Quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion operator*(Quaternion rhs)
	{
		return Quaternion(
			this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
			this->w * rhs.y + this->y * rhs.w + this->z * rhs.x - this->x * rhs.z,
			this->w * rhs.z + this->z * rhs.w + this->x * rhs.y - this->y * rhs.x,
			this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z
		);
	}

	float Dot(Quaternion b)
	{
		return x * x + y * y + z * z + w * w;
	}

	Vector3 operator*(Vector3 point)
	{
		float num = this->x * 2.f;
		float num2 = this->y * 2.f;
		float num3 = this->z * 2.f;
		float num4 = this->x * num;
		float num5 = this->y * num2;
		float num6 = this->z * num3;
		float num7 = this->x * num2;
		float num8 = this->x * num3;
		float num9 = this->y * num3;
		float num10 = this->w * num;
		float num11 = this->w * num2;
		float num12 = this->w * num3;
		Vector3 result = Vector3();
		result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
		return result;
	}
};

inline float NormalizeAngle(float angle) {
	while (angle > 360.0f) {
		angle -= 360.0f;
	}
	while (angle < 0.0f) {
		angle += 360.0f;
	}
	return angle;
}

inline Vector3 NormalizeAngles(Vector3 angles) {
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

inline Vector3 EulerAngles(Quaternion q1) {
	float num = q1.w * q1.w;
	float num2 = q1.x * q1.x;
	float num3 = q1.y * q1.y;
	float num4 = q1.z * q1.z;
	float num5 = num2 + num3 + num4 + num;
	float num6 = q1.x * q1.w - q1.y * q1.z;
	Vector3 vector;
	if (num6 > 0.4995f * num5) {
		vector.y = 2.0f * std::atan2f(q1.y, q1.x);
		vector.x = 1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	if (num6 < -0.4995f * num5) {
		vector.y = -2.0f * std::atan2f(q1.y, q1.x);
		vector.x = -1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	Quaternion quaternion = Quaternion(q1.w, q1.z, q1.x, q1.y);
	vector.y = std::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	vector.x = std::asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
	vector.z = std::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
	return NormalizeAngles(vector * 57.2958f);
}

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}

	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline Vector2 operator/(const Vector2& v) const {
		return Vector2(x / v.x, y / v.y);
	}

	inline float Distance(const Vector2& Dst) {
		return sqrt(powf(this->x - Dst.x, 2) + powf(this->y - Dst.y, 2));
	}

	inline bool Zero() const
	{
		return (x <= 0.f || y <= 0.f);

		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}
};

inline Vector2 GetScreenCenter()
{
	return Vector2(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2);
}

class ScreenSize
{
public:
	ScreenSize(float width, float height)
	{
		this->Width = width;
		this->Height = height;
	}

	ScreenSize()
	{
		Width = Height = 0.f;
	}

	float Width;
	float Height;
};

inline ScreenSize GetScreenSize()
{
	return ScreenSize(Vars::Global::ScreenWidth, Vars::Global::ScreenHigh);
}

inline float GetScreenWidth()
{
	return Vars::Global::ScreenWidth;
}

inline float GetScreenHeight()
{
	return Vars::Global::ScreenHigh;
}

struct Ray {
	Vector3 origin;
	Vector3 dir;

	Ray(Vector3 o, Vector3 d) {
		origin = o;
		dir = d;
	}
};

class Color {
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

class RustRect {
public:
	float m_XMin = 0;
	float m_YMin = 0;
	float m_Width = 0;
	float m_Height = 0;
};

class Vector4 {
public:
	float x, y, z, w;
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		}; float m[4][4];
	};
};

#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

inline float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

inline float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923

static float my_sqrt(float number) {
	long        i;
	float       x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y; // floating point bit level hacking [sic]
	i = 0x5f3759df - (i >> 1); // Newton's approximation
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

	return 1 / y;
}

__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
	Vector3 dir = Src - Dst;
	return Vector2{ RAD2DEG(std::asin(dir.y / dir.length())), RAD2DEG(-std::atan2(dir.x, -dir.z)) };
}

static double my_atan(double x) {
	// Return arctangent(x) given that 5/3 < x <= 2, with the same properties as atan.
	auto atani5 = [](double x) {
		constexpr double p00 = +0x1.124A85750FB5Cp+00;
		constexpr double p01 = +0x1.D59AE78C11C49p-03;
		constexpr double p02 = -0x1.8AD3C44F10DC3p-04;
		constexpr double p03 = +0x1.2B090AAD5F9DCp-05;
		constexpr double p04 = -0x1.881EC3D15241Fp-07;
		constexpr double p05 = +0x1.8CB82A74E0699p-09;
		constexpr double p06 = -0x1.3182219E21362p-12;
		constexpr double p07 = -0x1.2B9AD13DB35A8p-12;
		constexpr double p08 = +0x1.10F884EAC0E0Ap-12;
		constexpr double p09 = -0x1.3045B70E93129p-13;
		constexpr double p10 = +0x1.00B6A460AC05Dp-14;

		double y = x - 0x1.d555555461337p0;

		return ((((((((((+p10) * y + p09) * y + p08) * y + p07) * y + p06) * y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 4/3 < x <= 5/3, with the same properties as
	// atan.
	auto atani4 = [](double x) {
		constexpr double p00 = +0x1730BD281F69Dp-01;
		constexpr double p01 = +0x1.3B13B13B13B0Cp-02;
		constexpr double p02 = -0x1.22D719C06115Ep-03;
		constexpr double p03 = +0x1.C963C83985742p-05;
		constexpr double p04 = -0x1.135A0938EC462p-06;
		constexpr double p05 = +0x1.13A254D6E5B7Cp-09;
		constexpr double p06 = +0x1.DFAA5E77B7375p-10;
		constexpr double p07 = -0x14AC1342182D2p-10;
		constexpr double p08 = +0x1.25BAD4D85CBE1p-10;
		constexpr double p09 = -0x1.E4EEF429EB680p-12;
		constexpr double p10 = +0x1.B4E30D1BA3819p-14;
		constexpr double p11 = +0x1.0280537F097F3p-15;

		double y = x - 0x1.8000000000003p0;

		return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 1 < x <= 4 / 3, with the same properties as
	// atan.
	auto atani3 = [](double x) {
		constexpr double p00 = +0x1.B96E5A78C5C40p-01;
		constexpr double p01 = +0x1.B1B1B1B1B1B3Dp-02;
		constexpr double p02 = -0x1.AC97826D58470p-03;
		constexpr double p03 = +0x1.3FD2B9F586A67p-04;
		constexpr double p04 = -0x1.BC317394714B7p-07;
		constexpr double p05 = -0x1.2B01FC60CC37Ap-07;
		constexpr double p06 = +0x1.73A9328786665p-07;
		constexpr double p07 = -0x1.C0B993A09CE31p-08;
		constexpr double p08 = +0x1.2FCDACDD6E5B5p-09;
		constexpr double p09 = +0x1.CBD49DA316282p-13;
		constexpr double p10 = -0x1.0120E602F6336p-10;
		constexpr double p11 = +0x1.A89224FF69018p-11;
		constexpr double p12 = -0x1.883D8959134B3p-12;

		double y = x - 0x1.2aaaaaaaaaa96p0;

		return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
			p07) *
			y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 3 / 4 < x <= 1, with the same properties as
	// atan.
	auto atani2 = [](double x) {
		constexpr double p00 = +0x1.700A7C580EA7Ep-01;
		constexpr double p01 = +0x1.21FB781196AC3p-01;
		constexpr double p02 = -0x1.1F6A8499714A2p-02;
		constexpr double p03 = +0x1.41B15E5E8DCD0p-04;
		constexpr double p04 = +0x1.59BC93F81895Ap-06;
		constexpr double p05 = -0x1.63B543EFFA4EFp-05;
		constexpr double p06 = +0x1.C90E92AC8D86Cp-06;
		constexpr double p07 = -0x1.91F7E2A7A338Fp-08;
		constexpr double p08 = -0x1.AC1645739E676p-08;
		constexpr double p09 = +0x1.152311B180E6Cp-07;
		constexpr double p10 = -0x1.265EF51B17DB7p-08;
		constexpr double p11 = +0x1.CA7CDE5DE9BD7p-14;

		double y = x - 0x1.c0000000f4213p-1;

		return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 1/2 < x <= 3/4, with the same properties as
	// atan.
	auto atani1 = [](double x) {
		constexpr double p00 = +0x1.1E00BABDEFED0p-1;
		constexpr double p01 = +0x1.702E05C0B8155p-1;
		constexpr double p02 = -0x1.4AF2B78215A1Bp-2;
		constexpr double p03 = +0x1.5D0B7E9E69054p-6;
		constexpr double p04 = +0x1.A1247CA5D9475p-4;
		constexpr double p05 = -0x1.519E110F61B54p-4;
		constexpr double p06 = +0x1.A759263F377F2p-7;
		constexpr double p07 = +0x1.094966BE2B531p-5;
		constexpr double p08 = -0x1.09BC0AB7F914Cp-5;
		constexpr double p09 = +0x1F3B7C531AA4Ap-8;
		constexpr double p10 = +0x1.950E69DCDD967p-7;
		constexpr double p11 = -0x1.D88D31ABC3AE5p-7;
		constexpr double p12 = +0x1.10F3E20F6A2E2p-8;

		double y = x - 0x1.4000000000027p-1;

		return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
			p07) *
			y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 0x1p-27 < |x| <= 1/2, with the same properties
	// as atan.
	auto atani0 = [](double x) {
		constexpr double p03 = -0x1.555555555551Bp-2;
		constexpr double p05 = +0x1.99999999918D8p-3;
		constexpr double p07 = -0x1.2492492179CA3p-3;
		constexpr double p09 = +0x1.C71C7096C2725p-4;
		constexpr double p11 = -0x1.745CF51795B21p-4;
		constexpr double p13 = +0x1.3B113F18AC049p-4;
		constexpr double p15 = -0x1.10F31279EC05Dp-4;
		constexpr double p17 = +0x1.DFE7B9674AE37p-5;
		constexpr double p19 = -0x1.A38CF590469ECp-5;
		constexpr double p21 = +0x1.56CDB5D887934p-5;
		constexpr double p23 = -0x1.C0EB85F543412p-6;
		constexpr double p25 = +0x1.4A9F5C4724056p-7;

		// Square x.
		double x2 = x * x;

		return ((((((((((((+p25) * x2 + p23) * x2 + p21) * x2 + p19) * x2 + p17) *
			x2 +
			p15) *
			x2 +
			p13) *
			x2 +
			p11) *
			x2 +
			p09) *
			x2 +
			p07) *
			x2 +
			p05) *
			x2 +
			p03) *
			x2 * x +
			x;
	};
	// Return arctangent(x) given that 2 < x, with the same properties as atan.
	auto Tail = [](double x) {
		{
			constexpr double HalfPi = 0x3.243f6a8885a308d313198a2e037ap-1;

			// For large x, generate inexact and return pi/2.
			if (0x1p53 <= x)
				return HalfPi + DBL_EPSILON;
			if (x != x) // isnan
				return x - x;
		}

		constexpr double p03 = -0x1.5555555554A51p-2;
		constexpr double p05 = +0x1.999999989EBCAp-3;
		constexpr double p07 = -0x1.249248E1422E3p-3;
		constexpr double p09 = +0x1.C71C5EDFED480p-4;
		constexpr double p11 = -0x1.745B7F2D72663p-4;
		constexpr double p13 = +0x1.3AFD7A0E6EB75p-4;
		constexpr double p15 = -0x1.104146B1A1AE8p-4;
		constexpr double p17 = +0x1.D78252FA69C1Cp-5;
		constexpr double p19 = -0x1.81D33E401836Dp-5;
		constexpr double p21 = +0x1.007733E06CEB3p-5;
		constexpr double p23 = -0x1.83DAFDA7BD3FDp-7;

		constexpr double p000 = +0x1.921FB54442D18p0;
		constexpr double p001 = +0x1.1A62633145C07p-54;

		double y = 1 / x;

		// Square y.
		double y2 = y * y;

		return p001 -
			((((((((((((+p23) * y2 + p21) * y2 + p19) * y2 + p17) * y2 + p15) *
				y2 +
				p13) *
				y2 +
				p11) *
				y2 +
				p09) *
				y2 +
				p07) *
				y2 +
				p05) *
				y2 +
				p03) *
				y2 * y +
				y) +
			p000;
	};

	if (x < 0)
		if (x < -1)
			if (x < -5 / 3.)
				if (x < -2)
					return -Tail(-x);
				else
					return -atani5(-x);
			else if (x < -4 / 3.)
				return -atani4(-x);
			else
				return -atani3(-x);
		else if (x < -.5)
			if (x < -.75)
				return -atani2(-x);
			else
				return -atani1(-x);
		else if (x < -0x1.d12ed0af1a27fp-27)
			return atani0(x);
		else if (x <= -0x1p-1022)
			// Generate inexact and return x.
			return (DBL_EPSILON + 1) * x;
		else if (x == 0)
			return x;
		else
			// Generate underflow and return x.
			return x * DBL_EPSILON + x;
	else if (x <= +1)
		if (x <= +.5)
			if (x <= +0x1.d12ed0af1a27fp-27)
				if (x < +0x1p-1022)
					if (x == 0)
						return x;
					else
						// Generate underflow and return x.
						return x * DBL_EPSILON + x;
				else
					// Generate inexact and return x.
					return (DBL_EPSILON + 1) * x;
			else
				return atani0(x);
		else if (x <= +.75)
			return +atani1(+x);
		else
			return +atani2(+x);
	else if (x <= +5 / 3.)
		if (x <= +4 / 3.)
			return +atani3(+x);
		else
			return +atani4(+x);
	else if (x <= +2)
		return +atani5(+x);
	else
		return +Tail(+x);
}

static float my_atan2(float y, float x) {
	// https://en.wikipedia.org/wiki/Atan2#Definition (A compact expression with four
	// overlapping half-planes is: ...)
	if (x == 0) {
		if (y > 0.0f)
			return PI_2;
		else if (y < 0.0f)
			return -PI_2;
		return 0;
	}
	else if (x > 0)
		return my_atan(y / x);
	else if (x < 0)
		return PI + my_atan(y / x);
	else if (y > 0)
		return PI_2 - my_atan(y / x);
	else if (y < 0)
		return -PI_2 - my_atan(y / x);
	return 0;
}

inline static float my_sin(float x) {
	// useful to pre-calculate
	double x2 = x * x;
	double x4 = x2 * x2;

	// Calculate the terms
	// As long as abs(x) < sqrt(6), which is 2.45, all terms will be positive.
	// Values outside this range should be reduced to [-pi/2, pi/2] anyway for
	// accuracy. Some care has to be given to the factorials. They can be
	// pre-calculated by the compiler, but the value for the higher ones will exceed
	// the storage capacity of int. so force the compiler to use unsigned long longs
	// (if available) or doubles.
	double t1 = x * (1.0 - x2 / (2 * 3));
	double x5 = x * x4;
	double t2 = x5 * (1.0 - x2 / (6 * 7)) / (1.0 * 2 * 3 * 4 * 5);
	double x9 = x5 * x4;
	double t3 = x9 * (1.0 - x2 / (10 * 11)) / (1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9);
	double x13 = x9 * x4;
	double t4 = x13 * (1.0 - x2 / (14 * 15)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13);
	double x14 = x13 * x4;
	double t5 =
		x14 * (1.0 - x2 / (18 * 19)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17);
	double x15 = x14 * x4;
	double t6 = x15 * (1.0 - x2 / (22 * 23)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 *
			16 * 17 * 18 * 19 * 20 * 21);
	// add some more if your accuracy requires them.
	// But remember that x is smaller than 2, and the factorial grows very fast
	// so I doubt that 2^17 / 17! will add anything.
	// Even t4 might already be too small to matter when compared with t1.

	// Sum backwards
	double result = t6;
	result += t5;
	result += t4;
	result += t3;
	result += t2;
	result += t1;

	return result;
}

inline static float my_cos(float x) { return my_sin(x + PI_2); }

class MainCameraObjectDataClass
{
public:
	char pad_0000[220]; //0x0000
	struct Matrix4x4 GlobalCurrentViewMatrix; //0x00DC
}; //Size: 0x011

typedef struct _UncStr
{
	char stub[0x10];
	int len;
	wchar_t str[0];
} *pUncStr;

// **********************************************************************

inline Matrix4x4* GlobalCurrentViewMatrix = nullptr;

// **********************************************************************

bool GetMatrix();
bool WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos);