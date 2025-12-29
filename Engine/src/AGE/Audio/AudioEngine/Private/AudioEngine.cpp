#include "AGEpch.hpp"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Audio/Wwise/Public/WWiseEngine.h"

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
            return CreateRef<Wwise>();
        }

        case 2:
        {
            return CreateRef<FmodEngine>();
        }

        }

        return CreateRef<AGESound>();

    }

    template<typename T>
    T* AudioEngine::As()
    {
        AGE_CORE_ASSERT(false, "As() Failed");
    }




}

