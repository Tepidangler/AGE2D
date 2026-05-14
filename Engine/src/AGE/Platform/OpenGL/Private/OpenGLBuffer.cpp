#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLBuffer.h"
#include "Render/Public/Renderer2D.h"

#include <glad/glad.h>

namespace AGE
{

	uint32_t OpenGLVertexBuffer::s_RendererID = 0;
			////////////////////////////////////////////////////////////////////
			//																  //
			//																  //
			//						VERTEX BUFFER							  //
			//																  //
			//																  //
			////////////////////////////////////////////////////////////////////

	/**
 * @brief Constructs an OpenGLVertexBuffer with a given size.
 * 
 * This function creates an OpenGL buffer and initializes it with the specified size, data type (`GL_ARRAY_BUFFER`), and usage pattern (`GL_DYNAMIC_DRAW`). The created buffer is bound to the target `GL_ARRAY_BUFFER`.
 * 
 * @param Size The size of the buffer in bytes.
 */
/**
 * @brief Constructs an OpenGLVertexBuffer with a specified size.
 * 
 * This function creates an OpenGL buffer and initializes it with the given size. The buffer is created as dynamic, meaning its content can be changed frequently without needing to reallocate memory.
 * 
 * @param Size The size of the buffer in bytes.
 */
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		Bind();
		glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
		
	}

	/**
 * @brief Constructs an OpenGLVertexBuffer object.
 * 
 * This function creates a buffer and binds it to the target GL_ARRAY_BUFFER, then initializes its data with the provided vertices.
 * The size of the data is specified by the Size parameter.
 * 
 * @param Vertices Pointer to an array of Matrix3D objects representing the vertices for initialization.
 * @param Size Number of bytes in the Vertices array.
 * 
 * @return None
 */
/**
 * @brief Constructor for OpenGLVertexBuffer. 
 * Initializes a vertex buffer object with the given vertices and size.
 * The buffer is created as dynamic, meaning its content can be changed frequently.
 * 
 * @param Vertices Pointer to an array of Matrix3D objects representing the vertices.
 * @param Size Number of elements in the Vertices array.
 */
OpenGLVertexBuffer::OpenGLVertexBuffer(Matrix3D* Vertices, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_DYNAMIC_DRAW);
		
	}
	
	/**
 * @brief Constructs an OpenGLVertexBuffer with given vertices and size.
 * 
 * This function creates a new OpenGL vertex buffer object (VBO) using the `glCreateBuffers` function, assigns it a unique ID, binds it for use, and fills it with data using `glBufferData`. The data is specified as an array of floats and its size in bytes.
 * 
 * @param Vertices Pointer to the first element of the vertices array.
 * @param Size Number of bytes to allocate memory for the buffer object's data store.
 */
/**
 * @brief Constructs an OpenGLVertexBuffer with given vertices and size.
 * 
 * This function creates a new OpenGL vertex buffer object (VBO) using the `glCreateBuffers` function, assigns it a unique ID, binds it to the GL_ARRAY_BUFFER target, and fills it with data of specified size and content.
 * @param Vertices Pointer to an array of float values representing vertices.
 * @param Size The size in bytes of the buffer object's new data store.
 */
OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		Bind();
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
		

	}

	/**
 * @brief Destructor for OpenGLVertexBuffer. Deletes the vertex buffer object from GPU memory.
 * 
 * This function is responsible for deleting a Vertex Buffer Object (VBO) from the GPU's memory. It does this by calling glDeleteBuffers with the ID of the VBO to be deleted.
 * The VBO ID is stored in m_RendererID member variable.
 * 
 * @return void
 */
/**
 * @brief Destructor for OpenGLVertexBuffer. Deletes the vertex buffer object from GPU memory.
 * 
 * This function is responsible for deleting a Vertex Buffer Object (VBO) from the GPU's memory. The VBO was previously created and initialized by some other part of the program.
 * 
 * @return void
 */
OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
		
	}
	/**
 * @brief This function binds the OpenGL Vertex Buffer to the GL_ARRAY_BUFFER target.
 * 
 * The function uses glBindBuffer() from the OpenGL library to bind the buffer with ID m_RendererID to the GL_ARRAY_BUFFER target.
 * It is used when rendering vertex data in an OpenGL context.
 * 
 * @return void No return value. This function only modifies the state of the OpenGL context, not returning any information.
 */
/** 
 * @brief This function binds the OpenGL Vertex Buffer to the GL_ARRAY_BUFFER target.
 * 
 * The function uses glBindBuffer with arguments (GL_ARRAY_BUFFER, m_RendererID) to bind the buffer.
 * It is used when rendering vertex arrays and it sets the current vertex array buffer to be the one we want to use.
 * 
 * @return void No return value.
 */
void OpenGLVertexBuffer::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
	}
	/**
 * @brief Unbinds the OpenGL Vertex Buffer.
 *
 * This function binds an OpenGL buffer to a target with zero as its argument. In this case, it's binding GL_ARRAY_BUFFER to 0, effectively unbinding it.
 *
 * @return void
 */
/**
 * @brief This function unbinds the OpenGL Vertex Buffer.
 *
 * It binds the buffer target to GL_ARRAY_BUFFER and sets the buffer id to 0, effectively unbinding it from the current context.
 *
 * @return void
 */
void OpenGLVertexBuffer::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	/**
 * @brief Invalidates and deletes the OpenGL vertex buffer.
 *
 * This function first invalidates any existing data in the buffer using glInvalidateBufferData(). Then it deletes the 
 * buffer itself with glDeleteBuffers(). The buffer's ID is passed to these functions as a constant reference, ensuring that 
 * no changes are made to the buffer after its destruction.
 *
 * @return void
 */
/**
 * @brief Invalidates and deletes the OpenGL vertex buffer.
 *
 * This function first invalidates any existing data in the buffer using glInvalidateBufferData(). It then deletes the 
 * buffer itself with glDeleteBuffers() using the renderer ID of this object as argument. The buffer is marked for 
 * deletion and its memory becomes available for reuse by other objects, effectively invalidating it.
 *
 * @return void
 */
void OpenGLVertexBuffer::InvalidateBuffer() const
	{
		AGE_PROFILE_FUNCTION();
		glInvalidateBufferData(m_RendererID);
		
		glDeleteBuffers(1, &m_RendererID);
		
	}

	/**
 * @brief Adds data to the OpenGL Vertex Buffer.
 *
 * This function binds the buffer and adds new data to it using glBufferSubData. The data is added at the beginning of the buffer, replacing any existing data. 
 *
 * @param Verticies Pointer to an array of floats containing the data to be added.
 * @param Size The size in bytes of the data to be added.
 *
 * @return void
 */
/**
 * @brief Adds data to the OpenGL Vertex Buffer.
 *
 * This function binds the buffer and then uses glBufferSubData to add new data at the beginning of the buffer. 
 * The size of the data is specified by the Size parameter, which should be the number of floats in the Verticies array.
 *
 * @param[in] Verticies Pointer to an array of float values representing the vertices to add to the buffer.
 * @param[in] Size The size of the Verticies array, expressed as a uint32_t. This should be equal to the number of floats in the Verticies array.
 * 
 * @return void
 */
void OpenGLVertexBuffer::AddDataToBuffer(float* Verticies, uint32_t Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Verticies);
		
	}

	/**
 * @brief Adds data to the OpenGL Vertex Buffer.
 *
 * This function binds the buffer and updates its contents with new vertex data. The size of the data is specified by the 'Size' parameter, 
 * which should match the actual size of the data being added. The data itself is passed as a pointer to the 'Verticies' parameter.
 *
 * @param Verticies A pointer to the data that will be copied into the buffer.
 * @param Size The size in bytes of the data pointed to by 'Verticies'.
 * 
 * @return void
 */
/**
 * @brief Adds data to the OpenGL Vertex Buffer.
 *
 * This function binds the buffer and then uses glBufferSubData to add new data at the beginning of the buffer. 
 * The size of the data is specified by the Size parameter, and the actual data is pointed to by the Verticies pointer.
 *
 * @param[in] Verticies A pointer to the data that will be added to the buffer.
 * @param[in] Size The size in bytes of the data being added.
 * 
 * @return void
 */
void OpenGLVertexBuffer::AddDataToBuffer(const void* Verticies, uint32_t Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Verticies);
		
	}

	/**
 * @brief Creates a quad in the OpenGL vertex buffer.
 * 
 * This function takes in various parameters to create a quad, such as color, position, size, texture coordinates, tiling factor, and entity ID. It then populates an array of vertices with these details. The resulting array is returned by reference.
 * 
 * @param Target Pointer to the first element of the vertex array to be filled.
 * @param Color The color of the quad.
 * @param Position An array of positions for each vertex of the quad.
 * @param Size The size of the quad.
 * @param Transform The transformation matrix that will be applied to the vertices' positions.
 * @param TexCoords An array of texture coordinates for each vertex of the quad.
 * @param TilingFactor The tiling factor for the texture.
 * @param ID The ID of the texture being used.
 * @param EnttID The entity ID associated with the quad.
 * 
 * @return Pointer to the filled vertex array.
 */
/**
 * @brief Creates a quad in the OpenGL vertex buffer.
 * 
 * This function takes an array of vertices, colors, positions, texture coordinates, and other parameters to create a quad in the vertex buffer. The quad is created by filling four vertices with data from the provided arguments.
 * 
 * @param Target Pointer to the first element of the target array of vertices.
 * @param Color The color of the quad.
 * @param Position An array of positions for each vertex of the quad.
 * @param Size The size of the quad.
 * @param Transform The transformation matrix applied to the quad's position.
 * @param TexCoords An array of texture coordinates for each vertex of the quad.
 * @param TilingFactor The tiling factor used in the texture mapping.
 * @param ID The ID of the texture used by the quad.
 * @param EnttID The ID of the entity associated with the quad.
 * 
 * @return Pointer to the next available position after creating the quad.
 */
Vertex* OpenGLVertexBuffer::CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID)
	{

		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexTexCoords = TexCoords[i];
			Target->VertexColor = Color;
			Target->VertexTexID = ID;
			Target->VertexTilingFactor = TilingFactor;
			Target->VertexEntityID = EnttID;
			Target++;
		}

		return Target;
	}
	/**
 * @brief Creates a circle in the vertex buffer.
 *
 * This function takes an array of positions, applies a transformation to each position, and stores them into the target CircleVertex object. 
 * The color, thickness, fade factor, and entity ID are also stored for each vertex.
 *
 * @param Target Pointer to the CircleVertex object where the circle will be created.
 * @param Transform The transformation matrix that will be applied to the positions.
 * @param Position An array of Vector4 objects representing the positions of the vertices of the circle.
 * @param Color The color of the circle.
 * @param Thickness The thickness of the lines making up the circle.
 * @param Fade The fade factor of the circle.
 * @param EntID The entity ID associated with the circle.
 * 
 * @return Pointer to the CircleVertex object where the circle was created.
 */
/**
 * @brief Creates a circle vertex in the OpenGLVertexBuffer.
 *
 * This function takes an array of positions, applies a transformation to each position, and stores the transformed position, local position, color, thickness, fade, and entity ID into a CircleVertex struct. The function returns the updated target pointer.
 *
 * @param Target Pointer to the CircleVertex that will be populated with data.
 * @param Transform The transformation matrix to apply to each position.
 * @param Position Array of positions to transform and store in the vertex.
 * @param Color The color of the circle.
 * @param Thickness The thickness of the circle lines.
 * @param Fade The fade value for the circle.
 * @param EntID The entity ID associated with the circle.
 * 
 * @return Pointer to the updated CircleVertex struct.
 */
CircleVertex* OpenGLVertexBuffer::CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexWorldPosition = Transform * Position[i];
			Target->VertexLocalPosition = Vector3(Position[i] * 2.f);
			Target->VertexColor = Color;
			Target->VertexThickness = Thickness;
			Target->VertexFade = Fade;
			Target->CircleEntityID = EntID;
			Target++;
		}

		return Target;
	}
	/**
 * @brief Creates a line vertex in the OpenGL Vertex Buffer.
 * 
 * This function takes in parameters to create two vertices that form a line. The first vertex has its position set to Position0, color set to Color and LineEntityID set to EntID. The second vertex is similar but uses Position1 for its position.
 * @param Target Pointer to the target OpenGLVertexBuffer object where the new line will be added.
 * @param Color The color of the line.
 * @param Position0 The starting point of the line.
 * @param Position1 The ending point of the line.
 * @param EntID The entity ID associated with this line.
 * @return Pointer to the next available memory location in the OpenGLVertexBuffer object after adding two vertices.
 */
/**
 * @brief Creates a line vertex in the OpenGL Vertex Buffer.
 *
 * This function creates two vertices that form a line segment. The first vertex has its position set to Position0, color set to Color and LineEntityID set to EntID. The second vertex is similar but uses Position1 for its position. 
 *
 * @param Target Pointer to the target LineVertex object where the new vertices will be created.
 * @param Color The color of the line segment.
 * @param Position0 The starting point of the line segment.
 * @param Position1 The ending point of the line segment.
 * @param EntID The entity ID associated with the line segment.
 * 
 * @return Pointer to the next available LineVertex object after two vertices have been created.
 */
LineVertex* OpenGLVertexBuffer::CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID)
	{
		Target->VertexPosition = Position0;
		Target->VertexColor = Color;
		Target->LineEntityID = EntID;
		Target++;

		Target->VertexPosition = Position1;
		Target->VertexColor = Color;
		Target->LineEntityID = EntID;
		Target++;
		
		return Target;
	}

	/**
 * @brief This function creates a text vertex in an OpenGL vertex buffer.
 *
 * The function takes in several parameters including the target TextVertex pointer, a transformation matrix, 
 * position vectors, color, texture coordinates and texture ID. It then populates each of these values into 
 * the target TextVertex object for each vertex in the quadrilateral.
 *
 * @param Target Pointer to the TextVertex that will be filled with data.
 * @param Transform The transformation matrix used to transform the position vectors.
 * @param Position An array of Vector4 positions which represent the vertices of a text quadrilateral.
 * @param Color The color of the text.
 * @param TexCoords An array of Vector2 texture coordinates for each vertex in the text quadrilateral.
 * @param TexID The ID of the texture to be used for rendering the text.
 * @param EntID The entity ID associated with the text.
 * 
 * @return Pointer to the filled TextVertex object.
 */
/**
 * @brief This function creates a text vertex in an OpenGL vertex buffer.
 * 
 * The function takes in several parameters such as the target TextVertex, transformation matrix, position vector, color, texture coordinates, texture ID and entity ID. It then populates each of these values into the target TextVertex object for each vertex in the quadrilateral.
 * 
 * @param Target Pointer to a TextVertex that will be filled with data.
 * @param Transform The transformation matrix used to transform the position vector.
 * @param Position An array of Vector4 positions which represent the vertices of the text.
 * @param Color The color of the text vertex.
 * @param TexCoords An array of Vector2 texture coordinates for each vertex in the quadrilateral.
 * @param TexID The ID of the texture to be used for rendering the text.
 * @param EntID The entity ID associated with this text vertex.
 * 
 * @return Pointer to the filled TextVertex object.
 */
TextVertex* OpenGLVertexBuffer::CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID,int EntID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexColor = Color;
			Target->VertexTexCoords = TexCoords[i];
			Target->TexID = TexID;
			Target->EntityID = 0;
			Target++;
		}


		return Target;
	}

	/**
 * @brief Creates a tile with the given parameters and stores it in the provided TileVertex object.
 * 
 * This function takes an array of positions, texture coordinates, color, tiling factor, entity ID, and transforms them into vertex data for a quadrilateral tile. The resulting vertex data is stored in the provided `TileVertex` object.
 * @param Target Pointer to the TileVertex object where the created tile will be stored.
 * @param Color The color of the tile.
 * @param Position An array of positions that define the corners of the tile.
 * @param Size The size of the tile.
 * @param Transform A transformation matrix applied to the positions.
 * @param TexCoords An array of texture coordinates for each corner of the tile.
 * @param TilingFactor The tiling factor used in the texture mapping.
 * @param ID The ID of the texture used by the tile.
 * @param EnttID The entity ID associated with the tile.
 * 
 * @return Pointer to the `TileVertex` object where the created tile is stored.
 */
/**
 * @brief This function creates a tile with the given parameters.
 * 
 * The function takes in an array of positions, texture coordinates, color, tiling factor, entity ID and transforms them into vertices for a quadrilateral mesh. It then updates the target TileVertex object with these vertex attributes.
 * @param Target Pointer to the TileVertex object that will be updated.
 * @param Color The color of the tile.
 * @param Position An array of positions for each vertex of the tile.
 * @param Size The size of the tile.
 * @param Transform The transformation matrix applied to the vertices.
 * @param TexCoords An array of texture coordinates for each vertex of the tile.
 * @param TilingFactor The tiling factor used in the texture mapping.
 * @param ID The ID of the texture being used.
 * @param EnttID The entity ID associated with the tile.
 * 
 * @return Pointer to the updated Target object.
 */
TileVertex* OpenGLVertexBuffer::CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexTexCoords = TexCoords[i];
			Target->VertexColor = Color;
			Target->VertexTexID = ID;
			Target->VertexTilingFactor = TilingFactor;
			Target->VertexEntityID = EnttID;
			Target++;
		}

		return Target;
	}

////////////////////////////////////////////////////////////////////
//																  //
//																  //
//						INDEX BUFFER							  //
//																  //
//																  //
////////////////////////////////////////////////////////////////////	 	

	/**
 * @brief Constructor for OpenGLIndexBuffer. Creates an index buffer object and initializes it with the given indices.
 * 
 * @param Indices Pointer to the array of indices that will be used to initialize the buffer.
 * @param Count The number of elements in the Indices array.
 */
/**
 * @brief Constructs an OpenGLIndexBuffer object.
 * 
 * This function creates a new OpenGL index buffer and initializes it with the given indices. The number of indices is specified by the Count parameter.
 * 
 * @param Indices Pointer to the array of indices that will be copied into the GPU memory.
 * @param Count Number of indices in the Indices array.
 */
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count)
		:m_Count(Count)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	/**
 * @brief Destructor for OpenGLIndexBuffer. Deletes the buffer with ID m_RendererID using glDeleteBuffers function.
 * 
 * @param None
 * @return None
 */
/**
 * @brief Destructor for OpenGLIndexBuffer. Deletes the buffer with ID m_RendererID using glDeleteBuffers function.
 * 
 * @return void
 */
OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
		
	}
	/** 
 * @brief This function binds the OpenGL Index Buffer.
 * 
 * The function uses glBindBuffer to bind the buffer with ID 'm_RendererID' as an element array buffer (GL_ELEMENT_ARRAY_BUFFER).
 * It is used for rendering of indexed primitives, such as triangles or lines, using vertices from a vertex array.
 * 
 * @return void No return value.
 */
/** 
 * @brief This function binds the OpenGL Index Buffer.
 * 
 * It uses glBindBuffer to bind the buffer with target GL_ELEMENT_ARRAY_BUFFER and the ID of this buffer as argument.
 * The purpose of binding an index buffer is to specify which vertex array object (VAO) should be used for rendering.
 */
void OpenGLIndexBuffer::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		
	}
	/**
 * @brief This function unbinds the OpenGL Element Array Buffer.
 *
 * It binds the buffer target to GL_ELEMENT_ARRAY_BUFFER and sets the buffer ID to 0, effectively unbinding it from the current context.
 *
 * @return void
 */
/**
 * @brief This function unbinds the OpenGL Element Array Buffer.
 * 
 * It binds the buffer target to GL_ELEMENT_ARRAY_BUFFER and sets the buffer ID to 0, effectively unbinding it from any rendering operations that use this buffer.
 * 
 * @return void
 */
void OpenGLIndexBuffer::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	}
	/**
 * @brief Invalidates and deletes the OpenGL buffer.
 *
 * This function first invalidates any existing data in the buffer using glInvalidateBufferData(). Then it deletes the buffer itself with glDeleteBuffers(). 
 * The buffer's ID is passed to these functions, indicating which buffer should be affected.
 *
 * @return void
 */
/**
 * @brief This function is used to invalidate the buffer data and delete the OpenGL index buffer.
 * 
 * The function first calls glInvalidateBufferData() on the OpenGL context with the renderer ID of this object as an argument, which marks the buffer's data as needing update.
 * Then it deletes the buffer using glDeleteBuffers(), passing in the same renderer ID to remove the buffer from memory.
 * 
 * @return void
 */
void OpenGLIndexBuffer::InvalidateBuffer() const
	{
		AGE_PROFILE_FUNCTION();
		glInvalidateBufferData(m_RendererID);
		
		glDeleteBuffers(1, &m_RendererID);
		
	}

////////////////////////////////////////////////////////////////////
//																  //
//																  //
//						UNIFORM BUFFER							  //
//																  //
//																  //
////////////////////////////////////////////////////////////////////

	/**
 * @brief Constructor for OpenGLUniformBuffer. Creates a new uniform buffer object with the specified size and binding point.
 * 
 * @param Size The size of the buffer in bytes.
 * @param Binding The binding point for this buffer, which determines its location in the shader program.
 */
/**
 * @brief Constructor for OpenGLUniformBuffer. 
 * Initializes an OpenGL uniform buffer object with the specified size and binding point.
 *
 * @param Size The size of the buffer in bytes.
 * @param Binding The binding point for this buffer, which determines its location in the shader program.
 */
OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t Size, uint32_t Binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, Size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, Binding, m_RendererID);
	}
	/**
 * @brief Destructor for the OpenGLUniformBuffer class.
 * This function deletes a buffer object from OpenGL using glDeleteBuffers().
 * The buffer to be deleted is specified by its ID, which is stored in m_RendererID member variable of this instance.
 * 
 * @return void
 */
/**
 * @brief Destructor for the OpenGLUniformBuffer class.
 * This function deletes a buffer object from OpenGL using glDeleteBuffers().
 * The buffer to be deleted is specified by its ID, which is stored in m_RendererID member variable of this instance.
 */
OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	/**
 * @brief Bind the uniform buffer to a specific binding point in the GPU's memory.
 * 
 * This function binds the uniform buffer object (UBO) to a specific binding point in the OpenGL context. The UBO is essentially an array of uniform variables that can be accessed by shaders.
 *
 * @return void No return value.
 */
/**
 * @brief Bind the uniform buffer to a specific binding point in the GPU's memory.
 * 
 * This function binds the uniform buffer object (UBO) to a specific binding point in the GPU's memory. The binding point is specified by an integer argument, 'bindingPoint'. It allows data to be sent to shaders for rendering without having to re-upload it every frame.
 *
 * @param[in] bindingPoint An integer specifying the binding point in the GPU's memory where the UBO should be bound.
 */
void OpenGLUniformBuffer::Bind()
	{
	}
	/**
 * @brief Unbind function for the OpenGLUniformBuffer class. This function sets the buffer to an unbound state, meaning it is no longer bound to a target.
 * 
 * @return void
 */
/**
 * @brief Unbind function for the OpenGLUniformBuffer class. This function is used to unbind any buffer that has been bound in the current context. 
 * It sets the uniform binding point back to its default state, which is zero.
 *
 * @return void
 */
void OpenGLUniformBuffer::Unbind()
	{
	}
	/**
 * @brief This function sets the data of an OpenGL uniform buffer.
 * 
 * @param Data A pointer to the data that will be copied into the named buffer's data store.
 * @param Size The size in bytes of the data being uploaded.
 * @param Offset The offset in bytes from the beginning of the buffer where the new data will be placed.
 * 
 * @return void
 */
/**
 * @brief This function sets the data of an OpenGL uniform buffer.
 * 
 * @param Data A pointer to the data that will be copied into the named buffer's data store.
 * @param Size The size in bytes of the region of the buffer object that is being replaced.
 * @param Offset The offset, in basic machine units, within the buffer object where the replacement will begin.
 */
void OpenGLUniformBuffer::SetData(const void* Data, uint32_t Size, uint32_t Offset)
	{
		glNamedBufferSubData(m_RendererID, Offset, Size, Data);
	}
}