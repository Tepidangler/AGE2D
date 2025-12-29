# AGE2D

Compact, native C++ 2D game engine — a focused 2D adaptation of the Alcoy Game Engine family. AGE2D is built for performance, clarity, and extensibility: it provides an OpenGL renderer, an EnTT-based entity/component system, native C++ scripting (no VM), and a small tool/editor stack.

## Quick facts
- Primary language: C++ (C++20)
- Renderer: OpenGL
- Scripting: Native C++ via AGE::ScriptableEntity
- ECS: EnTT-backed AGE::Entity wrapper and typed components
- Build system: CMake (targets: Engine, Game, Editor)
- Platform: Windows — CMake files and vendor link paths are currently Windows-focused

## Table of Contents
- [Project summary](#project-summary)
- [Notable systems & architecture](#notable-systems--architecture)
- [Windows build (Visual Studio + CMake)](#windows-build-visual-studio--cmake)
- [Native C++ scripting (real API & example)](#native-c-scripting-real-api--example)
- [Technical Highlights](#technical-highlights)
- [Limitations](#limitations)
- [Contributing, license & contact](#contributing-license--contact)
- [Acknowledgements](#acknowledgements)

<a name="project-summary"></a>

## Project summary

AGE2D is a compact, pragmatic engine intended for 2D games and rapid iteration with native C++. It prefers explicit, high‑performance code rather than embedding a scripting VM. The design favors modular subsystems (Renderer2D, Scene, Audio, UI, Physics) and a small editor built on ImGui.

<a name="notable-systems--architecture"></a>

## Notable systems & where to look

- ECS & scene: Engine/src/AGE/Scene/Public
  - Entity (Entity.h) — thin wrapper over EnTT
  - Components (Components.h) — TransformComponent, SpriteRendererComponent, NativeScriptComponent, CameraComponent, physics/collider components
  - Scene (Scene.h/.cpp) — creation, runtime/update loop, serialization
- Scripting:
  - ScriptableEntity (Scene/Public/ScriptableEntity.h) — the native script base class you derive from
  - Native script glue: NativeScriptComponent (Components.h) — binds C++ script types to entities
- Rendering:
  - Renderer2D (Render/Public/Renderer2D.h/.cpp) — 2D draw calls: quads, sprites, circles, text
- Build + vendor libraries: CMakeLists.txt (top level) and Engine/CMakeLists.txt (vendor add_subdirectory calls)

<a name="windows-build-visual-studio--cmake"></a>
## Windows build (Visual Studio + CMake)

The project uses C++20 and is configured to build with Visual Studio on Windows. Steps:

1. Clone
   git clone https://github.com/Tepidangler/AGE2D.git
   cd AGE2D

2. Create and configure a build directory (Visual Studio 2022 example)
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

   Notes:
   - The Engine CMake config references many vendor libs under Engine/libs/vendor. The default setup includes those with add_subdirectory so no extra steps are usually required.
   - If you move vendors or use system libraries, set the Engine CMake cache variables (INC_GLFW, INC_GLAD, INC_GLM, etc.) or use vcpkg and point CMAKE_TOOLCHAIN_FILE appropriately.

3. Build
   cmake --build . --config Release

4. Artifacts
   - The build produces `Engine` (static lib) and the `Editor` and `Game` targets where applicable. There are no packaged sample runtime executables by default — the Game directory is the place to add your playable demo or test runner.

<a name="native-c-scripting-real-api--example"></a>

## Native C++ scripting — real API, concise

AGE2D uses a native C++ script base type. The relevant classes and patterns are taken directly from the repository:

- Base script type:
  - AGE::ScriptableEntity — override lifecycle callbacks:
    - void OnCreate();
    - void OnBeginPlay();
    - void OnUpdate(AGE::TimeStep DeltaTime);
    - void OnEvent(AGE::Event& E);
    - void OnDestroy();

- Engine entity API:
  - AGE::Entity provides AddComponent<T>(), GetComponent<T>(), HasComponent<T>() and CreateEntity() is on AGE::Scene.

- NativeScriptComponent:
  - struct AGE::NativeScriptComponent has:
    - ScriptableEntity* Instance;
    - ScriptableEntity* (*InstantiateScript)();
    - void (*DestroyScript)(NativeScriptComponent*);
    - template<typename T> void Bind(); // sets InstantiateScript and DestroyScript

<a name="how-to-write-and-bind-a-native-script"></a>

## How to write and bind a native script

- File: Game/src/Scripts/ExampleScript.hpp (example; add it to your Game project)

```cpp
#pragma once

#include "Scene/Public/ScriptableEntity.h"
#include "Scene/Public/Components.h"   // TransformComponent, NativeScriptComponent
#include "Core/Public/DeltaTime.h"     // TimeStep

namespace GameFramework
{
    class ExampleScript : public AGE::ScriptableEntity
    {
    public:
        ExampleScript() = default;
        virtual ~ExampleScript() = default;

        void OnCreate() override
        {
            // Called when the script instance is created
        }

        void OnBeginPlay() override
        {
            // Called when the scene/actor begins play
        }

        void OnUpdate(AGE::TimeStep DeltaTime) override
        {
            // Move right at 100 units/sec
            auto& transform = GetComponent<AGE::TransformComponent>();
            transform.Translation.x += 100.0f * DeltaTime;
        }

        void OnDestroy() override
        {
            // Cleanup
        }
    };
}
```

Bind the script to an entity (example usage inside a scene-setup function):

```cpp
// `scene` is a Ref<AGE::Scene> obtained from your project/app
AGE::Entity player = scene->CreateEntity("Player");

// Attach NativeScriptComponent and bind ExampleScript
auto& nsc = player.AddComponent<AGE::NativeScriptComponent>();
nsc.Bind<GameFramework::ExampleScript>();

// The runtime will call nsc.InstantiateScript() -> sets Instance, and lifecycle methods OnCreate/OnBeginPlay/OnUpdate will be called by the engine.
```

<a name="technical-highlights"></a>

## Technical highlights

- Native scripting architecture — (native C++: performance, tooling, compile-time safety vs. scripting VM hot‑reload).
- ECS integration (EnTT)
- Rendering pipeline
- Tools & Editor

<a name="limitations"></a>

## Limitations

- Platform: Windows is currently the primary supported target. Porting requires adjusting link paths and vendor settings in CMake.
- Hot reload: native scripting requires recompilation. I'm considering adding a dynamic-library hot-reload pattern (compile scripts into separate DLLs) to improve iteration speed.
- C++ standard: C++20 (engine and build are configured for modern toolchains).

<a name="contributing-license--contact"></a>

## Contributing

- Open an issue before proposing large changes.
- Keep PRs focused, small, and include a clear description & testing steps.
- Follow the CMake conventions established in the repo; update README and add small examples when adding new public APIs.

## License & contact

- See LICENSE in repository root for license details.
- Repo: https://github.com/Tepidangler/AGE2D
- Maintainer: @Tepidangler

<a name="acknowledgements"></a>

## Acknowledgements

Thanks to the third-party libraries included in the repo (ImGui, EnTT, Box2D/box2c, msdf-atlas-gen, stb, GLAD, GLFW, RTTR, YAML-CPP, etc.). Consult the individual libraries for their licenses.
