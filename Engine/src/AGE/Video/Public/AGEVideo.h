#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/FrameBuffer.h"
#include "Core/Public/DeltaTime.h"
#include "Camera/Public/EditorCamera.h"


namespace AGE
{
	typedef void IGRenderCallback(TimeStep DeltaTime);

	class VideoSource;

	class AGEVideo
	{
	public:
		static void Init();
		static void Shutdown();

		static VideoSource LoadVideoSource(const std::string& FileName);
		static void Play(const Ref<VideoSource>& Source, EditorCamera& Camera);
		static void Stop(const Ref<VideoSource>& Source);
		static void Stop(const std::vector<Ref<VideoSource>>& Sources);

	private:
		static void PlayVideo(const Ref<VideoSource>& Source);
		static void PlayVideoOpenGL(const Ref<VideoSource>& Source, EditorCamera& Camera);
		static void PlayVideoDX(const Ref<VideoSource>& Source);



	};



}
