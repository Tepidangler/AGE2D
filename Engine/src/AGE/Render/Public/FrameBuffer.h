#pragma once
#include "Core/Public/Core.h"
#include "Structs/Public/DataStructures.h"
#include "Math/Public/UtilityFunctions.h"
#include "Events/Public/Event.h"

#include <glm/glm.hpp>

namespace AGE
{
	enum class FramebufferTextureFormat
	{
		INVALIDFORMAT = 0,

		//Color
		RGBA8,
		RED_INTEGER,
		//DepthStencil
		DEPTH24STENCIL8,
		Depth = DEPTH24STENCIL8

	};


	struct FramebufferTextureSpecification
	{
		/**
 * @brief Default constructor for the FramebufferTextureSpecification class.
 */
/**
 * @brief Default constructor for the FramebufferTextureSpecification class.
 */
FramebufferTextureSpecification() = default;
		/**
 * @brief Constructs a FramebufferTextureSpecification object with the specified texture format.
 * 
 * @param Format The texture format to be used for this specification.
 */
COMMENT:
/**
 * @brief Constructs a FramebufferTextureSpecification object with the given texture format.
 * @param Format The format of the texture to be used for rendering.
 */
CONFIDENCE: 1.0;

FramebufferTextureSpecification(FramebufferTextureFormat Format)
			:TextureFormat(Format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::INVALIDFORMAT;
	};

	struct FramebufferAttachmentSpecification
	{
		/**
 * @brief Default constructor for the FramebufferAttachmentSpecification class.
 *
 * This function initializes a new instance of the FramebufferAttachmentSpecification class with default values.
 */
/**
 * @brief Default constructor for the FramebufferAttachmentSpecification class.
 */
FramebufferAttachmentSpecification() = default;

		/**
 * @brief Constructs a FramebufferAttachmentSpecification object with the given list of FramebufferTextureSpecifications.
 * 
 * @param attachments A std::initializer_list<FramebufferTextureSpecification> containing the specifications for each texture to be attached to the framebuffer.
 */
/**
 * @brief Constructs a FramebufferAttachmentSpecification object with the given list of FramebufferTextureSpecifications.
 * 
 * @param attachments A std::initializer_list<FramebufferTextureSpecification> containing the specifications for each texture attachment to be used in the framebuffer.
 */
FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			:Attachments(attachments) {}


		std::vector<FramebufferTextureSpecification> Attachments;
	};


	struct FrameBufferSpecification
	{
	public:
		uint32_t Width = 0;
		uint32_t Height = 0;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;
		uint32_t MipLevels;
		uint32_t ArraySize;
		uint32_t BindFlags;
		uint32_t CPUAccessFlags;
		uint32_t MiscFlags;
		bool SwapChainTarget = false;
	};

	

	class FrameBuffer
	{
	public:
		/**
 * @brief Virtual destructor for the FrameBuffer class.
 *
 * This function is responsible for releasing any resources that were acquired by the FrameBuffer object, such as memory or file handles. It does not return anything (void) and thus it doesn't need a Doxygen comment to document its return value. 
 */
/**
 * @brief Virtual destructor for the FrameBuffer class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not return anything and thus has an empty return type (void).
 */
virtual ~FrameBuffer() {}
		
		virtual FrameBufferSpecification& GetSpecification()  = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t Index = 0) const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		//virtual FrameBufferSpecification& SetSpecification() = 0;

		virtual void Resize(const uint32_t Width, const uint32_t Height) = 0;
		virtual const Vector2 GetWidthHeight() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual int ReadPixel(uint32_t AttachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t Index, int Value) = 0;

		virtual void Present() = 0;

		virtual void OnEvent(Event& E) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& Spec);

		template<typename T>
		T* As();
	};
}