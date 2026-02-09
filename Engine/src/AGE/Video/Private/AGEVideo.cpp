#include "AGEpch.hpp"
#include "Video/Public/AGEVideo.h"
#include "Video/Public/VideoSource.h"
#include "Render/Public/Renderer2D.h"
#include "Render/Public/RenderCommand.h"


namespace AGE
{
    void AGEVideo::Init()
    {
        CoreLogger::Info("Starting AGE Video Player!");
    }
    void AGEVideo::Shutdown()
    {
    }
    VideoSource AGEVideo::LoadVideoSource(const std::string& FileName)
    {
        return VideoSource(FileName);
    }

    void AGEVideo::Play(const Ref<VideoSource>& Source, EditorCamera& Camera)
    {
        switch (RendererAPI::GetAPI())
        {
        case 0:
        {
            CoreLogger::Assert(false, "Headless is currently unsupported!");
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        case 3:
        {
            break;
        }
        default:
        {
        }
        }
    }
    void AGEVideo::Stop(const Ref<VideoSource>& Source)
    {
    }
    void AGEVideo::Stop(const std::vector<Ref<VideoSource>>& Sources)
    {
    }

    void AGEVideo::PlayVideo(const Ref<VideoSource>& Source)
    {

    }

    void AGEVideo::PlayVideoOpenGL(const Ref<VideoSource>& Source, EditorCamera& Camera)
    {
        CoreLogger::Assert(false, "OpenGL Not Implemented!");
    }
    void AGEVideo::PlayVideoDX(const Ref<VideoSource>& Source)
    {
        CoreLogger::Assert(false, "Direct X Not Implemented!");
    }
}