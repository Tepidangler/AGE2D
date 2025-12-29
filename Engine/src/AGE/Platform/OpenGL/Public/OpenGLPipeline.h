#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Pipeline.h"

namespace AGE
{
	class OpenGLPipeline : public Pipeline
	{
	public:

		OpenGLPipeline();
		virtual ~OpenGLPipeline();

		virtual void Init() override;
		virtual void StartBatch2D() override;
		virtual void NextBatch2D() override;
		virtual void Flush2D() override;

		virtual Renderer2DData& GetData() override;


		virtual void ResetStats() override;

		virtual Statistics& GetStats() override;

		void GenerateDefaultTextures();

	private:
		Renderer2DData m_Data;



	};
}