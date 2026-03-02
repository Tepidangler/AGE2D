#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLFrameBuffer.h"

#include <glad/glad.h>
namespace AGE
{
	namespace Utils
	{
		static GLenum TextureTarget(bool Multisampled)
		{
			return Multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}
	
		static void CreateTextures(bool Multisampled, uint32_t* OutID, uint32_t Count)
		{
			glCreateTextures(TextureTarget(Multisampled), (int)Count, OutID);;
		}
	
		static void BindTexture(bool Multisampled, uint32_t ID)
		{
			glBindTexture(TextureTarget(Multisampled), ID);
		}
	
		static void AttachColorTexture(uint32_t ID, int Samples, GLenum InternalFormat, GLenum Format, uint32_t Width, uint32_t Height, int Index)
		{
			bool Multisampled = Samples > 1;
	
			if (Multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Samples, InternalFormat, (int)Width, (int)Height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, (int)InternalFormat, (int)Width, (int)Height, 0, Format, GL_UNSIGNED_BYTE, nullptr);
	
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
	
			glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0 + Index), TextureTarget(Multisampled), ID, 0);
		}
	
	
		static void AttachDepthTexture(uint32_t ID, int Samples, GLenum Format, GLenum AttachmentType, uint32_t Width, uint32_t Height)
		{
			bool Multisampled = Samples > 1;
	
			if (Multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Samples, Format, (int)Width, (int)Height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, Format, (int)Width, (int)Height);
	
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
	
			glFramebufferTexture2D(GL_FRAMEBUFFER, AttachmentType, TextureTarget(Multisampled), ID, 0);
		}
	
	
		static bool IsDepthFormat(FramebufferTextureFormat Format)
		{
			switch (Format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
			{
				return true;
			}
			default:
			{
				break;
			}
			}

			return false;
	
		}

		static GLenum AGETextureFormatToGL(FramebufferTextureFormat Format)
		{
			switch (Format)
			{
			case FramebufferTextureFormat::RGBA8:
			{
				return GL_RGBA8;
			}
			case FramebufferTextureFormat::RED_INTEGER:
			{
				return GL_RED_INTEGER;
			}

			default:
			{
				CoreLogger::Assert(false, "Invalid Format");
				return 0;	
			}
			}
		}
	}
	
		static const uint32_t s_MaxFramebufferSize = 8192;
	
		OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& Spec)
			:m_Specification(Spec)
		{
			for (auto FBSpec : m_Specification.Attachments.Attachments)
			{
				if (!Utils::IsDepthFormat(FBSpec.TextureFormat))
				{
					m_ColorAttachmentSpecifications.emplace_back(FBSpec);
				}
				else
				{
					m_DepthAttachmentSpecification = FBSpec;
				}
			}

			Invalidate();
		}
		OpenGLFrameBuffer::~OpenGLFrameBuffer()
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures((int)m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);
		}
		void OpenGLFrameBuffer::Invalidate()
		{
	
			if (m_RendererID)
			{
				glDeleteFramebuffers(1, &m_RendererID);
				glDeleteTextures((int)m_ColorAttachments.size(), m_ColorAttachments.data());
				glDeleteTextures(1, &m_DepthAttachment);
				m_ColorAttachments.clear();
				m_DepthAttachment = 0;
			}
	
			glCreateFramebuffers(1, &m_RendererID);
	

			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

			bool Multisample = m_Specification.Samples > 1;

			if (m_ColorAttachmentSpecifications.size())
			{
				m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
				Utils::CreateTextures(Multisample, m_ColorAttachments.data(), (uint32_t)m_ColorAttachments.size());

				for (size_t i = 0; i < m_ColorAttachments.size(); i++)
				{
					Utils::BindTexture(Multisample, m_ColorAttachments[i]);
					switch (m_ColorAttachmentSpecifications[i].TextureFormat)
					{
					case FramebufferTextureFormat::RGBA8:
					{
						Utils::AttachColorTexture(m_ColorAttachments[i], (int)m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, (int)i);
						break;
					}
					case FramebufferTextureFormat::RED_INTEGER:
					{
						Utils::AttachColorTexture(m_ColorAttachments[i], (int)m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, (int)i);
						break;
					}
					default:
					{
						break;
					}
					}
				}
			}
	
			if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::INVALIDFORMAT)
			{
				Utils::CreateTextures(Multisample, &m_DepthAttachment, 1);
				Utils::BindTexture(Multisample, m_DepthAttachment);
				switch (m_DepthAttachmentSpecification.TextureFormat)
				{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
				{
					Utils::AttachDepthTexture(m_DepthAttachment, (int)m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
					break;
				}
				default:
				{
					break;
				}
				}
			}
			
			if (m_ColorAttachments.size() > 1)
			{
				CoreLogger::Assert(m_ColorAttachments.size() <= 4, "Color Attachments is not less than or equal to 4");
				GLenum Buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
				glDrawBuffers((int)m_ColorAttachments.size(), Buffers);
			}
			else if (m_ColorAttachments.empty())
			{
				// Only Depth Pass
				glDrawBuffer(GL_NONE);
			}

			CoreLogger::Error("OpenGL Error: {0}", glGetError());
	
			CoreLogger::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void OpenGLFrameBuffer::Resize(const uint32_t Width, const uint32_t Height)
		{
			if (Width == 0 || Height == 0 || Width > s_MaxFramebufferSize || Height > s_MaxFramebufferSize)
			{
				CoreLogger::Warn("Attempted to resize Framebuffer to {0},{1}", Width, Height);
	
				return;
			}
			m_Specification.Width = Width;
			m_Specification.Height = Height;
	
			Invalidate();
		}
		void OpenGLFrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	
			glViewport(0, 0, (int)m_Specification.Width, (int)m_Specification.Height);
		}
		void OpenGLFrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
		}

		int OpenGLFrameBuffer::ReadPixel(uint32_t AttachmentIndex, int x, int y)
		{
			CoreLogger::Assert(AttachmentIndex < m_ColorAttachments.size(), "Attachment Index is larger than number of Elements in Color Attachments array!");

			glReadBuffer(GL_COLOR_ATTACHMENT0 + AttachmentIndex);
			int PixelData;

			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &PixelData);
			return PixelData;
		}

		void OpenGLFrameBuffer::ClearAttachment(uint32_t Index , int Value)
		{

			CoreLogger::Assert(Index < m_ColorAttachments.size(), "Index is greater that number of color attachments!");

			auto& Spec = m_ColorAttachmentSpecifications[Index];
			glClearTexImage(m_ColorAttachments[Index], 0, Utils::AGETextureFormatToGL(Spec.TextureFormat), GL_INT, &Value);
		}

		void OpenGLFrameBuffer::OnEvent(Event& E)
		{
		}
	
}