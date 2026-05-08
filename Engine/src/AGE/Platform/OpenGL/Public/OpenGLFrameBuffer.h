#pragma once
#include "Render/Public/FrameBuffer.h"
#include "Core/Public/Log.h"


namespace AGE
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& Spec);
		~OpenGLFrameBuffer();

		void Invalidate();

		/**
 * @brief This function is used for presenting some content or data.
 *
 * @return Nothing is returned as this function is a pure virtual function in the base class. It does not return any value.
 */
virtual void Present() override {}
		virtual void Resize(const uint32_t Width, const uint32_t Height) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual int ReadPixel(uint32_t AttachmentIndex, int x, int y) override;
		/**
 * @brief Gets the specification of the frame buffer.
 *
 * This function returns a reference to the current specification of the frame buffer. The caller can use this information to determine how the frame buffer is configured and what it supports.
 *
 * @return A reference to the current FrameBufferSpecification object representing the specification of the frame buffer.
 */
virtual FrameBufferSpecification& GetSpecification() override { return m_Specification; }
		/**
 * @brief Returns the specification of the frame buffer.
 *
 * This function returns a reference to the specification object that holds details about the current state of the frame buffer.
 * The returned value is constant and should not be modified by the caller.
 *
 * @return A const reference to the FrameBufferSpecification object representing the current state of the frame buffer.
 */
virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

		COMMENT:
/**
 * @brief This function returns the width and height of an object as a Vector2.
 * @return A Vector2 with x-coordinate representing the width and y-coordinate representing the height.
 */
CONFIDENCE: 1.0;

virtual const Vector2 GetWidthHeight() const override { return Vector2((float)m_Specification.Width, (float)m_Specification.Height); }

		/**
 * @brief Get the Renderer ID for a specific Color Attachment
 * @param Index The index of the color attachment to get the renderer ID from. Default is 0.
 * @return The Renderer ID of the specified color attachment, or 0 if the index is out of range.
 */
virtual uint32_t GetColorAttachmentRendererID(uint32_t Index = 0) const override { CoreLogger::Assert(Index < m_ColorAttachments.size(), "Index is greater than number of available color attachments!"); return m_ColorAttachments[Index]; }
		/**
 * @brief This function returns the ID of the depth attachment renderer.
 * @return The ID of the depth attachment renderer as a uint32_t value.
 */
virtual uint32_t GetDepthAttachmentRendererID() const override {return m_DepthAttachment;}

		virtual void ClearAttachment(uint32_t Index, int Value) override;

		virtual void OnEvent(Event& E) override;

		
	private:

		uint32_t m_RendererID = 0;

		std::vector<uint32_t> m_ColorAttachments;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::INVALIDFORMAT;
		uint32_t m_DepthAttachment = 0;

		int m_nrChannels = 4;

		FrameBufferSpecification m_Specification;

	};
}