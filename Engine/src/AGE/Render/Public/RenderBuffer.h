#pragma once
#include "Structs/Public/DataStructures.h"
#include "Math/Public/UtilityFunctions.h"
#include "Core/Public/Log.h"


struct Matrix3D;

namespace AGE
{
	enum class ShaderDataType
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
 * This function takes a `ShaderDataType` enum value as input and returns its corresponding size in bytes. The return values are calculated based on the enum values, which represent different types of data that can be used in shaders. 
 *
 * @param Type The `ShaderDataType` to get the size for.
 * @return uint32_t The size of the given ShaderDataType in bytes.
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
		ShaderDataType DataType;
		uint32_t Size = 0;
		uint32_t Offset = 0;
		uint32_t DataStepRate = 0;
		bool Normalized = false;

		/**
 * @brief Default constructor for BufferElement class.
 */
BufferElement() {};

		/**
 * @brief BufferElement is a class representing an element in a buffer. 
 * It holds information about the name, type of data, size and offset of the data, as well as whether it's normalized or not.
 * 
 * @param Type The type of shader data (e.g., float, int).
 * @param Name The name of the buffer element.
 * @param normalized A boolean indicating if the data is normalized. Default value is false.
 */
BufferElement(ShaderDataType Type, const std::string& Name, bool normalized = false)
			: Name(Name), DataType(Type), Size(ShaderDataTypeSize(Type)), Offset(0), Normalized(normalized)
		{

		}

		/**
 * @brief GetComponentCount returns the number of components in a shader data type.
 * 
 * This function takes into account the current value of DataType and returns the appropriate number of components.
 * The return values are as follows:
 * - For DataType = 0, it returns 1 (Unknown ShaderDataType).
 * - For DataType = 1 to 4 inclusive, it returns 1.
 * - For DataType = 5 to 6 inclusive, it returns 9.
 * - For DataType = 7 to 8 inclusive, it returns 2.
 * - For DataType = 9 to 10 inclusive, it returns 3.
 * - For DataType = 11, it returns 4 (Unknown ShaderDataType).
 * 
 * @return uint32_t The number of components in the shader data type.
 */
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
 * @brief Constructor for the BufferLayout class. Initializes the buffer layout with a list of elements.
 * 
 * @param Elements A std::initializer_list<BufferElement> containing the elements to be added to the layout.
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

		COMMENT:
/**
 * @brief Returns an iterator pointing to the beginning of the buffer elements vector.
 * @return An iterator to the start of the buffer elements vector.
 */
CONFIDENCE: 1.0;

[[nodiscard]] std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

		/**
 * @brief Returns an iterator pointing to the theoretical element past the last element of the vector.
 * @return An iterator to the theoretical element past the end of the vector.
 */
[[nodiscard]] std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		COMMENT:
/**
 * @brief Returns a constant iterator pointing to the beginning of the buffer elements.
 * @return A constant iterator to the first element in the container.
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
 * @brief Calculates the offsets and stride for each element in a container.
 * The function iterates over all elements, setting their offset to the current total offset (which starts at 0),
 * then incrementing the total offset by the size of the current element. It also updates the overall stride which is the sum of sizes of all elements.
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
 * This function is responsible for releasing any resources that were acquired by the VertexBuffer object, such as memory or GPU resources. It does not return anything and thus has an empty return type (void).
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
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not return anything and has no parameters.
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
 * This function is responsible for releasing any resources that were acquired by the UniformBuffer object, such as memory or GPU resources. It does not return anything and thus has an empty return type (void).
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