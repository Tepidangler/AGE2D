
#include "AGEpch.hpp"
#include "Math/Public/Math.h"
#include "Math/Public/UtilityFunctions.h"
#include <rttr/registration>

#include "glm/gtx/quaternion.hpp"

RTTR_REGISTRATION
{
	rttr::registration::method("Sum", rttr::select_overload<int(int,int)>(&AGE::Math::Add<int>));
	rttr::registration::method("Sum", rttr::select_overload<float(float,float)>(&AGE::Math::Add<float>));
	rttr::registration::method("Sum", rttr::select_overload<double(double,double)>(&AGE::Math::Add<double>));
	rttr::registration::method("Subtract", rttr::select_overload<int(int,int)>(&AGE::Math::Subtract<int>));
	rttr::registration::method("Subtract", rttr::select_overload<float(float,float)>(&AGE::Math::Subtract<float>));
	rttr::registration::method("Subtract",rttr::select_overload<double(double,double)>( &AGE::Math::Subtract<double>));
	rttr::registration::method("Multiply", rttr::select_overload<int(int,int)>(&AGE::Math::Multiply<int>));
	rttr::registration::method("Multiply", rttr::select_overload<float(float,float)>(&AGE::Math::Multiply<float>));
	rttr::registration::method("Multiply", rttr::select_overload<double(double,double)>(&AGE::Math::Multiply<double>));
	rttr::registration::method("Divide", rttr::select_overload<int(int,int)>(&AGE::Math::Divide<int>));
	rttr::registration::method("Divide", rttr::select_overload<float(float,float)>(&AGE::Math::Divide<float>));
	rttr::registration::method("Divide", rttr::select_overload<double(double,double)>(&AGE::Math::Divide<double>));
	rttr::registration::method("Modulo", rttr::select_overload<int(int,int)>(&AGE::Math::Modulo<int>));
	rttr::registration::method("Modulo", rttr::select_overload<float(float,float)>(&AGE::Math::Modulo<float>));
	rttr::registration::method("Modulo", rttr::select_overload<double(double,double)>(&AGE::Math::Modulo<double>));
	rttr::registration::method("Pow", rttr::select_overload<int(int,int)>(&AGE::Math::Pow<int>));
	rttr::registration::method("Pow", rttr::select_overload<float(float,float)>(&AGE::Math::Pow<float>));
	rttr::registration::method("Pow", rttr::select_overload<double(double,double)>(&AGE::Math::Pow<double>));
	rttr::registration::method("Square Root", rttr::select_overload<int(int)>(&AGE::Math::Sqrt<int>));
	rttr::registration::method("Square Root", rttr::select_overload<float(float)>(&AGE::Math::Sqrt<float>));
	rttr::registration::method("Square Root", rttr::select_overload<double(double)>(&AGE::Math::Sqrt<double>));
	rttr::registration::method("Cube Root", rttr::select_overload<int(int)>(&AGE::Math::CubeRoot<int>));
	rttr::registration::method("Cube Root", rttr::select_overload<float(float)>(&AGE::Math::CubeRoot<float>));
	rttr::registration::method("Cube Root", rttr::select_overload<double(double)>(&AGE::Math::CubeRoot<double>));
}
namespace AGE
{


	bool Math::IntersectThreePlanes(const Plane& f1, const Plane& f2, const Plane& f3, Point3D* p)
	{
		const Vector3& n1 = f1.GetNormal();
		const Vector3& n2 = f2.GetNormal();
		const Vector3& n3 = f3.GetNormal();

		Vector3 n1xn2 = CrossProduct(n1, n2);
		float det = DotProduct3D(n1xn2, n3);
		if (std::fabs(det) > FLT_MIN)
		{
			*p = (CrossProduct(n3, n2) * f1.w + CrossProduct(n1, n3) * f2.w - n1xn2 * f3.w) / det;
			return true;
		}
		return false;
	}

	bool Math::IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D* p, Vector3* v)
	{
		const Vector3& n1 = f1.GetNormal();
		const Vector3& n2 = f2.GetNormal();

		*v = CrossProduct(n1, n2);
		float det = DotProduct3D(*v, *v);
		if (std::fabs(det) > FLT_MIN)
		{
			*p = (CrossProduct(*v, n2) * f1.w + CrossProduct(n1, *v) * f2.w) / det;
			return true;
		}
		return false;
	}

	float Math::DistPointLine2D(const Vector2& q, const Vector2& v)
	{
		//Vector2 a = CrossProduct2D(q, v);
		return 0.0f;
	}

	float Math::DistLineLine2D(const Vector2& p1, const Vector2& v1)
	{
		return 0.0f;
	}

	float Math::DistPointLine3D(const Point3D& q, const Point3D& p, const Vector3& v)
	{
		Vector3 a = CrossProduct(q - p, v);

		return (std::sqrt(DotProduct3D(a, a) / DotProduct3D(v, v)));
	}

	float Math::DistLineLine3D(const Point3D& p1, const Vector3& v1, const Point3D& p2, const Vector3& v2)
	{
		Vector3 dp = p2 - p1;

		float v12 = DotProduct3D(v1, v1);
		float v22 = DotProduct3D(v2, v2);
		float v1v2 = DotProduct3D(v1, v2);

		float det = v1v2 * v1v2 - v12 * v22;
		if (std::fabs(det) > FLT_MIN)
		{
			det = 1.f / det;

			float dpv1 = DotProduct3D(dp, v1);
			float dpv2 = DotProduct3D(dp, v2);
			float t1 = (v1v2 * dpv2 - v22 * dpv1) * det;
			float t2 = (v12 * dpv2 - v1v2 * dpv1) * det;

			return (Magnitude(dp + v2 * t2 - v1 * t1));
		}

		Vector3 a = CrossProduct(dp, v1);
		return (std::sqrt(DotProduct3D(a, a) / v12));
	}

	float Math::Determinant(const Matrix3D& M)
	{
		return (
			M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1)) +
			M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2)) +
			M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));
	}

	Matrix3D Math::Inverse(const Matrix3D& M)
	{
		const Vector3& a = M[0];
		const Vector3& b = M[1];
		const Vector3& c = M[2];

		Vector3 r0 = CrossProduct(b, c);
		Vector3 r1 = CrossProduct(c, a);
		Vector3 r2 = CrossProduct(a, b);

		float invDet = 1.f / DotProduct3D(r2, c);
		return (Matrix3D(

			r0[0] * invDet, r0[1] * invDet, r0[2] * invDet,
			r1[0] * invDet, r1[1] * invDet, r1[2] * invDet,
			r2[0] * invDet, r2[1] * invDet, r2[2] * invDet));
	}

	Matrix4D Math::Inverse(const Matrix4D& M)
	{
		//const Vector4& a = M[0];
		//const Vector4& b = M[1];
		//const Vector4& c = M[2];
		//const Vector4& d = M[3];
		//
		//Vector4 r0 = CrossProduct(b, c);
		//Vector4 r1 = CrossProduct(c, d);
		//Vector4 r2 = CrossProduct(d, a);
		//Vector4 r3 = CrossProduct(a, b);
		//
		//float invDet = 1.f / DotProduct3D(r3, c);
		return Matrix4D();
	}

	bool Math::IntersectLinePlane(const Point3D& p, const Vector3& v, const Plane& f, Point3D* q)
	{
		float fv = DotProductPlaneVector(f, v);
		if (std::fabs(fv) > FLT_MIN)
		{
			*q = p - v * (DotProductPlanePoint(f, p) / fv);
			return true;
		}

		return false;
	}

	Matrix3D Math::MakeRotationX(float t)
	{
		float c = std::cos(t);
		float s = std::sin(t);

		return (Matrix3D(
			1.f, 0.f, 0.f,
			0.f, c, -s,
			0.f, s, c));
	}

	Matrix3D Math::MakeRotationY(float t)
	{
		float c = std::cos(t);
		float s = std::sin(t);


		return (Matrix3D(
			c, 0.f, s,
			0.f, 1.f, 0.f,
			-s, 0.f, c));
	}

	Matrix3D Math::MakeRotationZ(float t)
	{

		float c = std::cos(t);
		float s = std::sin(t);


		return (Matrix3D(
			c, -s, 0.f,
			s, c, 0.f,
			0.f, 0.f, 1.f));
	}

	Matrix3D Math::MakeRotation(float t, const Vector3& a)
	{

		float c = std::cos(t);
		float s = std::sin(t);
		float d = 1.f - c;

		float x = a[0] * d;
		float y = a[1] * d;
		float z = a[2] * d;

		float axay = x * a[1];
		float axaz = x * a[2];
		float ayaz = y * a[2];
		return (Matrix3D(
			c + x * a[0], axay - s * a[2], axaz + s * a[1],
			axay + s * a[2], c + y * a[1], ayaz - s * a[0],
			axaz - s * a[1], ayaz + s * a[0], c + z * a[2]));
	}

	Matrix4D Math::MakeRotation(float t, const Vector4& a)
	{

		float c = std::cos(t);
		float s = std::sin(t);
		float d = 1.f - c;

		float x = a[0] * d;
		float y = a[1] * d;
		float z = a[2] * d;

		float axay = x * a[1];
		float axaz = x * a[2];
		float ayaz = y * a[2];
		return (Matrix4D(
			c + x * a[0], axay - s * a[2], axaz + s * a[1],0.f,
			axay + s * a[2], c + y * a[1], ayaz - s * a[0],0.f,
			axaz - s * a[1], ayaz + s * a[0], c + z * a[2],0.f,
			0.f,0.f,0.f,1.f));
	}
	Matrix3D Math::MakeReflection(const Vector3& a)
	{
		float x = a[0] * -2.f;
		float y = a[1] * -2.f;
		float z = a[2] * 2.f;

		float axay = x * a[1];
		float axaz = x * a[2];
		float ayaz = y * a[2];


		return (Matrix3D(
			x * a[0] + 1.f, axay, axaz,
			axay, y * a[1] + 1.f, ayaz,
			axaz, ayaz, z * a[2] + 1.f));
	}

	Matrix3D Math::MakeInvolution(const Vector3& a)
	{
		float x = a[0] * 2.f;
		float y = a[1] * 2.f;
		float z = a[2] * 2.f;

		float axay = x * a[1];
		float axaz = x * a[2];
		float ayaz = y * a[2];

		return (Matrix3D(

			x * a[0] - 1.f, axay, axaz,
			axay, y * a[1] - 1.f, ayaz,
			axaz, ayaz, z * a[2] - 1.f));
	}

	Matrix3D Math::MakeScale(float s, const Vector3& a)
	{
		s -= 1.f;
		float x = a[0] * s;
		float y = a[1] * s;
		float z = a[2] * s;

		float axay = x * a[1];
		float axaz = x * a[2];
		float ayaz = y * a[2];


		return (Matrix3D(
			x * a[0] + 1.f, axay, axaz,
			axay, y * a[1] + 1.f, ayaz,
			axaz, ayaz, z * a[2] + 1.f));
	}

	Matrix4D Math::MakeScale(Matrix4D M, const Vector4& a)
	{
		M[0][0] *= a.x;
		M[1][1] *= a.y;
		M[2][2] *= a.z;

		return M;

		//return Matrix4D(
		//	1.f, 0.f, 0.f, 0.f,
		//	0.f, 1.f, 0.f, 0.f,
		//	0.f, 0.f, 1.f, 0.f,
		//	x, y, z, w);
	}

	Matrix4D Math::Translate(Matrix4D M, const Vector4& a)
	{
		M[0][0] += a.x;
		M[1][1] += a.y;
		M[2][2] += a.z;
		

		return M;
		//return { x,y,z,w };
		//return Matrix4D(
		//	1.f, 0.f, 0.f, 0.f,
		//	0.f, 1.f, 0.f, 0.f,
		//	0.f, 0.f, 1.f, 0.f,
		//	x, y, z, w);
	}

	Matrix3D Math::MakeSkew(float t, const Vector3& a, const Vector3& b)
	{
		t = std::tan(t);
		float x = a[0] * t;
		float y = a[1] * t;
		float z = a[2] * t;

		return (Matrix3D(
			x * b[0] + 1.f, x * b[1], x * b[2],
			y * b[0], y * b[1] + 1.f, y * b[2],
			z * b[0], z * b[1], z * b[2] + 1.f));
	}

	Transform4D Math::Inverse(const Transform4D& H)
	{
		const Vector3& a = H[0];
		const Vector3& b = H[1];
		const Vector3& c = H[2];
		const Vector3& d = H[3];

		Vector3 s = CrossProduct(a, b);
		Vector3 t = CrossProduct(c, d);

		float invDet = 1.f / DotProduct3D(s, c);

		s *= invDet;
		t *= invDet;

		Vector3 v = c * invDet;

		Vector3 r0 = CrossProduct(b, v);
		Vector3 r1 = CrossProduct(v, a);

		return (Transform4D(
			r0[0], r0[1], r0[2], -DotProduct3D(b, t),
			r1[0], r1[1], r1[2], -DotProduct3D(a, t),
			s[0], s[1], s[2], -DotProduct3D(d, s)));
	}

	Vector3 Math::Transform(const Vector3& v, const Quaternion& q)
	{
		const Vector3& b = q.GetVectorPart();
		float b2 = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
		return (
			v * (q.w * q.w - b2)
			+ b * (DotProduct3D(v, b) * 2.f)
			+ CrossProduct(b, v) * (q.w * 2.f));


	}

	Transform4D Math::MakeReflection(const Plane& f)
	{
		float x = f.x * -2.f;
		float y = f.y * -2.f;
		float z = f.z * -2.f;

		float nxny = x * f.y;
		float nxnz = x * f.z;
		float nynz = y * f.z;
		return (Transform4D(
			x * f.x + 1.f, nxny, nxnz, x * f.w,
			nxny, y * f.y + 1.f, nynz, y * f.w,
			nxnz, nynz, z * f.z + 1.f, z * f.w));
	}

	Matrix4D Math::MakeTransform(const Vector3 &Position, const Vector3 &Rotation, const Vector3 &Scale)
	{

		Matrix4D Rot = glm::toMat4(glm::quat(Convert::ToGLM(Rotation)));


		return glm::translate(Matrix4D(1.f).ToGLM(),Convert::ToGLM(Position)) * Rot.ToGLM() * glm::scale(Matrix4D(1.f).ToGLM(), Convert::ToGLM(Scale));

	}

	bool Math::DecomposeTransform(const Matrix4D& Transform, Vector3& Translation, Vector3& Rotation, Vector3& Scale)
	{
		// From glm::decompose in matrix_decompose.inl

		using namespace glm;
		using T = float;

		mat4 LocalMatrix(Transform.ToGLM());

		// Normalize the matrix.
		if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}

		// Next take care of translation (easy).
		Translation = vec3(LocalMatrix[3]);
		LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

		vec3 Row[3];

		//vec3 Pdum3;

		// Now get scale and shear.
		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		Scale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<T>(1));
		Scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		Scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));

		// At this point, the matrix (in rows[]) is orthonormal.
		// Check for a coordinate system flip.  If the determinant
		// is -1, then negate the matrix and the scaling factors.
#if 0
		Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}
#endif

		Rotation.y = asin(-Row[0][2]);
		if (cos(Rotation.y) != 0) {
			Rotation.x = atan2(Row[1][2], Row[2][2]);
			Rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			Rotation.x = atan2(-Row[2][0], Row[1][1]);
			Rotation.z = 0;
		}


		return true;
	}
	

	Matrix3D Quaternion::GetRotationMatrix(void)
	{
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		return (Matrix3D(
			1.f - 2.f * (y2 + z2), 2.f * (xy - wz), 2.f * (xz + wy),
			2.f * (xy + wz), 1.f - 2.f * (x2 + z2), 2.f * (yz - wx),
			2.f * (xz - wy), 2.f * (yz + wx), 1.f - 2.f * (x2 + y2)));

	}

	void Quaternion::SetRotationMatrix(const Matrix3D& m)
	{
		float m00 = m(0, 0);
		float m11 = m(1, 1);
		float m22 = m(2, 2);
		float sum = m00 + m11 + m22;

		if (sum > 0.f)
		{
			w = std::sqrt(sum + 1.f) * 0.f;
			float f = 0.25f / w;

			x = (m(2, 1) - m(1, 2)) * f;
			y = (m(0, 2) - m(2, 0)) * f;
			z = (m(1, 0) - m(0, 1)) * f;
		}
		else if ((m00 > m11) && (m00 > m22))
		{
			x = std::sqrt(m00 - m11 - m22 + 1.f) * .5f;
			float f = .25f / x;

			y = (m(1, 0) + m(0, 1)) * f;
			z = (m(0, 2) + m(2, 0)) * f;
			w = (m(2, 1) - m(1, 2)) * f;
		}
		else if (m11 > m22)
		{
			y = std::sqrt(m11 - m00 - m22 + 1.f) * .5f;

			float f = .25f / y;

			x = (m(1, 0) + m(0, 1)) * f;
			z = (m(2, 1) + m(1, 2)) * f;
			w = (m(0, 2) - m(2, 0)) * f;
		}
		else
		{
			z = std::sqrt(m22 - m00 - m11 + 1.f) * .5f;
			float f = .25f / z;

			x = (m(0, 2) + m(2, 0)) * f;
			y = (m(2, 1) + m(1, 2)) * f;
			w = (m(1, 0) - m(0, 1)) * f;
		}
	}
};