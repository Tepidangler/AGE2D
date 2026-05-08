#pragma once

#include "MathStructures.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <numbers>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>



namespace AGE
{
	class Math
	{
	public:

		/**
 * @brief Calculates the magnitude of a three-dimensional vector.
 * 
 * This function takes a const reference to a Vector3 object and returns its magnitude by calculating the square root of the sum of the squares of each component (x, y, z).
 * 
 * @param v A constant reference to a Vector3 object representing the vector for which we want to calculate the magnitude.
 * @return float The magnitude of the input vector.
 */
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

		/**
 * @brief Computes the dot product of two 2D vectors.
 * 
 * This function takes two Vector2 objects as input and returns their dot product. The dot product is calculated by multiplying the corresponding elements from each vector together (a[0]*b[0] + a[1]*b[1]) and summing these products up.
 * 
 * @param a First Vector2 object to use in the dot product calculation.
 * @param b Second Vector2 object to use in the dot product calculation.
 * @return The result of the dot product operation.
 */
static inline float DotProduct2D(const Vector2& a, const Vector2& b)
		{
			return (a[0] * b[0] + a[1] * b[1]);
		}
		//Implementation of Dot Product in 3D
		/**
 * @brief Computes the dot product of two Vector3 objects.
 *
 * The function takes in two Vector3 objects, 'a' and 'b', and returns their dot product.
 * This is calculated as the sum of the products of corresponding elements from each vector. 
 * For example, for vectors [a1, a2, a3] and [b1, b2, b3], the dot product would be (a1*b1 + a2*b2 + a3*b3).
 *
 * @param a The first Vector3 object.
 * @param b The second Vector3 object.
 * 
 * @return A float representing the dot product of 'a' and 'b'.
 */
static inline float DotProduct3D(const Vector3& a, const Vector3& b)
		{
			return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
		}

		/**
 * @brief Computes the dot product of a plane and a vector in three-dimensional space.
 * 
 * This function takes two parameters, a Plane object (consisting of x, y, z coordinates) and a Vector3 object (also consisting of x, y, z coordinates). It returns the dot product of these two sets of coordinates.
 * @param f The Plane for which to compute the dot product.
 * @param v The Vector3 for which to compute the dot product.
 * @return float The computed dot product.
 */
static float DotProductPlaneVector(const Plane& f, const Vector3& v)
		{
			return (f.x * v[0] + f.y * v[1] + f.z * v[2]);
		}

		/**
 * @brief Computes the dot product of a plane and a point in 3D space.
 *
 * The function takes as input a Plane object (consisting of four components x, y, z, w) and a Point3D object (consisting of three components [0], [1], [2]). It returns the dot product of these two vectors which is calculated as follows: 
 * f.x*p[0] + f.y*p[1] + f.z*p[2] + f.w. The Plane object represents a plane in 3D space, and the Point3D object represents a point on that same plane.
 *
 * @param f A const reference to a Plane object representing a plane in 3D space.
 * @param p A const reference to a Point3D object representing a point on the plane.
 *
 * @return The dot product of the plane and the point as a float value.
 */
static float DotProductPlanePoint(const Plane& f, const Point3D& p)
		{
			return (f.x * p[0] + f.y * p[1] + f.z * p[2] + f.w);
		}

		static bool IntersectLinePlane(const Point3D& p, const Vector3& v, const Plane& f, Point3D* q);

		//Implementation of Cross Product in 2D 

		/**
 * @brief Compute the cross product of two 2D vectors.
 * 
 * This function calculates the cross product of two 2D vectors, which is a scalar value representing the z-component of the vector formed by taking the cross product in three dimensions. The result is returned as a float.
 * @param a First Vector for Cross Product operation.
 * @param b Second Vector for Cross Product operation.
 * @return A float that represents the cross product of two 2D vectors.
 */
static inline float CrossProduct2D(const Vector2& a, const Vector2& b)
		{
			return (a[0] * b[1] - b[0] * a[1]); // Since there really isn't anyway to do a 2D Cross product what 
			//we've opted to do is return a scalar when I guess would be applied along the x and y axes respectively
		}

		//Implementation of Cross Product in 3D

		/**
 * @brief Computes the cross product of two vectors.
 * 
 * The function takes two Vector3 objects as input and returns their cross product.
 * It uses the standard mathematical formula for calculating the cross product of three-dimensional vectors, which is (a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1).
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return Vector3 The cross product of the two input vectors.
 */
static inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
		{
			return (Vector3(

				a[1] * b[2] - a[2] * b[1],
				a[2] * b[2] - a[0] * b[2],
				a[0] * b[1] - a[1] * b[0]));
		}

		//Implementation of Projection on 2D plane

		/**
 * @brief Computes the projection of a vector on another.
 *
 * This function takes two vectors as input and returns their projection. The projection is calculated by multiplying the first vector (a) with the ratio of its dot product with the second vector (b) divided by the square of the magnitude of the second vector (b). 
 *
 * @param a The vector to be projected.
 * @param b The vector onto which the projection is computed.
 * @return The projection of vector 'a' on vector 'b'.
 */
static inline Vector2 Project2D(const Vector2& a, const Vector2& b)
		{
			return (b * (DotProduct2D(a, b) / DotProduct2D(b, b)));
		}

		// Implementation of Rejection in 2D
		/**
 * @brief Computes the rejection of one vector from another in a 2D space.
 * 
 * This function takes two vectors 'a' and 'b', computes their dot product (DotProduct2D(a, b)) and divides it by the square of the magnitude of vector 'b'. The result is then subtracted from vector 'a' to yield a new vector.
 * 
 * @param a First input vector.
 * @param b Second input vector.
 * @return Vector2 Resulting rejection vector.
 */
static inline Vector2 Reject2D(const Vector2& a, const Vector2& b)
		{
			return (a - b * (DotProduct2D(a, b) / DotProduct2D(b, b)));
		}

		// Implementation of Projection in 3D

		/**
 * @brief Projects a vector 'a' onto another vector 'b'.
 *
 * This function takes two vectors as input. The first one is the vector to be projected (a) and the second one is the vector onto which we want to project (b). 
 * It returns a new Vector3 that results from projection of vector 'a' on 'b'.
 *
 * @param a The vector to be projected.
 * @param b The vector onto which we want to project.
 * @return A new Vector3 resulting from the projection of vectors 'a' and 'b'.
 */
static inline Vector3 Project3D(const Vector3& a, Vector3& b)
		{
			return (b * (DotProduct3D(a, b) / DotProduct3D(b, b)));
		}

		// Implementation of Rejection in 3D

		/**
 * @brief Rejects a vector from another in three dimensions.
 *
 * This function calculates the rejection of one vector (`a`) from another (`b`). 
 * The rejection is calculated as `a - b * ((a . b) / (b . b))`, where '.' denotes dot product.
 *
 * @param a Vector to be rejected.
 * @param b Vector to reject from.
 * @return Vector resulting from the rejection of vector `a` from `b`.
 */
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
		/**
 * @brief This function applies a 4x4 homogeneous transformation matrix to a Line object.
 * The transformation is performed in 3D space and the resultant line is returned.
 *
 * @param[in] line - A const reference to the Line object that needs to be transformed.
 * @param[in] H - A const reference to the Transform4D object representing the homogeneous transformation matrix.
 *
 * @return The function returns a new Line object which is the result of applying the 4x4 transformation matrix to the input line.
 */
static Line Transform(const Line& line, const Transform4D& H)
		{
			Matrix3D adj(CrossProduct(H[1], H[2]), CrossProduct(H[2], H[0]), CrossProduct(H[0], H[1])); // Calculate the transpose of the adjugate of the upper-left 3x3 portion of H
			const Point3D& t = H.GetTranslation();

			Vector3 v = H * line.Direction;
			Vector3 m = adj * line.Moment + CrossProduct(t, v);
			return(Line(v, m));
		}

		/**
 * @brief Converts an angle from degrees to radians.
 *
 * This function takes a degree value and converts it into radians by multiplying the degree value with pi (3.14159) and dividing by 180.
 * The result is then returned as a float.
 *
 * @param Deg The angle in degrees to be converted.
 * @return The equivalent angle in radians.
 */
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

		/**
 * @brief Converts degrees to radians for each component of a Vector3 object.
 *
 * This function takes a Vector3 object as input and returns a new Vector3 object where each component is the original value converted from degrees to radians. 
 * The conversion formula used here is: radian = degree * pi / 180.
 *
 * @param Vec A Vector3 object containing the values in degrees that need to be converted to radians.
 * @return A new Vector3 object where each component has been converted from degrees to radians.
 */
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
		/**
 * @brief Converts a given angle from radians to degrees.
 * 
 * This function takes an input in radians and converts it into degrees using the formula (Rad / pi) * 180.
 * The result is then returned as output in degrees.
 * 
 * @param Rad Angle in radians to be converted to degrees.
 * @return float Converted angle in degrees.
 */
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

		/**
 * @brief Converts radians to degrees for a Vector3 object.
 * 
 * This function takes a Vector3 object as input and returns a new Vector3 object where each component is the equivalent angle in degrees. The conversion formula used here is th / pi * 180, where 'th' represents the radian angle.
 * 
 * @param Vec A Vector3 object representing the angles in radians to be converted to degrees.
 * @return A new Vector3 object with each component being the equivalent angle in degrees.
 */
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

		/**
 * @brief Converts an angle from degrees to radians.
 *
 * This function takes a float value representing the degree and returns its equivalent in radians. It uses the std::acosf() function, which is expected to return the arc cosine of the input value, converted into radians by dividing it by 180.
 *
 * @param Deg The angle in degrees to be converted.
 * @return The angle in radians equivalent to the input degree.
 */
static float DegreeToRadians(float Deg)
		{
			return std::acosf(Deg) /180.f;
		}

		static bool DecomposeTransform(const Matrix4D& Transform, Vector3& Translation, Vector3& Rotation, Vector3& Scale);


		/**
 * @brief Computes the cosine of an angle in radians.
 * 
 * This function takes an input parameter 'a' which represents an angle in radians and returns the cosine of that angle.
 * The result is a floating-point number representing the cosine of the input angle.
 * 
 * @param a An angle in radians.
 * @return A float value representing the cosine of the input angle.
 */
static float Cos(float a)
		{
			return std::cos(a);
		}

		/**
 * @brief Computes the sine of an angle in radians.
 * 
 * This function takes an input parameter 'a' which represents an angle in radians and returns its sine value.
 * The result is computed using the standard C++ library function std::sin().
 * 
 * @param a Angle in radians to compute the sine of.
 * @return Sine of the input angle.
 */
static float Sin(float a)
		{
			return std::sin(a);
		}

		/**
 * @brief Computes the arc cosine of input value.
 * 
 * This function takes in a floating-point number and returns its arc cosine, which is the angle in radians whose cosine is the specified number.
 * The result will be between 0 and pi (inclusive). If the argument is not within the range [-1,1], then NaN is returned.
 *
 * @param a Floating-point value for which to compute arc cosine.
 * @return Arc cosine of input value in radians.
 */
static float ACos(float a)
		{
			return std::acos(a);
		}
		/**
 * @brief Calculates the square root of a given number.
 * 
 * This function takes in a single parameter, 'a', which is the number to calculate the square root for. It returns the square root of 'a' as a float value.
 * If 'a' is negative, it will return NaN (Not a Number).
 * 
 * @param a The input number whose square root needs to be calculated.
 * @return Returns the square root of 'a'.
 */
static float Sqrt(float a)
		{
			return std::sqrtf(a);
		}

		template<typename T>
		/**
 * @brief This function adds two generic type parameters and returns the result.
 * @param[in] a The first parameter to add.
 * @param[in] b The second parameter to add.
 * @return Returns the sum of 'a' and 'b'.
 */
static T Add(T a, T b)
		{
			return a + b;
		}
		template<typename T>
		/**
 * @brief This function subtracts two values of type T and returns the result.
 * @param[in] a The first value to be subtracted.
 * @param[in] b The second value to be subtracted from the first one.
 * @return The result of the subtraction operation. If the inputs are invalid, it may return an incorrect result or throw an exception.
 */
static T Subtract(T a, T b)
		{
			return a - b;
		}
		template<typename T>
		/**
 * @brief This function multiplies two values of type T and returns the result.
 * 
 * @param a The first value to multiply.
 * @param b The second value to multiply.
 * @return The product of a and b.
 */
static T Multiply(T a, T b)
		{
			return a * b;
		}
		template<typename T>
		/**
 * @brief Performs division operation on two numbers of type T.
 *
 * This function takes in two parameters of the same type T and returns their quotient when they are divided. If the divisor is zero, it will throw an exception to avoid undefined behavior.
 * 
 * @param a The first number of type T for division operation.
 * @param b The second number of type T for division operation.
 * @return Returns the result of the division operation on two numbers.
 * @throws std::invalid_argument if divisor is zero to avoid undefined behavior.
 */
static T Divide(T a, T b)
		{
			return a / b;
		}

		/** 
 * @brief Computes the modulus of two numbers using fmod function from cmath library.
 * 
 * @param a The first number in the operation.
 * @param b The second number in the operation. Must be non-zero to avoid division by zero.
 * 
 * @return Returns the remainder of the division of 'a' by 'b'. If 'b' is zero, returns NaN (Not a Number).
 */
static double Modulo(double a, double b)
		{
			return std::fmod(a,b);
		}

		/**
 * @brief Computes the power of a number.
 *
 * This function takes two parameters and returns the result of raising the first parameter to the power of the second. 
 * If no exponent is provided, it defaults to 2.0.
 *
 * @param a The base number.
 * @param b The exponent. Defaults to 2.0 if not specified.
 * @return Returns the result of raising 'a' to the power of 'b'.
 */
static float Pow(float a, float b = 2.f)
		{
			return std::powf(a, b);
		}

		/**
 * @brief Calculates the cube root of a number.
 * 
 * This function takes in a single parameter, 'a', and returns its cube root using the standard library's `std::cbrtf` function.
 * The input should be greater than or equal to zero; attempting to calculate the cube root of negative numbers will result in undefined behavior.
 * 
 * @param a A float number for which we want to find its cube root.
 * @return Returns the cube root of 'a'.
 */
static float CubeRoot(float a)
		{
			return std::cbrtf(a);
		}

	};

	/**
 * @brief Computes the dot product of two lines in a 3D space.
 *
 * This function calculates the dot product of two lines represented by their direction vectors and moment vectors. The result is negative because of the way the dot product is defined.
 *
 * @param L1 First line to be used for computation.
 * @param L2 Second line to be used for computation.
 *
 * @return Negative float value representing the dot product of two lines in a 3D space.
 */
inline float operator ^(const Line& L1, const Line& L2)
	{
		return (-(Math::DotProduct3D(L1.Direction, L2.Moment) + Math::DotProduct3D(L2.Direction, L1.Moment)));
	}
}

