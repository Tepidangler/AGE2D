
#include "AGEpch.hpp"
#include "Math/Public/Math.h"
#include "Math/Public/UtilityFunctions.h"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/registration>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/registration>
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <rttr/registration>
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
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
	rttr::registration::method("Modulo", &AGE::Math::Modulo);
	rttr::registration::method("Pow", &AGE::Math::Pow);
	rttr::registration::method("Square Root", &AGE::Math::Sqrt);
	rttr::registration::method("Cube Root", &AGE::Math::CubeRoot);
}
namespace AGE
{


	/**
 * @brief Computes the intersection point of three planes in a 3D space.
 *
 * Given three planes, this function computes and returns their intersection point if they are not parallel (i.e., have a non-zero determinant). The intersection point is calculated using Cramer's rule.
 *
 * @param f1 First plane to intersect with.
 * @param f2 Second plane to intersect with.
 * @param f3 Third plane to intersect with.
 * @param p Pointer to a Point3D object where the intersection point will be stored if it exists.
 * 
 * @return True if planes are not parallel (determinant is non-zero), false otherwise.
 */
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

	/**
 * @brief Computes the distance between a point and a line in 2D space.
 * 
 * This function calculates the shortest distance from a given point to a line defined by two points. The line is represented as an origin (v) and a direction vector (q).
 * 
 * @param q A Vector2 representing the direction of the line.
 * @param v A Vector2 representing the origin of the line.
 * @return float Returns the distance between the point and the line in 2D space. If the input parameters are invalid, it returns NaN (Not a Number).
 */
float Math::DistPointLine2D(const Vector2& q, const Vector2& v)
	{
		//Vector2 a = CrossProduct2D(q, v);
		return 0.0f;
	}

	/**
 * @brief Computes the shortest distance between two lines in 2D space.
 * 
 * This function calculates the shortest distance between any point on line1 and any point on line2.
 * The result is a float value representing this minimum distance.
 *
 * @param p1 A constant reference to Vector2 object representing one point on the first line.
 * @param v1 A constant reference to Vector2 object representing direction vector of the first line.
 * 
 * @return Returns a float value representing the shortest distance between two lines in 2D space.
 */
float Math::DistLineLine2D(const Vector2& p1, const Vector2& v1)
	{
		return 0.0f;
	}

	/**
 * @brief Computes the distance between a point and a line in 3-dimensional space.
 * 
 * The function calculates the shortest distance from a given point to a line defined by an origin point (p) and a direction vector (v). It uses the formula for the distance between two points, which is sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2), where (x1, y1, z1) are the coordinates of the first point and (x2, y2, z2) are the coordinates of the second point.
 * 
 * @param q The Point3D object representing the point for which we want to compute the distance from the line.
 * @param p The Point3D object representing the origin point of the line.
 * @param v The Vector3 object representing the direction vector of the line.
 * 
 * @return A float value representing the shortest distance between the given point and the line. If the direction vector is zero, it returns Unknown.
 */
float Math::DistPointLine3D(const Point3D& q, const Point3D& p, const Vector3& v)
	{
		Vector3 a = CrossProduct(q - p, v);

		return (std::sqrt(DotProduct3D(a, a) / DotProduct3D(v, v)));
	}

	/**
 * @brief Calculates the distance between two lines in 3D space.
 *
 * The function calculates the shortest distance between two lines defined by points and directions. It uses the method of calculating the intersection point of the two lines, which is then used to calculate the distance from that point to either of the original line's points. If the determinant of the matrix formed by the direction vectors of the two lines is zero (i.e., the lines are parallel), it calculates a perpendicular distance using cross product instead.
 *
 * @param p1 The first point on the first line.
 * @param v1 The direction vector of the first line.
 * @param p2 The first point on the second line.
 * @param v2 The direction vector of the second line.
 *
 * @return The shortest distance between the two lines. If the determinant is zero, it returns the perpendicular distance.
 */
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

	/**
 * @brief Calculates the determinant of a 3x3 matrix.
 *
 * This function calculates the determinant of a 3x3 matrix using the formula for calculating the determinant of a 3x3 matrix.
 * The input is a const reference to a Matrix3D object, which represents the matrix whose determinant we want to calculate.
 *
 * @param M A const reference to a Matrix3D object representing the matrix whose determinant we want to calculate.
 *
 * @return Returns a float value representing the determinant of the input 3x3 matrix. If the input matrix is not a 3x3 matrix, the behavior is undefined.
 */
float Math::Determinant(const Matrix3D& M)
	{
		return (
			M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1)) +
			M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2)) +
			M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));
	}

	/**
 * Computes the inverse of a 3x3 matrix.
 *
 * The function takes as input a const reference to a Matrix3D object and returns an instance of Matrix3D that represents the inverse of the input matrix. It uses linear algebra methods, specifically the method of calculating the inverse of a matrix.
 *
 * @param M A const reference to the 3x3 matrix to be inverted.
 * @return An instance of Matrix3D representing the inverse of the input matrix.
 */
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

	/**
 * @brief Computes the inverse of a 4x4 matrix.
 *
 * This function takes as input a constant reference to a 4x4 matrix and returns its inverse. The function uses various mathematical operations such as cross product and dot product to compute the inverse.
 *
 * @param M A constant reference to the 4x4 matrix to be inverted.
 * @return The inverse of the input matrix. If the determinant of the input matrix is zero, this function returns an identity matrix.
 */
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

	/**
 * @brief This function calculates the intersection point of a line and plane.
 *
 * The function takes in three parameters - a point 'p' on the line, a direction vector 'v', and a plane 'f'. It computes the intersection point 'q' where the line intersects with the plane. 
 * If there is an intersection, it returns true; otherwise, false.
 *
 * @param p A const reference to Point3D object representing a point on the line.
 * @param v A const reference to Vector3 object representing the direction of the line.
 * @param f A const reference to Plane object representing the plane.
 * @param q Pointer to Point3D object where the intersection point will be stored if there is an intersection.
 * 
 * @return Returns true if a valid intersection exists, false otherwise.
 */
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

	/**
 * @brief Creates a rotation matrix around the X axis.
 *
 * This function creates and returns a 3x3 rotation matrix that represents a rotation of 't' radians about the X-axis. The cosine and sine functions are used to calculate the values in the matrix, based on the input parameter 't'.
 *
 * @param t The angle of rotation in radians.
 * @return A 3x3 Matrix3D representing a rotation transformation.
 */
Matrix3D Math::MakeRotationX(float t)
	{
		float c = std::cos(t);
		float s = std::sin(t);

		return (Matrix3D(
			1.f, 0.f, 0.f,
			0.f, c, -s,
			0.f, s, c));
	}

	/**
 * @brief Creates a rotation matrix around the Y axis.
 *
 * This function creates and returns a 3x3 rotation matrix that represents a rotation of 't' radians about the Y-axis. The cosine and sine of 't' are used to calculate the values in the matrix.
 *
 * @param t The angle of rotation, in radians.
 * @return A Matrix3D object representing a 3x3 rotation matrix.
 */
Matrix3D Math::MakeRotationY(float t)
	{
		float c = std::cos(t);
		float s = std::sin(t);


		return (Matrix3D(
			c, 0.f, s,
			0.f, 1.f, 0.f,
			-s, 0.f, c));
	}

	/**
 * @brief Creates a rotation matrix around the Z axis.
 *
 * This function creates and returns a 3x3 rotation matrix that represents a rotation of 't' radians about the Z-axis. The cosine and sine of 't' are used to calculate the values in the matrix.
 *
 * @param t The angle (in radians) by which to rotate.
 * @return A 3x3 Matrix3D representing a rotation of 't' radians about the Z-axis.
 */
Matrix3D Math::MakeRotationZ(float t)
	{

		float c = std::cos(t);
		float s = std::sin(t);


		return (Matrix3D(
			c, -s, 0.f,
			s, c, 0.f,
			0.f, 0.f, 1.f));
	}

	COMMENT:
/**
 * @brief Creates a rotation matrix for a given angle and axis.
 *
 * This function creates a rotation matrix that represents a rotation of the specified angle around the provided axis. The rotation is performed in 3D space.
 *
 * @param t The angle of rotation, in radians.
 * @param a The axis of rotation, represented as a Vector3 object.
 * @return A Matrix3D object representing the rotation matrix.
 */
CONFIDENCE: 1.0;

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

	/**
 * Creates a rotation matrix based on the given angle and axis.
 * 
 * The function creates a 4x4 rotation matrix using Rodrigues' rotation formula. It takes an angle 't' in radians and a Vector4 'a', representing the axis of rotation.
 * 
 * @param t Angle of rotation in radians.
 * @param a Axis of rotation represented as a Vector4.
 * 
 * @return Matrix4D representing the rotation matrix.
 */
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
	COMMENT:
/**
 * @brief Creates a reflection matrix for a given vector.
 *
 * This function takes an input Vector3 and creates a reflection matrix based on it. The resulting matrix will reflect any point across the line defined by the input vector.
 *
 * @param a A const reference to the Vector3 that serves as the basis of the reflection.
 * 
 * @return Returns a Matrix3D object representing the reflection matrix.
 */
CONFIDENCE: 1.0;

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

	/**
 * @brief Creates an involution matrix from a vector.
 *
 * This function takes a Vector3 object as input and returns a Matrix3D object that represents the involution matrix corresponding to the given vector. The input vector is multiplied by 2 before being used in the calculations, which may affect the resulting matrix if the original values of the vector were not zero or one.
 *
 * @param a A Vector3 object representing the basis vectors for the transformation.
 * @return Matrix3D Returns a Matrix3D object that represents the involution matrix corresponding to the input vector.
 */
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

	/**
 * @brief Creates a scaling matrix from a scale factor and a vector.
 *
 * This function takes in a scale factor `s` and a Vector3 `a`, then it creates a 3D scaling matrix based on these inputs. The scale factor is subtracted by 1 to ensure the resulting matrix remains orthogonal.
 *
 * @param s The scale factor.
 * @param a The vector used for scaling.
 * @return A Matrix3D representing the created scaling matrix.
 */
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

	/**
 * @brief This function scales a given Matrix4D by the x, y and z components of a Vector4.
 * 
 * @param M The Matrix4D to be scaled.
 * @param a A reference to the Vector4 containing the scaling factors.
 * 
 * @return Returns the scaled Matrix4D.
 */
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

	/**
 * @brief Translates a Matrix4D by a Vector4.
 *
 * This function takes in an existing Matrix4D and a Vector4 representing the translation vector. 
 * It adds the x, y, and z components of the Vector4 to the corresponding elements in the Matrix4D, effectively translating it.
 * The modified Matrix4D is then returned.
 *
 * @param M The Matrix4D to be translated.
 * @param a The translation vector.
 * 
 * @return The translated Matrix4D.
 */
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

	/**
 * @brief Creates a skew symmetric matrix from given parameters.
 *
 * This function takes three parameters, two vectors and one scalar. The scalar is first converted to its tangent value using the tan() function. 
 * Then it multiplies each component of the first vector by this tangent value. These results are used to construct a skew symmetric matrix.
 *
 * @param t Scalar input which is first converted to its tangent value.
 * @param a Vector for multiplication with the tangent value.
 * @param b Vector for further multiplication in the construction of the resulting 3x3 Matrix.
 *
 * @return A 3x3 Matrix that represents skew symmetric transformation.
 */
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

	/**
 * @brief Computes the inverse of a homogeneous transformation matrix.
 * 
 * This function takes as input a constant reference to a Transform4D object which represents a homogeneous transformation matrix. It then computes and returns the inverse of this matrix.
 * 
 * @param H A const reference to the Transform4D object to be inverted.
 * @return The inverse of the input Transform4D object.
 */
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

	/**
 * @brief This function applies a transformation to a vector using a quaternion.
 *
 * The transformation is defined by the formula:
 * result = v * (q.w^2 - |b|^2) + b * (2 * dot(v, b)) + cross(b, v) * (2 * q.w)
 * where 'v' is the input vector, 'q' is the quaternion representing the transformation, and 'b' is the vector part of 'q'.
 * 
 * @param v The input vector to be transformed.
 * @param q The quaternion that defines the transformation.
 * @return A Vector3 object representing the transformed vector.
 */
Vector3 Math::Transform(const Vector3& v, const Quaternion& q)
	{
		const Vector3& b = q.GetVectorPart();
		float b2 = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
		return (
			v * (q.w * q.w - b2)
			+ b * (DotProduct3D(v, b) * 2.f)
			+ CrossProduct(b, v) * (q.w * 2.f));


	}

	/**
 * @brief Reflects a plane in 4D space.
 *
 * This function takes a Plane object and returns a Transform4D that represents the reflection of the plane across the origin. The transformation matrix is calculated based on the equation for reflection in 4 dimensions, which involves negating each component of the plane's normal vector (x, y, z) and scaling it by -1.
 *
 * @param f Plane object to be reflected.
 * @return Transform4D representing the reflection transformation.
 */
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

	/**
 * @brief Creates a transformation matrix from position, rotation and scale vectors.
 *
 * This function takes in three vectors representing the position, rotation, and scale of an object respectively. 
 * It uses these vectors to create a transformation matrix that can be used for transformations in 3D space.
 * The rotation is expected to be provided as Euler angles (pitch, yaw, roll).
 *
 * @param Position A Vector3 representing the position of the object.
 * @param Rotation A Vector3 representing the rotation of the object in Euler angles (pitch, yaw, roll).
 * @param Scale A Vector3 representing the scale of the object.
 * 
 * @return Matrix4D The transformation matrix created from the input vectors.
 */
Matrix4D Math::MakeTransform(const Vector3 &Position, const Vector3 &Rotation, const Vector3 &Scale)
	{

		Matrix4D Rot = glm::toMat4((glm::quat)*const_cast<Vector3*>(&Rotation));


		return glm::translate(Matrix4D(1.f).ToGLM(),(glm::vec3)*const_cast<Vector3*>(&Position)) * Rot.ToGLM() * glm::scale(Matrix4D(1.f).ToGLM(), (glm::vec3)*const_cast<Vector3*>(&Scale));

	}

	/**
 * @brief Decomposes a transformation matrix into translation, rotation and scale components.
 *
 * This function takes an input transformation matrix and decomposes it into its individual components - translation, rotation and scale. 
 * The decomposition is performed using the glm library's functions for matrix operations. It first isolates perspective by clearing the last column of the matrix, then calculates translation, scale and rotation from the remaining rows.
 *
 * @param Transform The input transformation matrix to be decomposed.
 * @param Translation Output parameter where the translation component will be stored.
 * @param Rotation Output parameter where the rotation component will be stored in Euler angles (in radians).
 * @param Scale Output parameter where the scale component will be stored.
 * 
 * @return Returns true if successful, false otherwise. If the input matrix is not invertible or has no perspective, this function returns false.
 */
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
		Translation = Vector3(vec3(LocalMatrix[3]));
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
			Rotation.x = atan2f(Row[1][2], Row[2][2]);
			Rotation.z = atan2f(Row[0][1], Row[0][0]);
		}
		else {
			Rotation.x = atan2f(-Row[2][0], Row[1][1]);
			Rotation.z = 0;
		}


		return true;
	}
	

	/**
 * @brief Calculates the rotation matrix associated with this quaternion.
 *
 * The function first calculates various intermediate values that are used in the calculation of the rotation matrix. These include products of the quaternion components and their squares. It then constructs a 3x3 Matrix3D object using these calculated values to represent the rotation represented by the quaternion.
 *
 * @return A 3x3 Matrix3D representing the rotation associated with this quaternion.
 */
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

	/**
 * @brief Sets the orientation from a given rotation matrix.
 *
 * This function converts a 3x3 rotation matrix into a quaternion representation of an orientation. It uses a formula based on the trace of the input matrix to determine which calculation path to take (sum > 0 or max element). The resulting quaternion is stored in this object for later use.
 *
 * @param m The 3x3 rotation matrix.
 */
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