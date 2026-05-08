#pragma once


#include "Core/Public/AGEpch.hpp"
#include "Core/Public/Core.h"
#include "Math/Public/MathStructures.h"
#include "Events/Public/Event.h"
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <zlib.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>



namespace AGE
{
#ifdef AG_PLATFORM_WINDOWS
	struct XInputControllerSettings
	{
	public:

		/**
 * @brief Default constructor for the XInputControllerSettings class.
 * 
 * This function initializes an instance of the XInputControllerSettings class with its default settings.
 * It does not take any parameters and returns void.
 */
XInputControllerSettings() = default;

		int LeftThumbstickDeadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		int RightThumbstickDeadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

		int LeftTriggerDeadzone, RightTriggerDeadzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

		// Left Motor Speed
		uint16_t LowFreqMotorSpeed = 0;
		// Right Motor Speed
		uint16_t HighFreqMotorSpeed = 0;
	};

	struct XInputControllerInfo
	{
	public:
		/**
 * @brief Default constructor for XInputControllerInfo class.
 *
 * This function initializes an instance of the XInputControllerInfo class with its members set to their default values.
 * It does not perform any specific initialization tasks, as indicated by the '= default' syntax in C++11.
 * 
 * @return An instance of XInputControllerInfo with all members initialized to their default values.
 */
XInputControllerInfo() = default;

		ulong_t PacketNumber = 0;

		ulong_t UserIndex = 0;

		bool bShouldVibrate = true;

		bool bConnected = false;

		uint8_t BatteryType = 0;

		uint8_t BatteryLevel = 0;

		XInputControllerSettings Settings;

		std::function<void(Event&)> CallbackFn;

		/**
 * @brief Checks the connection status of the object.
 * 
 * This function returns a boolean value indicating whether or not the object is connected to its source.
 * It does this by returning the 'bConnected' member variable directly.
 * 
 * @return bool - Returns true if connected, false otherwise.
 */
operator bool()
		{
			return bConnected;
		}

		uint16_t ButtonState = 0;
	};
#endif
	class VertexBuffer;
	class ConstantBuffer;

	struct AGEPixel
	{
	public:
		float RGBAf[4];
		uint8_t RGBAc[4];
		uint32_t U32RBGA[4];

		/**
 * @brief Default constructor for the AGEPixel class.
 */
AGEPixel() = default;

		/**
 * @brief Constructs an instance of AGEPixel with the given RGBA values.
 * 
 * The function takes four uint8_t parameters representing the red, green, blue and alpha components of a pixel in the range [0,255]. It then converts these values to Uint32_t format for internal use.
 * @param a Red component (uint8_t).
 * @param b Green component (uint8_t).
 * @param c Blue component (uint8_t).
 * @param d Alpha component (uint8_t).
 */
AGEPixel(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
		{
			RGBAc[0] = a;
			RGBAc[1] = b;
			RGBAc[2] = c;
			RGBAc[3] = d;

			//Convert to Uint32_t 

			U32RBGA[0] = RGBAc[0];
			U32RBGA[1] = RGBAc[1];
			U32RBGA[2] = RGBAc[2];
			U32RBGA[3] = RGBAc[3];
			
		}

		/**
 * @brief Constructs an instance of AGEPixel with four float values.
 * 
 * This function takes in four float values and assigns them to the RGBAf array. It then converts these floats into a uint32_t representation, which it stores in the U32RBGA array.
 * @param a The first float value.
 * @param b The second float value.
 * @param c The third float value.
 * @param d The fourth float value.
 */
AGEPixel(float a, float b, float c, float d)
		{
			RGBAf[0] = a;
			RGBAf[1] = b;
			RGBAf[2] = c;
			RGBAf[3] = d;

			float tmp[4] = { a,b,c,d };
			uint32_t* tmp1 = ConvertFloatToU32(tmp);
			//Convert to Uint32_t 

			U32RBGA[0] = tmp1[0];
			U32RBGA[1] = tmp1[1];
			U32RBGA[2] = tmp1[2];
			U32RBGA[3] = tmp1[3];

		}

		/**
 * @brief This function converts the object to a Bytef pointer.
 *
 * The function returns a pointer of type Bytef that points to the RGBA color array.
 * It is used for certain operations in the Zlib library, which requires data to be in this format.
 * 
 * @return A pointer of type Bytef pointing to the RGBA color array.
 */
operator Bytef*()
		{
			return (Bytef*)RGBAc;
		}

		/**
 * @brief Converts the RGBA color to a uint32_t value.
 *
 * The function shifts and bitwise OR operations are used to convert each of the four bytes (RGBA) into their respective positions in the 32-bit integer.
 *
 * @return A uint32_t representation of the RGBA color.
 */
operator uint32_t()
		{
			return (uint32_t)((RGBAc[0] << 0) | (RGBAc[1] << 8) | (RGBAc[2] << 16) | (RGBAc[3] << 24));
		}
	private:
#pragma warning(push, 0)
		/**
 * Converts an array of floats representing RGBA values into a uint32_t array.
 * The function takes in an array of float values, converts it into the RGBA format and returns a pointer to the converted data.
 * 
 * @param Bytes Pointer to the input float array with size at least 4.
 * 
 * @return A pointer to the uint32_t array containing the converted values.
 */
uint32_t* ConvertFloatToU32(float* Bytes)
		{
			double rgb[4] = { Bytes[0], Bytes[1], Bytes[2], 0};
			__m128 alpha = _mm_set1_ps(Bytes[3]);
			uint32_t out[4];
			
			__m128 tmp1 = _mm256_cvtpd_ps(_mm256_load_pd(&rgb[0]));
			
			__m128 fact = _mm_set1_ps(Bytes[3] > 0 ? 255.f / Bytes[3] : 0);
			
			tmp1 = _mm_mul_ps(fact, tmp1); //rbg0
			alpha = _mm_mul_ps(_mm_set1_ps(255.f), _mm_set1_ps(Bytes[3])); //alpha
			tmp1 = _mm_insert_ps(tmp1, alpha, _MM_MK_INSERTPS_NDX(1,3, 0x00000400));
			
			__m128i tmp1i = _mm_cvtps_epi32(tmp1);
			
			_mm_store_si128((__m128i*)out, tmp1i);
			U32RBGA[0] = out[0];
			U32RBGA[1] = out[1];
			U32RBGA[2] = out[2];
			U32RBGA[3] = out[3];
			return U32RBGA;
		}
#pragma warning(pop)
	};

	typedef struct alignas(16) _constantBufferStruct
	{
		Vector4 Eye;
		Vector4 At;
		Vector4 Up;
		Matrix4D World;
		Matrix4D View;
		Matrix4D Projection;
		Matrix4D ViewProjectionWorldMatrix;
		float AspectRatio;

	}  ConstantBufferStruct;

	typedef struct alignas(16) _constantBufferStruct2D
	{
		Matrix4D ViewMatrixProjection;

	} ConstantBufferStruct2D;

	typedef struct _vertexPositionColor
	{
		Vector3 VertexPosition;
		Vector3 VertexColor;

	}VertexPositionColor;

	typedef struct _vertexPositionColorTangent
	{
		Vector3 VertexPosition;
		Vector3 VertexNormal;
		Vector3 VertexTangent;
	} VertexPositionColorTangent;

	struct Vertex
	{
		Vector3 VertexPosition = { .5f,-.5f,0.f };
		Vector2 VertexTexCoords = { 0.f,0.f };
		Vector4 VertexColor = { 1.f,1.f,1.f,1.f };
		float VertexTexID = 0.f;
		float VertexTilingFactor = 0.f;
		int VertexEntityID = -1;
	};
	
	struct CircleVertex
	{
		Vector3 VertexWorldPosition;
		Vector3 VertexLocalPosition;
		Vector4 VertexColor;
		float VertexThickness;
		float VertexFade;


		int CircleEntityID;
	};

	struct LineVertex
	{
		Vector3 VertexPosition;
		Vector4 VertexColor;
		int LineEntityID;
	};

	struct TextVertex
	{
		Vector3 VertexPosition;
		Vector4 VertexColor;
		Vector2 VertexTexCoords;
		float TexID;

		//Vector4 OutlineColor;

		int EntityID;
	};

	struct TileVertex
	{
		Vector3 VertexPosition;
		Vector2 VertexTexCoords;
		Vector4 VertexColor;
		float VertexTexID ;
		float VertexTilingFactor;
		int VertexEntityID = -1;

	};

	struct QuadProperties
	{
		float Alpha = 1.f;
		Vector2 Size = { 1.f, 1.f };
		Vector4 Color = { 1.f, 1.f, 1.f, Alpha };
		float TilingFactor = 1.f;
		Vector4 TintColor = { 1.f,1.f,1.f,1.f };
		Vector2 TextureCoords[4] = { { 1.f, 1.f }, { 1.f, 0.f },{ 0.f, 0.f }, { 0.f, 1.f } };
		Matrix4D Transform{ 1.f };

		//Editor-Only
		int EntityID = -1;
		/**
 * @brief Resets all properties of the object to default values.
 * 
 * This function resets all properties of an object to their initial state. The properties include Alpha, Size, Color, TilingFactor, TintColor, TextureCoords, Transform and EntityID. All are set to their respective defaults: Alpha is set to 1.0f, Size is set to {1.0f, 1.0f}, Color is set to {1.0f, 1.0f, 1.0f, 1.0f}, TilingFactor is set to 1.0f, TintColor is set to {1.0f, 1.0f, 1.0f, 1.0f}, TextureCoords are set to {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}}, Transform is set to {1.0f} and EntityID is set to -1.
 * 
 * @return void
 */
void ResetProperties()
		{
			Alpha = 1.f;
			Size = { 1.f, 1.f };
			Color = { 1.f, 1.f, 1.f, 1.f };
			TilingFactor = 1.f;
			TintColor = { 1.f,1.f,1.f,1.f };
			TextureCoords[0] = { 1.f, 1.f };
			TextureCoords[1] = { 1.f, 0.f };
			TextureCoords[2] = { 0.f, 0.f };
			TextureCoords[3] = { 0.f, 1.f };
			Transform = { 1.f };
			EntityID = -1;
		}
	};

	struct CircleProperties
	{

	};
	
	struct LineProperties
	{

	};

	class AGEFont; // Font Forward Declaration
	struct StringProperties
	{
		Ref<AGEFont> TextFont;
		std::string Text;
		std::string FontName;
		Vector4 Color = {0.f,0.f,0.f,1.f};
		double FontSize =1.0;
		Vector3 Position = {0.f};
		Vector3 Rotation = {0.f};
	};

	struct UniformBufferObj
	{
		Matrix4D World;
		Matrix4D View;
		Matrix4D Projection;
	};

	struct Box2DQueryContext
	{
		Vector2 Point;
		b2BodyId BodyID = b2_nullBodyId;
	};

	struct ScreenResolution
	{
		uint32_t x = 1280;
		uint32_t y = 720;

		/**
 * @brief This function returns a pair of unsigned 32-bit integers representing the resolution of the system.
 * @return A pair containing two uint32_t values - x and y.
 */
std::pair<uint32_t,uint32_t> GetResolution() {return std::make_pair(x,y);}
		/**
 * @brief Sets the resolution of the display to a specified width and height.
 *
 * This function sets the resolution of the display by setting the private variables x and y to the input parameters X and Y respectively. 
 * The values are then used in other functions to determine the size of the display.
 *
 * @param X The new width for the display.
 * @param Y The new height for the display.
 *
 * @return void
 */
void SetResolution(uint32_t X, uint32_t Y) {x = X; y= Y;}

		/**
 * @brief This function returns the width of an object.
 * @return uint32_t The width of the object in pixels.
 */
uint32_t GetWidth() {return x;}
		/**
 * @brief This function returns the height of an object.
 * @return The height as a uint32_t value. If there is no specific height set, it will return 0.
 */
uint32_t GetHeight() {return y;}


	};

	/**
* We're storing and organizing this data for readabilities sake, the ultimate reality is that I don't foresee writing code to be able to fiddle with Aseprite files in the engine
* however, if the need arises the foundation is already set up and I just have to build a UI to do that.
*/

	struct AsepriteVariant;
	struct AGEPoint
	{
		/**
 * @brief Default constructor for the AGEPoint class.
 *
 * Initializes an instance of the AGEPoint class with default values.
 */
AGEPoint() = default;
		/**
 * @brief Constructs an AGEPoint with the given coordinates (x, y).
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 */
AGEPoint(int32_t x, int32_t y)
			:X(x), Y(y) {}
		/**
 * @brief Default destructor for the AGEPoint class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not perform any operations on the state of the object itself. 
 *
 * @return void
 */
~AGEPoint() = default;
		int32_t X;
		int32_t Y;

		/**
 * @brief Compares two AGEPoint objects for equality based on their X and Y coordinates.
 * 
 * This function compares the X and Y coordinates of two AGEPoint objects for exact match. It returns true if both X and Y coordinates are equal, false otherwise.
 * 
 * @param Other The AGEPoint object to compare with this one.
 * @return True if the X and Y coordinates of both objects are identical, False otherwise.
 */
bool operator==(const AGEPoint& Other)
		{
			bool x = X == Other.X;
			bool y = Y == Other.Y;

			return x && y;
		}

		/**
 * @brief Compares two AGEPoint objects for inequality.
 *
 * This function compares the X and Y coordinates of two AGEPoint objects for inequality. It returns true if either the X or Y coordinate is not equal to the corresponding coordinate in the other object, and false otherwise.
 *
 * @param Other The AGEPoint object to compare with this one.
 * @return True if the X or Y coordinates are not equal, False otherwise.
 */
bool operator!=(const AGEPoint& Other)
		{
			bool x = X == Other.X;
			bool y = Y == Other.Y;

			return !x || !y;
		}

	};
	struct AGESize
	{
		/**
 * @brief Default constructor for the AGESize class.
 *
 * This function initializes an instance of the AGESize class with default values. It does not take any parameters and returns nothing.
 */
AGESize() = default;
		/**
 * @brief Constructs an instance of AGESize with the specified width and height.
 * @param width The width to be set for this AGESize object.
 * @param height The height to be set for this AGESize object.
 */
AGESize(int32_t width, int32_t height)
			:Width(width), Height(height) {}
		/**
 * @brief Default destructor for the AGESize class.
 *
 * This function is used to clean up any resources that are being used by an instance of the AGESize class. It's a good practice to provide a default destructor in C++, as it helps ensure proper memory management and resource deallocation when objects go out of scope or are explicitly destroyed. 
 *
 * @return void
 */
~AGESize() = default;

		int32_t Width;
		int32_t Height;
	};
	struct AGERect
	{
	public:
		/**
 * @brief Default constructor for AGERect class.
 *
 * Initializes an instance of the AGERect class with default values.
 */
AGERect() = default;
		/**
 * @brief Constructs an AGERect object with a specified point, width and height.
 * 
 * @param Point The top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
AGERect(AGEPoint Point, int32_t width, int32_t height)
			: XY(Point), Width(width), Height(height) {}

		/**
 * @brief Constructs an instance of AGERect with the specified x and y coordinates, width, and height.
 * 
 * @param x The x-coordinate of the top left corner of the rectangle.
 * @param y The y-coordinate of the top left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
AGERect(int32_t x, int32_t y, int32_t width, int32_t height)
			:XY({x,y}), Width(width), Height(height) {}
		/**
 * @brief Default destructor for AGERect class.
 *
 * This function is used to clean up any resources that the object may be using, such as memory or file handles. It's a good practice to provide a default destructor in C++ classes, even if it does nothing. This helps ensure that objects of the class can always be safely destroyed without causing problems.
 * 
 * @return void
 */
~AGERect() = default;

		AGEPoint XY;
		int32_t Width;
		int32_t Height;

		/**
 * @brief Checks whether the current point is equal to another point.
 *
 * This function compares the x and y coordinates of the current point with those of a given point. If both are identical, it returns true. Otherwise, it returns false.
 *
 * @param Point The AGEPoint object to compare with the current point.
 * 
 * @return True if the points have the same x and y coordinates; otherwise, false.
 */
bool Contains(AGEPoint Point)
		{
			return XY == Point;
		}
	};

	using AseVector = std::vector<AsepriteVariant>;

	using VariantBase = std::variant < std::nullptr_t,
		bool,
		int8_t, uint8_t,
		int16_t, uint16_t,
		int32_t, uint32_t,
		int64_t, uint64_t,
		float, double,
		std::string,
		AGEPoint, AGESize, AGERect,
		AseVector, std::map<std::string, AsepriteVariant>,
		uint8_t*>;

	enum class AsepriteChunkType : uint16_t
	{
		OldPaletteChunk1 = 0x0004,
		OldPaletteChunk2 = 0x0011,
		LayerChunk = 0x2004,
		CelChunk = 0x2005,
		CelExtraChunk = 0x2006,
		ColorProfileChunk = 0x2007,
		ExternalFilesChunk = 0x2008,
		MaskChunk = 0x2016,
		TagsChunk = 0x2018,
		NewPaletteChunk = 0x2019,
		UserDataChunk = 0x2020,
		SliceChunk = 0x2022,
		TilesetChunk = 0x2023
	};

	enum class AsepritePropertyTypes : uint16_t
	{
		Boolean = 0x0001,
		Int8 = 0x0002,
		Int16 = 0x0004,
		Uint16 = 0x0005,
		Int32 = 0x0006,
		Uint32 = 0x0007,
		Int64 = 0x0008,
		Uint64 = 0x0009,
		Fixed = 0x000A,
		Float = 0x000B,
		Double = 0x000C,
		String = 0x000D,
		Point = 0x000E,
		Size = 0x000F,
		Rect = 0x0010,
		Vector = 0x0011,
		NestedMapProps = 0x0012,
		UUID = 0x0013

	};

	enum class CharMovementStatus
	{
		Idle = 0,
		Walking = 1,
		Running = 2,
		BattleIdle = 3,
		BattleAttack = 4,
		BattleCast = 5,
		UNDEFINED = 6
	};

	struct AsepritePropertyData
	{
		uint16_t Type;
		bool Boolean;
		int8_t Int8;
		uint8_t Byte;
		int16_t Int16;
		uint16_t Uint16;
		int32_t Int32;
		uint32_t Uint32;
		int64_t Int64;
		uint64_t Uint64;
		double  Fixed;
		float Float;
		double Double;
		std::string String;
		AGEPoint Point;
		AGESize Size;
		AGERect Rect;
		AseVector Vec;
	};

	struct AsepriteVariant : public VariantBase
	{
		//Copied this implementation right out of the Aseprite user_data.h

		/**
 * @brief Default constructor for AsepriteVariant class.
 *
 * This function initializes an instance of the AsepriteVariant class with its default values.
 */
AsepriteVariant() = default;
		/**
 * @brief Copy constructor for the AsepriteVariant class.
 *
 * This function creates a new instance of AsepriteVariant that is a copy of an existing one. It uses the '= default' syntax to indicate that this function should use the compiler-generated default implementation.
 *
 * @param v The existing AsepriteVariant instance to be copied.
 */
AsepriteVariant(const AsepriteVariant& v) = default;

		template<typename T>
		/**
 * @brief Constructs a variant object with the provided value of type T.
 * @tparam T The type of the value to be stored in the variant.
 * @param v The value to be moved into the variant.
 */
AsepriteVariant(T&& v) : VariantBase(std::forward<T>(v)) { }

		// Avoid using Variant.operator=(const char*) because the "const
		// char*" is converted to a bool implicitly by MSVC.
		/**
 * @brief Overloaded assignment operator that disallows the use of a const char* as an argument.
 *
 * This function is marked as deleted to prevent its usage with a const char*. It will not compile if someone tries to assign a const char* value to this object.
 * 
 * @param[in] rhs The right-hand side of the assignment operation, which should not be a const char*.
 * @return A reference to the modified AsepriteVariant object.
 */
AsepriteVariant& operator=(const char*) = delete;

		template<typename T>
		/**
 * @brief Assignment operator for AsepriteVariant.
 *
 * This function overloads the assignment operator to allow for moving of values into an AsepriteVariant object. It takes a rvalue reference (T&&) as its parameter, which allows it to accept both lvalues and rvalues. The function then uses std::forward to forward the value to VariantBase's assignment operator, effectively transferring ownership or copying the value as appropriate.
 * 
 * @param v The value to be moved into this AsepriteVariant object.
 * @return A reference to the modified AsepriteVariant object.
 */
AsepriteVariant& operator=(T&& v) {
			VariantBase::operator=(std::forward<T>(v));
			return *this;
		}

		/**
 * @brief Returns the value of the 'index' function which is also the type of this object.
 * @return The return value of the 'index' function, indicating the current state or position within a sequence of values.
 */
const size_t type() const {
			return index();
		}
	};

	struct AsepritePixelData
	{
		AsepriteChunkType ChunkType;
		uint16_t Flags;
		std::vector<uint8_t> Pixels;
		std::string Name;
	};

	struct AsepriteSliceKey
	{
		uint32_t FrameNumber;
		int32_t SliceX;
		int32_t SliceY;
		uint32_t SliceWidth;
		uint32_t SliceHeight;

		int32_t CenterX;
		int32_t CenterY;
		uint32_t CenterWidth;
		uint32_t CenterHeight;

		int32_t PivotX;
		int32_t PivotY;
	};

	struct AsepriteExternalFileEntry
	{
		uint32_t ID;
		uint8_t Type;
		std::string Name;
	};

	struct AsepriteTag
	{
		uint16_t FromFrame;
		uint16_t ToFrame;
		uint8_t LoopDirection;
		uint16_t RepeatTimes;

		uint8_t RGB[3]; //Deprecated in newer versions
		std::string Name;
	};

	struct AsepriteUserProps
	{
		std::string Name;
		uint16_t Type;
		uint32_t NumofElementsInVec;
		uint16_t ElementsType;
		//Probably have to do some sort of templated vector thing TODO: Look into that in the future
		AsepritePropertyData PropData;


		std::map<uint32_t, uint8_t*> NestedPropsMap;
		uint8_t UUID[16];


	};

	struct AsepriteUserData
	{
		uint32_t Flags;
		std::string Text;
		uint8_t RGBA[4];
		uint32_t Size;
		uint32_t NumOfPropMaps;
		std::vector<std::pair<uint32_t, uint32_t>> PropMapKeyPairs;
		std::map<uint32_t, std::vector<AsepriteUserProps>> UserProps;

	};

	struct AsepriteCelChunk
	{
	public:
		/**
 * @brief Default constructor for AsepriteCelChunk class.
 */
AsepriteCelChunk() = default;
		/**
 * @brief Default destructor for AsepriteCelChunk class.
 *
 * This function is responsible for releasing any resources that the class may be using, such as memory or file handles. It does not perform any operations on the object itself, but rather cleans up after it when it's no longer needed.
 * 
 * @return void
 */
~AsepriteCelChunk() = default;


		uint16_t LayerIndex;
		int16_t x;
		int16_t y;
		uint8_t Opacity;
		uint16_t CelType;
		int16_t zIndex;
		uint16_t Width;
		uint16_t Height;
		uint16_t FramePosition; // Frame position to link with
		std::vector<AsepritePixelData> PixelDatas;

		/**
 * @brief This function returns the sum of the layer index and z-index.
 * @return The sum of the layer index and z-index as an integer. If either or both indices are not set, the result will be 0.
 */
int order() const
		{
			return LayerIndex + zIndex;
		}

		//bool operator<(const AsepriteCelChunk& B) const
		//{
		//	return (order() < B.order()) || (order() == B.order() && (zIndex < B.zIndex));
		//}
	};

	struct AsepriteLayer
	{
	public:
		/**
 * @brief Default constructor for AsepriteLayer class.
 *
 * This function initializes an instance of the AsepriteLayer class with default values.
 * It is used to create a new layer in Aseprite, which can then be manipulated and edited.
 * 
 * @return An instance of the AsepriteLayer class with all fields initialized to their default values.
 */
AsepriteLayer() = default;
		/**
 * @brief Constructs an AsepriteLayer object with the given layer index and z-index.
 * @param LIndex The index of the layer in the Aseprite document.
 * @param ZIndex The z-index of the layer, determining its stacking order relative to other layers.
 */
AsepriteLayer(int LIndex, int ZIndex)
			:Layerindex(LIndex), zIndex(ZIndex) {}
		/**
 * @brief Default copy constructor for the AsepriteLayer class.
 *
 * This function is used to create a new instance of AsepriteLayer by copying an existing one. It uses the 'default' keyword, which means it does not perform any special operations and simply copies all member variables from the source object to the target object.
 *
 * @param[in] layer The existing AsepriteLayer instance to be copied.
 * 
 * @return A new AsepriteLayer instance with the same properties as the input layer.
 */
AsepriteLayer(const AsepriteLayer&) = default;

		int Layerindex;
		int zIndex;

		uint16_t Flags;
		uint16_t Type;
		uint16_t Child;
		uint16_t BlendMode;
		uint8_t Opacity;
		std::string Name;
		std::vector<AsepriteCelChunk> CelChunks;

	};

	struct AsepriteOldPaletteChunk
	{
		AsepriteChunkType Type;
		uint16_t NumOfPackets;
		uint8_t NumOfPalettesToSkip;
		uint8_t NumOfColors;
		std::vector<uint8_t*> Colors;

	};

	struct AsepriteColorProfileChunk
	{
		uint16_t Type;
		uint16_t Flags;
		double Gamma;
		uint32_t ICCProfileDataLength;
		std::vector<std::byte> ICCProfileData; // More info: http://www.color.org/ICC1V42.pdf

	};

	struct AsepriteExternalFilesChunk
	{
		uint32_t NumOfEntries;
		std::vector<AsepriteExternalFileEntry> Entries;

	};

	struct AsepriteMaskChunk
	{
		int16_t x;
		int16_t y;
		uint16_t Width;
		uint16_t Height;
		std::string Name;
		std::vector<std::byte> Data; //Bit Map Data
	};

	struct AsepriteTagsChunk
	{
		uint16_t NumOfTags;
		std::vector<AsepriteTag> Tags;
	};

	struct AsepritePaletteChunk
	{
		uint32_t Size;
		uint32_t FirstIndexToChange;
		uint32_t LastIndexToChange;
		std::vector<AsepritePixelData> Entries;
	};

	struct AsepriteSliceChunk
	{
		uint32_t NumOfSliceKeys;
		uint32_t Flags;
		std::string Name;
		std::vector<AsepriteSliceKey> Slices;
	};

	struct AsepriteChunk
	{
	public:
		/**
 * @brief Default constructor for AsepriteChunk class.
 *
 * This function initializes an instance of the AsepriteChunk class with its members set to their default values.
 *
 * @return An instance of the AsepriteChunk class with all members initialized to their default values.
 */
AsepriteChunk() = default;
		/**
 * @brief Default copy constructor for the AsepriteChunk class.
 *
 * This function is used to create a new instance of AsepriteChunk by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param other The existing AsepriteChunk instance to copy from.
 *
 * @return A new AsepriteChunk object that is a copy of the input parameter.
 */
AsepriteChunk(const AsepriteChunk&) = default;

		uint32_t Size;
		AsepriteChunkType Type;
		std::vector<std::byte> Data;
	};

	struct AsepriteHeader
	{
	public:
		/**
 * @brief Default constructor for AsepriteHeader class.
 *
 * This function initializes an instance of the AsepriteHeader class with its default values.
 * It does not take any parameters and returns a new instance of the class.
 * 
 * @return Newly created instance of AsepriteHeader class.
 */
AsepriteHeader() = default;
		/**
 * @brief Default copy constructor for the AsepriteHeader class.
 *
 * This function is used to create a new instance of AsepriteHeader by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 * 
 * @param other The existing AsepriteHeader instance to copy from.
 */
AsepriteHeader(const AsepriteHeader&) = default;
		//HeaderData
		uint32_t FileSize;
		uint16_t MagicNumber = 0xA5E0;
		uint16_t Frames;
		uint16_t Width;
		uint16_t Height;
		uint16_t Depth;
		uint32_t Flags;
		uint16_t Speed; // Deprecated, but we're leaving just incase anyone is using older versions where this is still valid or needed
		uint32_t whoknows = 0;
		uint32_t whoknowsagain = 0;
		uint8_t  EntryIndex;
		//skip 3 uint8_t
		uint16_t NumOfColors;
		uint8_t PixelWidth;
		uint8_t PixelHeight;
		int16_t x;
		int16_t y;
		uint16_t GridWidth;
		uint16_t GridHeight;
	};

	struct AsepriteFrameData
	{
	public:
		/**
 * @brief Default constructor for AsepriteFrameData class.
 *
 * This function initializes an instance of the AsepriteFrameData class with default values.
 * It is used to create a new instance of this class without any specific initialization.
 * 
 * @return An instance of AsepriteFrameData with all fields initialized to their default values.
 */
AsepriteFrameData() = default;
		/**
 * @brief Default copy constructor for the AsepriteFrameData class.
 *
 * This function is used to create a new instance of AsepriteFrameData by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param other The existing AsepriteFrameData instance to copy from.
 */
AsepriteFrameData(const AsepriteFrameData&) = default;
		//FrameData
		uint32_t BytesInFrame;
		uint16_t MagicNumber = 0xF1FA;
		uint16_t NumOfChunks;
		uint16_t FrameDuration;
		//two uint8_t which will be 0
		uint32_t NewNumOfChunks; // If 0 use NumOfChunks

		std::vector<AsepriteChunk> ChunkData;	
		std::vector<AsepriteLayer> Layers;
		std::vector<AsepriteOldPaletteChunk> OldPaletteChunks;
		std::vector<AsepritePaletteChunk> NewPaletteChunks;
	};

	struct AsepriteFileData
	{
	public:
		/**
 * @brief Default constructor for AsepriteFileData class.
 *
 * This function initializes an instance of the AsepriteFileData class with default values. It is used to create a new object without any specific data.
 * 
 * @return An instance of AsepriteFileData with all fields initialized to their default values.
 */
AsepriteFileData() = default;
		/**
 * @brief Constructs an instance of the AsepriteFileData class using a const reference to an AsepriteHeader object.
 * @param HeaderData A const reference to an AsepriteHeader object containing header data for the Aseprite file.
 */
AsepriteFileData(const AsepriteHeader& HeaderData)
			:Header(HeaderData) {}
		/**
 * @brief Default copy constructor for the AsepriteFileData class.
 *
 * This function is used to create a new instance of AsepriteFileData by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 * 
 * @param other The existing AsepriteFileData instance to copy from.
 */
AsepriteFileData(const AsepriteFileData&) = default;

		AsepriteHeader Header;
		std::vector<AsepriteFrameData> Frames;

	};


	struct QueryParams
	{
		Vector2 Point2D;
		Vector3 Point3D;
		b2ShapeId ShapeID2D;
		b2Polygon Box2D;
		b2Capsule Capsule2D;
		b2Segment Segment2D;
		b2BodyId InstigatorID;
		Vector3 Location;
		Vector3 Rotation;
		//b2OverlapResultFcn* Func;
		//typedef bool b2OverlapResultFcn(b2ShapeId shapeId, void* context);
		b2OverlapResultFcn* OverlapFunc2D;
		b2CastResultFcn* CastFunc2D;
		bool Result;
		void* Context;
	};
	
}


