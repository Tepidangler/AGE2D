#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Pipeline.h"

namespace AGE
{
	class OpenGLPipeline : public Pipeline
	{
	public:

		OpenGLPipeline();
		~OpenGLPipeline() override;

		void Init() override;
		void StartBatch2D() override;
		void NextBatch2D() override;
		void Flush2D() override;

		Renderer2DData& GetData() override;
		void ResetStats() override;
		Statistics& GetStats() override;
		void GenerateDefaultTextures();

	private:
		Renderer2DData m_Data;
	};
}