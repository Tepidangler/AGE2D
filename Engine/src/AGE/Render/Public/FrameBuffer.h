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
		None = 0,

		//Color
		RGBA8,
		RED_INTEGER,
		//DepthStencil
		DEPTH24STENCIL8,
		Depth = DEPTH24STENCIL8

	};


	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat Format)
			:TextureFormat(Format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;

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
		DXGI_FORMAT DXGIFormat;
		DXGI_SAMPLE_DESC DXGISampleDesc;
		D3D11_USAGE DXGIUsage;
		uint32_t BindFlags;
		uint32_t CPUAccessFlags;
		uint32_t MiscFlags;
		bool SwapChainTarget = false;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV;

	public:

		//Getters
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetSRV() { return SRV; }
	};

	

	class FrameBuffer
	{
	public:
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