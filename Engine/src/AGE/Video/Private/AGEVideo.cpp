#include "AGEpch.hpp"
#include "Video/Public/AGEVideo.h"
#include "Video/Public/VideoSource.h"
#include "Render/Public/Renderer2D.h"
#include "Render/Public/RenderCommand.h"
#if 0

namespace AGE
{
    /**
 * @brief Initializes the AGE Video Player.
 * 
 * This function initializes the AGE Video Player by logging an information message stating that the player is starting.
 * It does not take any parameters and does not return anything.
 */
/** 
 * @brief Initializes the AGE Video Player.
 *
 * This function initializes the AGE Video Player by logging an informational message stating that the player is starting.
 * It does not take any parameters and does not return anything.
 */
void AGEVideo::Init()
    {
        CoreLogger::Info("Starting AGE Video Player!");
    }
    /**
 * @brief Shuts down the AGEVideo instance.
 *
 * This function is used to clean up any resources that were allocated during the lifetime of this object, such as memory or file handles. It prepares the object for destruction by setting all member variables to their default state and performing other necessary cleanup tasks.
 *
 * @return void
 */
/**
 * @brief Shuts down the AGEVideo instance.
 * 
 * This function is used to clean up any resources that were allocated during initialization of the AGEVideo object, such as memory or file handles. It prepares the object for deletion by setting it into a safe state and cleaning up any remaining references.
 *
 * @return void
 */
void AGEVideo::Shutdown()
    {
    }
    /**
 * @brief Loads a video source from the given file name and returns it.
 * 
 * This function takes in a string representing the filename of the video to be loaded, creates a new VideoSource object with this filename, and then returns it.
 * 
 * @param FileName The name of the file containing the video data.
 * @return A new VideoSource object initialized with the given filename.
 */
/**
 * @brief Loads a video source from the given file name.
 * 
 * This function takes in a string representing the filename of the video to be loaded, and returns a VideoSource object.
 * The returned VideoSource object is initialized with the provided filename.
 * 
 * @param FileName A const reference to a string containing the filename of the video source to load.
 * @return Returns a VideoSource object representing the loaded video source.
 */
VideoSource AGEVideo::LoadVideoSource(const std::string& FileName)
    {
        return VideoSource(FileName);
    }

    /**
 * @brief Plays a video with the given source and camera.
 *
 * This function plays a video using the provided source and camera. It first checks the current RendererAPI, 
 * then performs different actions based on its value. If it's headless (RendererAPI::GetAPI() returns 0), 
 * an assertion is triggered with a message indicating that Headless mode is currently unsupported. For other cases, 
 * no specific action is taken and the function simply exits without doing anything else.
 *
 * @param Source The video source to play.
 * @param Camera The camera used for rendering the video.
 */
/**
 * @brief Plays a video with the given source and camera.
 *
 * This function plays a video using the provided source and camera. It first checks the current RendererAPI, 
 * then performs different actions based on its value. If it's headless (RendererAPI::GetAPI() returns 0), 
 * an assertion is triggered with a message indicating that Headless mode is currently unsupported. For other cases, 
 * no specific action is taken and the function simply exits without doing anything else.
 *
 * @param Source The video source to play.
 * @param Camera The camera used for rendering the video.
 */
void AGEVideo::Play(const Ref<VideoSource>& Source, EditorCamera& Camera)
    {
        switch ((int)RendererAPI::GetAPI())
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
    /**
 * @brief Stops the video playback for a specific source.
 * 
 * This function is used to stop the video playback for a given VideoSource. It takes a reference to a constant VideoSource object as its parameter, indicating which source to stop.
 * 
 * @param Source A const reference to the VideoSource to be stopped.
 * @return void No return value.
 */
/**
 * @brief Stops the video playback for a specific source.
 * 
 * This function is used to stop the video playback for a given VideoSource. It takes a reference to a constant VideoSource object as its parameter, indicating which source should be stopped.
 * 
 * @param Source A const reference to the VideoSource that needs to be stopped.
 */
void AGEVideo::Stop(const Ref<VideoSource>& Source)
    {
    }
    /**
 * @brief Stops the operation of a list of VideoSources.
 * 
 * This function is used to stop the operation of a list of VideoSources. It takes in a constant reference to a vector of VideoSource references as its parameter.
 * The function does not return any value, it simply stops the operations of the provided sources.
 * 
 * @param Sources A constant reference to a vector of VideoSource references. This is the list of VideoSources that will have their operation stopped.
 * 
 * @return None
 */
/** 
 * @brief Stops the operation of a list of VideoSources.
 * 
 * This function is used to stop the operation of a list of VideoSources. It takes in a constant reference to a vector of Ref<VideoSource> objects, which represent the sources that need to be stopped.
 * 
 * @param Sources A constant reference to a vector of Ref<VideoSource> objects representing the sources to be stopped.
 * 
 * @return void This function does not return any value.
 */
void AGEVideo::Stop(const std::vector<Ref<VideoSource>>& Sources)
    {
    }

    /**
 * @brief Plays a video with the given source.
 * 
 * This function is used to play a video using the provided VideoSource reference. The source can be any type of video, such as file-based or stream-based sources.
 * 
 * @param Source A const reference to a VideoSource object representing the source from which the video will be played.
 * 
 * @return void No return value is expected for this function.
 */
/**
 * @brief Plays a video with the given source.
 * 
 * This function is used to play a video using the provided VideoSource reference. The source can be any type of video, such as file-based or stream-based sources.
 * 
 * @param Source A const reference to a VideoSource object representing the source from which the video will be played.
 */
void AGEVideo::PlayVideo(const Ref<VideoSource>& Source)
    {

    }

    /**
 * @brief Plays a video using OpenGL.
 *
 * This function plays a video using the OpenGL API. It takes as parameters a reference to a VideoSource object and an EditorCamera object. 
 * The function is currently not implemented, so it will always assert with the message "OpenGL Not Implemented!".
 *
 * @param Source A const reference to a VideoSource object representing the video source.
 * @param Camera An EditorCamera object representing the camera used for rendering the video.
 */
/**
 * @brief Plays a video using OpenGL.
 *
 * This function plays the provided video source using OpenGL. The camera is used to view the video.
 *
 * @param Source A reference to the VideoSource that will be played.
 * @param Camera An EditorCamera object which provides the view for viewing the video.
 * 
 * @return void
 */
void AGEVideo::PlayVideoOpenGL(const Ref<VideoSource>& Source, EditorCamera& Camera)
    {
        CoreLogger::Assert(false, "OpenGL Not Implemented!");
    }
    /**
 * @brief Plays a video using DirectX.
 *
 * This function is currently not implemented and will always throw an assertion error with the message "Direct X Not Implemented!". 
 * It's intended to be used for future development when we have fully implemented support for DirectX in our AGE framework.
 *
 * @param Source The video source to play. This parameter is currently not used and will always result in an assertion error if a non-null value is passed.
 * 
 * @return Nothing is returned as the function always throws an exception.
 */
/**
 * @brief Plays a video using DirectX.
 *
 * This function is currently not implemented and will always throw an assertion error with the message "Direct X Not Implemented!". 
 * It's intended to be used for future development when we have fully implemented support for DirectX in our AGEVideo class.
 *
 * @param Source The video source to play. This parameter is currently not used and will always result in an assertion error if a non-null value is passed.
 * 
 * @return Nothing as the function always throws an exception.
 */
void AGEVideo::PlayVideoDX(const Ref<VideoSource>& Source)
    {
        CoreLogger::Assert(false, "Direct X Not Implemented!");
    }
}
#endif