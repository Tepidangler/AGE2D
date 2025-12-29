#pragma once
#include "Structs/Public/DataStructures.h"
#include "Math/Public/UtilityFunctions.h"

struct Matrix3D;

namespace AGE
{
	enum class ShaderDataType
	{
		None = 0,
		Float = 1,
		Float2 = 2,
		Float3 = 3,
		Float4 = 4,
		Mat3 = 5,
		Mat4 = 6,
		Int = 7,
		Int2 = 8,
		Int3 = 9,
		Int4 = 10,
		Bool = 11

	};

	static uint32_t ShaderDataTypeSize(ShaderDataType Type)
	{
		switch ((int)Type)
		{
		case 0:
			break;
		case 1:
			return sizeof(float);
			break;
		case 2:
			return 2 * sizeof(float);
			break;
		case 3:
			return 3 * sizeof(float);
			break;
		case 4:
			return 4 * sizeof(float);
			break;
		case 5:
			return 3 * 3 * sizeof(float);
			break;
		case 6:
			return 4 * 4 * sizeof(float);
			break;
		case 7:
			return sizeof(int);
			break;
		case 8:
			return 2 * sizeof(int);
			break;
		case 9:
			return 3 * sizeof(int);
			break;
		case 10:
			return 4 * sizeof(int);
			break;
		case 11:
			return sizeof(bool);
			break;
		}

		AGE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name = "";
		uint32_t Index = 0;
		DXGI_FORMAT Format;
		uint32_t Slot = 0;
		uint32_t Offset = 0;
		D3D11_INPUT_CLASSIFICATION SlotClass;
		uint32_t DataStepRate = 0;
		uint32_t Size = 0;
		ShaderDataType DataType;
		bool Normalized = false;

		uint32_t ElementBinding = 0;
		uint32_t ElementLocation = 0;

		BufferElement() {};

		BufferElement(ShaderDataType Type, const std::string& Name, bool normalized = false)
			: Name(Name), DataType(Type), Size(ShaderDataTypeSize(Type)), Offset(0), Normalized(false)
		{

		}

		uint32_t GetComponentCount()  const
		{
			switch ((int)DataType)
			{
			case 0:
				break;
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			case 3:
				return 3;
				break;
			case 4:
				return 4;
				break;
			case 5:
				return 9;
				break;
			case 6:
				return 16;
				break;
			case 7:
				return 1;
				break;
			case 8:
				return 2;
				break;
			case 9:
				return 3;
				break;
			case 10:
				return 4;
				break;
			case 11:
				return 1;
				break;
			
			}
			AGE_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}


	};

	class BufferLayout
	{
	public:

		BufferLayout();

		BufferLayout(const std::initializer_list<BufferElement>& Elements)
			: m_Elements(Elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& E : m_Elements)
			{
				E.Offset = offset;
				offset += E.Size;
				m_Stride += E.Size;
			}
		}



	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

		virtual void InvalidateBuffer() const = 0;

		virtual void SetLayout(const BufferLayout& Layout) = 0;

		virtual void AddDataToBuffer(float* Verticies, uint32_t Size) = 0;
		virtual void AddDataToBuffer(const void* Verticies, uint32_t Size) = 0;
		
		virtual const BufferLayout& GetLayout() const = 0;

		virtual Vertex* CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) = 0;
		virtual CircleVertex* CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID) = 0;
		virtual LineVertex* CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID = -1) = 0;
		virtual TextVertex* CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID, int EntID) = 0;
		virtual TileVertex* CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) = 0;


		static Ref<VertexBuffer> Create(Matrix3D* Vertices, uint32_t Size);
		static Ref<VertexBuffer> Create(uint32_t Size);


		static Ref<VertexBuffer> Create(float* Vertices = nullptr, uint32_t Size = 0);

		template<typename T>
		T* As();
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

		virtual void InvalidateBuffer() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* Indices, uint32_t Count);

		virtual uint32_t GetCount() = 0;

		template<typename T>
		T* As();
	};

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(const void* Data, uint32_t Size, uint32_t Offset = 0) = 0;

		static Ref<UniformBuffer> Create(uint32_t Size, uint32_t Binding);
		template<typename T>
		T* As();
	};
}