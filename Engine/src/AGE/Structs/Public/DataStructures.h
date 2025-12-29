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
#include "DirectXMath.h"
#include "d3d11_4.h"



namespace AGE
{

	struct XInputControllerSettings
	{
	public:

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
		XInputControllerInfo() = default;

		ulong_t PacketNumber = 0;

		ulong_t UserIndex = 0;

		bool bShouldVibrate = true;

		bool bConnected = false;

		uint8_t BatteryType = 0;

		uint8_t BatteryLevel = 0;

		XInputControllerSettings Settings;

		std::function<void(Event&)> CallbackFn;

		operator bool()
		{
			return bConnected;
		}

		uint16_t ButtonState = 0;
	};

	class VertexBuffer;
	class ConstantBuffer;

	struct AGEPixel
	{
	public:
		float RGBAf[4];
		uint8_t RGBAc[4];
		uint32_t U32RBGA[4];

		AGEPixel() = default;

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

		operator Bytef*()
		{
			return (Bytef*)RGBAc[0];
		}

		operator uint32_t()
		{
			return ((RGBAc[0] << 0) | (RGBAc[1] << 8) | (RGBAc[2] << 16) | (RGBAc[3] << 24));
		}
	private:
#pragma warning(push, 0)
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

			return out;
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

	class Font; // Font Forward Declaration
	struct StringProperties
	{
		Ref<Font> TextFont;
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

		std::pair<uint32_t,uint32_t> GetResolution() {return std::make_pair(x,y);}
		void SetResolution(uint32_t X, uint32_t Y) {x = X; y= Y;}

		uint32_t GetWidth() {return x;}
		uint32_t GetHeight() {return y;}


	};

	/**
* We're storing and organizing this data for readabilities sake, the ultimate reality is that I don't foresee writing code to be able to fiddle with Aseprite files in the engine
* however, if the need arises the foundation is already set up and I just have to build a UI to do that.
*/

	struct AsepriteVariant;
	struct AGEPoint
	{
		AGEPoint() = default;
		AGEPoint(int32_t x, int32_t y)
			:X(x), Y(y) {}
		~AGEPoint() = default;
		int32_t X;
		int32_t Y;

		bool operator==(const AGEPoint& Other)
		{
			bool x = X == Other.X;
			bool y = Y == Other.Y;

			return x && y;
		}

		bool operator!=(const AGEPoint& Other)
		{
			bool x = X == Other.X;
			bool y = Y == Other.Y;

			return !x || !y;
		}

	};
	struct AGESize
	{
		AGESize() = default;
		AGESize(int32_t width, int32_t height)
			:Width(width), Height(height) {}
		~AGESize() = default;

		int32_t Width;
		int32_t Height;
	};
	struct AGERect
	{
	public:
		AGERect() = default;
		AGERect(AGEPoint Point, int32_t width, int32_t height)
			: XY(Point), Width(width), Height(height) {}

		AGERect(int32_t x, int32_t y, int32_t width, int32_t height)
			:XY({x,y}), Width(width), Height(height) {}
		~AGERect() = default;

		AGEPoint XY;
		int32_t Width;
		int32_t Height;

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

		AsepriteVariant() = default;
		AsepriteVariant(const AsepriteVariant& v) = default;

		template<typename T>
		AsepriteVariant(T&& v) : VariantBase(std::forward<T>(v)) { }

		// Avoid using Variant.operator=(const char*) because the "const
		// char*" is converted to a bool implicitly by MSVC.
		AsepriteVariant& operator=(const char*) = delete;

		template<typename T>
		AsepriteVariant& operator=(T&& v) {
			VariantBase::operator=(std::forward<T>(v));
			return *this;
		}

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


		std::map<uint32_t, uint8_t[]> NestedPropsMap;
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
		AsepriteCelChunk() = default;
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
		AsepriteLayer() = default;
		AsepriteLayer(int LIndex, int ZIndex)
			:Layerindex(LIndex), zIndex(ZIndex) {}
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
		AsepriteChunk() = default;
		AsepriteChunk(const AsepriteChunk&) = default;

		uint32_t Size;
		AsepriteChunkType Type;
		std::vector<std::byte> Data;
	};

	struct AsepriteHeader
	{
	public:
		AsepriteHeader() = default;
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
		AsepriteFrameData() = default;
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
		AsepriteFileData() = default;
		AsepriteFileData(const AsepriteHeader& HeaderData)
			:Header(HeaderData) {}
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


