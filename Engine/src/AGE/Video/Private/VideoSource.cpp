#include "AGEpch.hpp"
#include "Video/Public/VideoSource.h"
#if 0
namespace AGE
{

  

    /**
 * @brief Constructs a VideoSource object with the given file path.
 * 
 * This function constructs a VideoSource object and sets its file path to the provided string.
 * The file path is used by other functions in this class to access the video data.
 * 
 * @param FilePath A const reference to a string representing the file path of the video source.
 */
VideoSource::VideoSource(const std::string& FilePath)
        :m_FilePath(FilePath)
    {

    }

    /**
 * @brief Seeks a specific frame in the video source.
 * 
 * This function is used to navigate to a particular frame within the video source. The exact behavior of this function depends on the implementation and can vary between different types of VideoSource objects.
 * 
 * @return void
 */
void VideoSource::SeekFrame()
    {
    }

    /**
 * @brief Read a single frame from the video source.
 *
 * This function reads and processes a single frame from the video source. The exact behavior depends on the specific implementation of the VideoSource class. 
 *
 * @return void
 */
void VideoSource::ReadFrame()
    {

    }

    /**
 * @brief This function is used to create a texture from the video source.
 * 
 * The function does not take any parameters and returns void. It's assumed that this function will be called when a new frame of video data is available, which would trigger the creation of a new texture.
 * 
 * @return Unknown
 */
void VideoSource::MakeTexture()
    {
       

    }

    /**
 * @brief Increments the frame count of the video source by one.
 * 
 * This function increments the internal counter that keeps track of the number of frames processed by the VideoSource object. It does not take any parameters and returns void.
 */
void VideoSource::IncrementFrameCount()
    {

    }

    /**
 * @brief Destructor for the VideoSource class.
 *
 * This function is responsible for releasing any resources that were acquired by the VideoSource object, such as memory or file handles. It does not return anything and has no parameters.
 */
VideoSource::~VideoSource()
    {

    }
}
#endif