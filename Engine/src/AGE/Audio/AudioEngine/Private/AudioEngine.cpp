#include "AGEpch.hpp"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Audio/Wwise/Public/WWiseEngine.h"
#include "Core/Public/Log.h"

namespace AGE
{
    Ref<AudioEngine> AudioEngine::Create(AudioEngineType Type)
    {

        switch (Type)
        {
        case 0:
        {
            return CreateRef<AGESound>();
        }

        case 1:
        {
#ifdef WITH_WWISE
            return CreateRef<Wwise>();
#else
            CoreLogger::Assert(false, "AGE was not built with WWise! You can enable WWise by setting the BUILD_WITH_WWISE option to ON in the CMake File");
            return nullptr;
#endif
        }

        case 2:
        {
#if WITH_FMOD
            return CreateRef<FmodEngine>();
#else
            CoreLogger::Assert(false, "AGE was not built with FMod! You can enable WWise by setting the BUILD_WITH_FMOD option to ON in the CMake File");
            return nullptr;
#endif
        }

        }

        return CreateRef<AGESound>();

    }

    template<typename T>
    T* AudioEngine::As()
    {
        CoreLogger::Assert(false, "As() Failed");
    }




}

