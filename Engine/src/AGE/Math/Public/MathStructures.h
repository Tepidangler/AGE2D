#pragma once

#include <glm/glm.hpp>
#ifdef AG_PLATFORM_WINDOWS
#include "DirectXMath.h"
#include "d3d11_4.h"
#endif
#include "Math/Public/Vector2.h"
#include "Math/Public/Vector3.h"
#include "Math/Public/Vector4.h"

namespace AGE
{

	struct Point3D : Vector3
	{
		/**
 * @brief Default constructor for the Point3D class.
 * This function initializes a new instance of the Point3D class with all coordinates set to zero.
 *
 * @return A new instance of the Point3D class with x, y and z coordinates set to 0.
 */
/**
 * @brief Default constructor for the Point3D class.
 * Initializes a new instance of the Point3D class with x, y and z coordinates set to zero.
 *
 * @return A new instance of the Point3D class with all coordinates initialized to 0.
 */
Point3D() = default;

		/**
 * @brief Constructs a Point3D object with the given coordinates.
 * 
 * This constructor creates a Point3D object by initializing its x, y and z coordinates using the provided arguments. It inherits from Vector3 class.
 * 
 * @param a The x-coordinate of the point.
 * @param b The y-coordinate of the point.
 * @param c The z-coordinate of the point.
 */
/**
 * @brief Constructs a Point3D object by initializing its coordinates with the given values.
 * 
 * @param a The x-coordinate of the point.
 * @param b The y-coordinate of the point.
 * @param c The z-coordinate of the point.
 */
Point3D(float a, float b, float c) : Vector3(a, b, c) {}

		/**
 * @brief Assigns a Vector3 to a Point3D.
 *
 * This operator overload allows for the assignment of a Vector3 to a Point3D. 
 * It takes in a const reference to a Vector3 and returns a new Point3D with the same x, y, and z values as the input Vector3.
 *
 * @param v The Vector3 to be assigned.
 * @return A new Point3D with the same x, y, and z coordinates as the input Vector3.
 */
/**
 * @brief Assigns a Vector3 to a Point3D.
 *
 * This operator overload allows for the assignment of a Vector3 to a Point3D object. The x, y and z coordinates 
 * of the Vector3 are used to initialize the corresponding members in the Point3D object.
 *
 * @param v A const reference to the Vector3 that is being assigned.
 * @return A new Point3D object with the same values as the input Vector3.
 */
const Point3D operator =(Vector3 v) const
		{
			return Point3D(v[0], v[1], v[2]);
		}

		/**
 * @brief This function takes a Vector3 as input and returns a Point3D object. 
 * The returned Point3D is constructed from the x, y, z components of the input vector.
 *
 * @param v A Vector3 object representing the coordinates in space.
 * @return A Point3D object with the same coordinates as the input vector.
 */
/**
 * @brief This function takes a Vector3 as input and returns a Point3D object. 
 * The returned Point3D is constructed from the x, y, z components of the input Vector3.
 * 
 * @param v A Vector3 object representing the coordinates in space.
 * @return A Point3D object with the same coordinates as the input Vector3.
 */
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
		/**
 * @brief Default constructor for the Matrix2D class.
 *
 * Initializes a new instance of the Matrix2D class with default values.
 */
/**
 * @brief Default constructor for the Matrix2D class.
 *
 * This function initializes a new instance of the Matrix2D class with default values. It uses the '= default' syntax to delegate construction to the compiler-generated default constructor.
 *
 * @return A newly constructed Matrix2D object.
 */
Matrix2D() = default;

		/// | n00, n01 |
		/// | n10, n11 |
		/**
 * @brief Constructs a 2x2 matrix with the given values.
 * @param n00 The value to be assigned to the element at row 0, column 0.
 * @param n01 The value to be assigned to the element at row 0, column 1.
 * @param n10 The value to be assigned to the element at row 1, column 0.
 * @param n11 The value to be assigned to the element at row 1, column 1.
 */
/**
 * @brief Constructs a 2x2 matrix with the given values.
 * 
 * @param n00 The value to be assigned to the element at row 0, column 0 of the matrix.
 * @param n01 The value to be assigned to the element at row 0, column 1 of the matrix.
 * @param n10 The value to be assigned to the element at row 1, column 0 of the matrix.
 * @param n11 The value to be assigned to the element at row 1, column 1 of the matrix.
 */
Matrix2D(float n00, float n01,
			float n10, float n11)
		{
			n[0][0] = n00; n[0][1] = n01;
			n[1][0] = n10; n[1][1] = n11;
		}

		/// | a[0], a[1]|
		/// | b[0], b[1]|

		/**
 * @brief Constructs a 2D Matrix from two Vector2 objects.
 * 
 * The constructor initializes the matrix with values from two vectors, `a` and `b`. 
 * Each vector is represented as an (x, y) pair where x and y are the coordinates of the vector.
 * The first row of the matrix gets the values from vector a and the second row from vector b.
 *
 * @param a A Vector2 object representing the first row of the matrix.
 * @param b A Vector2 object representing the second row of the matrix.
 */
/**
 * @brief Constructs a 2x2 matrix from two Vector2 objects.
 * @param a The first vector to use for the construction of the matrix.
 * @param b The second vector to use for the construction of the matrix.
 */
Matrix2D(const Vector2& a, const Vector2& b)
		{
			n[0][0] = a[0]; n[0][1] = a[1];
			n[1][0] = b[0]; n[1][1] = b[1];
		}

		/**
 * @brief Accesses an element in the matrix using two indices.
 *
 * This function allows access to a single element in the matrix through its two-dimensional coordinates (i, j). 
 * It returns a reference to the requested element which can be used for read or write operations.
 *
 * @param i The first index of the element to access.
 * @param j The second index of the element to access.
 * @return A reference to the accessed element.
 */
/**
 * @brief Accesses an element in the matrix using two indices.
 *
 * This function allows access to a single element in the matrix by providing 
 * two indices, i and j. It returns a reference to the element at position (i,j) 
 * in the matrix. The indices are zero-based.
 *
 * @param i The first index of the element to be accessed.
 * @param j The second index of the element to be accessed.
 * @return A reference to the element at position (i,j).
 */
float& operator ()(int i, int j)
		{
			return(n[j][i]);
		}

		/**
 * @brief Accesses the element at position (i, j) in a two-dimensional array.
 *
 * This function allows you to access an element at a specific location in a 2D array using the subscript operator syntax. The indices i and j specify the position of the desired element.
 *
 * @param i The index along the first dimension (row).
 * @param j The index along the second dimension (column).
 *
 * @return A constant reference to the element at position (i, j) in the array.
 */
/**
 * @brief Access the element at a given position in constant time.
 *
 * This function allows for constant-time access to elements in the matrix. It takes two parameters, i and j, which represent the row and column indices of the desired element respectively. The function returns a reference to the requested element.
 *
 * @param i The index of the row (starting from 0).
 * @param j The index of the column (starting from 0).
 * @return A constant reference to the element at position (i,j) in the matrix.
 */
const float& operator ()(int i, int j) const
		{
			return(n[j][i]);
		}


		/**
 * @brief This function is an overloaded operator that allows for accessing Vector2 objects as if they were arrays.
 * It returns a reference to the jth element of the vector.
 * 
 * @param j The index of the element to access. Must be in the range [0, size-1].
 * @return A reference to the jth element of the vector.
 */
/**
 * @brief This function is an overloaded operator [] that returns a reference to the Vector2 object at index 'j' in the array.
 * @param j The index of the element to be accessed in the array.
 * @return A reference to the Vector2 object at index 'j'.
 */
Vector2& operator [](int j)
		{
			return (*reinterpret_cast<Vector2*>(n[j]));
		}

		/**
 * @brief Returns a constant reference to the element at index 'j' in the vector.
 *
 * This function returns a constant reference to the element at index 'j'. It is used for accessing elements of the vector without modifying them. 
 * The returned value should not be modified as it may lead to undefined behavior if the original data is changed elsewhere.
 *
 * @param j Index of the element to return. Must be a valid index within the range of the vector.
 * @return A constant reference to the element at index 'j'.
 */
/**
 * @brief This function returns a reference to the Vector2 object at index 'j' in an array of Vector2 objects.
 * 
 * @param j The index of the Vector2 object in the array.
 * @return A const reference to the Vector2 object at index 'j'.
 */
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

		/**
 * @brief Default constructor for the Matrix3D class.
 *
 * This function initializes a new instance of the Matrix3D class with all elements set to zero.
 *
 * @return A newly initialized Matrix3D object.
 */
/**
 * @brief Default constructor for the Matrix3D class.
 *
 * This function initializes a new instance of the Matrix3D class with default values. It is used to create an empty matrix object that can be populated with data later on.
 * 
 * @return A new instance of the Matrix3D class with no specific initialization.
 */
Matrix3D() = default;

		COMMENT:
/**
 * @brief Constructs a 3x3 Matrix with the given values.
 * 
 * @param n00,n01,n02 Values for the first row of the matrix.
 * @param n10,n11,n12 Values for the second row of the matrix.
 * @param n20,n21,n22 Values for the third row of the matrix.
 */
CONFIDENCE: 1.0;

/**
 * @brief Constructs a 3x3 Matrix with the given values.
 * 
 * The function initializes a 3x3 matrix using the provided nine float parameters, each representing an element of the matrix in row-major order (i.e., n[0][0], n[0][1], ..., n[2][2]).
 *
 * @param n00 Value for the first element of the matrix.
 * @param n01 Value for the second element of the matrix.
 * @param n02 Value for the third element of the matrix.
 * @param n10 Value for the fourth element of the matrix.
 * @param n11 Value for the fifth element of the matrix.
 * @param n12 Value for the sixth element of the matrix.
 * @param n20 Value for the seventh element of the matrix.
 * @param n21 Value for the eighth element of the matrix.
 * @param n22 Value for the ninth element of the matrix.
 */
Matrix3D(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22)
		{
			n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
			n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
			n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
		}

		/**
 * @brief Constructs a 3D Matrix from three Vector3 instances.
 * 
 * The constructor initializes the matrix with the x, y and z components of the input vectors.
 * It sets the first row to correspond to the vector 'a', the second row to 'b' and the third row to 'c'.
 * @param a First Vector3 instance for initialization.
 * @param b Second Vector3 instance for initialization.
 * @param c Third Vector3 instance for initialization.
 */
/**
 * @brief Constructs a 3D Matrix from three Vector3 instances.
 * 
 * The constructor initializes the matrix with the x, y and z components of the input vectors.
 * This is used to create a 3D transformation matrix for transformations in 3D space.
 * 
 * @param a First vector instance. Contains x, y and z components.
 * @param b Second vector instance. Contains x, y and z components.
 * @param c Third vector instance. Contains x, y and z components.
 */
Matrix3D(const Vector3& a, const Vector3& b, const Vector3& c)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		}

		/**
 * @brief Constructs a 3D Matrix from a void pointer.
 *
 * This function takes in a void pointer to an object of type Matrix3D, casts it to the appropriate type, and then copies its values into this Matrix3D instance.
 *
 * @param Ptr A void pointer to an existing Matrix3D object.
 */
/**
 * @brief Constructs a 3D Matrix from a void pointer.
 *
 * This function takes in a void pointer to an object of type Matrix3D, casts it to the appropriate type and then copies its values into this instance's matrix data members.
 *
 * @param Ptr A void pointer to an object of type Matrix3D.
 */
Matrix3D(void* Ptr)
		{
			Matrix3D Mat = *(Matrix3D*)Ptr;

			for (int i = 0; i < 3; ++i)
			{
				n[i][0] = Mat[i][0]; n[i][1] = Mat[i][1]; n[i][2] = Mat[i][2];
			}
		}

		/**
 * @brief Accesses an element in the matrix using two indices.
 *
 * This function allows access to a single element in the matrix through its two-dimensional indexing scheme. The elements are accessed by their row and column indices, with 0 being the first index for both.
 *
 * @param i The column index of the element to be accessed. Must be within the range [0, size_of_column).
 * @param j The row index of the element to be accessed. Must be within the range [0, size_of_row).
 * 
 * @return A reference to the float value at position (i,j) in the matrix.
 *
 * @throws std::out_of_range if either i or j is out of the valid range for their respective dimensions.
 */
/**
 * @brief Accesses an element in the matrix using two indices.
 *
 * This function allows access to a single element of the matrix through its two-dimensional coordinates (i, j). It returns a reference to the requested element.
 *
 * @param i The first index for accessing the element.
 * @param j The second index for accessing the element.
 * @return A reference to the accessed element.
 */
float& operator ()(int i, int j)
		{
			return (n[j][i]);
		}

		/**
 * @brief Returns a constant reference to the element at position (i, j).
 *
 * This function returns a constant reference to the element in the matrix at position (i, j), where i and j are zero-based indices. 
 * The returned value cannot be modified by this function. If you need to modify the matrix elements, use other functions provided by the class.
 *
 * @param i Zero-based index for the row of the element to return.
 * @param j Zero-based index for the column of the element to return.
 * 
 * @return Constant reference to the (i, j)-th element in the matrix.
 */
/**
 * @brief Access the element at position (i, j) in a two-dimensional array.
 *
 * This function allows you to access an element at a specific location in a two-dimensional array using 0-based indexing. The indices i and j represent the row and column of the desired element respectively.
 *
 * @param i The row index of the element to be accessed.
 * @param j The column index of the element to be accessed.
 * @return A constant reference to the element at position (i, j).
 */
const float& operator ()(int i, int j) const
		{
			return (n[j][i]);
		}

		/**
 * @brief This function is an overloaded operator that allows for accessing Vector3 objects in a vector of void pointers. It returns a reference to the jth element in the vector.
 * 
 * @param j The index of the element to access.
 * @return A reference to the jth Vector3 object.
 */
/**
 * @brief This function returns a reference to the Vector3 object at index 'j' in the array.
 *
 * @param j The index of the Vector3 object in the array.
 * @return A reference to the Vector3 object at index 'j'.
 */
Vector3& operator [](int j)
		{
			return (*reinterpret_cast<Vector3*>(n[j]));
		}

		/**
 * @brief This function returns a constant reference to the Vector3 object at index 'j' in the array.
 * 
 * @param j The index of the Vector3 object in the array.
 * @return A constant reference to the Vector3 object at index 'j'.
 */
/**
 * @brief This function returns a constant reference to the Vector3 object at index 'j' in the array.
 * @param j The index of the Vector3 object in the array.
 * @return A constant reference to the Vector3 object at index 'j'.
 */
const Vector3& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3*>(n[j]));
		}

		/**
 * @brief Converts the 3x3 matrix to a GLM mat3.
 *
 * This function takes no parameters and returns a glm::mat3 object that represents the same data as the current 3x3 matrix. The returned object is constructed by copying the elements of the current matrix into it, in row-major order.
 *
 * @return A glm::mat3 object representing the same data as the current 3x3 matrix.
 */
/**
 * @brief Converts the 3x3 matrix to a GLM mat3.
 *
 * This function takes no parameters and returns a glm::mat3 object that represents the same 3x3 matrix as this one. The elements of the returned mat3 are identical to those in this matrix, with indices running from 0 to 2 for both rows and columns.
 *
 * @return A glm::mat3 representation of the current 3x3 matrix.
 */
inline glm::mat3 ToGLM()
		{
			return glm::mat3(
				n[0][0], n[0][1], n[0][2],
				n[1][0], n[1][1], n[1][2],
				n[2][0], n[2][1], n[2][2]);
		}
		/**
 * @brief Converts the 3x3 matrix to a GLM mat3.
 *
 * This function converts the current 3x3 matrix into a glm::mat3 by copying its elements directly.
 * The resulting glm::mat3 is returned.
 *
 * @return A glm::mat3 representation of this 3x3 matrix.
 */
/**
 * @brief Converts the matrix to a GLM mat3.
 * 
 * This function converts the current matrix into a glm::mat3 by extracting its elements and returning them in a new glm::mat3 object.
 * The returned glm::mat3 will have the same values as this matrix, but it is guaranteed to be of type glm::mat3.
 * 
 * @return A glm::mat3 containing the same data as this matrix.
 */
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

		/**
 * @brief Default constructor for the Matrix4D class.
 *
 * Initializes a new instance of the Matrix4D class with all elements set to zero.
 */
/**
 * @brief Default constructor for the Matrix4D class.
 *
 * Initializes a new instance of the Matrix4D class with all elements set to zero.
 */
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

		/**
 * @brief Constructs a 4x4 matrix with the given value on the diagonal and zeros elsewhere.
 * 
 * @param f The value to be placed on the diagonal of the matrix.
 * 
 * This constructor initializes a 4x4 matrix where all elements are zero except for the main diagonal, which contains 'f'.
 */
/**
 * @brief Constructs a 4x4 matrix with the given value on the diagonal and zero elsewhere.
 * 
 * @param f The value to be placed on the diagonal of the matrix.
 */
Matrix4D(float f)
		{
			n[0][0] = f; n[0][1] = 0.f; n[0][2] = 0.f; n[0][3] = 0.f;
			n[1][0] = 0.f; n[1][1] = f; n[1][2] = 0.f; n[1][3] = 0.f;
			n[2][0] = 0.f; n[2][1] = 0.f; n[2][2] = f; n[2][3] = 0.f;
			n[3][0] = 0.f; n[3][1] = 0.f; n[3][2] = 0.f; n[3][3] = 1.f;
		}

		COMMENT:
/**
 * @brief Constructs a 4x4 matrix from a glm::mat4.
 *
 * This function takes a 4x4 matrix represented by the GLM library and constructs a Matrix4D object with its values.
 *
 * @param M A 4x4 matrix represented as a glm::mat4.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief Constructs a 4x4 matrix from a glm::mat4.
 *
 * @param M The input 4x4 matrix to be copied into this Matrix4D instance.
 */
CONFIDENCE: 1.0;

Matrix4D(glm::mat4 M)
		{
			n[0][0] = M[0][0]; n[0][1] = M[0][1]; n[0][2] = M[0][2]; n[0][3] = M[0][3];
			n[1][0] = M[1][0]; n[1][1] = M[1][1]; n[1][2] = M[1][2]; n[1][3] = M[1][3];
			n[2][0] = M[2][0]; n[2][1] = M[2][1]; n[2][2] = M[2][2]; n[2][3] = M[2][3];
			n[3][0] = M[3][0]; n[3][1] = M[3][1]; n[3][2] = M[3][2]; n[3][3] = M[3][3];
		}
#ifdef AG_PLATFORM_WINDOWS
		COMMENT:
/**
 * @brief Constructs a 4x4 matrix from an XMMATRIX.
 * 
 * The constructor takes in an instance of the DirectX::XMMATRIX class and extracts its components into this Matrix4D object.
 * 
 * @param M An instance of the DirectX::XMMATRIX class to be used for initialization.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief Constructs a 4x4 matrix from an XMMATRIX.
 * 
 * This function takes an instance of the XMMATRIX class and extracts its components into this Matrix4D object. The four rows of the XMMATRIX are stored in the corresponding elements of the n member array.
 *
 * @param M An instance of the XMMATRIX to be copied into this Matrix4D.
 */
CONFIDENCE: 1.0;

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

		/**
 * @brief Constructs a 4x4 matrix from four vectors.
 * 
 * The constructor initializes the 4x4 matrix with the given vectors. Each vector is interpreted as a row of the matrix in order (X, Y, Z, W).
 * 
 * @param a Vector representing the first row of the matrix.
 * @param b Vector representing the second row of the matrix.
 * @param c Vector representing the third row of the matrix.
 * @param p Vector representing the fourth row of the matrix.
 */
/**
 * @brief Constructs a 4x4 matrix from four vectors.
 * 
 * The constructor initializes the 4x4 matrix with the given vectors. Each vector is interpreted as a row of the matrix in order (X, Y, Z, W).
 * 
 * @param a Vector representing the first row of the matrix.
 * @param b Vector representing the second row of the matrix.
 * @param c Vector representing the third row of the matrix.
 * @param p Vector representing the fourth row of the matrix.
 */
Matrix4D(DirectX::XMVECTOR a, DirectX::XMVECTOR b, DirectX::XMVECTOR c, DirectX::XMVECTOR p)
		{
			n[0][0] = DirectX::XMVectorGetX(a); n[0][1] = DirectX::XMVectorGetY(a); n[0][2] = DirectX::XMVectorGetZ(a); n[0][3] = DirectX::XMVectorGetW(a);
			n[1][0] = DirectX::XMVectorGetX(b); n[1][1] = DirectX::XMVectorGetY(b); n[1][2] = DirectX::XMVectorGetZ(b); n[1][3] = DirectX::XMVectorGetW(b);
			n[2][0] = DirectX::XMVectorGetX(c); n[2][1] = DirectX::XMVectorGetY(c); n[2][2] = DirectX::XMVectorGetZ(c); n[2][3] = DirectX::XMVectorGetW(c);
			n[3][0] = DirectX::XMVectorGetX(p); n[3][1] = DirectX::XMVectorGetY(p); n[3][2] = DirectX::XMVectorGetZ(p); n[3][3] = DirectX::XMVectorGetW(p);
		}
#endif
		/**
 * @brief Constructs a 4D Matrix from four Vector4 instances.
 * 
 * The function takes in four Vector4 instances, each representing one row of the matrix. It assigns the x, y, z and w components of these vectors to the corresponding elements in the matrix.
 * 
 * @param a First Vector4 instance representing the first row of the matrix.
 * @param b Second Vector4 instance representing the second row of the matrix.
 * @param c Third Vector4 instance representing the third row of the matrix.
 * @param d Fourth Vector4 instance representing the fourth row of the matrix.
 */
/**
 * @brief Constructs a 4D matrix using four vectors.
 * 
 * The constructor initializes the 4x4 matrix with values from four Vector4 objects, each representing one row of the matrix.
 * 
 * @param a First vector to initialize the first row of the matrix.
 * @param b Second vector to initialize the second row of the matrix.
 * @param c Third vector to initialize the third row of the matrix.
 * @param d Fourth vector to initialize the fourth row of the matrix.
 */
Matrix4D(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
			n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
		}

		/**
 * @brief Constructs a Matrix4D object from an existing pointer to another Matrix4D.
 *
 * This constructor creates a new Matrix4D object that is initialized with the values of the Matrix4D pointed to by Ptr. 
 * The matrix elements are copied one-by-one, ensuring accurate copying of all data.
 *
 * @param Ptr A pointer to an existing Matrix4D object.
 */
/**
 * @brief Constructs a Matrix4D object from a void pointer.
 * 
 * This function takes in a void pointer to an existing Matrix4D object, and copies its values into the new Matrix4D object.
 * The input is expected to be of type `void*` which can hold any data type but should point to a valid Matrix4D object.
 * If the provided pointer does not point to a valid Matrix4D object, the behavior is undefined.
 * 
 * @param Ptr A void pointer to an existing Matrix4D object.
 */
Matrix4D(void* Ptr)
		{
			Matrix4D Mat = *(Matrix4D*)Ptr;

			for (int i = 0; i < 4; ++i)
			{
				n[i][0] = Mat[i][0]; n[i][1] = Mat[i][1]; n[i][2] = Mat[i][2]; n[i][3] = Mat[i][3];
			}
		}

		/**
 * @brief Copy constructor for the Matrix4D class.
 *
 * This function creates a new instance of the Matrix4D class by copying all data from another existing Matrix4D object.
 *
 * @param other The Matrix4D object to copy from.
 */
/**
 * @brief Copy constructor for a 4x4 matrix class.
 *
 * This function creates a deep copy of the input matrix, copying all elements to the newly created object.
 *
 * @param other The Matrix4D instance to be copied.
 */
Matrix4D(const Matrix4D& other) = default;

		/**
 * @brief Accesses the element at position (i, j) in a two-dimensional array.
 *
 * This function allows for accessing and modifying elements of a two-dimensional array using the subscript operator syntax. 
 * The indices i and j specify the location of the desired element within the array.
 *
 * @param i The first index, representing the row in the two-dimensional array.
 * @param j The second index, representing the column in the two-dimensional array.
 *
 * @return A reference to the float value at position (i, j) in the array.
 */
/**
 * @brief Accesses an element in the matrix using two indices.
 *
 * This function allows access to a specific element in the matrix by providing two indices, i and j. It returns a reference to this element. 
 * The returned value can be used for reading or writing the value of the specified element.
 *
 * @param i The first index. Must be within the range [0, size1).
 * @param j The second index. Must be within the range [0, size2).
 *
 * @return A reference to the matrix element at position (i,j).
 */
float& operator ()(int i, int j)
		{
			return (n[j][i]);
		}

		/**
 * @brief This function returns a constant reference to the element at position (i, j) in the matrix.
 * 
 * @param i The row index of the element to return.
 * @param j The column index of the element to return.
 * @return A constant reference to the element at position (i, j).
 */
/**
 * @brief Access the element at position (i, j) in a two-dimensional array.
 *
 * This function allows for constant access to an element at position (i, j) in a 2D array. The indices i and j should be within the valid range of the array.
 *
 * @param i The row index of the element to access.
 * @param j The column index of the element to access.
 * @return A constant reference to the accessed element.
 */
const float& operator ()(int i, int j) const
		{
			return (n[j][i]);
		}

		/**
 * @brief This function returns a reference to the Vector4 object at index 'j' in the array.
 * 
 * @param j The index of the Vector4 object in the array.
 * @return A reference to the Vector4 object at index 'j'.
 */
/**
 * @brief This function returns a reference to the Vector4 object at index 'j' in the array.
 *
 * @param j The index of the Vector4 object in the array.
 * @return A reference to the Vector4 object at index 'j'.
 */
Vector4& operator [](int j)
		{
			return (*reinterpret_cast<Vector4*>(n[j]));
		}

		/**
 * @brief This function returns a constant reference to the Vector4 at index 'j' in the array.
 * 
 * @param j The index of the Vector4 in the array.
 * @return A constant reference to the Vector4 at index 'j'.
 */
/**
 * @brief This function returns a constant reference to the Vector4 at index 'j' in the array.
 *
 * @param j The index of the Vector4 element to return.
 * @return A constant reference to the Vector4 at index 'j'.
 */
const Vector4& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector4*>(n[j]));
		}
#ifdef AG_PLATFORM_WINDOWS
		/// | a[0], a[1], a[2], p[0] |
		/// | b[0], b[1], b[2]  p[1] |
		/// | c[0], c[1], c[2]  p[2] |
		/// | 0.f, 0.f, 0.f, 1.f |
		/**
 * @brief Converts the 4x4 matrix to a DirectX::XMFLOAT4X4.
 *
 * This function takes no parameters and returns an instance of `DirectX::XMFLOAT4X4`, which represents the current 4x4 matrix in row-major order. The elements are ordered as follows:
 * - n[0][0] to n[0][3]
 * - n[1][0] to n[1][3]
 * - n[2][0] to n[2][3]
 * - n[3][0] to n[3][3].
 * 
 * @return A `DirectX::XMFLOAT4X4` object representing the current 4x4 matrix.
 */
/**
 * @brief Converts the 4x4 matrix to a DirectX::XMFLOAT4X4.
 *
 * This function takes a 4x4 matrix and converts it into a format that can be used with the DirectX Math library's XMFLOAT4X4 structure. The conversion is done by simply copying each element from the source matrix to the corresponding position in the new XMFLOAT4X4 object.
 *
 * @return A DirectX::XMFLOAT4X4 containing the same data as the original 4x4 matrix, but in a format compatible with the DirectX Math library.
 */
inline DirectX::XMFLOAT4X4 ToXMFloat4X4()
		{
			return DirectX::XMFLOAT4X4(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		}
		/**
 * @brief Converts the 4x4 matrix to an XMMATRIX.
 *
 * This function takes a 4x4 matrix and converts it into an XMMATRIX, which is used in DirectX programming for vector and matrix operations.
 * The input matrix is expected to be stored as a 16-element array where the elements are arranged in row-major order (i.e., n[row][column]).
 *
 * @return An XMMATRIX representation of the input 4x4 matrix.
 */
/**
 * @brief Converts the 4x4 matrix to an XMMATRIX.
 *
 * This function takes a 4x4 matrix and converts it into an XMMATRIX, which is used in DirectX programming for vector and matrix operations.
 * The input matrix is represented as a 2D array of floats where each row corresponds to one of the four rows of the matrix.
 *
 * @return An XMMATRIX representation of the 4x4 matrix.
 */
inline DirectX::XMMATRIX ToXMMat()
		{
			return DirectX::XMMATRIX(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		};
#endif
		/**
 * @brief Converts the current matrix to a GLM mat4.
 * 
 * This function converts the current matrix into a glm::mat4 by directly copying its values into the new object. The order of elements is as follows:
 * - n[0][0] through n[0][3]
 * - n[1][0] through n[1][3]
 * - n[2][0] through n[2][3]
 * - n[3][0] through n[3][3]
 * 
 * @return glm::mat4 The converted matrix.
 */
/**
 * @brief Converts the current matrix to a GLM mat4.
 * 
 * This function converts the current matrix into a glm::mat4 by directly copying each element from the original matrix to the new one.
 * The resulting matrix will have the same values as the original, but it is in the format used by GLM (OpenGL Mathematics).
 * 
 * @return A glm::mat4 containing the same data as the current matrix.
 */
inline glm::mat4 ToGLM()
		{
			return glm::mat4(
				n[0][0], n[0][1], n[0][2], n[0][3],
				n[1][0], n[1][1], n[1][2], n[1][3],
				n[2][0], n[2][1], n[2][2], n[2][3],
				n[3][0], n[3][1], n[3][2], n[3][3]);
		}
		/**
 * @brief Converts the matrix to a GLM mat4.
 * 
 * This function converts the current matrix into a glm::mat4 by directly copying each element from the original matrix to the new one.
 * The order of elements is maintained in row-major order (i.e., n[0][0] through n[3][3]).
 * 
 * @return A glm::mat4 with the same values as this matrix, but in a format compatible with GLM.
 */
/**
 * @brief Converts the matrix to a GLM mat4.
 * 
 * This function converts the current matrix into a glm::mat4 by directly copying each element from the original matrix to the new one.
 * The order of elements is as follows: [0][0], [0][1], [0][2], [0][3], [1][0], [1][1], [1][2], [1][3], [2][0], [2][1], [2][2], [2][3], [3][0], [3][1], [3][2], [3][3].
 * 
 * @return glm::mat4 The converted matrix.
 */
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
		/**
 * @brief Default constructor for the Transform4D class.
 *
 * This function initializes a new instance of the Transform4D class with default values.
 * The default values are typically set to identity transformations, but this behavior can be overridden in derived classes.
 *
 * @return A new instance of the Transform4D class with default values.
 */
/**
 * @brief Default constructor for the Transform4D class.
 */
Transform4D() = default;

		/**
 * @brief Constructs a 4x4 transformation matrix from the given parameters.
 * 
 * The function initializes a 4x4 transformation matrix with the provided values.
 * It assumes that the last row and column are [0, 0, 0, 1] respectively.
 * 
 * @param n00,n01,n02,n03,n10,n11,n12,n13,n20,n21,n22,n23 Values for the matrix elements.
 * 
 * @return void
 */

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

		COMMENT:
/**
 * @brief Constructs a 4x4 transformation matrix from three vectors and a point.
 * 
 * The resulting matrix represents the transformation that would be equivalent to applying the given vectors as basis vectors in order, followed by translating by the given point. This is commonly used in computer graphics for transformations of objects.
 *
 * @param a First vector defining the transformation.
 * @param b Second vector defining the transformation.
 * @param c Third vector defining the transformation.
 * @param p Point to translate after applying vectors.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief Constructs a 4x4 transformation matrix from three vectors and a point.
 * 
 * The resulting matrix represents the transformation that would be equivalent to applying a rotation defined by the input vectors, followed by a translation by the input point.
 * 
 * @param a First vector defining the rotation.
 * @param b Second vector defining the rotation.
 * @param c Third vector defining the rotation.
 * @param p Point representing the translation.
 */
CONFIDENCE: 1.0;

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

		/**
 * @brief This function is an overloaded operator that returns a reference to the Vector3 object at index 'j' in the array.
 * @param j The index of the element in the array to return.
 * @return A reference to the Vector3 object at index 'j'.
 */
/**
 * @brief This function is an overloaded operator [] that returns a reference to the Vector3 object at index 'j' in the array.
 * @param j The index of the element to be accessed in the array.
 * @return A reference to the Vector3 object at index 'j'.
 */
Vector3& operator [](int j)
		{
			return (*reinterpret_cast<Vector3*>(n[j]));
		}

		/**
 * @brief This function returns a constant reference to the Vector3 object at index 'j' in the array.
 * 
 * @param j The index of the Vector3 object in the array.
 * @return A constant reference to the Vector3 object at index 'j'.
 */
/**
 * @brief This function returns a constant reference to the Vector3 object at index 'j' in the array.
 *
 * @param j The index of the Vector3 object in the array.
 * @return A constant reference to the Vector3 object at index 'j'.
 */
const Vector3& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3*>(n[j]));
		}

		/**
 * @brief Returns the translation of this object.
 *
 * This function returns a reference to the translation component of this object. The returned value is 
 * const and should not be modified by the caller.
 *
 * @return A constant reference to the translation component of this object.
 */
/**
 * @brief Returns the translation of this object.
 *
 * This function returns a reference to the translation component of this object. The returned value is 
 * interpreted as a const Point3D&, meaning that it cannot be modified by the caller.
 *
 * @return A constant reference to the translation component of this object.
 */
const Point3D& GetTranslation(void) const
		{
			return (*reinterpret_cast<const Point3D*>(n[3]));
		}

		/**
 * @brief Sets the translation of the object to a new position specified by a Point3D object.
 *
 * This function sets the coordinates (x, y, z) of the fourth row and column of the transformation matrix 
 * to match those of the input Point3D object 'p'. The purpose of this function is to update the translation 
 * component of the transformation matrix based on a new position.
 *
 * @param p A constant reference to a Point3D object representing the new position.
 */
/**
 * @brief Sets the translation of the object to a new position defined by a Point3D object.
 *
 * This function sets the coordinates (x, y, z) of the fourth row and columns of the transformation matrix to 
 * match those of the input Point3D object 'p'. It is assumed that the transformation matrix 'n' has been properly initialized before this call.
 *
 * @param p A const reference to a Point3D object representing the new position.
 */
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

		/**
 * @brief Default constructor for the Quaternion class.
 *
 * Initializes a new instance of the Quaternion class with all elements set to zero.
 */
/**
 * @brief Default constructor for the Quaternion class.
 * This function initializes a new instance of the Quaternion class with all elements set to zero.
 * The quaternion is initialized as the identity quaternion, which represents no rotation in 3D space.
 *
 * @return A default constructed Quaternion object.
 */
Quaternion() = default;

		/**
 * @brief Quaternion constructor.
 *
 * This function is used to initialize a new instance of the Quaternion class with four parameters representing the x, y, z and w components of the quaternion respectively.
 * 
 * @param a The value for the x component of the quaternion.
 * @param b The value for the y component of the quaternion.
 * @param c The value for the z component of the quaternion.
 * @param s The value for the w component of the quaternion.
 */
/**
 * @brief Quaternion constructor.
 *
 * This function initializes a new instance of the Quaternion class with given values for x, y, z and w coordinates.
 *
 * @param a The value to initialize x coordinate.
 * @param b The value to initialize y coordinate.
 * @param c The value to initialize z coordinate.
 * @param s The value to initialize w coordinate.
 */
Quaternion(float a, float b, float c, float s)
		{
			x = a; y = b; z = c;
			w = s;
		}

		/**
 * @brief Constructs a Quaternion from a Vector3 and a scalar value.
 * 
 * This function takes in a Vector3 and a scalar, which are used to initialize the x, y, z coordinates of the Quaternion and its w (scalar) component respectively.
 *
 * @param v The input vector that will be used to set the x, y, and z components of the quaternion.
 * @param s The scalar value that will be used to initialize the w component of the quaternion.
 */
/**
 * @brief Quaternion constructor that takes a Vector3 and a scalar as input parameters.
 * @param v A const reference to a Vector3 object representing the vector part of the quaternion.
 * @param s The float value representing the scalar part of the quaternion.
 */
Quaternion(const Vector3& v, float s)
		{
			x = v.x; y = v.y; z = v.z;
			w = s;
		}

		/**
 * @brief Returns a reference to the x component of the vector.
 * @details This function returns a reference to the x component of the vector, which can be used for direct manipulation or read-only access. 
 * The returned value is reinterpreted as a Vector3& object.
 * @return A reference to the x component of the vector.
 */
/**
 * @brief Returns a reference to the first three elements of this vector.
 *
 * This function returns a reference to the first three elements of the vector. The returned object can be used for modifying these values directly, without needing to access them through other member functions or operators. 
 *
 * @return A reference to the first three elements of the vector.
 */
Vector3& GetVectorPart(void)
		{
			return (reinterpret_cast<Vector3&>(x));
		}

		/**
 * @brief Returns a reference to the first three components of this vector.
 * @details This function returns a reference to the first three components of the current vector object. 
 * The returned reference can be used for read-only access to these components, or for modifying them directly if desired.
 * @return A const reference to the first three components of the vector.
 */
/**
 * @brief Returns a constant reference to the first three elements of the vector.
 * @details This function returns a constant reference to the first three elements of the vector. 
 * It is used when you want to access these elements without modifying them, and it avoids unnecessary copying.
 * The returned object should not be modified as it directly references internal data of this instance.
 * @return A constant reference to the first three elements of the vector.
 */
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

		/**
 * @brief Default constructor for the Plane class.
 *
 * This function initializes a new instance of the Plane class with default values.
 * It does not take any parameters and returns no value.
 */
/**
 * @brief Default constructor for the Plane class.
 *
 * This function initializes a new instance of the Plane class with default values.
 * It is used to create an empty plane object that can be populated with data later.
 * 
 * @return A new Plane object with all fields initialized to their default values.
 */
Plane() = default;

		/**
 * @brief Constructs a Plane object with the given parameters.
 * 
 * This function initializes a Plane object with four floating-point values, which represent the coordinates of a plane in 3D space. The first three parameters (nx, ny, nz) define the normal vector of the plane and the fourth parameter (d) is the distance from the origin to the plane along this direction.
 * @param nx The x-coordinate of the normal vector of the plane.
 * @param ny The y-coordinate of the normal vector of the plane.
 * @param nz The z-coordinate of the normal vector of the plane.
 * @param d The distance from the origin to the plane along its normal direction.
 */
/**
 * @brief Constructs a Plane object with the given parameters.
 * 
 * @param nx The x-coordinate of the plane's normal vector.
 * @param ny The y-coordinate of the plane's normal vector.
 * @param nz The z-coordinate of the plane's normal vector.
 * @param d The distance from the origin to the plane along its normal vector.
 */
Plane(float nx, float ny, float nz, float d)
		{
			x = nx;
			y = ny;
			z = nz;
			w = d;
		}

		/**
 * @brief Constructs a Plane object with the given normal vector and distance from origin.
 * 
 * @param n The normal vector of the plane.
 * @param d The distance from the origin to the plane along its normal direction.
 */
/**
 * @brief Constructs a Plane object from a Vector3 and a float.
 * 
 * The plane is defined by the equation ax + by + cz = w, where (x, y, z) are the components of the input vector and 'w' is the input float.
 * 
 * @param n A Vector3 representing the direction of the plane.
 * @param d A float representing a point on the plane along the normal from which the distance to the origin is measured.
 */
Plane(const Vector3& n, float d)
		{
			x = n.x;
			y = n.y;
			z = n.z;
			w = d;
		}

		/**
 * @brief Returns a reference to the normal vector of this object.
 * @return A constant reference to the internal normal vector.
 */
/**
 * @brief Returns a reference to the normal vector of this object.
 * @return A constant reference to the internal normal vector.
 */
const Vector3& GetNormal(void) const
		{
			return (reinterpret_cast<const Vector3&>(x));
		}

	};

	struct Line
	{
		Vector3 Direction;
		Vector3 Moment;

		/**
 * @brief Default constructor for the Line class.
 *
 * This function initializes a new instance of the Line class with default values.
 * It does not take any parameters and returns no value.
 */
/**
 * @brief Default constructor for the Line class.
 */
Line() = default;

		/**
 * @brief Constructs a Line object with given direction and moment vectors.
 * 
 * @param vx The x component of the direction vector.
 * @param vy The y component of the direction vector.
 * @param vz The z component of the direction vector.
 * @param mx The x component of the moment vector.
 * @param my The y component of the moment vector.
 * @param mz The z component of the moment vector.
 */
/**
 * @brief Constructs a Line object with given direction and moment vectors.
 * 
 * @param vx The x component of the direction vector.
 * @param vy The y component of the direction vector.
 * @param vz The z component of the direction vector.
 * @param mx The x component of the moment vector.
 * @param my The y component of the moment vector.
 * @param mz The z component of the moment vector.
 */
Line(float vx, float vy, float vz, float mx, float my, float mz) : Direction(vx, vy, vz), Moment(mx, my, mz)
		{
		}

		/**
 * @brief Constructs a Line object with given direction and moment vectors.
 * 
 * @param v The direction vector of the line.
 * @param m The moment vector of the line.
 */
/**
 * @brief Constructs a Line object with given direction and moment vectors.
 * 
 * @param v The direction vector of the line.
 * @param m The moment vector of the line.
 */
Line(const Vector3& v, const Vector3& m)
		{
			Direction = v;
			Moment = m;
		}

	};

	/**
 * @brief Performs a matrix-vector multiplication.
 * 
 * Multiplies a Vector4 by each row of a Matrix4D to produce a new Matrix4D.
 */
/**
 * @brief This function performs a matrix-vector multiplication.
 * It takes a Vector4 and a Matrix4D as input and returns the result of multiplying the vector by the matrix.
 * The operation is performed component-wise, resulting in a new Matrix4D where each element is the product of the corresponding elements from the input vectors and matrices.
 * 
 * @param V A Vector4 to be multiplied with the Matrix4D.
 * @param M The Matrix4D to multiply with the Vector4.
 * @return The result of the multiplication as a new Matrix4D.
 */
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

	/**
 * @brief Adds two 4x4 matrices together element-wise.
 *
 * This function takes two 4x4 matrices as input and returns a new matrix that is the result of adding the corresponding elements from the input matrices.
 * The addition operation is performed component-wise, meaning it adds the x values together for each Vector4 in the Matrix4D objects.
 *
 * @param M1 The first 4x4 matrix to add.
 * @param M2 The second 4x4 matrix to add.
 * @return A new 4x4 matrix that is the result of adding the input matrices together element-wise.
 */
/**
 * @brief This function performs element-wise addition of two 4x4 matrices.
 * 
 * @param M1 The first matrix to be added.
 * @param M2 The second matrix to be added.
 * 
 * @return A new Matrix4D object resulting from the addition operation. Each Vector4 in this matrix corresponds to a row of the original two input matrices, and is the sum of the corresponding rows in the input matrices.
 */
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

	
/**
 * @brief This function performs a matrix-vector multiplication operation.
 * 
 * The function takes in two parameters - a Matrix4D and a Vector4. It multiplies the vector by each row of the matrix separately, adds these results together, and returns the resulting Vector3.
 * 
 * @param M A const reference to the Matrix4D that will be used for multiplication.
 * @param V A const reference to the Vector4 that will be multiplied with the rows of the Matrix4D.
 * 
 * @return The function returns a Vector3 which is the result of the matrix-vector multiplication operation.
 */
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

		//glm::mat4 mat = M.ToGLM();
		//glm::vec4 vec{V.x, V.y, V.z, V.w};
		//glm::vec4 New = mat*vec;



		return {Add2(0, 0), Add2(1, 1), Add2(2, 2)};
		//return {New.x, New.y, New.z};
	}

	COMMENT:
/**
 * @brief Performs a matrix multiplication operation.
 *
 * This function multiplies two matrices together using the standard matrix multiplication rules. The resulting matrix is a new object and does not modify the original matrices.
 *
 * @param A The first input Matrix3D to be multiplied.
 * @param B The second input Matrix3D to be multiplied.
 * 
 * @return A new Matrix3D that represents the result of the multiplication operation.
 */
CONFIDENCE: 1.0;

/**
 * @brief This function performs a matrix multiplication operation on two matrices.
 *
 * The function takes as input two Matrix3D objects (A and B), each representing a 3x3 matrix. It returns a new Matrix3D object that represents the result of multiplying A by B.
 *
 * @param A The first operand for the multiplication operation.
 * @param B The second operand for the multiplication operation.
 *
 * @return A new Matrix3D object representing the product of matrices A and B.
 */
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

	COMMENT:
/**
 * @brief Multiplies two 4x4 matrices.
 *
 * This function multiplies two 4x4 matrices A and B together using the standard matrix multiplication rules.
 * The result is a new 4x4 matrix that represents the product of A and B.
 *
 * @param A The first input matrix.
 * @param B The second input matrix.
 * @return Matrix4D The resulting 4x4 matrix after multiplication.
 */
CONFIDENCE: 1.0;

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * This function multiplies two 4x4 matrices A and B together using the standard matrix multiplication rules.
 * The result is a new 4x4 matrix that represents the product of A and B.
 *
 * @param A The first input matrix.
 * @param B The second input matrix.
 * @return Matrix4D The resulting 4x4 matrix after the multiplication operation.
 */
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

	/**
 * @brief This function performs a matrix-vector multiplication operation.
 * 
 * Given a Matrix3D and a Vector3, this function computes the result of multiplying the Matrix3D by the Vector3. The resulting Vector3 is returned as output.
 * 
 * @param M A const reference to the Matrix3D that will be multiplied.
 * @param v A const reference to the Vector3 that will be multiplied.
 * @return Returns a new Vector3 which is the result of multiplying the input Matrix3D by the input Vector3.
 */
/**
 * @brief Multiplies a Matrix3D by a Vector3 and returns the result as a new Vector3.
 * 
 * This function performs a matrix-vector multiplication operation on the input vector 'v' using the provided 3x3 matrix 'M'. The resulting vector is returned as a new Vector3 object.
 * 
 * @param M A const reference to the Matrix3D that will be multiplied by the Vector3.
 * @param v A const reference to the Vector3 that will be multiplied by the Matrix3D.
 * 
 * @return A new Vector3 resulting from the multiplication of 'M' and 'v'.
 */
inline Vector3 operator *(const Matrix3D& M, const Vector3& v)
	{
		return (Vector3(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
			M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
			M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
	}
	/**
 * @brief This function performs a matrix-vector multiplication operation.
 * It takes a Vector3 and a Matrix4D as input and returns the result of multiplying the vector by the matrix.
 * The resulting Vector3 is calculated as follows: 
 * - x component = M(0, 0)*v.x + M(0, 1)*v.y + M(0, 2)*v.z
 * - y component = M(1, 0)*v.x + M(1, 1)*v.y + M(1, 2)*v.z
 * - z component = M(2, 0)*v.x + M(2, 1)*v.y + M(2, 2)*v.z
 * @param v The Vector3 to be multiplied by the Matrix4D.
 * @param M The Matrix4D that will multiply the Vector3.
 * @return A new Vector3 resulting from the multiplication of the input Vector3 and Matrix4D.
 */
/**
 * @brief Multiplies a Vector3 by a Matrix4D from the left.
 *
 * This function multiplies a Vector3 on the left side of a Matrix4D to yield another Vector3. The result is computed as follows:
 * -# Each component of the Vector3 is multiplied by the corresponding row in the Matrix4D.
 * -# These products are then summed together to form the components of the resulting Vector3.
 * 
 * @param v The Vector3 to be multiplied from the left.
 * @param M The Matrix4D to multiply with.
 * @return A new Vector3 that is the result of the multiplication.
 */
inline Vector3 operator *(const Vector3& v, const Matrix4D& M)
	{
		return (Vector3(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
			M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
			M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
	}
	/**
 * @brief This function adds a Point3D and Vector3 together to produce another Point3D.
 * 
 * @param a The Point3D that will be added to the Vector3.
 * @param b The Vector3 that will be added to the Point3D.
 * @return A new Point3D which is the result of adding the input Point3D and Vector3 together.
 */
/**
 * @brief This function overloads the '+' operator to add a Vector3 to a Point3D.
 * It takes two parameters - a constant reference to a Point3D (a) and a constant reference 
 * to a Vector3 (b). The function returns a new Point3D that is the result of adding b to a.
 * @param a A constant reference to a Point3D object.
 * @param b A constant reference to a Vector3 object.
 * @return A new Point3D which is the sum of the input Point3D and Vector3.
 */
inline Point3D operator +(const Point3D& a, const Vector3& b)
	{
		return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	/**
 * @brief Subtracts a vector from a point in 3D space.
 *
 * This function subtracts the components of a vector from the corresponding components of a point to yield a new point.
 *
 * @param a The point from which the vector is subtracted.
 * @param b The vector that is subtracted.
 * @return A new Point3D object representing the result of the subtraction.
 */
/**
 * @brief Subtracts a vector from a point in 3D space.
 *
 * This function subtracts the components of a vector from the corresponding components of a point to yield a new point.
 *
 * @param a The point from which the vector is subtracted.
 * @param b The vector that is subtracted.
 * @return A new Point3D object representing the result of the subtraction.
 */
inline Point3D operator -(const Point3D& a, const Vector3& b)
	{
		return (Point3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	/**
 * @brief Subtracts two Point3D objects and returns the resulting Vector3 object.
 *
 * This function subtracts the coordinates of two Point3D objects to create a new Vector3 object. 
 * The x-coordinate of the result is obtained by subtracting the x-coordinates of the two points, 
 * the y-coordinate is obtained by subtracting the y-coordinates and so on.
 *
 * @param a First Point3D object to be subtracted.
 * @param b Second Point3D object which will be subtracted from the first one.
 * @return Vector3 object resulting from the subtraction of two points.
 */
/**
 * @brief Subtracts two Point3D objects and returns the resulting Vector3 object.
 *
 * This function takes in two Point3D objects (a and b) and subtracts them component-wise, 
 * returning a new Vector3 object with the result of the subtraction. The x, y, and z components 
 * of the returned Vector3 are calculated as follows: (a.x - b.x), (a.y - b.y), and (a.z - b.z) respectively.
 *
 * @param a The first Point3D object to subtract from.
 * @param b The second Point3D object to subtract.
 * @return A Vector3 object representing the result of the subtraction.
 */
inline Vector3 operator -(const Point3D& a, const Point3D& b)
	{
		return (Vector3(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	COMMENT:
/**
 * @brief This function performs a matrix multiplication operation on two Transform4D objects.
 * The result is another Transform4D object which represents the product of the input matrices.
 *
 * @param A First Transform4D object to be multiplied.
 * @param B Second Transform4D object to be multiplied.
 * 
 * @return Resulting Transform4D object after multiplication operation.
 */
CONFIDENCE: 1.0;

/**
 * @brief Multiplies two 4x4 transformation matrices.
 *
 * This function takes in two 4x4 transformation matrices and returns a new matrix that represents their product.
 * The operation is performed component-wise, i.e., each element of the resulting matrix is the product of the corresponding elements from the input matrices.
 *
 * @param A The first matrix to multiply.
 * @param B The second matrix to multiply.
 * 
 * @return A new Transform4D object that represents the result of the multiplication.
 */
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
	/**
 * @brief Multiplies a Transform4D by a Vector3 to produce another Vector3.
 *
 * This function takes in a 4x4 transformation matrix and a 3-dimensional vector,
 * multiplies the two together according to standard matrix multiplication rules,
 * and returns the result as a new Vector3.
 *
 * @param H The Transform4D to be multiplied.
 * @param v The Vector3 to be multiplied.
 * @return A new Vector3 that is the product of the transformation and vector.
 */
/**
 * @brief Multiplies a Transform4D by a Vector3 to produce another Vector3.
 *
 * This function takes in a 4x4 transformation matrix and a 3-dimensional vector, and returns the result of multiplying the latter by the former. The operation is performed componentwise on each element of the vectors.
 *
 * @param H A const reference to the Transform4D to be multiplied.
 * @param v A const reference to the Vector3 to be multiplied.
 * @return A new Vector3 that is the result of the multiplication.
 */
inline Vector3 operator *(const Transform4D& H, const Vector3& v)
	{
		return (Vector3(H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
			H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
			H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z));
	}

	/**
 * @brief Multiplies a Transform4D by a Point3D to transform the point using the transformation matrix.
 *
 * This function multiplies each element of the Transform4D with corresponding elements in the Point3D, 
 * and sums them up to get the transformed coordinates. The resulting Point3D is returned as output.
 *
 * @param H The Transform4D that will be used for transformation.
 * @param p The Point3D that needs to be transformed.
 * @return A new Point3D which represents the result of the transformation.
 */
/**
 * @brief Multiplies a Transform4D by a Point3D to produce a new transformed Point3D.
 *
 * This function multiplies the elements of a Transform4D matrix with the corresponding elements of a Point3D, 
 * resulting in a new Point3D that has been transformed according to the transformation specified by the Transform4D.
 *
 * @param H The Transform4D to multiply.
 * @param p The Point3D to be multiplied.
 * @return A new Point3D that is the result of the multiplication.
 */
inline Point3D operator *(const Transform4D& H, const Point3D& p)
	{
		return (Point3D(H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
			H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
			H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3)));
	}
	/**
 * @brief This function performs a multiplication operation between a Vector3 and a Transform4D object.
 * 
 * The function takes in two parameters - a constant reference to a Vector3 object (n) and a constant reference to a Transform4D object (H). It returns a new Vector3 object which is the result of the multiplication operation.
 * 
 * @param n A constant reference to a Vector3 object.
 * @param H A constant reference to a Transform4D object.
 * @return The function returns a new Vector3 object that represents the result of the multiplication operation between the input Vector3 and Transform4D objects.
 */
/**
 * @brief This function performs a multiplication operation between a Vector3 and a Transform4D object.
 * 
 * The function takes two parameters - a const reference to a Vector3 (n) and a const reference to a Transform4D (H). It returns a new Vector3 that is the result of multiplying each element in the Vector3 by the corresponding elements in the Transform4D.
 * 
 * @param n A const reference to a Vector3 object.
 * @param H A const reference to a Transform4D object.
 * @return A new Vector3 that is the result of multiplying each element in the input Vector3 by the corresponding elements in the input Transform4D.
 */
inline Vector3 operator *(const Vector3& n, const Transform4D& H)
	{
		return (Vector3(n.x * H(0, 0) + n.y * H(1, 0) + n.z * H(2, 0),
			n.x * H(0, 1) + n.y * H(1, 1) + n.z * H(2, 1),
			n.x * H(0, 2) + n.y * H(1, 2) + n.z * H(2, 2)));
	}

	/**
 * @brief Multiplies a plane with a homogeneous transformation matrix.
 *
 * This function multiplies the components of a Plane object with a Transform4D object to produce a new Plane that is transformed by the given homogenous transformation.
 * 
 * @param f The Plane to be multiplied.
 * @param H The Transform4D to multiply with.
 * @return A new Plane resulting from the multiplication of the input Plane and Transform4D.
 */
/**
 * @brief This function multiplies a Plane by a Transform4D and returns the result as a new Plane.
 * 
 * The multiplication is performed component-wise on each of the x, y, z coordinates of the Plane,
 * and then adds the corresponding element from the Transform4D to the w coordinate (the fourth component) of the resulting Plane.
 * This allows for a transformation of the Plane by a 3D affine transformation represented by the Transform4D.
 * 
 * @param f The Plane to be multiplied.
 * @param H The Transform4D to multiply with.
 * @return A new Plane that is the result of the multiplication.
 */
inline Plane operator *(const Plane& f, const Transform4D& H)
	{
		return (Plane(f.x * H(0, 0) + f.y * H(1, 0) + f.z * H(2, 0),
			f.x * H(0, 1) + f.y * H(1, 1) + f.z * H(2, 1),
			f.x * H(0, 2) + f.y * H(1, 2) + f.z * H(2, 2),
			f.x * H(0, 3) + f.y * H(1, 3) + f.z * H(2, 3) + f.w));
	}

	/**
 * @brief Computes the cross product of two points in a 3D space.
 * 
 * The function calculates and returns a Line object representing the cross product of two Point3D objects, p and q.
 * The Line is defined by its direction vector (dx, dy, dz) and a scalar (length). In this context, the cross product
 * of two points in a 3D space results in a line that passes through both points and has a length equal to zero.
 *
 * @param p First Point3D object for cross product calculation.
 * @param q Second Point3D object for cross product calculation.
 * @return Line representing the cross product of two points in 3D space.
 */
/**
 * @brief Computes the cross product of two points in a 3D space.
 *
 * The function calculates and returns a Line object representing the cross product of two Point3D objects, p and q.
 * The Line is defined by its direction vector (dx, dy, dz) and a scalar (length). In this context, the cross product
 * of two points in 3D space corresponds to the line that passes through both points and has a non-zero length.
 *
 * @param p First Point3D object.
 * @param q Second Point3D object.
 * @return Line representing the cross product of p and q.
 */
inline Line operator ^(const Point3D& p, const Point3D& q)
	{
		return (Line(q.x - p.x, q.y - p.y, q.z - p.z,
			p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x));
	}

	/**
 * @brief Computes the cross product of two planes.
 *
 * This function calculates the cross product of two planes by performing a matrix multiplication operation on their vectors. The resulting vector is then converted into a Line object, which represents the line that lies in the intersection of the two input planes.
 *
 * @param f The first plane for the cross product.
 * @param g The second plane for the cross product.
 * @return A Line object representing the cross product of the two input planes.
 */
/**
 * @brief Computes the cross product of two planes.
 *
 * This function computes the cross product of two planes and returns a line as result. The line is defined by its direction vector (dx, dy, dz) and a point on the line (x0, y0, z0). 
 *
 * @param f The first plane.
 * @param g The second plane.
 * @return A Line that represents the cross product of the two planes.
 */
inline Line operator ^(const Plane& f, const Plane& g)
	{
		return (Line(f.z * g.y - f.y * g.z,
			f.x * g.z - f.z * g.x,
			f.y * g.x - f.x * g.y,
			f.x * g.w - f.w * g.x,
			f.y * g.w - f.w * g.y,
			f.z * g.w - f.w * g.z));
	}

	/**
 * @brief Computes the plane perpendicular to a line and passing through a point.
 *
 * This function calculates the plane that is perpendicular to the given line (L) and passes through the specified point (p). 
 * The normal of this plane is defined by the direction vector of the line, which is used as the x, y, and z coordinates respectively.
 * The constant of the plane is calculated using the cross product of the moment vector of the line with the position vector of the point.
 *
 * @param L A const reference to a Line object representing the line for which we want to calculate the plane.
 * @param p A const reference to a Point3D object representing the point through which the plane passes.
 * @return Plane The resulting plane perpendicular to the input line and passing through the specified point.
 */
/**
 * @brief Computes the plane perpendicular to a line and passing through a point in 3D space.
 * 
 * Given a line and a point, this function computes the plane that is perpendicular to the line and passes through the point. The normal of the plane points along the direction vector of the line.
 * 
 * @param L A const reference to the Line object for which the plane is being computed.
 * @param p A const reference to the Point3D object representing the point in space.
 * @return Plane Returns a Plane object that represents the plane perpendicular to the input line and passing through the input point.
 */
inline Plane operator ^(const Line& L, const Point3D& p)
	{
		return (Plane(L.Direction.y * p.z - L.Direction.z * p.y + L.Moment.x,
			L.Direction.z * p.x - L.Direction.x * p.z + L.Moment.y,
			L.Direction.x * p.y - L.Direction.y * p.x + L.Moment.z,
			-L.Moment.x * p.x - L.Moment.y * p.y - L.Moment.z * p.z));
	}
	/**
 * @brief Computes the plane that intersects a given line and point.
 * 
 * This function takes in a Point3D object 'p' and a Line object 'L', computes the Plane that they both represent, and returns it. The result is equivalent to computing (L ^ p).
 * 
 * @param p A const reference to the Point3D object representing the point of intersection.
 * @param L A const reference to the Line object representing the line of intersection.
 * @return Plane Returns a Plane that intersects with the input Line and Point3D.
 * 
 * @exception None. This function does not throw any exceptions under normal circumstances.
 */
/**
 * @brief Computes the plane through a point and a line.
 *
 * This function takes a point and a line as input and computes the plane that passes through both of them. The result is returned in the form of a Plane object.
 * 
 * @param p A const reference to a Point3D object representing the point.
 * @param L A const reference to a Line object representing the line.
 * @return Returns a Plane object that represents the plane through the input point and line.
 */
inline Plane operator ^(const Point3D& p, const Line& L)
	{
		return (L ^ p);
	}
	/**
 * @brief Computes the cross product of a line and a plane in 3D space.
 *
 * The function takes two parameters, a line (L) represented by its moment vector and direction vector, and a plane (f) represented by its normal vector. It returns a Vector4 that represents the result of the cross product operation between the line and the plane.
 *
 * @param L A const reference to the Line object representing the line in 3D space.
 * @param f A const reference to the Plane object representing the plane in 3D space.
 *
 * @return A Vector4 that represents the cross product of the input line and plane. The x, y, z components correspond to the result of the cross product operation, while the w component is always zero.
 */
/**
 * @brief Computes the cross product of a line and a plane in 3D space.
 *
 * The function takes two parameters, a Line object (L) and a Plane object (f). It returns a Vector4 which represents the result of the cross product operation.
 *
 * @param L A const reference to the Line object for which the cross product is computed.
 * @param f A const reference to the Plane object with respect to which the cross product is computed.
 * 
 * @return Returns a Vector4 representing the result of the cross product operation. The components of this vector are calculated as follows:
 * -# The x component is the dot product of L.Moment.y and f.z, minus the dot product of L.Moment.z and f.y, plus the dot product of L.Direction.x and f.w.
 * -# The y component is the dot product of L.Moment.z and f.x, minus the dot product of L.Moment.x and f.z, plus the dot product of L.Direction.y and f.w.
 * -# The z component is the dot product of L.Moment.x and f.y, minus the dot product of L.Moment.y and f.x, plus the dot product of L.Direction.z and f.w.
 * -# The w component is negative of the sum of L.Direction.x and L.Direction.y times f.x, minus the sum of L.Direction.y and L.Direction.z times f.y, minus the sum of L.Direction.z and L.Direction.x times f.z.
 */
inline Vector4 operator ^(const Line& L, const Plane& f)
	{
		return (Vector4(
			L.Moment.y * f.z - L.Moment.z * f.y + L.Direction.x * f.w,
			L.Moment.z * f.x - L.Moment.x * f.z + L.Direction.y * f.w,
			L.Moment.x * f.y - L.Moment.y * f.x + L.Direction.z * f.w,
			-L.Direction.x * f.x - L.Direction.y * f.y - L.Direction.z * f.z));
	}
	/**
 * @brief Computes the intersection of a plane and line.
 *
 * This function calculates the intersection point between a given plane and line. The result is returned as a Vector4, which represents a homogeneous coordinate in 3D space.
 *
 * @param f A constant reference to the Plane object representing the plane.
 * @param L A constant reference to the Line object representing the line.
 * @return A Vector4 representing the intersection point between the plane and line.
 */
/**
 * @brief Computes the intersection of a plane and a line.
 *
 * This function calculates the intersection point between a given plane and line. The result is returned as a Vector4, which represents the intersection point in homogeneous coordinates.
 *
 * @param f A constant reference to the Plane object representing the plane.
 * @param L A constant reference to the Line object representing the line.
 * 
 * @return A Vector4 representing the intersection point between the plane and line.
 */
inline Vector4 operator ^(const Plane& f, const Line& L)
	{
		return (L ^ f);
	}

	/**
 * @brief Computes the signed distance between a point and a plane.
 *
 * The function calculates the signed distance from a given point to a specified plane. It uses the formula for the dot product of two points, with an additional constant term. 
 * This result is positive if the point lies in one side of the plane and negative if it lies on the other side. Zero indicates that the point lies exactly on the plane.
 *
 * @param p The Point3D object representing the point for which to calculate the signed distance.
 * @param f The Plane object representing the plane from which to compute the signed distance.
 * 
 * @return A float value representing the signed distance between the point and the plane.
 */
/**
 * @brief Computes the signed distance from a point to a plane.
 *
 * This function calculates the signed distance between a given point and a plane. The sign of the result indicates which side of the plane the point is on, with positive values indicating one side and negative values indicating the other.
 *
 * @param p The 3D point for which to calculate the signed distance.
 * @param f The plane from which to compute the signed distance.
 * @return The signed distance between the point and the plane.
 */
inline float operator ^(const Point3D& p, const Plane& f)
	{
		return (p.x * f.x + p.y * f.y + p.z * f.z + f.w);
	}

	/**
 * @brief Computes the signed distance between a point and a plane.
 *
 * This function calculates the signed distance from a given point to a plane. The sign of this value indicates which side of the plane the point lies on, with positive values indicating one side and negative values indicating the other. Zero means that the point is exactly on the plane. 
 *
 * @param f The Plane for which we want to compute the signed distance.
 * @param p The Point3D from which we want to calculate the signed distance.
 * @return float Returns a floating-point value representing the signed distance between the point and the plane.
 */
/**
 * @brief Computes the signed distance between a point and a plane.
 *
 * This function calculates the signed distance from a given point to a plane. The sign of the result indicates which side of the plane the point lies on, with positive values indicating one side and negative values indicating the other. Zero means that the point is exactly on the plane.
 *
 * @param f The Plane for which we want to compute the signed distance.
 * @param p The Point3D from which we want to compute the signed distance.
 * 
 * @return A float representing the signed distance between the given point and plane.
 */
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


		/**
 * @brief This function returns the total number of vertices in all quads.
 * 
 * The function multiplies the number of quads by 4 to get the total vertex count.
 * 
 * @return uint32_t Total number of vertices in all quads.
 */
/**
 * @brief This function returns the total number of vertices in all quads.
 * It multiplies the count of quads by 4 to get the total vertex count.
 *
 * @return The total number of vertices in all quads.
 */
uint32_t GetTotalQuadVertexCount() { return QuadCount * 4; }
		/**
 * @brief This function returns the total number of indices used by all quads in the scene.
 *        Each quad is composed of four vertices and each vertex has three coordinates, so a quad uses 24 indices.
 *        The function multiplies the number of quads (QuadCount) by 6 to get the total index count.
 * @return uint32_t Total number of indices used by all quads in the scene.
 */
/**
 * @brief This function returns the total number of indices used by all quads in the system.
 * The count is calculated as the product of the quad count and 6, representing each quad's four triangles (2 triangles per face) and three vertices per triangle.
 *
 * @return uint32_t Total index count for all quads.
 */
uint32_t GetTotalQuadIndexCount() { return QuadCount * 6; }
		/**
 * @brief Calculates the total number of vertices in all tiles.
 *
 * This function multiplies the number of tiles by 4 to get the total vertex count.
 * The assumption is that each tile has 4 vertices.
 *
 * @return Total number of vertices across all tiles.
 */
/**
 * @brief This function returns the total number of vertices in all tiles.
 * The calculation is based on each tile having 4 vertices.
 * Therefore, it multiplies the number of tiles by 4 to get the total vertex count.
 *
 * @return uint32_t Total number of vertices across all tiles.
 */
uint32_t GetTotalTileVertexCount() { return TileCount * 4; }
		/**
 * @brief This function returns the total number of tile indices in the game world.
 * The count is calculated by multiplying the total number of tiles (TileCount) with 6.
 * @return uint32_t Total number of tile indices in the game world.
 */
/**
 * @brief This function returns the total number of tile indices in the game world.
 * The count is calculated by multiplying the total number of tiles (TileCount) with 6.
 * @return uint32_t Total number of tile indices in the game world.
 */
uint32_t GetTotalTileIndexCount() { return TileCount * 6; }
		/**
 * @brief Calculates the total number of vertices in a cube.
 *
 * The function multiplies the number of cubes by 8 to get the total vertex count.
 * This is because each cube has 8 vertices.
 *
 * @return uint32_t Total number of vertices in all cubes.
 */
/**
 * @brief Calculates the total number of vertices in a cube.
 *
 * The function multiplies the number of cubes by 8 to get the total vertex count.
 * This is because each cube has 8 vertices.
 *
 * @return uint32_t Total number of vertices in all cubes.
 */
uint32_t GetTotalCubeVertexCount() { return CubeCount * 8; }
		/**
 * @brief This function returns the total count of cube indices in the scene.
 * The count is calculated by multiplying the number of cubes (@c CubeCount) by 36 (the number of indices per cube).
 * @return Total count of cube indices in the scene.
 */
/**
 * @brief This function returns the total count of cube indices in the scene.
 *        Each cube has 36 indices (2 for each of its 18 edges).
 * @return The total number of cube indices in the scene.
 */
uint32_t GetTotalCubeIndexCount() { return CubeCount * 36; }
		/**
 * @brief Calculates the total number of vertices in all spheres.
 *
 * This function multiplies the number of spheres by 8 to get the total vertex count.
 * It assumes that each sphere has 8 vertices.
 *
 * @return The total number of vertices in all spheres.
 */
/**
 * @brief Calculates the total number of vertices in all spheres.
 *
 * This function multiplies the count of spheres by 8 to get the total vertex count.
 * It assumes that each sphere has 8 vertices.
 *
 * @return The total number of vertices in all spheres.
 */
uint32_t GetTotalSphereVertexCount() { return SphereCount * 8; }
		/**
 * @brief This function returns the total number of sphere indices in the scene.
 * Each sphere is represented by 36 indices (12 for each face).
 * The count of spheres is multiplied by 36 to get the total index count.
 * @return uint32_t Total number of sphere indices in the scene.
 */
/**
 * @brief This function returns the total number of sphere indices in the scene.
 * The calculation is based on the assumption that each sphere has 36 indices (vertices, normals and texture coordinates).
 * @return uint32_t Total number of sphere indices.
 */
uint32_t GetTotalSphereIndexCount() { return SphereCount * 36; }
		/**
 * @brief This function returns the total number of vertices in all cylinders.
 * The calculation is based on each cylinder having 8 vertices.
 * @return uint32_t Total number of vertices in all cylinders.
 */
/**
 * @brief This function returns the total number of vertices in all cylinders.
 * The calculation is based on each cylinder having 8 vertices.
 * @return uint32_t Total count of vertices in all cylinders.
 */
uint32_t GetTotalCylinderVertexCount() { return CylinderCount * 8; }
		/**
 * @brief This function returns the total number of cylinders in the system, multiplied by 18.
 * @return The total count of cylinders in the system.
 */
/**
 * @brief This function returns the total count of cylinder indices based on the number of cylinders.
 * @return The total count of cylinder indices as a uint32_t value.
 */
uint32_t GetTotalCylinderIndexCount() { return CylinderCount * 18; }
		/**
 * @brief Calculates the total number of vertices in a pyramid.
 *
 * The function multiplies the number of pyramids by 5 to get the total vertex count.
 *
 * @return uint32_t Total number of vertices in all pyramids.
 */
/**
 * @brief Calculates the total number of vertices in a pyramid.
 *
 * The function multiplies the number of pyramids by 5 to get the total vertex count.
 *
 * @return uint32_t Total number of vertices in all pyramids.
 */
uint32_t GetTotalPyramidVertexCount() { return PyramidCount * 5; }
		/**
 * @brief This function calculates the total number of indices in a pyramid.
 * The pyramid is represented as an array where each element represents a cube.
 * Each cube has 6 faces, so to get the total number of indices, we multiply the number of cubes by 6.
 * @return uint32_t Total number of indices in the pyramid.
 */
/**
 * @brief This function calculates the total number of indices in a pyramid.
 * The pyramid is represented as an equilateral triangle and each face of the triangle is a cube, so the total number of cubes that make up the pyramid is multiplied by 6 to get the total number of indices.
 * @return uint32_t This function returns the total number of indices in the pyramid as an unsigned 32-bit integer.
 */
uint32_t GetTotalPyramidIndexCount() { return CubeCount * 6; }
		//uint32_t GetTotalVertexCount() {return}
		//uint32_t GetTotalIndexCount()  {return}
	};

}