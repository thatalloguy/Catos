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
- Nodes
- - [x] Node
- - [ ] Attaching scripts to nodes.
---
- [x] Scripting.
- - [x] Loading Dll's / c++ scripts.
---
- [ ] Solid Serialization System.
- - [x] Saving most objects to yaml.
- - [x] Loading most objects from yaml.
- - [ ] Saving most objects to binary.
- - [ ] Loading most objects from binary.
- - [x] Support for (custom) STL objects (string, vector, hashmap)
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
- [ ] A tweening API.
---
- Utils
- - [ ] Commands.
- - [ ] Debug camera
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

### Serialization system.
Powered by the reflection system, Catos can write most cpp classes to both yaml and binary(WIP). 
It can also later read them back from yaml and binary. Yaml is meant to be used for the editor so that any errors/corrupted files can be easily read and fixed.
Binary is for exported games and meant for loading objects fast.

### Modern renderer.
Catos's renderer is meant to be customized for any situation. Instead of being a out of the box solution its more of a dynamic framework, with which the user can create their own render pipelines and passes.

### Error codes and their meanings:
- 200-299 are codes from the player
- 100-199 are codes from the core engine
- 300-399 are codes from the editor


## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=thatalloguy/catos&type=Date)](https://www.star-history.com/#thatalloguy/catos&Date)

### Dependencies
  - SDL3
  - rapidyml
  - imgui
  - spdlog
  - stb_image
