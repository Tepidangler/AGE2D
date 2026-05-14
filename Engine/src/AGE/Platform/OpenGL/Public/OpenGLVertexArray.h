#pragma once
#include "Render/Public/VertexArray.h"
#include <memory>

namespace AGE
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();

		~OpenGLVertexArray() override;

		void Bind() const override;

		void Unbind() const override;

		void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) override;

		void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) override;

		/**
 * @brief Returns a constant reference to the vertex buffers associated with this object.
 * @return A constant reference to the vector of VertexBuffer objects.
 */
/**
 * @brief Returns a constant reference to the vertex buffers of this object.
 * @return A constant reference to the vector of vertex buffers (m_VertexBuffers).
 */
const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		/**
 * @brief Returns the index buffer associated with this object.
 * @return A constant reference to the index buffer.
 */
/**
 * @brief Returns the index buffer associated with this object.
 * @return A constant reference to the index buffer.
 */
const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
		
		void EnableVertexAttribArray(uint32_t ArrayID) const override;

		void MakeVertexAttribPtr(uint32_t index, int size, uint32_t type, uint8_t normalized, int stride, const void* pointer) const override;

		/**
 * @brief Returns an iterator pointing to the beginning of the vertex buffer list.
 *
 * This function returns an iterator that points to the first element in the vector of vertex buffers. If there are no elements, the returned iterator will be equal to end().
 *
 * @return An iterator pointing to the start of the vertex buffer list.
 */
/**
 * @brief Returns an iterator pointing to the first element in the vertex buffer list.
 * @return An iterator pointing to the first element in the vertex buffer list. If the container is empty, the returned iterator will be equal to end().
 */
std::vector<Ref<VertexBuffer>>::iterator begin() override { return m_VertexBuffers.begin(); }

		/**
 * @brief Returns an iterator pointing to the theoretical element that follows the last element of the container.
 * This function is used in range-based for loops and similar contexts where a sentinel value is needed.
 *
 * @return An iterator to the theoretical element that follows the last element of the container.
 */
/**
 * @brief Returns an iterator pointing to the theoretical element that follows the last element of the container.
 * This function returns an iterator to an imaginary element following the last actual element in the vector, which is valid but does not point to any real data (as vectors are sparse containers).
 * 
 * @return An iterator to the theoretical element that follows the end of the sequence controlled by the container.
 */
std::vector<Ref<VertexBuffer>>::iterator end() override { return m_VertexBuffers.end(); }

		/**
 * @brief Returns a constant iterator pointing to the beginning of the vertex buffer list.
 * 
 * This function returns an iterator that points to the first element in the vector of VertexBuffer objects, which represents the start of the vertex buffers collection. The returned iterator can be used with standard container functions like std::advance or std::next to move through the collection.
 *
 * @return A constant iterator pointing to the beginning of the vertex buffer list. If no elements exist in the vector, the returned iterator will equal end().
 */
/**
 * @brief Returns a constant iterator pointing to the beginning of the vertex buffer list.
 * @return A constant iterator pointing to the first element in the vertex buffer list. If the container is empty, the returned iterator will be equal to end().
 */
std::vector<Ref<VertexBuffer>>::const_iterator begin() const override { return m_VertexBuffers.begin(); }

		/**
 * @brief Returns a constant iterator pointing to the theoretical element past the last element of the vertex buffer vector.
 * @return A constant iterator pointing to the theoretical element past the end of the vertex buffer vector.
 */
/**
 * @brief Returns an iterator pointing to the past-the-end element in the container.
 * @return A constant iterator pointing to the past-the-end element of the container.
 */
std::vector<Ref<VertexBuffer>>::const_iterator end() const override { return m_VertexBuffers.end(); }


	private:

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_ArrayID;
	};
}