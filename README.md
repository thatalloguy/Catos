# Catos Engine

###### modern lightweight ECS cpp game engine

(Wiki) https://thatalloguy.github.io/catos/html/index.html

️
#
#
#### Planned Features / ToDo

---
- [x] Reflection system
- - [ ] ~~constructors~~
- - [x] Methods
- - [x] Properties
---
- [ ] C# scripting engine
- - [x] Creating instances of classes.
- - [x] Calling functions of instances.
- - [x] Getting and Setting fields.
- - [x] Calling Cpp from C#
- - [ ] Refactor.
- - [ ] Script Object. 
---
- [ ] Editor 
- - [ ] ECS manipulation.
- - [ ] Project management.
- - [ ] World View tab
- - [ ] Asset browser.
---

- [ ] ECS
- - [x] Entities.
- - [x] Components
- - [x] Queries.
- - [ ] Scripting (C#) compatibility.
- - [ ] Parent & children.
---
- [ ] Resource manager
---
- [x] Atomus implementation.
#


### Rendering with
https://github.com/thatalloguy/Atomus

#### Ideas for the engine

###### - Vulkan renderer (+ opengl):
After ive finished the asset manager i will continue dev on my personal vulkan renderer.
After that I am hoping to write a RHI so that i can support multiple graphic api's.
- UPDATE: I finished Atomus (vulkan renderer) and i dont think il create an RHI anytime soon 😅.

###### - C# as scripting lang
I really like C# and i would like to have it as my scripting lang.
However ive learned that implementing C# is a PITA, but im hoping that my new reflection system will make my life easier.


###### - Physics engine
In the past ive used PhysX, bullet and reactphysics3d. But i dislike all 3.
I have heard lots of good stuff about Joltphysics and i might give it a try for this engine.

###### - Audio Engine
Ive never really done much with audio, but ive seen the steam audio api and im hoping to try it!

###### - Editor GUI
For the editor il be using IMGUI since ive lots of experience with it.
However this time around i would like to modify the feel of imgui.

###### - Game GUI
At this point what i will use is far away, but i would either want something to functions like remUI.
But i could also end up writing my own (IF i were to write my own GUI lib the editor will use that instead of imgui).


