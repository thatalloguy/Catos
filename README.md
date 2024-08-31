# Catos Engine
[![Language](https://img.shields.io/badge/Native_language-C++-blue.svg)](https://isocpp.org/)
[![Language](https://img.shields.io/badge/Scripting_Language-Python-yellow.svg)](https://www.python.org/)



###### modern lightweight ECS cpp game engine

Check out the [Documentation](https://thatalloguy.github.io/catos/html/index.html)

️
#
#
#### ToDo

---
- [x] Reflection system
- - [ ] ~~constructors~~
- - [x] Methods
- - [x] Properties
- - [x] Automatic pkpy binding generation.
---
- [x] Custom STL (standard Library)
- - [x] String
- - [x] Vector
- - [x] HashMap
---
- [ ] Entity Model
- - [x] Worlds.
- - [ ] Entities.
- - [ ] Entity blueprints
---
- [ ] Scripting.
- - [x] Loading python scripting.
- - [ ] exposing cpp api to python.
---
- [ ] Render Abstraction Layer (for vulkan).
- - [ ] Ability to create new pipelines.
- - [ ] Ability to create new RenderPasses.
- - [ ] Ability to bind objects to pipelines / passes.
- - [ ] More general control over the entire render pipeline.
---
- [ ] Solid Serialization System.
- - [ ] Saving most objects to json or binary.
- - [ ] Loading most objects from json or binary.
- - [ ] Support for (custom) STL objects (string, vector, etc..)
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
---
- Good Input System
- - [ ] Ability to define actions.
- - [ ] Binding both controller input and keyboard / mouse input to actions.
---
- [ ] A tweening API.
---
- Utils
- - [ ] Commands.
--- 
- [ ] UI system.
- - [ ] Kinda like HTML.
---
- [ ] Editor 
- - [ ] ECS manipulation.
- - [ ] Project management.
- - [ ] World View tab
- - [ ] Asset browser.
#


## Dependencies
###  - doctest
###  - fastgltf
###  - glfw
###  - glm
###  - imgui
###  - pocketpy / gsoc24 (Experimental)
###  - spdlog
###  - stb_image
###  - tinystl ( REMOVED SOON )
###  - vk-bootstrap
###  - vkVulkanMemoryAllocator
