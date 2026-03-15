#pragma once

#include "Render/Public/RenderBuffer.h"

namespace AGE
{
	class VertexArray
	{
	public:
		
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) = 0;

		virtual void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;


		virtual void EnableVertexAttribArray(uint32_t ArrayID) const = 0;

		virtual void MakeVertexAttribPtr(uint32_t index, int size, uint32_t type, uint8_t normalized, int stride, const void* pointer) const = 0;

		virtual std::vector<Ref<VertexBuffer>>::iterator begin() = 0;

		virtual std::vector<Ref<VertexBuffer>>::iterator end() = 0;

		virtual std::vector<Ref<VertexBuffer>>::const_iterator begin() const = 0;
		virtual std::vector<Ref<VertexBuffer>>::const_iterator end() const = 0;

		static Ref<VertexArray> Create();
	};
}