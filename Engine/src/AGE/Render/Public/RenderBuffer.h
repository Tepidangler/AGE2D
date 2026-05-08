#pragma once
#include "Structs/Public/DataStructures.h"
#include "Math/Public/UtilityFunctions.h"
#include "Core/Public/Log.h"


struct Matrix3D;

namespace AGE
{
	enum class ShaderDataType : uint16_t
	{
		INVALIDSHADERDATATYPE = 0,
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
		Boolean = 11

	};

	/**
 * @brief Returns the size of a shader data type in bytes.
 * 
 * @param Type ShaderDataType enumeration value representing different types of shader data.
 * @return uint32_t Size of the shader data type in bytes.
 */
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

		CoreLogger::Assert(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name = "";
		uint32_t Index = 0;
		uint32_t Slot = 0;
		uint32_t Offset = 0;
		uint32_t DataStepRate = 0;
		uint32_t Size = 0;
		ShaderDataType DataType;
		bool Normalized = false;

		uint32_t ElementBinding = 0;
		uint32_t ElementLocation = 0;

		/**
 * @brief Default constructor for BufferElement class.
 * Initializes an empty buffer element.
 */
BufferElement() {};

		/**
 * @brief Constructs a BufferElement object with the given parameters.
 * 
 * This constructor initializes a new BufferElement object with the provided ShaderDataType, Name, and normalized flag. The Size is set based on the ShaderDataTypeSize function, Offset is initialized to 0, and Normalized is also initialized to false.
 * @param Type The type of data contained in this element (e.g., float, int).
 * @param Name A string representing the name or identifier for this buffer element.
 * @param normalized If true, indicates that the data should be normalized before use. Defaults to false.
 */
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
			CoreLogger::Assert(false, "Unknown ShaderDataType!");
			return 0;
		}


	};

	class BufferLayout
	{
	public:

		BufferLayout();

		/**
 * @brief Construct a new Buffer Layout object.
 * 
 * This constructor initializes the buffer layout with a list of elements. The elements are used to calculate the offsets and strides for each attribute in the vertex data.
 * 
 * @param Elements A std::initializer_list<BufferElement> containing the elements to be added to the layout. Each element represents an attribute in the vertex data, including its type (e.g., float, int), whether it's normalized, and its size.
 */
BufferLayout(const std::initializer_list<BufferElement>& Elements)
			: m_Elements(Elements)
		{
			CalculateOffsetsAndStride();
		}

		/**
 * @brief Returns a constant reference to the vector of BufferElements stored in this object.
 * @return A constant reference to the vector of BufferElements (m_Elements).
 */
inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		/**
 * @brief Returns the stride value of the object.
 * @return The stride value as a uint32_t.
 */
inline uint32_t GetStride() const { return m_Stride; }

		/**
 * @brief Returns an iterator pointing to the beginning of the buffer elements vector.
 * @return An iterator to the start of the buffer elements vector.
 */
[[nodiscard]] std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

		COMMENT:
/**
 * @brief Returns an iterator pointing to the theoretical element past the last element of the vector.
 * @return An iterator to the theoretical element past the end of the vector.
 */
CONFIDENCE: 1.0;

[[nodiscard]] std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		COMMENT:
/**
 * @brief Returns a constant iterator pointing to the beginning of the buffer elements.
 * @return A constant iterator to the first element in the buffer.
 */
CONFIDENCE: 1.0;

[[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

		/**
 * @brief Returns a constant iterator pointing to the past-the-end element in the buffer elements vector.
 * @return A constant iterator pointing to the past-the-end element.
 */
[[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:

		/**
 * @brief Calculates the offsets and stride for each element in a container of elements.
 * The function iterates over all elements, setting their offset to the current total offset (which is incremented by the size of the element), 
 * and updating the total stride (incremented by the size of the element). This allows for efficient memory access when rendering data in a shader.
 * @return void
 */
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
		
		/**
 * @brief Virtual destructor for the VertexBuffer class.
 *
 * This function is responsible for releasing any resources that were acquired by the VertexBuffer object during its lifetime. It does not return anything and has no parameters.
 */
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
		/**
 * @brief Virtual destructor for the IndexBuffer class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not perform any operations on the actual data stored in the buffer.
 * 
 * @return void
 */
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
		/**
 * @brief Virtual destructor for the UniformBuffer class.
 *
 * This function is responsible for freeing any resources that were allocated during the lifetime of an object of this class. It does not take any parameters and returns nothing.
 */
virtual ~UniformBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(const void* Data, uint32_t Size, uint32_t Offset = 0) = 0;

		static Ref<UniformBuffer> Create(uint32_t Size, uint32_t Binding);
		template<typename T>
		T* As();
	};
}