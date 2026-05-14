#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLFrameBuffer.h"

#include <glad/glad.h>
namespace AGE
{
	namespace Utils
	{
		/**
 * @brief Determines the OpenGL texture target based on whether multisampling is enabled.
 * 
 * This function takes a boolean parameter indicating if multisampling should be used. If true, it returns GL_TEXTURE_2D_MULTISAMPLE; otherwise, it returns GL_TEXTURE_2D.
 * 
 * @param Multisampled A boolean value indicating whether to use multisampling or not.
 * @return The OpenGL texture target corresponding to the input parameter.
 */
/**
 * @brief Determines the OpenGL texture target based on whether multisampling is enabled.
 *
 * This function takes a boolean parameter indicating if multisampling should be used. If true, it returns GL_TEXTURE_2D_MULTISAMPLE; otherwise, it returns GL_TEXTURE_2D. 
 *
 * @param Multisampled A boolean value indicating whether to use multisampling or not.
 * @return The OpenGL texture target based on the input parameter. Returns GL_TEXTURE_2D if false is passed and GL_TEXTURE_2D_MULTISAMPLE if true is passed.
 */
static GLenum TextureTarget(bool Multisampled)
		{
			return Multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}
	
		/**
 * @brief Creates a set of textures.
 *
 * This function creates a set of OpenGL textures using the glCreateTextures function. The number of textures to be created is specified by 'Count'. 
 * The parameter 'Multisampled' determines whether the textures are multisampled or not, and 'OutID' is an array that will hold the IDs of the newly created textures.
 *
 * @param Multisampled A boolean value indicating if the textures should be multisampled.
 * @param OutID An array to store the IDs of the newly created textures.
 * @param Count The number of textures to create.
 * 
 * @return void
 */
/**
 * @brief Creates a set of textures.
 * 
 * This function creates a set of OpenGL textures with the specified parameters. The number of textures to be created is given by 'Count'.
 * If 'Multisampled' is true, multisampling will be used for the textures; otherwise, they won't. The IDs of the newly created textures are stored in the array pointed to by 'OutID'.
 * 
 * @param Multisampled A boolean indicating whether or not to use multisampling.
 * @param OutID An array that will store the IDs of the newly created textures.
 * @param Count The number of textures to be created.
 */
static void CreateTextures(bool Multisampled, uint32_t* OutID, uint32_t Count)
		{
			glCreateTextures(TextureTarget(Multisampled), (int)Count, OutID);;
		}
	
		/**
 *  @brief This function binds a texture to the OpenGL context.
 *  
 *  The function takes two parameters, a boolean indicating whether the texture is multisampled and an unsigned integer representing the ID of the texture. It uses these values to determine the appropriate target for binding the texture with glBindTexture().
 *  
 *  @param Multisampled A boolean value that indicates if the texture is multisampled or not.
 *  @param ID An unsigned integer representing the ID of the texture to be bound.
 *  
 *  @return void
 */
/**
 *  @brief This function binds a texture to the OpenGL context.
 *  
 *  It takes two parameters, one boolean and one unsigned integer. The boolean indicates whether the texture is multisampled or not, while the unsigned integer represents the ID of the texture.
 *  The function uses these inputs to determine the correct target for binding the texture using glBindTexture().
 *  
 *  @param Multisampled A boolean indicating if the texture is multisampled (true) or not (false).
 *  @param ID An unsigned integer representing the ID of the texture.
 *  
 *  @return void
 */
static void BindTexture(bool Multisampled, uint32_t ID)
		{
			glBindTexture(TextureTarget(Multisampled), ID);
		}
	
		/**
 * @brief Attaches a color texture to the framebuffer.
 * 
 * This function sets up and attaches a color texture to the OpenGL framebuffer object. The texture can be either multisampled or regular, depending on the 'Samples' parameter. It then binds this texture as a color attachment point for rendering.
 */
/**
 * @brief Attach a color texture to the framebuffer.
 * 
 * This function attaches a color texture to the OpenGL framebuffer. The texture can be either multisampled or regular. If it's multisampled, we use glTexImage2DMultisample to create the texture with specified samples and internal format. Otherwise, we use glTexImage2D to create a 2D texture with given width, height, and format. We then set various texture parameters such as minification and magnification filters, wrapping modes etc., before attaching it to the framebuffer using glFramebufferTexture2D.
 * 
 * @param ID The OpenGL ID of the texture to attach.
 * @param Samples Number of samples for multisampling (if any).
 * @param InternalFormat The internal format of the texture.
 * @param Format The format of the pixel data.
 * @param Width The width of the texture.
 * @param Height The height of the texture.
 * @param Index The index for color attachment point in framebuffer object.
 */
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
	
	
		
/**
 * This function is used to attach a depth texture to the frame buffer. It takes in several parameters including the OpenGL ID, number of samples for multisampling, format of the texture data, type of attachment and dimensions of the texture. 
 * The function first checks if the texture should be multisampled based on the provided sample count. If it is, a multisample texture image is created using glTexImage2DMultisample. Otherwise, a regular 2D texture storage is created with glTexStorage2D and some basic parameters are set for the texture.
 * Finally, the function attaches the texture to the frame buffer using glFramebufferTexture2D.
 */
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
	
	
		/**
 * @brief Checks if the given format is a depth format.
 * 
 * This function checks whether the provided FramebufferTextureFormat is one of the depth formats. It returns true for DEPTH24STENCIL8 and false otherwise.
 * 
 * @param Format The format to check.
 * @return True if the format is a depth format, false otherwise.
 */
/**
 * @brief Checks if the given format is a depth format.
 * 
 * This function checks whether the provided FramebufferTextureFormat is one of the depth formats. The only depth format currently supported by this application is DEPTH24STENCIL8.
 * 
 * @param Format The format to check.
 * @return True if the format is a depth format, false otherwise.
 */
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

		/**
 * @brief Converts a FramebufferTextureFormat to its corresponding GLenum.
 *
 * This function takes in a FramebufferTextureFormat and returns the equivalent GLenum value. It handles four formats: RGBA8, RED_INTEGER. For any other format, it asserts false and returns 0.
 *
 * @param Format The FramebufferTextureFormat to convert.
 * @return The corresponding GLenum for the input FramebufferTextureFormat. If the input is not a recognized format, it will return 0.
 */
/**
 * @brief Converts a FramebufferTextureFormat to its corresponding GLenum.
 *
 * This function takes in a FramebufferTextureFormat and returns the equivalent GLenum value. It handles four cases: RGBA8, which corresponds to GL_RGBA8, RED_INTEGER, which corresponds to GL_RED_INTEGER, and any other format that is not handled by this function results in an assertion failure with a message "Invalid Format".
 * 
 * @param Format The FramebufferTextureFormat to convert.
 * @return The corresponding GLenum value for the given FramebufferTextureFormat.
 */
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
	
		/**
 * @brief Constructor for OpenGLFrameBuffer class.
 *
 * This constructor takes a FrameBufferSpecification object as input, which contains the specifications of the frame buffer to be created. 
 * It iterates over the Attachments in the specification and separates them into color attachments (those that are not depth formats) and depth attachment (the one that is).
 * Finally, it calls Invalidate() function to create the actual frame buffer object with OpenGL.
 *
 * @param Spec The FrameBufferSpecification object containing specifications for the frame buffer.
 */
/**
 * @brief Constructor for OpenGLFrameBuffer class.
 * 
 * This constructor initializes an instance of the OpenGLFrameBuffer class with a FrameBufferSpecification object. It processes the attachments in the specification and separates them into color and depth attachments, based on their format. The Invalidate() function is then called to generate the frame buffer object (FBO) and its associated textures.
 * 
 * @param Spec A const reference to a FrameBufferSpecification object containing information about the attachments for this frame buffer.
 */
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
		/**
 * @brief Destructor for the OpenGLFrameBuffer class.
 * This function deletes both color and depth attachments associated with the frame buffer object.
 */
/**
 * @brief Destructor for the OpenGLFrameBuffer class.
 * This function deletes the framebuffer and its associated color and depth attachments from GPU memory.
 */
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
		/**
 * @brief Resizes the OpenGL FrameBuffer to a new size.
 *
 * This function resizes the framebuffer to the specified width and height, provided they are within the maximum allowed size (s_MaxFramebufferSize). 
 * If the dimensions are invalid or exceed the maximum size, it logs a warning message and returns without changing anything.
 *
 * @param Width The new width for the FrameBuffer.
 * @param Height The new height for the FrameBuffer.
 */
/**
 * @brief Resizes the OpenGL FrameBuffer to a specified width and height.
 *
 * The function checks if the provided dimensions are within the maximum framebuffer size limit (s_MaxFramebufferSize). 
 * If they are, it updates the m_Specification object with the new dimensions and calls Invalidate() to regenerate the framebuffer. 
 * If the dimensions are not valid, a warning is logged and no action is taken.
 *
 * @param Width The desired width for the FrameBuffer. Must be greater than zero and less or equal to s_MaxFramebufferSize.
 * @param Height The desired height for the FrameBuffer. Must be greater than zero and less or equal to s<｜begin▁of▁sentence｜>MaxFramebufferSize.
 */
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
		/**
 * @brief This function binds the OpenGL framebuffer to be used for rendering operations.
 * 
 * The function first calls glBindFramebuffer with GL_FRAMEBUFFER and m_RendererID as arguments, which binds the framebuffer object with the given ID.
 * Then it sets the viewport using glViewport with (0, 0) and (m_Specification.Width, m_Specification.Height) as arguments, setting the dimensions of the rendering area to match the size of the framebuffer's client area.
 */
/**
 * @brief Binds the OpenGL framebuffer object for rendering.
 * 
 * This function binds the framebuffer object associated with this instance of `OpenGLFrameBuffer` to the GL_FRAMEBUFFER target, and sets the viewport dimensions according to the specification provided when the framebuffer was created.
 *
 * @return void
 */
void OpenGLFrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	
			glViewport(0, 0, (int)m_Specification.Width, (int)m_Specification.Height);
		}
		/**
 * @brief Unbinds the current frame buffer.
 *
 * This function binds the default frame buffer to the OpenGL context using glBindFramebuffer().
 * The GL_FRAMEBUFFER target is used, and 0 is passed as argument to unbind the currently bound frame buffer.
 *
 * @return void
 */
/**
 * @brief Unbinds the current frame buffer.
 * 
 * This function binds the default frame buffer to the OpenGL context using glBindFramebuffer().
 * The GL_FRAMEBUFFER target is used, and 0 is passed as argument to unbind the currently bound frame buffer.
 *
 * @return void
 */
void OpenGLFrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
		}

		/**
 * @brief Reads a single pixel from the OpenGL framebuffer.
 *
 * This function reads a single pixel at the specified (x, y) coordinates in the color attachment of the framebuffer. 
 * The pixel data is returned as an integer value.
 *
 * @param AttachmentIndex Index of the color attachment to read from. It should be less than the number of elements in m_ColorAttachments array.
 * @param x X-coordinate of the pixel to read.
 * @param y Y-coordinate of the pixel to read.
 * 
 * @return The integer value of the pixel at (x, y) coordinates in the specified color attachment.
 */
/**
 * @brief Reads a single pixel from the OpenGL framebuffer.
 *
 * This function reads a single pixel at the specified (x, y) coordinates in the color attachment 
 * of the OpenGL framebuffer. The pixel data is returned as an integer value.
 *
 * @param AttachmentIndex Index of the color attachment to read from. Must be less than the number 
 *                        of elements in m_ColorAttachments array.
 * @param x Horizontal position of the pixel to read, starting at 0 for leftmost column.
 * @param y Vertical position of the pixel to read, starting at 0 for top row.
 *
 * @return The integer value of the pixel data at (x, y).
 */
int OpenGLFrameBuffer::ReadPixel(uint32_t AttachmentIndex, int x, int y)
		{
			CoreLogger::Assert(AttachmentIndex < m_ColorAttachments.size(), "Attachment Index is larger than number of Elements in Color Attachments array!");

			glReadBuffer(GL_COLOR_ATTACHMENT0 + AttachmentIndex);
			int PixelData;

			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &PixelData);
			return PixelData;
		}

		/**
 * @brief Clears a specific color attachment at the given index with a specified value.
 *
 * This function clears the color attachment at the provided index to the specified value using OpenGL's glClearTexImage function. 
 * It first checks if the provided index is within the valid range of color attachments, and then retrieves the corresponding specification for that attachment.
 * The texture format from the specification is used in the call to glClearTexImage. If the index is out of bounds or there are no color attachments at all, it will assert with an error message. 
 *
 * @param Index The zero-based index of the color attachment to clear.
 * @param Value The value to which to clear the specified color attachment.
 */
/**
 * @brief Clears a specific color attachment at the given index with a specified value.
 * 
 * This function clears a color attachment at the provided index to a specified value using OpenGL's glClearTexImage function. The function first checks if the provided index is within the valid range of color attachments, and throws an assertion error if it isn't. Then, it retrieves the specification for the corresponding color attachment and uses this information to clear the texture with the specified value.
 * 
 * @param Index The index of the color attachment to be cleared.
 * @param Value The value to which the color attachment should be cleared.
 */
void OpenGLFrameBuffer::ClearAttachment(uint32_t Index , int Value)
		{

			CoreLogger::Assert(Index < m_ColorAttachments.size(), "Index is greater that number of color attachments!");

			auto& Spec = m_ColorAttachmentSpecifications[Index];
			glClearTexImage(m_ColorAttachments[Index], 0, Utils::AGETextureFormatToGL(Spec.TextureFormat), GL_INT, &Value);
		}

		/**
 * @brief Handles events for the OpenGLFrameBuffer class.
 * 
 * This function takes an event as input and processes it based on its type. The exact behavior of this function depends on the specifics of the Event class, which is not defined in this file.
 * 
 * @param E Reference to the Event object that needs processing.
 */
/**
 * @brief Handles events for the OpenGLFrameBuffer class.
 * 
 * This function takes an Event object as input and handles it according to its type. The exact behavior of this function depends on the specific implementation of the Event class, which is not specified here.
 * 
 * @param E An instance of the Event class that needs to be handled.
 */
void OpenGLFrameBuffer::OnEvent(Event& E)
		{
		}
	
}