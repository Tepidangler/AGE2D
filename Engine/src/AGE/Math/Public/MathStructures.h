#pragma once

#include <glm/glm.hpp>
#include "DirectXMath.h"
#include "d3d11_4.h"
#include "Math/Public/Vector2.h"
#include "Math/Public/Vector3.h"
#include "Math/Public/Vector4.h"

namespace AGE
{

	struct Point3D : Vector3
	{
		Point3D() = default;

		Point3D(float a, float b, float c) : Vector3(a, b, c) {}

		const Point3D operator =(Vector3 v) const
		{
			return Point3D(v[0], v[1], v[2]);
		}

		const Point3D operator()(Vector3 v) const
		{
			return Point3D(v[0], v[1], v[2]);
		}



	};

	//2D
	//Structure for Matricies
	struct Matrix2D
	{
	private:
		float n[2][2];

	public:
		Matrix2D() = default;

		/// | n00, n01 |
		/// | n10, n11 |
		Matrix2D(float n00, float n01,
			float n10, float n11)
		{
			n[0][0] = n00; n[0][1] = n01;
			n[1][0] = n10; n[1][1] = n11;
		}

		/// | a[0], a[1]|
		/// | b[0], b[1]|

		Matrix2D(const Vector2& a, const Vector2& b)
		{
			n[0][0] = a[0]; n[0][1] = a[1];
			n[1][0] = b[0]; n[1][1] = b[1];
		}

		float& operator ()(int i, int j)
		{
			return(n[j][i]);
		}

		const float& operator ()(int i, int j) const
		{
			return(n[j][i]);
		}


		Vector2& operator [](int j)
		{
			return (*reinterpret_cast<Vector2*>(n[j]));
		}

		const Vector2& operator[](int j) const
		{
			return (*reinterpret_cast<const Vector2*>(n[j]));
		}

	};

	//3D
	struct Matrix3D
	{
	private:

		float		n[3][3];

	public:

		Matrix3D() = default;

		Matrix3D(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22)
		{
			n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
			n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
			n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
		}

		Matrix3D(const Vector3& a, const Vector3& b, const Vector3& c)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		}

		Matrix3D(void* Ptr)
		{
			Matrix3D Mat = *(Matrix3D*)Ptr;

			for (int i = 0; i < 3; ++i)
			{
				n[i][0] = Mat[i][0]; n[i][1] = Mat[i][1]; n[i][2] = Mat[i][2];
			}
		}

		float& operator ()(int i, int j)
		{
			return (n[j][i]);
		}

		const float& operator ()(int i, int j) const
		{
			return (n[j][i]);
		}

		Vector3& operator [](int j)
		{
			return (*reinterpret_cast<Vector3*>(n[j]));
		}

		const Vector3& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3*>(n[j]));
		}

		inline glm::mat3 ToGLM()
		{
			return glm::mat3(
				n[0][0], n[0][1], n[0][2],
				n[1][0], n[1][1], n[1][2],
				n[2][0], n[2][1], n[2][2]);
		}
		inline glm::mat3 ToGLM() const
		{
			return glm::mat3(
				n[0][0], n[0][1], n[0][2],
				n[1][0], n[1][1], n[1][2],
				n[2][0], n[2][1], n[2][2]);
		}
	};

	//4D
	struct Matrix4D
	{
	protected:

		float		n[4][4];

	public:

		Matrix4D() = default;

		Matrix4D(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23,
			float n30, float n31, float n32, float n33)
		{
			n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
			n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
			n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
			n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
		}

		Matrix4D(float f)
		{
			n[0][0] = f; n[0][1] = 0.f; n[0][2] = 0.f; n[0][3] = 0.f;
			n[1][0] = 0.f; n[1][1] = f; n[1][2] = 0.f; n[1][3] = 0.f;
			n[2][0] = 0.f; n[2][1] = 0.f; n[2][2] = f; n[2][3] = 0.f;
			n[3][0] = 0.f; n[3][1] = 0.f; n[3][2] = 0.f; n[3][3] = 1.f;
		}

		Matrix4D(glm::mat4 M)
		{
			n[0][0] = M[0][0]; n[0][1] = M[0][1]; n[0][2] = M[0][2]; n[0][3] = M[0][3];
			n[1][0] = M[1][0]; n[1][1] = M[1][1]; n[1][2] = M[1][2]; n[1][3] = M[1][3];
			n[2][0] = M[2][0]; n[2][1] = M[2][1]; n[2][2] = M[2][2]; n[2][3] = M[2][3];
			n[3][0] = M[3][0]; n[3][1] = M[3][1]; n[3][2] = M[3][2]; n[3][3] = M[3][3];
		}

		Matrix4D(DirectX::XMMATRIX M)
		{
			DirectX::XMVECTOR a, b, c, p;
			a = M.r[0];
			b = M.r[1];
			c = M.r[2];
			p = M.r[3];

			n[0][0] = DirectX::XMVectorGetX(a); n[0][1] = DirectX::XMVectorGetY(a); n[0][2] = DirectX::XMVectorGetZ(a); n[0][3] = DirectX::XMVectorGetW(a);
			n[1][0] = DirectX::XMVectorGetX(b); n[1][1] = DirectX::XMVectorGetY(b); n[1][2] = DirectX::XMVectorGetZ(b); n[1][3] = DirectX::XMVectorGetW(b);
			n[2][0] = DirectX::XMVectorGetX(c); n[2][1] = DirectX::XMVectorGetY(c); n[2][2] = DirectX::XMVectorGetZ(c); n[2][3] = DirectX::XMVectorGetW(c);
			n[3][0] = DirectX::XMVectorGetX(p); n[3][1] = DirectX::XMVectorGetY(p); n[3][2] = DirectX::XMVectorGetZ(p); n[3][3] = DirectX::XMVectorGetW(p);
		}

		Matrix4D(DirectX::XMVECTOR a, DirectX::XMVECTOR b, DirectX::XMVECTOR c, DirectX::XMVECTOR p)
		{
			n[0][0] = DirectX::XMVectorGetX(a); n[0][1] = DirectX::XMVectorGetY(a); n[0][2] = DirectX::XMVectorGetZ(a); n[0][3] = DirectX::XMVectorGetW(a);
			n[1][0] = DirectX::XMVectorGetX(b); n[1][1] = DirectX::XMVectorGetY(b); n[1][2] = DirectX::XMVectorGetZ(b); n[1][3] = DirectX::XMVectorGetW(b);
			n[2][0] = DirectX::XMVectorGetX(c); n[2][1] = DirectX::XMVectorGetY(c); n[2][2] = DirectX::XMVectorGetZ(c); n[2][3] = DirectX::XMVectorGetW(c);
			n[3][0] = DirectX::XMVectorGetX(p); n[3][1] = DirectX::XMVectorGetY(p); n[3][2] = DirectX::XMVectorGetZ(p); n[3][3] = DirectX::XMVectorGetW(p);
		}

		Matrix4D(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
			n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
		}

		Matrix4D(void* Ptr)
		{
			Matrix4D Mat = *(Matrix4D*)Ptr;

			for (int i = 0; i < 4; ++i)
			{
				n[i][0] = Mat[i][0]; n[i][1] = Mat[i][1]; n[i][2] = Mat[i][2]; n[i][3] = Mat[i][3];
			}
		}

		Matrix4D(const Matrix4D& other) = default;

		float& operator ()(int i, int j)
		{
			return (n[j][i]);
		}

		const float& operator ()(int i, int j) const
		{
			return (n[j][i]);
		}

		Vector4& operator [](int j)
		{
			return (*reinterpret_cast<Vector4*>(n[j]));
		}

		const Vector4& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector4*>(n[j]));
		}

		/// | a[0], a[1], a[2], p[0] |
		/// | b[0], b[1], b[2]  p[1] |
		/// | c[0], c[1], c[2]  p[2] |
		/// | 0.f, 0.f, 0.f, 1.f |
		inline DirectX::XMFLOAT4X4 ToXMFloat4X4()
		{
			return DirectX::XMFLOAT4X4(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		}
		inline DirectX::XMMATRIX ToXMMat()
		{
			return DirectX::XMMATRIX(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		};

		inline glm::mat4 ToGLM()
		{
			return glm::mat4(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		}
		inline glm::mat4 ToGLM() const
		{
			return glm::mat4(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		}
	};

	struct Transform4D : Matrix4D
	{
		Transform4D() = default;

		Transform4D(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23)
		{
			n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
			n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
			n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
			n[3][0] = n03; n[3][1] = n13; n[3][2] = n23;

			n[0][3] = n[1][3] = n[2][3] = 0.0F;
			n[3][3] = 1.0F;
		}

		Transform4D(const Vector3& a, const Vector3& b,
			const Vector3& c, const Point3D& p)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
			n[3][0] = p.x; n[3][1] = p.y; n[3][2] = p.z;

			n[0][3] = n[1][3] = n[2][3] = 0.0F;
			n[3][3] = 1.0F;
		}

		Vector3& operator [](int j)
		{
			return (*reinterpret_cast<Vector3*>(n[j]));
		}

		const Vector3& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3*>(n[j]));
		}

		const Point3D& GetTranslation(void) const
		{
			return (*reinterpret_cast<const Point3D*>(n[3]));
		}

		void SetTranslation(const Point3D& p)
		{
			n[3][0] = p.x;
			n[3][1] = p.y;
			n[3][2] = p.z;
		}
	};

	struct Quaternion
	{
		float		x, y, z, w;

		Quaternion() = default;

		Quaternion(float a, float b, float c, float s)
		{
			x = a; y = b; z = c;
			w = s;
		}

		Quaternion(const Vector3& v, float s)
		{
			x = v.x; y = v.y; z = v.z;
			w = s;
		}

		Vector3& GetVectorPart(void)
		{
			return (reinterpret_cast<Vector3&>(x));
		}

		const Vector3& GetVectorPart(void) const
		{
			return (reinterpret_cast<const Vector3&>(x));
		}

		Matrix3D GetRotationMatrix(void);
		void SetRotationMatrix(const Matrix3D& m);
	};

	struct Plane
	{
		float		x, y, z, w;

		Plane() = default;

		Plane(float nx, float ny, float nz, float d)
		{
			x = nx;
			y = ny;
			z = nz;
			w = d;
		}

		Plane(const Vector3& n, float d)
		{
			x = n.x;
			y = n.y;
			z = n.z;
			w = d;
		}

		const Vector3& GetNormal(void) const
		{
			return (reinterpret_cast<const Vector3&>(x));
		}

	};

	struct Line
	{
		Vector3 Direction;
		Vector3 Moment;

		Line() = default;

		Line(float vx, float vy, float vz, float mx, float my, float mz) : Direction(vx, vy, vz), Moment(mx, my, mz)
		{
		}

		Line(const Vector3& v, const Vector3& m)
		{
			Direction = v;
			Moment = m;
		}

	};

	inline Matrix4D operator *(const Vector4& V, const Matrix4D& M)
	{
		float vx = V.x;
		float vy = V.y;
		float vz = V.z;
		float vw = V.w;

		return Matrix4D(
			M(0, 0) * vx, M(0, 1) * vy, M(0, 2) * vz, M(0, 3) * vw,
			M(1, 0) * vx, M(1, 1) * vy, M(1, 2) * vz, M(1, 3) * vw,
			M(2, 0) * vx, M(2, 1) * vy, M(2, 2) * vz, M(2, 3) * vw,
			M(3, 0) * vx, M(3, 1) * vy, M(3, 2) * vz, M(3, 3) * vw);
	}

	inline Matrix4D operator +(const Matrix4D& M1, const Matrix4D& M2)
	{
		Vector4 Src1A = M1[0];
		Vector4 Src1B = M1[1];
		Vector4 Src1C = M1[2];
		Vector4 Src1D = M1[3];

		Vector4 Src2A = M2[0];
		Vector4 Src2B = M2[1];
		Vector4 Src2C = M2[2];
		Vector4 Src2D = M2[3];

		Vector4 New1 = { Src1A.x + Src2A.x, Src1A.y + Src2A.y, Src1A.z + Src2A.z, Src1A.w + Src2A.w };
		Vector4 New2 = { Src1B.x + Src2B.x, Src1B.y + Src2B.y, Src1B.z + Src2B.z, Src1B.w + Src2B.w };
		Vector4 New3 = { Src1C.x + Src2C.x, Src1C.y + Src2C.y, Src1C.z + Src2C.z, Src1C.w + Src2C.w };
		Vector4 New4 = { Src1D.x + Src2D.x, Src1D.y + Src2D.y, Src1D.z + Src2D.z, Src1D.w + Src2D.w };
		return  Matrix4D(New1, New2, New3, New4);
	}

	inline Vector3 operator *(const Matrix4D& M, const Vector4& V)
	{
		Vector4 const Temp0(V[0]);
		Vector4 const Temp1(V[1]);
		Matrix4D const Mov0(Temp0.x, 0.f, 0.f, 0.f, 0.f, Temp0.y, 0.f, 0.f, 0.f, 0.f, Temp0.z, 0.f, 0.f, 0.f, 0.f, Temp0.w);
		Matrix4D const Mov1(Temp1.x, 0.f, 0.f, 0.f, 0.f, Temp1.y, 0.f, 0.f, 0.f, 0.f, Temp1.z, 0.f, 0.f, 0.f, 0.f, Temp1.w);
		Matrix4D const Mul0 = M[0] * Mov0;
		Matrix4D const Mul1 = M[1] * Mov1;
		Matrix4D const Add0 = Mul0 + Mul1;
		Vector4 const Temp2(V[2]);
		Vector4 const Temp3(V[3]);
		Matrix4D const Mov2(Temp2.x, 0.f, 0.f, 0.f, 0.f, Temp2.y, 0.f, 0.f, 0.f, 0.f, Temp2.z, 0.f, 0.f, 0.f, 0.f, Temp2.w);
		Matrix4D const Mov3(Temp3.x, 0.f, 0.f, 0.f, 0.f, Temp3.y, 0.f, 0.f, 0.f, 0.f, Temp3.z, 0.f, 0.f, 0.f, 0.f, Temp3.w);
		Matrix4D const Mul2 = M[2] * Mov2;
		Matrix4D const Mul3 = M[3] * Mov3;
		Matrix4D const Add1 = Mul2 + Mul3;
		Matrix4D const Add2 = Add0 + Add1;

		return Vector3(Add2(0, 0), Add2(1, 1), Add2(2, 2));
	}

	inline Matrix3D operator *(const Matrix3D& A, const Matrix3D& B)
	{
		return (Matrix3D(A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
			A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
			A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
			A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
			A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
			A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
			A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
			A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
			A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2)));
	}

	inline Matrix4D operator *(const Matrix4D& A, const Matrix4D& B)
	{
		return (Matrix4D(
			A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0) + A(0, 3) * B(3, 0), //M00
			A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1) + A(0, 3) * B(3, 1), //M01
			A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2) + A(0, 3) * B(3, 2), //M02
			A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3) * B(3, 3), //M03
			A(1, 0) * B(1, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0) + A(1, 3) * B(3, 0), //M10
			A(1, 0) * B(1, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1) + A(1, 3) * B(3, 1), //M11
			A(1, 0) * B(1, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2) + A(1, 3) * B(3, 2), //M12
			A(1, 0) * B(1, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3) * B(3, 3), //M13
			A(2, 0) * B(2, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0) + A(2, 3) * B(3, 0), //M20
			A(2, 0) * B(2, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1) + A(2, 3) * B(3, 1), //M21
			A(2, 0) * B(2, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2) + A(2, 3) * B(3, 2), //M22
			A(2, 0) * B(2, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 3) + A(2, 3) * B(3, 3), //M23
			A(3, 0) * B(3, 0) + A(3, 1) * B(1, 0) + A(3, 2) * B(2, 0) + A(3, 3) * B(3, 0), //M30
			A(3, 0) * B(3, 1) + A(3, 1) * B(1, 1) + A(3, 2) * B(2, 1) + A(3, 3) * B(3, 1), //M31
			A(3, 0) * B(3, 2) + A(3, 1) * B(1, 2) + A(3, 2) * B(2, 2) + A(3, 3) * B(3, 2), //M32
			A(3, 0) * B(3, 2) + A(3, 1) * B(1, 2) + A(3, 2) * B(2, 3) + A(3, 3) * B(3, 3)  //M33
		));
	}

	inline Vector3 operator *(const Matrix3D& M, const Vector3& v)
	{
		return (Vector3(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
			M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
			M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
	}
	inline Vector3 operator *(const Vector3& v, const Matrix4D& M)
	{
		return (Vector3(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
			M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
			M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
	}
	inline Point3D operator +(const Point3D& a, const Vector3& b)
	{
		return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	inline Point3D operator -(const Point3D& a, const Vector3& b)
	{
		return (Point3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	inline Vector3 operator -(const Point3D& a, const Point3D& b)
	{
		return (Vector3(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	inline Transform4D operator *(const Transform4D& A, const Transform4D& B)
	{
		return (Transform4D(
			A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
			A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
			A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
			A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3),
			A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
			A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
			A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
			A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3),
			A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
			A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
			A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2),
			A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3)));
	}
	inline Vector3 operator *(const Transform4D& H, const Vector3& v)
	{
		return (Vector3(H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
			H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
			H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z));
	}

	inline Point3D operator *(const Transform4D& H, const Point3D& p)
	{
		return (Point3D(H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
			H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
			H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3)));
	}
	inline Vector3 operator *(const Vector3& n, const Transform4D& H)
	{
		return (Vector3(n.x * H(0, 0) + n.y * H(1, 0) + n.z * H(2, 0),
			n.x * H(0, 1) + n.y * H(1, 1) + n.z * H(2, 1),
			n.x * H(0, 2) + n.y * H(1, 2) + n.z * H(2, 2)));
	}

	inline Plane operator *(const Plane& f, const Transform4D& H)
	{
		return (Plane(f.x * H(0, 0) + f.y * H(1, 0) + f.z * H(2, 0),
			f.x * H(0, 1) + f.y * H(1, 1) + f.z * H(2, 1),
			f.x * H(0, 2) + f.y * H(1, 2) + f.z * H(2, 2),
			f.x * H(0, 3) + f.y * H(1, 3) + f.z * H(2, 3) + f.w));
	}

	inline Line operator ^(const Point3D& p, const Point3D& q)
	{
		return (Line(q.x - p.x, q.y - p.y, q.z - p.z,
			p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x));
	}

	inline Line operator ^(const Plane& f, const Plane& g)
	{
		return (Line(f.z * g.y - f.y * g.z,
			f.x * g.z - f.z * g.x,
			f.y * g.x - f.x * g.y,
			f.x * g.w - f.w * g.x,
			f.y * g.w - f.w * g.y,
			f.z * g.w - f.w * g.z));
	}

	inline Plane operator ^(const Line& L, const Point3D& p)
	{
		return (Plane(L.Direction.y * p.z - L.Direction.z * p.y + L.Moment.x,
			L.Direction.z * p.x - L.Direction.x * p.z + L.Moment.y,
			L.Direction.x * p.y - L.Direction.y * p.x + L.Moment.z,
			-L.Moment.x * p.x - L.Moment.y * p.y - L.Moment.z * p.z));
	}
	inline Plane operator ^(const Point3D& p, const Line& L)
	{
		return (L ^ p);
	}
	inline Vector4 operator ^(const Line& L, const Plane& f)
	{
		return (Vector4(
			L.Moment.y * f.z - L.Moment.z * f.y + L.Direction.x * f.w,
			L.Moment.z * f.x - L.Moment.x * f.z + L.Direction.y * f.w,
			L.Moment.x * f.y - L.Moment.y * f.x + L.Direction.z * f.w,
			-L.Direction.x * f.x - L.Direction.y * f.y - L.Direction.z * f.z));
	}
	inline Vector4 operator ^(const Plane& f, const Line& L)
	{
		return (L ^ f);
	}

	inline float operator ^(const Point3D& p, const Plane& f)
	{
		return (p.x * f.x + p.y * f.y + p.z * f.z + f.w);
	}

	inline float operator ^(const Plane& f, const Point3D& p)
	{
		return (-(p ^ f));
	}

	struct Statistics
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCount = 0;
		uint32_t LineCount = 0;
		uint32_t CircleCount = 0;
		uint32_t TextCount = 0;
		uint32_t TileCount = 0;

		uint32_t CubeCount = 0;
		uint32_t SphereCount = 0;
		uint32_t CylinderCount = 0;
		uint32_t PyramidCount = 0;
		uint32_t ModelCount = 0;


		uint32_t GetTotalQuadVertexCount() { return QuadCount * 4; }
		uint32_t GetTotalQuadIndexCount() { return QuadCount * 6; }
		uint32_t GetTotalTileVertexCount() { return TileCount * 4; }
		uint32_t GetTotalTileIndexCount() { return TileCount * 6; }
		uint32_t GetTotalCubeVertexCount() { return CubeCount * 8; }
		uint32_t GetTotalCubeIndexCount() { return CubeCount * 36; }
		uint32_t GetTotalSphereVertexCount() { return SphereCount * 8; }
		uint32_t GetTotalSphereIndexCount() { return SphereCount * 36; }
		uint32_t GetTotalCylinderVertexCount() { return CylinderCount * 8; }
		uint32_t GetTotalCylinderIndexCount() { return CylinderCount * 18; }
		uint32_t GetTotalPyramidVertexCount() { return PyramidCount * 5; }
		uint32_t GetTotalPyramidIndexCount() { return CubeCount * 6; }
		//uint32_t GetTotalVertexCount() {return}
		//uint32_t GetTotalIndexCount()  {return}
	};

}