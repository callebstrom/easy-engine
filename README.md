# EasyEngine
An experimental cross-platform game engine created for personal and educational purposes

## How to build
### Dependencies

Ensure dependency submarkmodule in `vendor` are built with the correct configuration

#### bullet3
1. Generate project files for configuration (`Release` or `Debug`) by going to `vendor/all/bullet3/build3` and running:
    ```
    ./premake4 --double --enable_multithreading --dynamic-runtime vs2010
    ```
2. Open `vendor\all\bullet3\build3\vs2010\0_Bullet3Solution.sln`
3. When prompted select to update project files to the latest toolchain version
4. Build the `x64` static library for these projects:
   - BulletCollision
   - BulletDynamics
   - LinearMath 

## TODO
### Rendering
- ~~Event driven render lifecycle~~
- ~~Basic 3D Mesh rendering~~
- 2D shape rendering
- UI framework
- ~~Basic materials~~
- ~~Basic textures~~
- Support normal maps
- Support displacement maps
- PBR
- SSAO
- Basic shadow mapping

### Physics
- Multi-threaded physics
- Add built-in `PhysicsComponent`
- Support collisions using `bulletphysics/bullet3`
- Add forces to `PhysicsComponent`

### Logging
- ~~Support consistent core and client logging~~
- Support logging to file

### ECS
- ~~Basic template based ECS~~
- ~~Support multiple component combinations per system~~
- Ensure memory locality of ECS components

### User Input
- ~~Emit events for keyboard and mouse input~~
- Support repeated keys

### Events
- ~~Basic event system~~
- ~~Support sync and async built-in events~~
- Support custom client events
- Support non-async custom client events

### Model loading
- ~~Basic support of common scene/model formats (meshes, textures and materials)~~
- Load normal maps
- Load displacement maps
- Load bones
- Load skeletal animations (depends on loading bones)

### Build
- Add premake configuration
- Support OSX builds

## Screenshots
### easy-engine-sandbox
![T pose Sylvanas in Sandbox](https://i.gyazo.com/099dffaae68593493f87ec96fb6ff77c.png "T pose Sylvanas in Sandbox")
