# Catos Engine

###### modern lightweight ECS cpp game engine

(Wiki)
https://github.com/thatalloguy/Catos/wiki
###### Different one comming sometime 🤷‍♂️
#
#
#### Planned Features / ToDo

- [x] Reflection system
- - [ ] ~~constructors~~
- - [x] Methods
- - [x] Properties
- [x] EC.
- - [x] Entity Creation.
- - [x] Central system for handling entities.
- - [x] Base component

- [ ] Python scripting (via pocketPy)
- - [x] Custom Component creation (in python)
- - [ ] get Info from cpp
- - [ ] change info that affects cpp (in python)
- [ ] Resource manager
- [ ] Dynamic Editor (via the reflection)
- [ ] Atomus implementation.
#
### EC system blueprint.
![image](https://github.com/thatalloguy/Catos/assets/51132972/f8a23b4e-8511-40bb-9648-cb252d856b83)
#

### Rendering with
https://github.com/thatalloguy/Atomus

##### Ideas for the engine

###### - Vulkan renderer (+ opengl):
After ive finished the asset manager i will continue dev on my personal vulkan renderer.
After that I am hoping to write a RHI so that i can support multiple graphic api's.
- UPDATE: I finished Atomus (vulkan renderer) and i dont think il create an RHI anytime soon 😅.

###### - C# as scripting lang
I really like C# and i would like to have it as my scripting lang.
However ive learned that implementing C# is a PITA, but im hoping that my new reflection system will make my life easier.
- UPDATE: I started on a pocketpy  implementation, will not be using C#.
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


