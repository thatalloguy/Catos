# Catos Engine
[![Language](https://img.shields.io/badge/Native_language-C++-blue.svg)](https://isocpp.org/)
[![Language](https://img.shields.io/badge/Scripting_Language-Python-yellow.svg)](https://www.python.org/)

![image](https://github.com/user-attachments/assets/bac6a8e8-cb13-4629-87ea-2bb2ab6255e8)

###### my personal cross-platform game engine

Check out the [Documentation](https://thatalloguy.github.io/catos/html/index.html)

### Compiles on:
- [x] Macos with Clang
- [x] Windows with visual studio and cl
- [ ] Ubuntu with Clang
️
#
#
#### ToDo

---
- [x] Reflection system
- - [x] Methods
- - [x] Properties
- - [x] Automatic pkpy binding generation.
- - [x] Constructors
---
- [x] Custom STL (standard Library)
- - [x] String
- - [x] Vector
- - [x] HashMap
---
- [x] Entity Model
- - [x] Worlds.
- - [x] Entities.
---
- [x] Scripting.
- - [x] Loading python scripting.
- - [x] exposing cpp api to python.
---
- [ ] Solid Serialization System.
- - [ ] Saving most objects to ~~json~~ yaml or binary.
- - [ ] Loading most objects from json or binary.
- - [ ] Support for (custom) STL objects (string, vector, hashmap)
---
- [ ] Renderer.
- - [ ] Migrate to SDL_GPU
---
- [ ] Renderer (High level):
- - [x] Shadows.
- - [x] GLTF loader.
- - [ ] PBR render pipeline.
- - [ ] (Skeleton) Animations.
---
- [ ] Resource manager
- - [ ] Finding files only by Name not a path.
- - [ ] Moving and copying files / folders to projects.
- - [ ] Baking Assets for faster loading (Models, textures, sounds).
- - [ ] Automatically passing along the asset to their corresponding manager.
---
- Sound Engine
- - [ ] Copy from Quack engine.
- - [ ] Better audio settings.
- - [ ] Better steam audio integration.
- - [ ] Effects such as fall-off.
- - [ ] More optimization
---
- Good Input System
- - [ ] Ability to define actions.
- - [ ] Binding both controller input and keyboard / mouse input to actions.
- - [ ] API func that only returns true when an action is pressed initially 
---
- Nodes
- - [ ] Camera3D
- - [ ] Mesh3D
- - [ ] RigidBody3D
- - [ ] Collider3D
- - [ ] Attaching scripts to nodes.
---
- [ ] A tweening API.
---
- Utils
- - [ ] Commands.
- - [ ] Debug camera
--- 
- [ ] UI system.
- - [ ] Kinda like HTML.
---
- [ ] Editor 
- - [ ] Node manipulation.
- - [ ] Project management.
- - [ ] World View tab
- - [ ] Asset browser.
- - [ ] Undo/redo
- - [ ] Copy/paste
#

## Current Features:

### reflection system
Catos uses/depents allot on its own custom reflection system. The system is written across: registry.h, typeinfo.h, property.h, method.h
The reflection system support any fundemental type and some special types, such as `catos::vector` and `std::unordered_map` .

### Automatic python binding.
Powered by its reflection system, Catos can automatically bind cpp class with properties and functions to python.

### Serialization system.
Powered by the reflection system, Catos can write most cpp classes to both yaml and binary(WIP). 
It can also later read them back from yaml and binary. Yaml is meant to be used for the editor so that any errors/corrupted files can be easily read and fixed.
Binary is for exported games and meant for loading objects fast.

### Modern renderer.
Catos's renderer is meant to be customizable at heart. The current renderer is written ontop of opengl and allows the user to easily create their own `Pipelines` and `RenderPasses` .
However the plan is to migrate from opengl to SDL_GPU, which is a relatively thin layer ontop of both DirectX12, Vulkan and Metal. This will recuire me to rewrite the entire render structure.
This is because SDL_GPU already has `RenderPasses` and `Pipelines` out of the box. The implementation will be focused on ease of customization with the help of nodes, which is meant to function as a framegraph.
Allowing the user to specify what shaders, pipelines, buffers, textures and passes should be used and how. With the introduction of SDL_GPU it also means that we can't use GLSL but only HLSL, I intend to write a small validation layer (if needed) and then use SDL_Shadercross to compile them.

### Window management.
The current windowing library is GLFW-3, however with the introduction of SDL_GPU I see no reason to stay with GLFW and therefor I will migrate to SDL 3.



## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=thatalloguy/catos&type=Date)](https://www.star-history.com/#thatalloguy/catos&Date)

## Dependencies
###  - doctest
###  - fastgltf [ V0.7.2 ]
###  - glfw
###  - rapidyml
###  - imgui
###  - [imgui dock](https://github.com/BentleyBlanks/imguiDock)
###  - pocketpy / gsoc24 (Experimental)
###  - spdlog
###  - stb_image

## Notes:
### in order to load python bindings you must do '#define CATOS_SCRIPTING_ENABLED'

