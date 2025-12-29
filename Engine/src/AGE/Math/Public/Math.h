#pragma once

#include "MathStructures.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <numbers>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "rttr/detail/registration/registration_impl.h"


namespace AGE
{
	class Math
	{
	public:

		static inline float Magnitude(const Vector3& v)
		{
			return (std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
		}

		static bool IntersectThreePlanes(const Plane& f1, const Plane& f2, const Plane& f3, Point3D* p);

		static bool IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D* p, Vector3* v);

		static float DistPointLine2D(const Vector2& q, const Vector2& p);

		static float DistLineLine2D(const Vector2& p1, const Vector2& v1);

		static float DistPointLine3D(const Point3D& q, const Point3D& p, const Vector3& v);

		static float DistLineLine3D(const Point3D& p1, const Vector3& v1, const Point3D& p2, const Vector3& v2);

		// Calculates the Determinant of a 3x3 Matrix
		static float Determinant(const Matrix3D& M);
		// Calculates the inverse of a 3x3 Matrix
		static Matrix3D Inverse(const Matrix3D& M);

		// Calculates the inverse of a 4x4 Matrix
		static Matrix4D Inverse(const Matrix4D& M);
		//Implementation of Dot Product in 2D

		static inline float DotProduct2D(const Vector2& a, const Vector2& b)
		{
			return (a[0] * b[0] + a[1] * b[1]);
		}
		//Implementation of Dot Product in 3D
		static inline float DotProduct3D(const Vector3& a, const Vector3& b)
		{
			return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
		}

		static float DotProductPlaneVector(const Plane& f, const Vector3& v)
		{
			return (f.x * v[0] + f.y * v[1] + f.z * v[2]);
		}

		static float DotProductPlanePoint(const Plane& f, const Point3D& p)
		{
			return (f.x * p[0] + f.y * p[1] + f.z * p[2] + f.w);
		}

		static bool IntersectLinePlane(const Point3D& p, const Vector3& v, const Plane& f, Point3D* q);

		//Implementation of Cross Product in 2D 

		static inline float CrossProduct2D(const Vector2& a, const Vector2& b)
		{
			return (a[0] * b[1] - b[0] * a[1]); // Since there really isn't anyway to do a 2D Cross product what 
			//we've opted to do is return a scalar when I guess would be applied along the x and y axes respectively
		}

		//Implementation of Cross Product in 3D

		static inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
		{
			return (Vector3(

				a[1] * b[2] - a[2] * b[1],
				a[2] * b[2] - a[0] * b[2],
				a[0] * b[1] - a[1] * b[0]));
		}

		//Implementation of Projection on 2D plane

		static inline Vector2 Project2D(const Vector2& a, const Vector2& b)
		{
			return (b * (DotProduct2D(a, b) / DotProduct2D(b, b)));
		}

		// Implementation of Rejection in 2D
		static inline Vector2 Reject2D(const Vector2& a, const Vector2& b)
		{
			return (a - b * (DotProduct2D(a, b) / DotProduct2D(b, b)));
		}

		// Implementation of Projection in 3D

		static inline Vector3 Project3D(const Vector3& a, Vector3& b)
		{
			return (b * (DotProduct3D(a, b) / DotProduct3D(b, b)));
		}

		// Implementation of Rejection in 3D

		static inline Vector3 Reject3D(const Vector3& a, Vector3& b)
		{
			return (a - b * (DotProduct3D(a, b) / DotProduct3D(b, b)));
		}
		static Vector3 Transform(const Vector3& v, const Quaternion& q);

		static Matrix3D MakeRotationX(float t);

		static Matrix3D MakeRotationY(float t);

		static Matrix3D MakeRotationZ(float t);

		//Creates a 3x3 Matrix that represents a rotation through the angle t about an arbitrary axis a and returns it in a Matrix3D
		static Matrix3D MakeRotation(float t, const Vector3& a);

		//Creates a 4x4 Matrix that represents a rotation through the angle t about an arbitrary axis a and returns it in a Matrix4D
		static Matrix4D MakeRotation(float t, const Vector4& a);

		// Creates a 3x3 Matrix that represents a reflection through the plane perpendicular to arbitrary vector a and return it in Matrix3D. Vector a is assumed to have unit length
		static Matrix3D MakeReflection(const Vector3& a);

		// Creates a 3x3 matrix that represents a involution through an arbitrary vector a and returns it in a Matrix3D. The vector a is assumed to have unit length
		static Matrix3D MakeInvolution(const Vector3& a);

		// Creates a 3x3 matrix that represents a scale by a factor of s along an arbitrary direction a and returns it in a Matrix3D. The vector a is assumed to have unit length.
		static Matrix3D MakeScale(float s, const Vector3& a);

		// Creates a 4x4 matrix that represents a scale by a factor of s along an arbitrary direction a and returns it in a Matrix4D. The vector a is assumed to have unit length.
		static Matrix4D MakeScale(Matrix4D M, const Vector4& a);
			   
		static Matrix4D Translate(Matrix4D M, const Vector4& a);

		// Creates a 3x3 matrix that represents  a skew by the angle t along the direction a based on the projected length along the direction b and returns it in a Matrix3d. 
		// The vectors a and b are assumed to be orthogonal and to have unit length
		static Matrix3D MakeSkew(float t, const Vector3& a, const Vector3& b);

		static Transform4D Inverse(const Transform4D& H);

		static Transform4D MakeReflection(const Plane& f);

		static Matrix4D MakeTransform(const Vector3& Position, const Vector3& Rotation, const Vector3& Scale);

		// Transforms a Line struct with a Transform3D struct
		static Line Transform(const Line& line, const Transform4D& H)
		{
			Matrix3D adj(CrossProduct(H[1], H[2]), CrossProduct(H[2], H[0]), CrossProduct(H[0], H[1])); // Calculate the transpose of the adjugate of the upper-left 3x3 portion of H
			const Point3D& t = H.GetTranslation();

			Vector3 v = H * line.Direction;
			Vector3 m = adj * line.Moment + CrossProduct(t, v);
			return(Line(v, m));
		}

		static float Radians(const float Deg)
		{
			/**
			* Convert 112deg to radians

			th/180 = thR/pi

			112/180 = thR/pi

			112pi/180 = thR

			28pi/45
			*/
			float Radians = (Deg * std::numbers::pi_v<float>) / 180.f;

			return Radians;
			

		}

		static Vector3 Radians(const Vector3 Vec)
		{
			/**
			* Convert 112deg to radians

			th/180 = thR/pi

			112/180 = thR/pi

			112pi/180 = thR

			28pi/45
			*/

			return { ((Vec.x * std::numbers::pi_v<float>) / 180.f),((Vec.y * std::numbers::pi_v<float>) / 180.f),((Vec.z * std::numbers::pi_v<float>) / 180.f) };


		}
		static float Degrees(const float Rad)
		{
			//Convert - (3pi / 4) radians to degrees
			//
			//th / 180 = thR / pi
			//
			//th / 180 = -(3pi / 4) / pi
			//
			//th = (180 * 3) / 4
			//
			//th = -(540) / 4
			//
			//th = -135

			float Deg = (Rad / std::numbers::pi_v<float>) * 180.f;

			return Deg;
		}

		static Vector3 Degrees(const Vector3 Vec)
		{
			//Convert - (3pi / 4) radians to degrees
			//
			//th / 180 = thR / pi
			//
			//th / 180 = -(3pi / 4) / pi
			//
			//th = (180 * 3) / 4
			//
			//th = -(540) / 4
			//
			//th = -135

			return { ((Vec.x / std::numbers::pi_v<float>) * 180.f),((Vec.y / std::numbers::pi_v<float>) * 180.f),((Vec.x / std::numbers::pi_v<float>) * 180.f	) };
		}

		static float DegreeToRadians(float Deg)
		{
			return std::acosf(Deg) /180.f;
		}

		static bool DecomposeTransform(const Matrix4D& Transform, Vector3& Translation, Vector3& Rotation, Vector3& Scale);


		static float Cos(float a)
		{
			return std::cos(a);
		}

		static float Sin(float a)
		{
			return std::sin(a);
		}

		static float ACos(float a)
		{
			return std::acos(a);
		}
		template<typename T>
		static T Sqrt(T a)
		{
			return std::sqrt(a);
		}

		template<typename T>
		static T Add(T a, T b)
		{
			return a + b;
		}
		template<typename T>
		static T Subtract(T a, T b)
		{
			return a - b;
		}
		template<typename T>
		static T Multiply(T a, T b)
		{
			return a * b;
		}
		template<typename T>
		static T Divide(T a, T b)
		{
			return a / b;
		}
		template<typename T>
		static T Modulo(T a, T b)
		{
			return std::fmod(a,b);
		}
		template<typename T>
		static T Pow(T a, T b = 2)
		{
			return std::pow(a, b);
		}
		template<typename T>
		static T CubeRoot(T a)
		{
			return std::cbrt(a);
		}

	};

	inline float operator ^(const Line& L1, const Line& L2)
	{
		return (-(Math::DotProduct3D(L1.Direction, L2.Moment) + Math::DotProduct3D(L2.Direction, L1.Moment)));
	}
}

